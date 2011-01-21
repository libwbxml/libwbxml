/*
 * libwbxml, the WBXML Library.
 * Copyright (C) 2002-2008 Aymerick Jehanne <aymerick@jehanne.org>
 * Copyright (C) 2009-2011 Michael Bell <michael.bell@opensync.org>
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 * 
 * LGPL v2.1: http://www.gnu.org/copyleft/lesser.txt
 * 
 * Contact: aymerick@jehanne.org
 * Home: http://libwbxml.aymerick.com
 */
 
/**
 * @file wbxml_parser.c
 * @ingroup wbxml_parser
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/03/12
 *
 * @brief WBXML Parser - Parse a WBXML document and call user defined Callbacks
 *
 * @todo Handle correctly charset
 *
 * @note WBXML Versions Differences:
 *            - WBXML 1.2: - No differences with WBXML 1.3, except a clarification in BNF for 'LITERAL' handling
 *            - WBXML 1.1: - No Switch Page mecanism
 *                         - An Attribute value can't be "opaque"
 *            - WBXML 1.0: - No 'charset' handling
 *                         - No 'opaque' support
 *                         - A strange 'body' rule description in BNF (just forget it).
 */

#include "wbxml_parser.h"
#include "wbxml_log.h"
#include "wbxml_internals.h"
#include "wbxml_base64.h"
#include "wbxml_charset.h"
#include <assert.h>


/* Memory management related defines */
#define WBXML_PARSER_MALLOC_BLOCK 5000
#define WBXML_PARSER_STRING_TABLE_MALLOC_BLOCK 200
#define WBXML_PARSER_ATTR_VALUE_MALLOC_BLOCK 100

/** Set it to '1' for Best Effort mode */
#define WBXML_PARSER_BEST_EFFORT 1

/** For unknown Tag Name or Attribute Name (in Best Effort Mode) */
#define WBXML_PARSER_UNKNOWN_STRING ((WB_UTINY *)"unknown")

/**
 * @brief The WBXML Application Token types
 */
typedef enum WBXMLTokenType_e {
    WBXML_TAG_TOKEN,        /**< Tag token */
    WBXML_ATTR_TOKEN        /**< Attribute token */
} WBXMLTokenType;


/**
 * @brief The WBXML Parser
 * @warning For now 'current_tag' field is only used for WV Content Parsing. And for this use, it works.
 *          But this field is reset after End Tag, and as there is no Linked List mecanism, this is bad for
 *          cascading elements: we don't fill this field with parent Tag when parsing End Tag.
 */
struct WBXMLParser_s {
    void                 *user_data;       /**< User Data */
    WBXMLContentHandler  *content_hdl;     /**< Content Handlers Callbacks */
    WBXMLBuffer          *wbxml;           /**< The wbxml we are parsing */    
    WBXMLBuffer          *strstbl;         /**< String Table specified in WBXML document */
    const WBXMLLangEntry *langTable;       /**< Current document Language Table */
    const WBXMLLangEntry *mainTable;       /**< Main WBXML Languages Table */
    const WBXMLTagEntry  *current_tag;     /**< Current Tag */
  
    WBXMLLanguage         lang_forced;     /**< Language forced by User */
    WB_ULONG              public_id;       /**< Public ID specified in WBXML document */    
    WB_LONG               public_id_index; /**< If Public ID is a String Table reference,
                                                this is the index defined in the strtbl */
    WBXMLCharsetMIBEnum   charset;         /**< Charset of WBXML document */
    WBXMLCharsetMIBEnum   meta_charset;    /**< Meta-info provided by user: only used if
                                                Charset is not specified in WBXML document */
    WB_ULONG              pos;             /**< Position of parsing curser in wbxml */    
    WBXMLVersion          version;         /**< WBXML Version field specified in WBXML document */
    WB_UTINY              tagCodePage;     /**< Current Tag Code Page */
    WB_UTINY              attrCodePage;    /**< Current Attribute Code Page */
};



/***************************************************
 *    Private Functions prototypes
 */

/* WBXML Parser functions */
static void wbxml_parser_reinit(WBXMLParser *parser);

/* Check functions */
static WB_BOOL is_token(WBXMLParser *parser, WB_UTINY token);
static WB_BOOL is_literal(WBXMLParser *parser);
static WB_BOOL is_attr_value(WBXMLParser *parser);
static WB_BOOL is_string(WBXMLParser *parser);
static WB_BOOL is_extension(WBXMLParser *parser);
static WB_BOOL check_public_id(WBXMLParser *parser);

/* Parse functions */
static WBXMLError parse_version(WBXMLParser *parser);
static WBXMLError parse_publicid(WBXMLParser *parser);
static WBXMLError parse_charset(WBXMLParser *parser);
static WBXMLError parse_strtbl(WBXMLParser *parser);
static WBXMLError parse_body(WBXMLParser *parser);

static WBXMLError parse_pi(WBXMLParser *parser);
static WBXMLError parse_element(WBXMLParser *parser);
static void free_attrs_table(WBXMLAttribute **attrs);

static WBXMLError parse_switch_page(WBXMLParser *parser, WBXMLTokenType  code_space);
static WBXMLError parse_stag(WBXMLParser *parser, WB_UTINY *tag, WBXMLTag **element);
static WBXMLError parse_tag(WBXMLParser *parser, WB_UTINY *tag, WBXMLTag **element);
static WBXMLError parse_attribute(WBXMLParser *parser, WBXMLAttribute **attr);
static WBXMLError parse_content(WBXMLParser *parser, WBXMLBuffer **result);

static WBXMLError parse_string(WBXMLParser *parser, WBXMLBuffer **result);
static WBXMLError parse_extension(WBXMLParser *parser, WBXMLTokenType code_space, WBXMLBuffer **result);
static WBXMLError parse_entity(WBXMLParser *parser, WBXMLBuffer **result);
static WBXMLError parse_opaque(WBXMLParser *parser, WBXMLBuffer **result);

static WBXMLError parse_literal(WBXMLParser *parser, WB_UTINY *tag, WBXMLBuffer **result);

static WBXMLError parse_attr_start(WBXMLParser *parser, WBXMLAttributeName **name, const WB_UTINY **value);
static WBXMLError parse_attr_value(WBXMLParser *parser, WBXMLBuffer **result);

static WBXMLError parse_termstr(WBXMLParser *parser, WBXMLBuffer **result);
static WBXMLError parse_inline(WBXMLParser *parser, WBXMLBuffer **result);
static WBXMLError parse_tableref(WBXMLParser *parser, WBXMLBuffer **result);
static WBXMLError parse_entcode(WBXMLParser *parser, WB_ULONG *result);

static WBXMLError get_strtbl_reference(WBXMLParser *parser, WB_ULONG index, WBXMLBuffer **result);

/* Basic Types Parse functions */
static WBXMLError parse_uint8(WBXMLParser *parser, WB_UTINY *result);
static WBXMLError parse_mb_uint32(WBXMLParser *parser, WB_ULONG *result);

/* Language Specific Decoding Functions */
static WBXMLError decode_base64_value(WBXMLBuffer **data);

#if defined( WBXML_SUPPORT_SI ) || defined( WBXML_SUPPORT_EMN )
static WBXMLError decode_datetime(WBXMLBuffer *buff);
#endif /* WBXML_SUPPORT_SI || WBXML_SUPPORT_EMN */

static WBXMLError decode_opaque_content(WBXMLParser *parser, WBXMLBuffer **data);
static WBXMLError decode_opaque_attr_value(WBXMLParser *parser, WBXMLBuffer **data);

#if defined( WBXML_SUPPORT_WV )
static WBXMLError decode_wv_content(WBXMLParser *parser, WBXMLBuffer **data);
static WBXMLError decode_wv_integer(WBXMLBuffer **data);
static WBXMLError decode_wv_datetime(WBXMLBuffer **data);
#endif /* WBXML_SUPPORT_WV */

/* Macro for error handling */
#define CHECK_ERROR if (ret != WBXML_OK) return ret;


/***************************************************
 *    Public Functions
 */

WBXML_DECLARE(WBXMLParser *) wbxml_parser_create(void)
{
    WBXMLParser *parser = NULL;

    parser = (WBXMLParser *) wbxml_malloc(sizeof(WBXMLParser));
    if (parser == NULL) {
        return NULL;
    }
    
    parser->wbxml = NULL;
    parser->user_data = NULL;
    parser->content_hdl = NULL;
    parser->strstbl = NULL;
    parser->langTable = NULL;

    /* Default Main WBXML Languages Table */
    parser->mainTable = wbxml_tables_get_main();

    parser->current_tag = NULL;

    parser->lang_forced = WBXML_LANG_UNKNOWN;
    parser->public_id = WBXML_PUBLIC_ID_UNKNOWN;    
    parser->public_id_index = -1;
    parser->charset = WBXML_CHARSET_UNKNOWN;
    parser->meta_charset = WBXML_CHARSET_UNKNOWN;
    parser->version = WBXML_VERSION_UNKNOWN;    
    
    parser->pos = 0;
    parser->tagCodePage = 0;
    parser->attrCodePage = 0;

    return parser;
}


WBXML_DECLARE(void) wbxml_parser_destroy(WBXMLParser *parser)
{
    if (parser == NULL)
        return;
    
    wbxml_buffer_destroy(parser->wbxml);
    wbxml_buffer_destroy(parser->strstbl);

    wbxml_free(parser);
}


WBXML_DECLARE(WBXMLError) wbxml_parser_parse(WBXMLParser *parser, WB_UTINY *wbxml, WB_ULONG wbxml_len)
{
    WBXMLError ret = WBXML_OK;

    if (parser == NULL)
        return WBXML_ERROR_NULL_PARSER;

    if ((wbxml == NULL) || (wbxml_len <= 0))
        return WBXML_ERROR_EMPTY_WBXML;

    /* Reinitialize WBXML Parser */
    wbxml_parser_reinit(parser);

    parser->wbxml = wbxml_buffer_create(wbxml, wbxml_len, WBXML_PARSER_MALLOC_BLOCK);
    if (parser->wbxml == NULL)
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;

    /* WBXML Version */
    ret = parse_version(parser);
    CHECK_ERROR

    if ((WB_UTINY)parser->version > WBXML_VERSION_13) {
        WBXML_WARNING((WBXML_PARSER, "This library only supports WBXML %s.", WBXML_VERSION_TEXT_13));
    }

    /* WBXML Public ID */
    ret = parse_publicid(parser);
    CHECK_ERROR

    /* Ignore Document Public ID if user has forced use of another Public ID */
    if (parser->lang_forced != WBXML_LANG_UNKNOWN)
        parser->public_id = wbxml_tables_get_wbxml_publicid(wbxml_tables_get_main(), parser->lang_forced);

    /* No charset in WBXML 1.0 */
    if (parser->version != WBXML_VERSION_10) {
        ret = parse_charset(parser);
        CHECK_ERROR
    }

    /* Check charset */
    if (parser->charset == WBXML_CHARSET_UNKNOWN) {
        if (parser->meta_charset != WBXML_CHARSET_UNKNOWN) {
            /* Use meta-information provided by user */
            parser->charset = parser->meta_charset;
      
            WBXML_DEBUG((WBXML_PARSER,
                        "Using provided meta charset: %ld",
                        parser->meta_charset));
        }
        else {
            /* Default Charset Encoding: UTF-8 */
            parser->charset = WBXML_PARSER_DEFAULT_CHARSET;
      
            WBXML_WARNING((WBXML_PARSER,
                           "No charset information found, using default : %x",
                           WBXML_PARSER_DEFAULT_CHARSET));
        }
    }

    /* WBXML String Table */
    ret = parse_strtbl(parser);
    CHECK_ERROR

    /* Now that we have parsed String Table, we can check Public ID */
    if (!check_public_id(parser)) {
        WBXML_ERROR((WBXML_PARSER, "PublicID not found"));
        return WBXML_ERROR_UNKNOWN_PUBLIC_ID;
    }

    /* Call to WBXMLStartDocumentHandler */
    if ((parser->content_hdl != NULL) && (parser->content_hdl->start_document_clb != NULL))
        parser->content_hdl->start_document_clb(parser->user_data, parser->charset, parser->langTable);

    /* WBXML Body */
    ret = parse_body(parser);
    CHECK_ERROR

    /* Call to WBXMLEndDocumentHandler */
    if ((parser->content_hdl != NULL) && (parser->content_hdl->end_document_clb != NULL))
        parser->content_hdl->end_document_clb(parser->user_data);

    return ret;
}


WBXML_DECLARE(void) wbxml_parser_set_user_data(WBXMLParser *parser, void *user_data)
{
    if (parser != NULL)
        parser->user_data = user_data;
}


WBXML_DECLARE(void) wbxml_parser_set_content_handler(WBXMLParser *parser, WBXMLContentHandler *content_handler)
{
    if (parser != NULL)
        parser->content_hdl = content_handler;
}


WBXML_DECLARE(void) wbxml_parser_set_main_table(WBXMLParser *parser, const WBXMLLangEntry *main_table)
{
    if (parser != NULL)
        parser->mainTable = main_table;
}


WBXML_DECLARE(WB_BOOL) wbxml_parser_set_language(WBXMLParser *parser, WBXMLLanguage lang)
{
    if (parser != NULL) {
        parser->lang_forced = lang;
        return TRUE;
    }

    return FALSE;
}


WBXML_DECLARE(WB_BOOL) wbxml_parser_set_meta_charset(WBXMLParser *parser,
                                                     WBXMLCharsetMIBEnum charset)
{
    if ( parser != NULL ) {
        parser->meta_charset = charset;
        return TRUE;
    }
  
    return FALSE;
}


WBXML_DECLARE(WB_ULONG) wbxml_parser_get_wbxml_public_id(WBXMLParser *parser)
{
    if ((parser != NULL) && (parser->langTable != NULL) && (parser->langTable->publicID != NULL))
        return parser->langTable->publicID->wbxmlPublicID;
    else
        return WBXML_PUBLIC_ID_UNKNOWN;
}


WBXML_DECLARE(const WB_UTINY *) wbxml_parser_get_xml_public_id(WBXMLParser *parser)
{
    if ((parser != NULL) && (parser->langTable != NULL) && (parser->langTable->publicID != NULL))
        return (const WB_UTINY *) parser->langTable->publicID->xmlPublicID;
    else
        return NULL;
}


WBXML_DECLARE(WBXMLVersion) wbxml_parser_get_wbxml_version(WBXMLParser *parser)
{
    if (parser != NULL)
        return parser->version;
    else
        return WBXML_VERSION_UNKNOWN;
}


WBXML_DECLARE(WB_LONG) wbxml_parser_get_current_byte_index(WBXMLParser *parser)
{
    if (parser != NULL)
        return parser->pos - 1;
    else
        return 0;
}


/***************************************************
 *    Private Functions
 */

/**************************
 * WBXML Parser functions
 */

/**
 * @brief Reinitialize a WBXML Parser
 * @param parser The WBXMLParser to reinitialize
 * @note Only reinitialize internal fields of parser, and so keep User Data
 *         and Content Handler pointers.
 */
static void wbxml_parser_reinit(WBXMLParser *parser)
{
    if (parser == NULL)
        return;

    wbxml_buffer_destroy(parser->wbxml);
    parser->wbxml           = NULL;
  
    wbxml_buffer_destroy(parser->strstbl);
    parser->strstbl         = NULL;
  
    parser->langTable       = NULL;
    parser->current_tag     = NULL;
  
    parser->public_id       = WBXML_PUBLIC_ID_UNKNOWN;    
    parser->public_id_index = -1;
    parser->charset         = WBXML_CHARSET_UNKNOWN;
    parser->version         = WBXML_VERSION_UNKNOWN;    
  
    parser->pos             = 0;
    parser->tagCodePage     = 0;
    parser->attrCodePage    = 0;    
}


/******************
 * Check functions
 */

/**
 * @brief Check if current byte a specified WBXML token
 * @param parser The WBXML Parser
 * @param token The WBXML token
 * @return TRUE is current byte is the specified token, FALSE otherwise
 */
static WB_BOOL is_token(WBXMLParser *parser, WB_UTINY token)
{
    WB_UTINY result;

    if (!wbxml_buffer_get_char(parser->wbxml, parser->pos, &result))
        return FALSE;

    return (WB_BOOL) (result == token);
}


/**
 * @brief Check if current byte is a WBXML literalTag token
 * @param parser The WBXML Parser
 * @return TRUE is current byte is a literalTag token, FALSE otherwise
 */
static WB_BOOL is_literal(WBXMLParser *parser)
{
    WB_UTINY result;

    if (!wbxml_buffer_get_char(parser->wbxml, parser->pos, &result))
        return FALSE;

    return (WB_BOOL) ((result == WBXML_LITERAL) || (result == WBXML_LITERAL_A) || (result == WBXML_LITERAL_C) || (result == WBXML_LITERAL_AC));
}


/**
 * @brief Check if next token to parse is an Attribute Value
 * @param parser The WBXML Parser
 * @return TRUE if next token to parse is an Attribute Value, FALSE otherwise
 * @note attrValue    = ([switchPage] ATTRVALUE | string | extension | entity | opaque)
 */
static WB_BOOL is_attr_value(WBXMLParser *parser)
{
    WB_UTINY cur_byte, next_byte;

    /* Get current byte */
    if (!wbxml_buffer_get_char(parser->wbxml, parser->pos, &cur_byte))
        return FALSE;

    /* If current byte is a switch page, check that following token is an Attribute Value token */
    if (is_token(parser, WBXML_SWITCH_PAGE)) {
        if (!wbxml_buffer_get_char(parser->wbxml, parser->pos + 2, &next_byte))
            return FALSE;

        /* Attribute Value is greater than or equal to 128 */
        if ((next_byte & 0x80) == 0x80)
            return TRUE;
    }

    /* Else, check current byte is an Attribute Value, a string, an extension, an entity or an opaque */
    if (((cur_byte & 0x80) == 0x80) ||
        (is_string(parser)) ||
        (is_extension(parser)) ||
        (is_token(parser, WBXML_ENTITY)) ||
        (is_token(parser, WBXML_OPAQUE)))
        return TRUE;

    return FALSE;
}


/**
 * @brief Check if current byte is a string
 * @param parser The WBXML Parser
 * @return TRUE if current byte is a string, FALSE otherwise
 */
static WB_BOOL is_string(WBXMLParser *parser)
{
    return (WB_BOOL) (is_token(parser, WBXML_STR_I) || is_token(parser, WBXML_STR_T));
}


/**
 * @brief Check if current byte is an extension
 * @param parser The WBXML Parser
 * @return TRUE if current byte is an extension, FALSE otherwise
 */
static WB_BOOL is_extension(WBXMLParser *parser)
{
    WB_UTINY cur_byte;

    /* If current byte is a switch page, check the following token */
    if (is_token(parser, WBXML_SWITCH_PAGE)) {
        if (!wbxml_buffer_get_char(parser->wbxml, parser->pos + 2, &cur_byte))
            return FALSE;
    }
    else {
        if (!wbxml_buffer_get_char(parser->wbxml, parser->pos, &cur_byte))
            return FALSE;
    }

    return (WB_BOOL) ((cur_byte == WBXML_EXT_I_0) || (cur_byte == WBXML_EXT_I_1) || (cur_byte == WBXML_EXT_I_2) ||
            (cur_byte == WBXML_EXT_T_0) || (cur_byte == WBXML_EXT_T_1) || (cur_byte == WBXML_EXT_T_2) ||
            (cur_byte == WBXML_EXT_0)   || (cur_byte == WBXML_EXT_1)   || (cur_byte == WBXML_EXT_2));
}


/**
 * @brief Check the Public ID
 * @param parser The WBXML Parser
 * @return TRUE if Public ID is found, FALSE otherwise
 */
static WB_BOOL check_public_id(WBXMLParser *parser)
{
    WBXMLBuffer *public_id = NULL;
    WB_LONG          index = 0;
    WBXMLError         ret;

    WBXML_DEBUG((WBXML_PARSER, "\t  Checking PublicID"));

    /* First check if we can figure out the Public ID */
    if ((parser->lang_forced == WBXML_LANG_UNKNOWN) && 
        (parser->public_id == WBXML_PUBLIC_ID_UNKNOWN) && 
        (parser->public_id_index == -1))
    {
        return FALSE;
    }


    /********************************************************
     * Case 1: Language is forced by user
     */

    if (parser->lang_forced != WBXML_LANG_UNKNOWN) {
        /* Search Language Entry */
        while (parser->mainTable[index].langID != WBXML_LANG_UNKNOWN) {
            if (parser->mainTable[index].langID == parser->lang_forced) {
                parser->langTable = &(parser->mainTable[index]);

                WBXML_DEBUG((WBXML_PARSER, "\t  Language Forced - PublicID : '%s'", parser->mainTable[index].publicID->xmlPublicID));

                return TRUE;
            }

            index++;
        }
    }


    /********************************************************
     * Case 2: Public ID is a normal token 
     *         (found in WBXML Document, or forced by user)
     */

    if (parser->public_id != WBXML_PUBLIC_ID_UNKNOWN) {
        WBXML_DEBUG((WBXML_PARSER, "\t  PublicID token: 0x%X", parser->public_id));

        /* Search Public ID Table */
        while (parser->mainTable[index].publicID != NULL) {
            if (parser->mainTable[index].publicID->wbxmlPublicID == parser->public_id) {
                parser->langTable = &(parser->mainTable[index]);

                WBXML_DEBUG((WBXML_PARSER, "\t  PublicID : '%s'", parser->mainTable[index].publicID->xmlPublicID));

                return TRUE;
            }

            index++;
        }
    }


    /********************************************************
     * Case 3: Public ID referenced in String Table 
     */
    if (parser->public_id_index != -1) {
        WBXML_DEBUG((WBXML_PARSER, "\t  PublicID is in String Table (index: 0x%X)", parser->public_id_index));

        ret = get_strtbl_reference(parser, (WB_ULONG) parser->public_id_index, &public_id);
        if (ret != WBXML_OK) {
            WBXML_ERROR((WBXML_PARSER, "Bad publicID reference in string table. %s", wbxml_errors_string(ret)));
            return FALSE;
        }

        WBXML_DEBUG((WBXML_PARSER, "\t  PublicID : '%s'", wbxml_buffer_get_cstr(public_id)));

        /* Search Public ID Table */
        while (parser->mainTable[index].publicID != NULL)
        {
            if ((parser->mainTable[index].publicID->xmlPublicID != NULL) && 
                (WBXML_STRCASECMP(parser->mainTable[index].publicID->xmlPublicID, wbxml_buffer_get_cstr(public_id)) == 0))
            {
                parser->langTable = &(parser->mainTable[index]);
                /* parser->public_id = parser->mainTable[index].publicID->wbxmlPublicID; */

                wbxml_buffer_destroy(public_id);
                return TRUE;
            }

            index++;
        }

        /* Clean up */
        wbxml_buffer_destroy(public_id);
    }

    /* Public ID not found in Tables */
    return FALSE;
}



/***************************
 *    WBXML Parse functions
 */

/**
 * @brief Parse WBXML version
 * @param parser The WBXML Parser
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note version = u_int8
 */
static WBXMLError parse_version(WBXMLParser *parser)
{   
    WBXMLError ret = WBXML_OK;
    
    /* Initialize version: 1.0 
     *
     * Do NOT keep 'WBXML_VERSION_UNKNOWN' (0xffffffff) because only one byte will change.
     * (for example, if the version is 0x02, then parser->version will be 0xffffff02)
     */
    WB_UTINY version = WBXML_VERSION_10;
    
    if ((ret = parse_uint8(parser, &version)) != WBXML_OK)
        return ret;
    
    parser->version = version;

    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsed version: 1.%d", parser->pos - 1, parser->version));

    return WBXML_OK;
}


/**
 * @brief Parse WBXML public id
 * @param parser The WBXML Parser
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note publicid = mb_u_int32 | ( zero index )
 * @note index = mb_u_int32
 */
static WBXMLError parse_publicid(WBXMLParser *parser)
{
    WB_UTINY public_id;
    WBXMLError ret;

    if (!wbxml_buffer_get_char(parser->wbxml, parser->pos, &public_id))
        return WBXML_ERROR_END_OF_BUFFER;

    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsed public id value: '0x%X'", parser->pos, public_id));

    if (public_id == 0x00) {
        parser->pos++;

        /* Get index (we will retrieve the Public ID later from string table) */
        ret = parse_mb_uint32(parser, (WB_ULONG *)&parser->public_id_index);
        WBXML_DEBUG((WBXML_PARSER, "(%d) Parsed public id index: '0x%x'", parser->pos-1, parser->public_id_index));
        return ret;
    }
    else {
        /* Get Public ID */
        ret = parse_mb_uint32(parser, &parser->public_id);        
        WBXML_DEBUG((WBXML_PARSER, "(%d) Parsed public id: '0x%x'", parser->pos-1, parser->public_id));
        return ret;
    }
}


/**
 * @brief Parse WBXML charset
 * @param parser The WBXML Parser
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note charset = mb_u_int32
 * @note "The binary XML format contains a representation of the XML document character encoding.
 *        This is the WBXML equivalent of the XML document format encoding attribute,
 *        which is specified in the ?xml processing instruction. The character set is encoded as
 *        a multi-byte positive integer value, representing the IANA-assigned MIB number for
 *        a character set. A value of zero indicates an unknown document encoding. In the case of
 *        an unknown encoding, transport meta-information should be used to determine the character
 *        encoding. If transport meta-information is unavailable, the default encoding of UTF-8
 *        should be assumed."
 */
static WBXMLError parse_charset(WBXMLParser *parser)
{
    /* definitions first ... or some compilers don't like it */
    const char *charset_name = NULL;

#if defined( WBXML_LIB_VERBOSE )
    WB_ULONG startpos = parser->pos;
#endif /* WBXML_LIB_VERBOSE */

    unsigned int charset = 0;
    WBXMLError ret = parse_mb_uint32(parser, &charset);

    if (ret != WBXML_OK) {
        WBXML_DEBUG((WBXML_PARSER, "(%d) failed to parse character set", startpos));
        return ret;
    }

    if (charset == 0) {
        WBXML_DEBUG((WBXML_PARSER, "(%d) The character set is zero.", startpos));
        if (parser->meta_charset != WBXML_CHARSET_UNKNOWN) {
            /* use character set from transport meta-information */
            WBXML_DEBUG((WBXML_PARSER, "(%d) Using charset from meta-info ...%d.", startpos, parser->meta_charset));
            charset = parser->meta_charset;
        } else {
            /* default encoding is UTF-8 */
            WBXML_DEBUG((WBXML_PARSER, "(%d) Enabling the default character set ... UTF-8.", startpos));
            charset = WBXML_CHARSET_UTF_8;
        }
    }

    if (!wbxml_charset_get_name(charset, &charset_name)) {
        WBXML_DEBUG((WBXML_PARSER, "(%d) failed to get character set name", charset));
        return WBXML_ERROR_CHARSET_NOT_FOUND;
    }
    parser->charset = (WBXMLCharsetMIBEnum) charset;

    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsed charset: '0x%X'", startpos, parser->charset));

    return WBXML_OK;
}


/**
 * @brief Parse WBXML string table
 * @param parser The WBXML Parser
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note strtbl = length *byte
 * @note length = mb_u_int32
 */
static WBXMLError parse_strtbl(WBXMLParser *parser)
{
    WB_UTINY  *data       = NULL;
    WB_ULONG   strtbl_len = 0;
    WB_UTINY   end_char   = 0;
    WBXMLError ret        = WBXML_OK;

    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing strtbl", parser->pos));

    /* Get String Table Length */
    ret = parse_mb_uint32(parser, &strtbl_len);
    if (ret != WBXML_OK)
        return WBXML_ERROR_END_OF_BUFFER;

    if (strtbl_len > 0) {
        /* Check this string table length */
        if (strtbl_len > wbxml_buffer_len(parser->wbxml) - parser->pos)
            return WBXML_ERROR_STRTBL_LENGTH;

        /* Get String Table */
        data = wbxml_buffer_get_cstr(parser->wbxml);
        parser->strstbl = wbxml_buffer_create(data + parser->pos, strtbl_len, WBXML_PARSER_STRING_TABLE_MALLOC_BLOCK);
        if (parser->strstbl == NULL)
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;

        /** @todo Damned ! Check the charset ! This may not be a simple NULL terminated string ! */

        /* Some phones doesn't terminate the String Table with a null char... let's correct this */
        if (!wbxml_buffer_get_char(parser->strstbl,
                                   wbxml_buffer_len(parser->strstbl) - 1,
                                   &end_char))
        {
            return WBXML_ERROR_INTERNAL;
        }

        /* If there is a correctly terminated string
         * then there is no reason to do anything.
         */
        if (end_char != '\0') {
            WBXML_DEBUG((WBXML_PARSER, "    Adding NULL bytes to strtbl."));
            /* A terminating NULL byte is not enough today.
             * There exists character sets with a fixed length of bytes.
             * Such strings must be terminated with a complete NULL character.
             * ASCII  => 1 byte
             * UTF-8  => 1 byte
             * UTF-16 => 2 bytes
             * UTF-32 => 4 bytes (I hope so)
             * UCS-2  => 2 bytes
             * I hope four NULL bytes are enough for all cases.
             */
            if (!wbxml_buffer_append_char(parser->strstbl, '\0'))
                return WBXML_ERROR_NOT_ENOUGH_MEMORY;
            if (!wbxml_buffer_append_char(parser->strstbl, '\0'))
                return WBXML_ERROR_NOT_ENOUGH_MEMORY;
            if (!wbxml_buffer_append_char(parser->strstbl, '\0'))
                return WBXML_ERROR_NOT_ENOUGH_MEMORY;
            if (!wbxml_buffer_append_char(parser->strstbl, '\0'))
                return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }

        parser->pos = parser->pos + strtbl_len;
    }

    return WBXML_OK;
}


/**
 * @brief Parse WBXML body
 * @param parser The WBXML Parser
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note body = *pi element *pi
 */
static WBXMLError parse_body(WBXMLParser *parser)
{
    WBXMLError ret = WBXML_OK;

    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing body", parser->pos));

    while (is_token(parser, WBXML_PI)) {
        if ((ret = parse_pi(parser)) != WBXML_OK)
            return ret;
    }

    if ((ret = parse_element(parser)) != WBXML_OK)
        return ret;

    while (is_token(parser, WBXML_PI)) {
        if ((ret = parse_pi(parser)) != WBXML_OK)
            return ret;
    }

    return WBXML_OK;
}


/**
 * @brief Parse WBXML pi
 * @param parser The WBXML Parser
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note pi = PI attrStart *attrValue END
 */
static WBXMLError parse_pi(WBXMLParser *parser)
{
    WBXMLAttributeName *attr_name    = NULL;
    const WB_UTINY     *start_value  = NULL;
    WBXMLBuffer        *attr_value   = NULL;
    WBXMLBuffer        *tmp_value    = NULL;
    WBXMLError          ret          = WBXML_OK;
  
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing PI", parser->pos));
  
    /* Skip PI */
    parser->pos++;    
      
    /* Parse attrStart */
    if ((ret = parse_attr_start(parser,
                                &attr_name,
                                &start_value)) != WBXML_OK)
    {
        return ret;
    }
      
    if (start_value != NULL ) {
        /* Create a buffer from attribute start value */
        attr_value = wbxml_buffer_create(start_value,
                                         WBXML_STRLEN(start_value),
                                         WBXML_PARSER_ATTR_VALUE_MALLOC_BLOCK);
    }
    else {
        /* Create an empty buffer */
        attr_value = wbxml_buffer_create(NULL,
                                         0,
                                         WBXML_PARSER_ATTR_VALUE_MALLOC_BLOCK);
    }
      
    if (attr_value == NULL) {
        /* Memory error */
        wbxml_attribute_name_destroy(attr_name);
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;
    } 
    
    
    /* Parse *attrValue */
    while (!is_token(parser, WBXML_END)) {
        /* Parse attrValue */
        if ((ret = parse_attr_value(parser, &tmp_value)) != WBXML_OK) {
            wbxml_attribute_name_destroy(attr_name);
            wbxml_buffer_destroy(attr_value);
            return ret;
        }
    
        /* Append to main attribute value buffer */
        if (!wbxml_buffer_append(attr_value, tmp_value)) {
            wbxml_attribute_name_destroy(attr_name);
            wbxml_buffer_destroy(attr_value);
            wbxml_buffer_destroy(tmp_value);
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }
        
        wbxml_buffer_destroy(tmp_value);
        tmp_value = NULL;
    }
      
    /* Skip END */
    parser->pos++;
      
    /* Append NULL char to attr value */
    if (wbxml_buffer_len(attr_value) > 0) {
        if (!wbxml_buffer_append_char(attr_value, '\0')) {
            wbxml_attribute_name_destroy(attr_name);
            wbxml_buffer_destroy(attr_value);

            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }
    }
      
    /* Callback WBXMLProcessingInstructionHandler */
    if ((parser->content_hdl != NULL) &&
        (parser->content_hdl->pi_clb != NULL))
    {
        parser->content_hdl->pi_clb(parser->user_data,
                                    wbxml_attribute_name_get_xml_name(attr_name),
                                    wbxml_buffer_get_cstr(attr_value));
    }
        
    wbxml_attribute_name_destroy(attr_name);
    wbxml_buffer_destroy(attr_value);
      
    return WBXML_OK;
}


/**
 * @brief Parse WBXML element
 * @param parser The WBXML Parser
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note element = ([switchPage] stag) [ 1*attribute END ] [ *content END ]
 */
static WBXMLError parse_element(WBXMLParser *parser)
{
    WBXMLTag        *element        = NULL;
    WBXMLAttribute  *attr           = NULL;
    WBXMLAttribute **attrs          = NULL;
    WBXMLBuffer     *content        = NULL;
  
    WB_ULONG         attrs_nb       = 0;
    WBXMLError       ret            = WBXML_OK;
    WB_UTINY         tag            = 0;
    WB_BOOL          is_empty       = FALSE;
  
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing element", parser->pos));
  
    if (is_token(parser, WBXML_SWITCH_PAGE)) {
        if ((ret = parse_switch_page(parser, WBXML_TAG_TOKEN)) != WBXML_OK) {
            return ret;
        }
    }
  
    /* Parse Tag */
    if ((ret = parse_stag(parser, &tag, &element)) != WBXML_OK ) {
        return ret;
    }

    WBXML_DEBUG((WBXML_PARSER, "<%s>", wbxml_tag_get_xml_name(element)));
  
    /* Set Current Tag */
    if (element->type == WBXML_VALUE_TOKEN) {
        parser->current_tag = element->u.token;
    }
  
    /* Parse Attributes */
    if (tag & WBXML_TOKEN_WITH_ATTRS) {
        WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing attributes", parser->pos));
    
        /* There must be at least one attribute */
        do {
            /* Parse attribute */
            if ((ret = parse_attribute(parser, &attr)) != WBXML_OK) {
                wbxml_tag_destroy(element);
                free_attrs_table(attrs);
                return ret;
            }
          
            /* Append this attribute in WBXMLAttribute **attrs table */
            attrs_nb++;
    
            if ((attrs = wbxml_realloc(attrs,
                                        (attrs_nb + 1) * sizeof(*attrs))) == NULL)
            {
                /* Clean-up */
                wbxml_tag_destroy(element);
                wbxml_attribute_destroy(attr);
                free_attrs_table(attrs);
                return WBXML_ERROR_NOT_ENOUGH_MEMORY;
            }
    
            attrs[(attrs_nb - 1)] = attr;
            attrs[attrs_nb] = NULL;
        } while ( !is_token(parser, WBXML_END) );
        
        /* Skip END */
        parser->pos++;
    }
    
    /* Is it an empty element ? */
    is_empty = (WB_BOOL) !(tag & WBXML_TOKEN_WITH_CONTENT);
      
    /* Callback WBXMLStartElementHandler */
    if ((parser->content_hdl != NULL) &&
        (parser->content_hdl->start_element_clb != NULL))
    {
        parser->content_hdl->start_element_clb(parser->user_data,
                                               element,
                                               attrs,
                                               is_empty);
    }
    
    /* Free Attributes */
    free_attrs_table(attrs);
    
    
    /* Parse *content */
    if (!is_empty) {
        /* There can be NO content */
        while (!is_token(parser, WBXML_END)) {
            /* Parse content */
            if ((ret = parse_content(parser, &content)) != WBXML_OK)
            {
                wbxml_tag_destroy(element);
                return ret;
            }
    
            /* Callback WBXMLCharactersHandler if content is not NULL */
            if ((content != NULL) &&
                (wbxml_buffer_len(content) != 0) &&
                (parser->content_hdl != NULL) &&
                (parser->content_hdl->characters_clb != NULL))
            {
                parser->content_hdl->characters_clb(parser->user_data,
                                                    wbxml_buffer_get_cstr(content),
                                                    0,
                                                    wbxml_buffer_len(content));
            }
          
            /* Free content */
            wbxml_buffer_destroy(content);
            content = NULL;
        }
        
        WBXML_DEBUG((WBXML_PARSER, "(%d) End of Element", parser->pos - 1));
        
        /* Skip END */
        parser->pos++;
    }
      
    /* Callback WBXMLEndElementHandler */
    if ((parser->content_hdl != NULL) &&
        (parser->content_hdl->end_element_clb != NULL))
    {
        parser->content_hdl->end_element_clb(parser->user_data,
                                             element,
                                             is_empty);
    }
    
    WBXML_DEBUG((WBXML_PARSER, "</%s>", wbxml_tag_get_xml_name(element)));
    
    /* Free Tag */
    wbxml_tag_destroy(element);
      
    /* Reset Current Tag */
    parser->current_tag = NULL;
      
    return WBXML_OK;
}


/**
 * @brief Free a (WBXMLAttribute *) table
 * @param attrs The table to ree
 */
static void free_attrs_table(WBXMLAttribute **attrs)
{
    WB_LONG i = 0;

    if (attrs != NULL) {
        while (attrs[i] != NULL) {
            /* Free attribute */
            wbxml_attribute_destroy(attrs[i++]);
        }
        wbxml_free(attrs);
    }
}


/**
 * @brief Parse WBXML switchPage
 * @param parser The WBXML Parser
 * @param code_space The token code space
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note switchPage = SWITCH_PAGE pageindex
 */
static WBXMLError parse_switch_page(WBXMLParser *parser, WBXMLTokenType code_space)
{
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing switchPage", parser->pos));

    if ((WB_UTINY) parser->version < (WB_UTINY) WBXML_VERSION_12) {
        WBXML_WARNING((WBXML_PARSER, "No Switch Page mecanism possible in WBXML < %s (current: %d)", WBXML_VERSION_TEXT_12, (WB_UTINY) parser->version));
    }

    /* Skip SWITCH_PAGE token */
    parser->pos++;

    /* Change Code Page in correct Code Space */
    if (code_space == WBXML_TAG_TOKEN)
        return parse_uint8(parser, &parser->tagCodePage);
    else
        if (code_space == WBXML_ATTR_TOKEN)
            return parse_uint8(parser, &parser->attrCodePage);
        else
            return WBXML_ERROR_INTERNAL;
}


/**
 * @brief Parse WBXML stag
 * @param parser The WBXML Parser
 * @param tag The parsed tag token
 * @param element The parsed element corresponding to token
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note stag = TAG | (literalTag index)
 */
static WBXMLError parse_stag(WBXMLParser *parser, WB_UTINY *tag, WBXMLTag **element)
{
    WBXMLBuffer *name = NULL;
    WBXMLError   ret  = WBXML_OK;
  
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing stag", parser->pos));
  
    if (is_literal(parser)) {
        /* Parse '(literalTag index)' */
        if ((ret = parse_literal(parser, tag, &name)) != WBXML_OK) {
            return ret;
        }
    
        /* Create Element Tag */
        if ((*element = wbxml_tag_create_literal(wbxml_buffer_get_cstr(name))) == NULL) {
            ret = WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }

        wbxml_buffer_destroy(name);
        return ret;
    }

    /* Parse 'TAG' */
    return parse_tag(parser, tag, element);
}


/**
 * @brief Parse WBXML Application Token (tag)
 * @param parser The WBXML Parser
 * @param tag The parsed token tag
 * @param element The parsed element (the text element corresponding to token)
 * @return WBXML_OK if parsing is OK, an error code otherwise
 */
static WBXMLError parse_tag(WBXMLParser *parser, WB_UTINY *tag, WBXMLTag **element)
{
    WB_ULONG index = 0;
    WB_UTINY token;
    WBXMLError ret = WBXML_OK;

    /* Parse UINT8 */
    ret = parse_uint8(parser, tag);
    if (ret != WBXML_OK)
        return ret;

    /* Remove ATTR and CONTENT bits */
    token = (WB_UTINY) (*tag & WBXML_TOKEN_MASK);

    /* Search tag in Tags Table */
    if (parser->langTable == NULL)
        return WBXML_ERROR_LANG_TABLE_UNDEFINED;

    if (parser->langTable->tagTable == NULL)
        return WBXML_ERROR_TAG_TABLE_UNDEFINED;

    
    while ((parser->langTable->tagTable[index].xmlName != NULL) &&
           ((parser->langTable->tagTable[index].wbxmlToken != token) ||
            (parser->langTable->tagTable[index].wbxmlCodePage != parser->tagCodePage))) {
        index++;
    }


    if (parser->langTable->tagTable[index].xmlName == NULL) {
#if WBXML_PARSER_BEST_EFFORT
        /* Create "unknown" Tag Element */
        if ((*element = wbxml_tag_create_literal(WBXML_PARSER_UNKNOWN_STRING)) == NULL)
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;

        return WBXML_OK;
#else
        return WBXML_ERROR_UNKNOWN_TAG;
#endif /* WBXML_PARSER_BEST_EFFORT */
    }

    if ((*element = wbxml_tag_create(WBXML_VALUE_TOKEN)) == NULL)
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;

    (*element)->u.token = &(parser->langTable->tagTable[index]);

    WBXML_DEBUG((WBXML_PARSER, "(%d) Token: 0x%X", parser->pos - 1, token));
    
    return WBXML_OK;
}


/**
 * @brief Parse WBXML attribute
 * @param parser The WBXML Parser
 * @param attr The resulting attribute parsed
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note attribute = attrStart *attrValue
 * @warning The attr_value parameter MUST be freed by caller
 */
static WBXMLError parse_attribute(WBXMLParser *parser, WBXMLAttribute **attr)
{
    WBXMLAttributeName *attr_name    = NULL;
    const WB_UTINY     *start_value  = NULL;
    WBXMLBuffer        *attr_value   = NULL;
    WBXMLBuffer        *tmp_value    = NULL;
    WBXMLError          ret          = WBXML_OK;
  
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing attribute", parser->pos));
  
    /* Parse attrStart */
    if ((ret = parse_attr_start(parser,
                                &attr_name,
                                &start_value)) != WBXML_OK)
    {
        return ret;
    }
  
    if ( start_value != NULL ) {
        /* Create a buffer from attribute start value */
        attr_value = wbxml_buffer_create(start_value,
                                         WBXML_STRLEN(start_value),
                                         WBXML_PARSER_ATTR_VALUE_MALLOC_BLOCK);
    }
    else {
        /* Create an empty buffer */
        attr_value = wbxml_buffer_create(NULL,
                                         0,
                                         WBXML_PARSER_ATTR_VALUE_MALLOC_BLOCK);
    }
  
    if (attr_value == NULL) {
        /* Memory error */
        wbxml_attribute_name_destroy(attr_name);        
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;
    }
  
    /* Construct Attribute Value */
    while (is_attr_value(parser)) {
        /* Parse attrValue */
        if ((ret = parse_attr_value(parser, &tmp_value)) != WBXML_OK) {
            wbxml_attribute_name_destroy(attr_name);
            wbxml_buffer_destroy(attr_value);
            return ret;
        }
    
        if (!wbxml_buffer_append(attr_value, tmp_value)) {
            wbxml_attribute_name_destroy(attr_name);
            wbxml_buffer_destroy(attr_value);
            wbxml_buffer_destroy(tmp_value);
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }
    
        wbxml_buffer_destroy(tmp_value);
        tmp_value = NULL;
    }
  
    if ((wbxml_buffer_len(attr_value) > 0) &&
        (attr_name->type == WBXML_VALUE_TOKEN)) 
    {
        /* Handle Language Specific Attribute Values */
        switch (parser->langTable->langID) {
    #if defined( WBXML_SUPPORT_SI )
        case WBXML_LANG_SI10:
          /* SI 1.0: Decode date for 'created' and 'si-expires' attributes */
          if ((attr_name->u.token->wbxmlCodePage == 0x00) && 
              ((attr_name->u.token->wbxmlToken == 0x0a) ||
               (attr_name->u.token->wbxmlToken == 0x10)))
          {
            if ((ret = decode_datetime(attr_value)) != WBXML_OK) {
              wbxml_attribute_name_destroy(attr_name);
              wbxml_buffer_destroy(attr_value);
              return ret;
            }
          }
          break;
    #endif /* WBXML_SUPPORT_SI */
      
    #if defined( WBXML_SUPPORT_EMN )
        case WBXML_LANG_EMN10:
          /* EMN 1.0: Decode date for 'timestamp' attribute */
          if ((attr_name->u.token->wbxmlCodePage == 0x00) &&
              (attr_name->u.token->wbxmlToken == 0x05))
          {
            if ((ret = decode_datetime(attr_value)) != WBXML_OK) {
              wbxml_attribute_name_destroy(attr_name);
              wbxml_buffer_destroy(attr_value);
              return ret;
            }
          }
          break;
    #endif /* WBXML_SUPPORT_EMN */
      
        default:
          break;
        }
    }
  
    /* Append NULL char to attr value */
    if (wbxml_buffer_len(attr_value) > 0) {
        if (!wbxml_buffer_append_char(attr_value, '\0')) {
            wbxml_attribute_name_destroy(attr_name);
            wbxml_buffer_destroy(attr_value);

            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }
    }
  
    if ((*attr = wbxml_attribute_create()) == NULL) {
        wbxml_attribute_name_destroy(attr_name);
        wbxml_buffer_destroy(attr_value);

        return WBXML_ERROR_NOT_ENOUGH_MEMORY;
    }
  
    (*attr)->name = attr_name;
    (*attr)->value = attr_value;
  
    return WBXML_OK;
}


/**
 * @brief Parse WBXML content
 * @param parser The WBXML Parser
 * @param result Resulting parsed content, if content is not an Element
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note content = element | string | extension | entity | pi | opaque
 */
static WBXMLError parse_content(WBXMLParser *parser, WBXMLBuffer **result)
{
    WB_UTINY cur_byte;
    WBXMLError ret = WBXML_OK;

    /* Debug */
    if (!wbxml_buffer_get_char(parser->wbxml, parser->pos, &cur_byte))
        return WBXML_ERROR_END_OF_BUFFER;

    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing content: '0x%X'", parser->pos, cur_byte));

    /* extension */
    if (is_extension(parser))
        return parse_extension(parser, WBXML_TAG_TOKEN, result);

    /* entity */
    if (is_token(parser, WBXML_ENTITY))
        return parse_entity(parser, result);

    /* string */
    if (is_string(parser))
        return parse_string(parser, result);

    /* opaque */
    if (is_token(parser, WBXML_OPAQUE)) {
        if ((ret = parse_opaque(parser, result)) != WBXML_OK)
            return ret;

        return decode_opaque_content(parser, result);
    }

    /* pi */
    if (is_token(parser, WBXML_PI))
        return parse_pi(parser);
        
    /** 
     * @note Non standard behaviour because of a Nokia 6600 bug
     *       that generate switch pages in wrong places.
     *
     * Thanks to Balaji Alasyam for finding this bug.
     *
     * Example : 02 9F 53 6A 00 6D 6C 71 C3 03 31 2E 31 01 72 C3 0A 53 79 6E
     *           63 4D 4C 2F 31 2E 31 01 65 C3 01 34 01 5B C3 01 31 01 6E 57
     *           C3 31 68 74 74 70 3A 2F 2F 32 31 30 2E 32 31 34 2E 31 36 31
     *           2E 31 37 32 3A 38 30 38 30 2F 74 65 73 74 2F 53 79 6E 63 4D
     *           4C 3F 75 73 65 72 3D 62 61 6C 75 01 01 67 57 C3 14 49 4D 45
     *           49 3A 33 35 31 35 34 36 30 30 35 33 39 34 31 39 39 01 01 5A
     *           00 01 4C C3 05 31 30 30 30 30 01 00 00 01 01 6B 46 4B C3 ...
     *                                            ^^^^^
     */
   
    /* switchPage */
    if ( is_token(parser, WBXML_SWITCH_PAGE) )
      return parse_switch_page(parser, WBXML_TAG_TOKEN);

    /** @note We have recurrency here ! */
    return parse_element(parser);
}


/**
 * @brief Parse WBXML string
 * @param parser [in]  The WBXML Parsertatic
 * @param result [out] The resulting parsed string
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note string = inline | tableref
 */
static WBXMLError parse_string(WBXMLParser *parser, WBXMLBuffer **result)
{
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing string", parser->pos));

    if (is_token(parser, WBXML_STR_I))
        return parse_inline(parser, result);

    if (is_token(parser, WBXML_STR_T))
        return parse_tableref(parser, result);

    return WBXML_ERROR_STRING_EXPECTED;
}


/**
 * @brief Parse WBXML extension
 * @param parser     The WBXML Parser
 * @param code_space The token code space
 * @param result     Resulting parsed extension
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note extension = [switchPage] (( EXT_I termstr ) | ( EXT_T index ) | EXT)
 * @note 5.8.4.2 - The effect of a switchPage preceding an extension will depend upon where the extension appears.
 *                   If switchPage appears in content, it will change the tag code page. Is switchPage appears in
 *                   an attribute list, it will change the attribute code page.
 * @note Extensions tokens are explained in WML Specifications (WAP-191-WML-20000219-a.pdf - 14.1.1 & 14.3)
 * @warning The resulting ext paramater MUST be freed by caller !
 */
static WBXMLError parse_extension(WBXMLParser *parser, WBXMLTokenType code_space, WBXMLBuffer **result)
{
    WB_UTINY   *ext   = NULL;
    WB_ULONG    len   = 0;
    WBXMLError  ret   = WBXML_OK;
    WB_UTINY    token = 0;

#if ( defined ( WBXML_SUPPORT_WML ) || defined ( WBXML_SUPPORT_WTA ) )
    WB_UTINY var_begin[3] = "$(",
             var_end[2]   = ")",
             escape[8]    = ":escape",
             unesc[7]     = ":unesc",
             noesc[7]     = ":noesc";

    WBXMLBuffer *var_value = NULL;
    WB_ULONG     index     = 0;
#endif /* WBXML_SUPPORT_WML || WBXML_SUPPORT_WTA */
  
#if defined ( WBXML_SUPPORT_WV )
    WB_ULONG ext_value = 0;
    WB_UTINY tab_index = 0;
#endif /* WBXML_SUPPORT_WV */
  
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing extension", parser->pos));
  
    /* Parse switchPage */
    if (is_token(parser, WBXML_SWITCH_PAGE)) {
        if ((ret = parse_switch_page(parser, code_space)) != WBXML_OK) {
          return ret;
        }
    }
  
    /* Get Extension Token */
    if ((ret = parse_uint8(parser, &token)) != WBXML_OK) {
        return ret;
    }


    /* Language specific treatment */
    switch (parser->langTable->langID) {

#if defined( WBXML_SUPPORT_WML )

    case WBXML_LANG_WML10:
    case WBXML_LANG_WML11:
    case WBXML_LANG_WML12:
    case WBXML_LANG_WML13:

#endif /* WBXML_SUPPORT_WML */
    
#if defined( WBXML_SUPPORT_WTA )

    case WBXML_LANG_WTAWML12:

#endif /* WBXML_SUPPORT_WTA */
    
#if ( defined( WBXML_SUPPORT_WML ) || defined( WBXML_SUPPORT_WTA ) )
    
        /*****************************
         * WML Variable Substitution 
         */
    
        switch (token) {
        case WBXML_EXT_0:
        case WBXML_EXT_1:
        case WBXML_EXT_2:
            WBXML_WARNING((WBXML_PARSER, "This extension token is reserved for futur use (ignoring)"));
            return WBXML_OK;

        case WBXML_EXT_I_0:
        case WBXML_EXT_I_1:
        case WBXML_EXT_I_2:
            /* Inline variable */
            if ((ret = parse_termstr(parser, &var_value)) != WBXML_OK) {
                WBXML_ERROR((WBXML_PARSER, "Bad Inline Extension"));
                return ret;
            }
            break;

        case WBXML_EXT_T_0:
        case WBXML_EXT_T_1:
        case WBXML_EXT_T_2:
            /* Index in String Table */
            if ((ret = parse_mb_uint32(parser, &index)) != WBXML_OK) {
                return ret;
            }

            if ((ret = get_strtbl_reference(parser,
                                            index,
                                            &var_value)) != WBXML_OK)
            {
                WBXML_ERROR((WBXML_PARSER, "Bad Extension reference in string table"));
                return ret;
            }
            break;

        default:
            return WBXML_ERROR_UNKNOWN_EXTENSION_TOKEN;
        }

        /* Build Variable */
        ext = (WB_UTINY*) wbxml_malloc(WBXML_STRLEN(var_begin) +
                                       wbxml_buffer_len(var_value) +
                                       WBXML_STRLEN(escape) +
                                       WBXML_STRLEN(var_end) + 1);
        if (ext == NULL) {
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }
    
        /* Generate "$(" */
        memcpy(ext + len, var_begin, WBXML_STRLEN(var_begin));
        len += WBXML_STRLEN(var_begin);
    
        /* Generate 'variable' */
        memcpy(ext + len, wbxml_buffer_get_cstr(var_value), wbxml_buffer_len(var_value));
        len += wbxml_buffer_len(var_value);

        /* Destroy 'variable' */
        wbxml_buffer_destroy(var_value);
    
        switch (token) {
        case WBXML_EXT_I_0:
        case WBXML_EXT_T_0:
            /* Generate ":escape" */
            memcpy(ext + len, escape, WBXML_STRLEN(escape));
            len += WBXML_STRLEN(escape);
            break;

        case WBXML_EXT_I_1:
        case WBXML_EXT_T_1:
            /* Generate ":unesc" */
            memcpy(ext + len, unesc, WBXML_STRLEN(unesc));
            len += WBXML_STRLEN(unesc);
            break;

        case WBXML_EXT_I_2:
        case WBXML_EXT_T_2:
            /* Generate ":noesc" */
            memcpy(ext + len, noesc, WBXML_STRLEN(noesc));
            len += WBXML_STRLEN(noesc);
            break;

        default:
            return WBXML_ERROR_UNKNOWN_EXTENSION_TOKEN;
        }
    
        /* Generate ")" */
        memcpy(ext + len, var_end, WBXML_STRLEN(var_end));
        len += WBXML_STRLEN(var_end);

        break;

#endif /* WBXML_SUPPORT_WML || WBXML_SUPPORT_WTA */

#if defined( WBXML_SUPPORT_WV )

    case WBXML_LANG_WV_CSP11:
    case WBXML_LANG_WV_CSP12:
    
        /**********************************
         * Wireless Village extension
         */
    
        if (token != WBXML_EXT_T_0) {
            WBXML_ERROR((WBXML_PARSER, "Only EXT_T_0 extensions authorized with Wireless Village CSP"));
            return WBXML_OK;
        }
    
        /* Get Extension Value Token */
        if ((ret = parse_mb_uint32(parser, &ext_value)) != WBXML_OK) {
            return ret;
        }

        /* Search Token in Extension Value Table */
        if (parser->langTable == NULL) {
            return WBXML_ERROR_LANG_TABLE_UNDEFINED;
        }
    
        if (parser->langTable->extValueTable == NULL) {
            return WBXML_ERROR_EXT_VALUE_TABLE_UNDEFINED;
        }
    
        tab_index = 0;
    
        while ((parser->langTable->extValueTable[tab_index].xmlName != NULL) &&
               (parser->langTable->extValueTable[tab_index].wbxmlToken != ext_value) )
        {
            tab_index++;
        }
    
        if (parser->langTable->extValueTable[tab_index].xmlName == NULL) {
#if WBXML_PARSER_BEST_EFFORT
            ext = (WB_UTINY *) wbxml_strdup((const WB_TINY*) WBXML_PARSER_UNKNOWN_STRING);
            len = WBXML_STRLEN(WBXML_PARSER_UNKNOWN_STRING);
            return WBXML_OK;
#else
            return WBXML_ERROR_UNKNOWN_EXTENSION_VALUE;
#endif /* WBXML_PARSER_BEST_EFFORT */
        }
    
        ext = (WB_UTINY *) wbxml_strdup((const WB_TINY*) parser->langTable->extValueTable[tab_index].xmlName);
        len = WBXML_STRLEN(parser->langTable->extValueTable[tab_index].xmlName);
        break;

#endif /* WBXML_SUPPORT_WV */
    
    default:
        WBXML_ERROR((WBXML_PARSER, "Extension tokens not allowed with this Document !"));
    }

    /* Set result */
    if (ext == NULL) {
        *result = NULL;
    }
    else {
        if ((*result = wbxml_buffer_create(ext, len, len)) == NULL) {
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }

        /** @todo Replace this local var by the direct creation of the result Buffer */
        wbxml_free(ext);
    }
  
    return WBXML_OK;
}


/**
 * @brief Parse WBXML entity
 * @param parser The WBXML Parser
 * @param result The resulting parsed entity
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note entity = ENTITY entcode
 * @note http://www.w3.org/TR/wbxml/ : 
 *         "The character entity token (ENTITY) encodes a numeric character entity. This has the same semantics
 *          as an XML numeric character entity (eg, &#32;). The mb_u_int32 refers to a character in the UCS-4
 *          character encoding. All entities in the source XML document must be represented using either a string
 *          token (eg, STR_I or the ENTITY token."
 * @warning The resulting entity paramater MUST be freed by caller !
 */
static WBXMLError parse_entity(WBXMLParser *parser, WBXMLBuffer **result)
{
    WB_ULONG   code   = 0;
    WBXMLError ret    = WBXML_OK;
  
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing entity", parser->pos));
  
    /* Skip ENTITY */
    parser->pos++;
  
    if ( (ret = parse_entcode(parser, &code)) != WBXML_OK ) {
        return ret;
    }
  
    /*
     * Convert the UCS-4 code to a UTF-8 encoded string.
     */

    assert(code < 0x80000000);

    if (code < 0x80)
    {
        /* For codes under 0x80, we don't need any fancy formatting. */
        WB_TINY entity[2] = {(WB_TINY)code, 0};

        /* Create result buffer */
        if ( (*result = wbxml_buffer_create_from_cstr(entity)) == NULL ) {
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }
      
        return WBXML_OK;
    }
    else
    {
        WB_UTINY masks[5] = {0xFC, 0xF8, 0xF0, 0xE0, 0xC0};
        WB_UTINY entity[7] = {0, 0, 0, 0, 0, 0, 0};

        int index = 5;
        while (code >= 0x40)
        {
            entity[index] = 0x80 | (code & 0x3F);
            code >>= 6; index--;
        }
        entity[index] = masks[index] | code;

        /* Create result buffer */
        if ( (*result = wbxml_buffer_create_from_cstr((WB_TINY *) entity + index)) == NULL ) {
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }
      
        return WBXML_OK;        
    }
}


/**
 * @brief Parse WBXML opaque
 * @param parser The WBXML Parser
 * @param result Resulting opaque data parsed
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note opaque = OPAQUE length *byte
 * @note length = mb_u_int32
 */
static WBXMLError parse_opaque(WBXMLParser *parser, WBXMLBuffer **result)
{
    WB_ULONG   len = 0;
    WBXMLError ret = WBXML_OK;
  
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing opaque", parser->pos));
  
    if (parser->version < WBXML_VERSION_11) {
        WBXML_WARNING((WBXML_PARSER, "No 'opaque' support in WBXML < %s", WBXML_VERSION_TEXT_11));
    }
  
    /* Skip OPAQUE */
    parser->pos++;
  
    if ((ret = parse_mb_uint32(parser, &len)) != WBXML_OK) {
        return ret;
    }

    /* Check that length specified in OPAQUE doesn't overflow wbxml length */
    if (len > wbxml_buffer_len(parser->wbxml) - parser->pos) {
        return WBXML_ERROR_BAD_OPAQUE_LENGTH;
    }

    /**
     * Create result buffer (don't create a static buffer, because this can be
     * modified while trying to decode this content)
     */
    *result = wbxml_buffer_create(wbxml_buffer_get_cstr(parser->wbxml) + parser->pos, len, len);
    if (*result == NULL) {
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;
    }
  
    parser->pos += len;
  
    return ret;
}


/**
 * @brief Parse WBXML literalTag
 * @param parser The WBXML Parser
 * @param mask   Resulting tag mask (WBXML_TOKEN_MASK          |
 *                                   WBXML_TOKEN_WITH_CONTENT  |
 *                                   WBXML_TOKEN_WITH_ATTRS    |
 *                                   (WBXML_TOKEN_WITH_CONTENT || WBXML_TOKEN_WITH_ATTRS))
 * @param result The resulting parsed literal
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note    result = ( literalTag index )
 *            literalTag = LITERAL | LITERAL_A | LITERAL_C | LITERAL_AC
 */
static WBXMLError parse_literal(WBXMLParser  *parser,
                                WB_UTINY     *mask,
                                WBXMLBuffer **result)
{
    WBXMLError ret     = WBXML_OK;
    WB_UTINY   token   = 0;
    WB_ULONG   index   = 0;
  
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing literalTag", parser->pos));
  
    /* Parse literalTag */
    if ( (ret = parse_uint8(parser, &token)) != WBXML_OK ) {
        return ret;
    }
  
    /* Parse index */
    if ( (ret = parse_mb_uint32(parser, &index)) != WBXML_OK ) {
        return ret;
    }
  
    /* Get string */
    if ( (ret = get_strtbl_reference(parser, index, result)) != WBXML_OK ) {
        return ret;
    }

    /* Build Tag Mask */
    switch(token) {
    case WBXML_LITERAL:
        *mask = WBXML_TOKEN_MASK;
        break;

    case WBXML_LITERAL_C:
        *mask = WBXML_TOKEN_WITH_CONTENT;
        break;

    case WBXML_LITERAL_A:
        *mask = WBXML_TOKEN_WITH_ATTRS;
        break;

    case WBXML_LITERAL_AC:
        *mask = ( WBXML_TOKEN_WITH_CONTENT | WBXML_TOKEN_WITH_ATTRS );
        break;

    default:
        return WBXML_ERROR_INTERNAL;
    }
  
    return WBXML_OK;
}


/**
 * @brief Parse WBXML attrStart
 * @param parser The WBXML Parser
 * @param name The Attribute Name parsed
 * @param value The Attribute Value associated, if any
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note attrStart = ([switchPage] ATTRSTART) | ( LITERAL index )
 */
static WBXMLError parse_attr_start(WBXMLParser         *parser,
                                   WBXMLAttributeName **name,
                                   const WB_UTINY     **value)
{
    WBXMLBuffer *literal_str = NULL;
    WB_UTINY     literal     = 0;    
    WB_UTINY     tag         = 0;
    WBXMLError   ret         = WBXML_OK;
    WB_ULONG     index       = 0;

    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing attrStart", parser->pos));
  
  
    /**************************
     * Case: ( LITERAL index ) 
     */
  
    if (is_token(parser, WBXML_LITERAL)) {
        if ((ret = parse_literal(parser, &literal, &literal_str)) != WBXML_OK) {
            return ret;
        }
    
        if ((*name = wbxml_attribute_name_create_literal(wbxml_buffer_get_cstr(literal_str))) == NULL) {
            ret = WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }
    
        /**
         * @todo Return Warning if 'literal' is different from 'WBML_TOKEN_MASK' (because it MUST be a 'LITERAL' token, not
         *       LITERAL_A, nor LITERAL_C, nor LITERAL_AC
         */

        wbxml_buffer_destroy(literal_str);
        return WBXML_OK;
    }
  
  
    /***********************************
     * Case: ( [switchPage] ATTRSTART )
     */
  
    /* Parse switchPage */
    if (is_token(parser, WBXML_SWITCH_PAGE)) {
        if ((ret = parse_switch_page(parser, WBXML_ATTR_TOKEN)) != WBXML_OK) {
            return ret;
        }
    }
  
    /* Parse UINT8 */
    if ((ret = parse_uint8(parser, &tag)) != WBXML_OK) {
        return ret;
    }
  
    WBXML_DEBUG((WBXML_PARSER, "\tToken: 0x%X", tag));
  
    /* Search tag in Tags Table */
    if (parser->langTable == NULL) {
        return WBXML_ERROR_LANG_TABLE_UNDEFINED;
    }
  
    if (parser->langTable->attrTable == NULL) { 
        return WBXML_ERROR_ATTR_TABLE_UNDEFINED;
    }

    while ((parser->langTable->attrTable[index].xmlName != NULL) &&
           ((parser->langTable->attrTable[index].wbxmlToken != tag) ||
            (parser->langTable->attrTable[index].wbxmlCodePage != parser->attrCodePage)))
    {
        index++;
    }
  
    if (parser->langTable->attrTable[index].xmlName == NULL) {
#if WBXML_PARSER_BEST_EFFORT
        /* Create "unknown" Attribute Name */
        if ((*name = wbxml_attribute_name_create_literal(WBXML_PARSER_UNKNOWN_STRING)) == NULL) {
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }
    
        return WBXML_OK;
#else
        return WBXML_ERROR_UNKNOWN_ATTR;
#endif /* WBXML_PARSER_BEST_EFFORT */
    }
  
    /* Create Token Attribute Name */
    if ((*name = wbxml_attribute_name_create(WBXML_VALUE_TOKEN)) == NULL) {
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;
    }
  
    (*name)->u.token = &(parser->langTable->attrTable[index]);
  
    /* Get Attribute start value (if any) */
    if (parser->langTable->attrTable[index].xmlValue != NULL) {
        *value = (const WB_UTINY *) parser->langTable->attrTable[index].xmlValue;
    }
  
    return WBXML_OK;
}


/**
 * @brief Parse WBXML attrValue
 * @param parser [in]  The WBXML Parser
 * @param result [out] The resulting Value parsed
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note attrValue = ([switchPage] ATTRVALUE) | string | extension | entity | opaque
 */
static WBXMLError parse_attr_value(WBXMLParser  *parser,
                                   WBXMLBuffer **result)
{
    WB_ULONG   index = 0;
    WB_UTINY   tag   = 0;
    WBXMLError ret   = WBXML_OK;
  
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing attrValue", parser->pos));
  
    /* Parse extension */
    if (is_extension(parser)) {
        return parse_extension(parser, WBXML_ATTR_TOKEN, result);
    }
  
    /* Parse entity */
    if (is_token(parser, WBXML_ENTITY)) {
        return parse_entity(parser, result);
    }
  
    /* Parse string */
    if (is_string(parser)) {
        return parse_string(parser, result);
    }

    /* Parse opaque */
    if (is_token(parser, WBXML_OPAQUE)) {
        if (parser->version < WBXML_VERSION_12) {
            WBXML_ERROR((WBXML_PARSER, "An Attribute value can't be 'opaque' in WBXML version < %s", WBXML_VERSION_TEXT_12));
        }
        
        if ((ret = parse_opaque(parser, result)) != WBXML_OK) 
            return ret;
        
        return decode_opaque_attr_value(parser, result);
    }
  
  
    /*****************************
     *    ([switchPage] ATTRVALUE)
     */
  
    /* Parse switchPage */
    if (is_token(parser, WBXML_SWITCH_PAGE)) {
        ret = parse_switch_page(parser, WBXML_ATTR_TOKEN);
        if (ret != WBXML_OK) {
            return ret;
        }
    }
  
    /* Parse UINT8 */
    ret = parse_uint8(parser, &tag);
    if (ret != WBXML_OK) {
        return ret;
    }
  
    /* Search tag in Tags Table */
    if (parser->langTable == NULL) {
        return WBXML_ERROR_LANG_TABLE_UNDEFINED;
    }
  
    if (parser->langTable->attrValueTable == NULL) {
        return WBXML_ERROR_ATTR_VALUE_TABLE_UNDEFINED;
    }
  
    while ((parser->langTable->attrValueTable[index].xmlName != NULL) &&
           ((parser->langTable->attrValueTable[index].wbxmlToken != tag) ||
            (parser->langTable->attrValueTable[index].wbxmlCodePage != parser->attrCodePage)))
    {
        index++;
    }
  
    if (parser->langTable->attrValueTable[index].xmlName == NULL) {
        return WBXML_ERROR_UNKNOWN_ATTR_VALUE;
    }

    *result = wbxml_buffer_sta_create_from_cstr(parser->langTable->attrValueTable[index].xmlName);

    return WBXML_OK;
}


/**
 * @brief Parse WBXML termstr
 * @param parser [in]  The WBXML Parser
 * @param result [out] The resulting parsed string
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note termstr = charset-dependent string with termination
 */
static WBXMLError parse_termstr(WBXMLParser  *parser,
                                WBXMLBuffer **result)
{
    WB_ULONG   max_len  = 0;
    WBXMLError ret      = WBXML_OK;
  
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing termstr", parser->pos));

    /* Get max possible string length */
    max_len = wbxml_buffer_len(parser->wbxml) - parser->pos;
  
    /* Convert to UTF-8 Buffer */
    if ((ret = wbxml_charset_conv_term((const WB_TINY *) (wbxml_buffer_get_cstr(parser->wbxml) + parser->pos),
                                       &max_len,
                                       parser->charset,
                                       result,
                                       WBXML_CHARSET_UTF_8)) != WBXML_OK) {
        return ret;
    }

    parser->pos += max_len;
  
    WBXML_DEBUG((WBXML_PARSER, "(%d) termstr: %s", parser->pos, wbxml_buffer_get_cstr(*result)));
  
    return WBXML_OK;
}


/**
 * @brief Parse WBXML inline
 * @param parser [in]  The WBXML Parser
 * @param result [out] The resulting parsed string
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note inline = STR_I termstr
 */
static WBXMLError parse_inline(WBXMLParser  *parser,
                               WBXMLBuffer **result)
{
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing inline", parser->pos));
  
    /* Skip STR_I */
    parser->pos++;
  
    return parse_termstr(parser, result);
}


/**
 * @brief Parse WBXML tableref
 * @param parser The WBXML Parser
 * @param result The resulting parsed string
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note tableref = STR_T index
 * @note index = mb_u_int32
 */
static WBXMLError parse_tableref(WBXMLParser  *parser,
                                 WBXMLBuffer **result)
{
    WB_ULONG index;
    WBXMLError ret = WBXML_OK;
  
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing tableref", parser->pos));
  
    /* Skip STR_T */
    parser->pos++;
  
    /* Parse index */
    if ((ret = parse_mb_uint32(parser, &index)) != WBXML_OK) {
        return ret;
    }
  
    return get_strtbl_reference(parser, index, result);
}


/**
 * @brief Parse WBXML entcode
 * @param parser [in] The WBXML Parser
 * @param result [out] The entcode parsed
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note entcode = mb_u_int32 // UCS-4 character code
 */
static WBXMLError parse_entcode(WBXMLParser *parser,
                                WB_ULONG    *result)
{
    WBXML_DEBUG((WBXML_PARSER, "(%d) Parsing entcode", parser->pos));
  
    return parse_mb_uint32(parser, result);
}


/**
 * @brief Get a string from String Table
 * @param parser The WBXML Parser
 * @param index  Index of string in String Table
 * @param result The resulting parsed string
 * @return WBXML_OK if OK, an error code otherwise
 */
static WBXMLError get_strtbl_reference(WBXMLParser  *parser,
                                       WB_ULONG      index,
                                       WBXMLBuffer **result)
{
    WB_ULONG   max_len = 0;
    WBXMLError ret     = WBXML_OK;

    /* WORKAROUND: 2011-Jan-21 Michael Bell
     * WORKAROUND:
     * WORKAROUND: Nokia encodes the name space not only in the publicid.
     * WORKAROUND: Some Nokia software encodes the SyncML name space
     * WORKAROUND: as an attribute without a name and without a string
     * WORKAROUND: table but with a LITAERAL and an index.
     * WORKAROUND:
     * WORKAROUND: Example:  ED 04 00 03 SYNCML:SYNCML1.2 00
     * WORKAROUND:   ED => 2D => SyncML
     * WORKAROUND:   04 => LITERAL (incl. ATTRSTART)
     * WORKAROUND:   00 => index 0 (without string table)
     * WORKAROUND:   03 => TOKEN_STR_I (inline sring)
     * WORKAROUND:
     * WORKAROUND: If this mistake is detected then "xmlns" is returned.
     */
    if (parser->strstbl == NULL && index == 0) {
        WBXML_DEBUG((WBXML_PARSER, "(%d) Workaround Nokia: NO string table, index 0 => encoded xmlns", parser->pos));

        /* UTF-8 xmlns */
        if ((*result = wbxml_buffer_create_from_cstr("xmlns")) == NULL) {
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }
        
        return WBXML_OK;
    }
  
    /* Check if strtbl is NULL */
    if (parser->strstbl == NULL) {
        return WBXML_ERROR_NULL_STRING_TABLE;
    }
  
    if (index >= wbxml_buffer_len(parser->strstbl)) {
        return WBXML_ERROR_INVALID_STRTBL_INDEX;
    }

    /* Get max possible string length */
    max_len = wbxml_buffer_len(parser->strstbl) - index;

    /* Convert to UTF-8 Buffer */
    if ((ret = wbxml_charset_conv_term((const WB_TINY *) (wbxml_buffer_get_cstr(parser->strstbl) + index),
                                       &max_len,
                                       parser->charset,
                                       result,
                                       WBXML_CHARSET_UTF_8)) != WBXML_OK) {
        return ret;
    }

    WBXML_DEBUG((WBXML_PARSER, "(%d) String Table Reference: %s", parser->pos, wbxml_buffer_get_cstr(*result)));

    return WBXML_OK;
}


/********************************
 *    Basic Types Parse functions
 */

/**
 * @brief Parse UINT8
 * @param parser [in] The WBXML Parser
 * @param result [out] Parsed UINT8
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note u_int8 = 8 bit unsigned integer
 */
static WBXMLError parse_uint8(WBXMLParser *parser, WB_UTINY *result)
{
    if (parser == NULL)
        return WBXML_ERROR_NULL_PARSER;

    if (result == NULL)
        return WBXML_ERROR_BAD_PARAMETER;

    if (parser->pos == wbxml_buffer_len(parser->wbxml))
        return WBXML_ERROR_END_OF_BUFFER;

    if (!wbxml_buffer_get_char(parser->wbxml, parser->pos, result))
        return WBXML_ERROR_END_OF_BUFFER;

    parser->pos++;

    return WBXML_OK;
}


/**
 * @brief Parse a MultiByte UINT32
 * @param parser The WBXML Parser
 * @param result The parsed MultiByte
 * @return WBXML_OK if parsing is OK, an error code otherwise
 * @note mb_u_int32 = 32 bit unsigned integer, encoded in multi-byte format
 */
static WBXMLError parse_mb_uint32(WBXMLParser *parser, WB_ULONG *result)
{
    WB_ULONG uint = 0, byte_pos;
    WB_UTINY cur_byte;

    if (parser == NULL)
        return WBXML_ERROR_NULL_PARSER;

    if (result == NULL)
        return WBXML_ERROR_BAD_PARAMETER;

    /* It's a 32bit integer, and so it fits to a maximum of 4 bytes */
    for (byte_pos = 0; byte_pos < 5; byte_pos++) {
        /* Get current byte */
        if (!wbxml_buffer_get_char(parser->wbxml, parser->pos, &cur_byte))
            return WBXML_ERROR_END_OF_BUFFER;

        /* Move to next byte */
        parser->pos++;

        /* Update uint value */
        uint = (uint << 7) | ((WB_UTINY)cur_byte & 0x7F);

        /* Check first bit, and stop if value is zero */
        if (!((WB_UTINY)cur_byte & 0x80)) {
            *result = uint;
            return WBXML_OK;
        }
    }

    return WBXML_ERROR_UNVALID_MBUINT32;
}


/****************************************
 * Language Specific Decoding Functions 
 */

/**
 * @brief Decode a BASE64 value
 * @param data [in/out]The value to decode
 * @return WBXML_OK if OK, another error code otherwise
 */
static WBXMLError decode_base64_value(WBXMLBuffer **data)
{
    WB_UTINY   *result = NULL;
    WBXMLError  ret    = WBXML_OK;
    
    if ((data == NULL) || (*data == NULL)) {
        return WBXML_ERROR_INTERNAL;
    }
    
    if ((result = wbxml_base64_encode((const WB_UTINY *) wbxml_buffer_get_cstr(*data),
                                      wbxml_buffer_len(*data))) == NULL)
    {
        return WBXML_ERROR_B64_ENC;
    }
    
    /* Reset buffer */
    wbxml_buffer_delete(*data, 0, wbxml_buffer_len(*data));
    
    /* Set data */
    if (!wbxml_buffer_append_cstr(*data, result)) {
        ret = WBXML_ERROR_NOT_ENOUGH_MEMORY;
    }
    
    wbxml_free(result);
    
    return ret;
}


#if ( defined( WBXML_SUPPORT_SI ) || defined( WBXML_SUPPORT_EMN ) )

/**************************************
 * SI 1.0 / EMN 1.0
 */

/**
 * @brief Decode a %Datetime Attribute Value
 * @param buff The Attribute Value to convert
 * @return WBXML_OK if OK, another error code otherwise
 * @note Used for:
 *      - SI 1.0: Decode date for 'created' and 'si-expires' attributes
 *      - EMN 1.0: Decode date for 'timestamp' attribute
 */
static WBXMLError decode_datetime(WBXMLBuffer *buff)
{
    WB_ULONG len = 0;

    /* Binary to Hexa */
    if (!wbxml_buffer_binary_to_hex(buff, TRUE))
        return WBXML_ERROR_INTERNAL;

    /* Check Integrity */
    len = wbxml_buffer_len(buff);
    if ((len < 8) || (len > 14) || (len == 9) || (len == 11) || (len == 13))
        return WBXML_ERROR_BAD_DATETIME;

    /* Date */

    /* "1999-" */
    if (!wbxml_buffer_insert_cstr(buff, (WB_UTINY *)"-", 4))
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;

    /* "1999-04-" */
    if (!wbxml_buffer_insert_cstr(buff, (WB_UTINY *)"-", 7))
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;

    /* "1999-04-30T" */
    if (!wbxml_buffer_insert_cstr(buff, (WB_UTINY *)"T", 10))
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;

    /* Time */

    /* Append ':' delimiters */
    if (len > 10) {
        if (!wbxml_buffer_insert_cstr(buff, (WB_UTINY *)":", 13))
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
    }

    if (len > 12) {
        if (!wbxml_buffer_insert_cstr(buff, (WB_UTINY *)":", 16))
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
    }

    /* Append Trailing Zeros */
    switch (len) {
    case 8:
        if (!wbxml_buffer_append_cstr(buff, (WB_UTINY *)"00:00:00"))
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        break;
    case 10:
        if (!wbxml_buffer_append_cstr(buff, (WB_UTINY *)":00:00"))
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        break;
    case 12:
        if (!wbxml_buffer_append_cstr(buff, (WB_UTINY *)":00"))
            return WBXML_ERROR_NOT_ENOUGH_MEMORY;
        break;
    default:
        /* 14 : Nothing to do */
        break;
    }

    /* Append ending 'Z' character */
    if (!wbxml_buffer_append_char(buff, 'Z'))
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;

    return WBXML_OK;
}

#endif /* WBXML_SUPPORT_SI || WBXML_SUPPORT_EMN */


/**
 * @brief Decode an Opaque Content buffer
 * @param parser The WBXML Parser
 * @param data The Opaque data buffer
 * @return WBXML_OK if OK, another error code otherwise
 */
static WBXMLError decode_opaque_content(WBXMLParser  *parser,
                                        WBXMLBuffer **data)
{
    switch (parser->langTable->langID) 
    {

#if defined( WBXML_SUPPORT_WV )

    case WBXML_LANG_WV_CSP11:
    case WBXML_LANG_WV_CSP12:
        return decode_wv_content(parser, data);
        break;

#endif /* WBXML_SUPPORT_WV */
    
#if defined( WBXML_SUPPORT_DRMREL )

    case WBXML_LANG_DRMREL10:
        /* ds:KeyValue */
        if ((parser->current_tag->wbxmlCodePage == 0x00) &&
            (parser->current_tag->wbxmlToken == 0x0C))
        {
            WBXMLError ret = WBXML_OK;
            
            /* Decode base64 value */ 
            if ((ret = decode_base64_value(data)) != WBXML_OK)
                return ret;

            return WBXML_OK;
        }
        break;

#endif /* WBXML_SUPPORT_DRMREL */    

#if defined( WBXML_SUPPORT_SYNCML )

    case WBXML_LANG_SYNCML_SYNCML10: 
    case WBXML_LANG_SYNCML_SYNCML11: 
    case WBXML_LANG_SYNCML_SYNCML12: 
        /* NextNonce */
        if ((parser->current_tag->wbxmlCodePage == 0x01) &&
            (parser->current_tag->wbxmlToken == 0x10)) 
        {
            WBXMLError ret = WBXML_OK;
            
            /* Decode base64 value */ 
            if ((ret = decode_base64_value(data)) != WBXML_OK)
                return ret;
                
            return WBXML_OK;
        }
        break;

#endif /* WBXML_SUPPORT_SYNCML */    

    default:
        /* NOP */
        break;
    } /* switch */
  
    return WBXML_OK;
}


/**
 * @brief Decode an Opaque Attribute Value buffer
 * @param parser The WBXML Parser
 * @param data The Opaque data buffer
 * @return WBXML_OK if OK, another error code otherwise
 */
static WBXMLError decode_opaque_attr_value(WBXMLParser *parser, WBXMLBuffer **data)
{
    switch (parser->langTable->langID) 
    {
#if defined( WBXML_SUPPORT_OTA_SETTINGS )

    case WBXML_LANG_OTA_SETTINGS:
    {
        WBXMLError ret = WBXML_OK;
        
        /* Decode base64 value */
        if ((ret = decode_base64_value(data)) != WBXML_OK)
            return ret; 

        return WBXML_OK;
    }

#endif /* WBXML_SUPPORT_OTA_SETTINGS */ 

    default:
        /* NOP */
        break;
    } /* switch */
  
    return WBXML_OK;
}


#if defined( WBXML_SUPPORT_WV )

/**************************************
 * WV 1.1 / WV 1.2
 */

/**
 * @brief Decode a WV Content encoded in an Opaque
 * @param parser The WBXML Parser
 * @param data The WV Integer to decode
 * @return WBXML_OK if OK, another error code otherwise
 * @note Used for:
 *      - WV 1.1 / 1.2
 */
static WBXMLError decode_wv_content(WBXMLParser  *parser, WBXMLBuffer **data)
{
    WBXMLWVDataType data_type = WBXML_WV_DATA_TYPE_STRING;
    WBXMLError      ret       = WBXML_OK;

    /* Wireless-Village 1.1 / 1.2 */
  
    /* 
     *  Specific WV Opaque Data Type Elements:
     *
     *        Integer:
     *            Code (0x00 / 0x0B)
     *            ContentSize (0x00 / 0x0F)
     *            MessageCount (0x00 / 0x1A)
     *            Validity (0x00 / 0x3C)
     *            KeepAliveTime (0x01 / 0x1C)
     *            SearchFindings (0x01 / 0x25)
     *            SearchID (0x01 / 0x26)
     *            SearchIndex (0x01 / 0x27)
     *            SearchLimit (0x01 / 0x28)
     *            TimeToLive (0x01 / 0x32)
     *            AcceptedCharSet (0x03 / 0x05)
     *            AcceptedContentLength (0x03 / 0x06)
     *            MultiTrans (0x03 / 0x0C)
     *            ParserSize (0x03 / 0x0D)
     *            ServerPollMin (0x03 / 0x0E)
     *            TCPPort (0x03 / 0x12)
     *            UDPPort (0x03 / 0x13)
     *            HistoryPeriod (0x09 / 0x08) [WV 1.2]
     *            MaxWatcherList (0x09 / 0x0A) [WV 1.2]
     *
     *        Date and Time:
     *            DateTime (0x00 / 0x11)
     *            DeliveryTime (0x06 / 0x1A)
     *
     *        Binary:
     *            ContentData (0x00 / 0x0D) (only if we have a:
     *                                       "<ContentEncoding>BASE64</ContentEncoding>" associated)
     */
  
    /***********************************************
     * Check the Data Type, given the Current Tag 
     */
  
    switch (parser->current_tag->wbxmlCodePage) {
    case 0x00:
        /* Code Page: 0x00 */
        switch (parser->current_tag->wbxmlToken) {
            case 0x0B: /* Code */
            case 0x0F: /* ContentSize */
            case 0x1A: /* MessageCount */
            case 0x3C: /* Validity */
                /* INTEGER */
                data_type = WBXML_WV_DATA_TYPE_INTEGER;
                break;

            case 0x11: /* DateTime */
                /* DATE_AND_TIME */
                data_type = WBXML_WV_DATA_TYPE_DATE_AND_TIME;
                break;

            case 0x0D: /* ContentData */
                /* BINARY */
                /** @todo Check if we have a: "<ContentEncoding>BASE64</ContentEncoding>" associated */
                /*
                    if (base64_encoded)
                        data_type = WBXML_WV_DATA_TYPE_BINARY;
                    else
                */
                data_type = WBXML_WV_DATA_TYPE_STRING;
            break;

            default:
                /* STRING */
                data_type = WBXML_WV_DATA_TYPE_STRING;
                break;
            }
            break;

    case 0x01:
        /* Code Page: 0x01 */
        switch (parser->current_tag->wbxmlToken) {
        case 0x1C: /* KeepAliveTime */
        case 0x25: /* SearchFindings */
        case 0x26: /* SearchID */
        case 0x27: /* SearchIndex */
        case 0x28: /* SearchLimit */
        case 0x32: /* TimeToLive */
            /* INTEGER */
            data_type = WBXML_WV_DATA_TYPE_INTEGER;
            break;

        default:
            /* STRING */
            data_type = WBXML_WV_DATA_TYPE_STRING;
            break;
        }
        break;

    case 0x03:
        /* Code Page: 0x03 */
        switch (parser->current_tag->wbxmlToken) {
        case 0x05: /* AcceptedCharSet */
        case 0x06: /* AcceptedContentLength */
        case 0x0C: /* MultiTrans */
        case 0x0D: /* ParserSize */
        case 0x0E: /* ServerPollMin */
        case 0x12: /* TCPPort */
        case 0x13: /* UDPPort */
            /* INTEGER */
            data_type = WBXML_WV_DATA_TYPE_INTEGER;
            break;

        default:
            /* STRING */
            data_type = WBXML_WV_DATA_TYPE_STRING;
            break;
        }
        break;

    case 0x05:
        /* Code Page: 0x05 */
        switch (parser->current_tag->wbxmlToken) {
        case 0x05: /* Altitude */
        case 0x09: /* Accuracy */
        case 0x32: /* Cpriority */
            /* INTEGER */
            data_type = WBXML_WV_DATA_TYPE_INTEGER;
            break;

        default:
            /* STRING */
            data_type = WBXML_WV_DATA_TYPE_STRING;
            break;
        }
        break;

    case 0x06:
        /* Code Page: 0x06 */
        switch (parser->current_tag->wbxmlToken) {
        case 0x1A: /* DeliveryTime */
            /* DATE AND TIME */
            data_type = WBXML_WV_DATA_TYPE_DATE_AND_TIME;
            break;

        default:
            /* STRING */
            data_type = WBXML_WV_DATA_TYPE_STRING;
            break;
        }
        break;

    case 0x09:
        /* Code Page: 0x09 */
        switch (parser->current_tag->wbxmlToken) {
        case 0x08: /* HistoryPeriod */
        case 0x0A: /* MaxWatcherList */
            /* INTEGER */
            data_type = WBXML_WV_DATA_TYPE_INTEGER;
            break;

        default:
            /* STRING */
            data_type = WBXML_WV_DATA_TYPE_STRING;
            break;
        }
        break;

    default:
        data_type = WBXML_WV_DATA_TYPE_STRING;
        break;
    } /* switch */
  
  
    /***********************************************
     * Decode the Opaque, given the Data Type found 
     */
  
    switch ( data_type ) {
    case WBXML_WV_DATA_TYPE_INTEGER:
        /* Decode Integer */
        if ( (ret = decode_wv_integer(data)) != WBXML_OK )
            return ret;
    
        return WBXML_OK;
        break;

    case WBXML_WV_DATA_TYPE_DATE_AND_TIME:
        /* Decode Date and Time */
        if ( (ret = decode_wv_datetime(data)) != WBXML_OK )
            return ret;
    
        return WBXML_OK;
        break;

    case WBXML_WV_DATA_TYPE_BINARY:
        /** @todo decode_wv_binary() */
        break;

    default:
        /* Do nothing. Keep this data as is. */
        break;
    } /* switch */
  
    return WBXML_OK;
}

/**
 * @brief Decode a WV Integer encoded in an Opaque
 * @param data The WV Integer to decode
 * @return WBXML_OK if OK, another error code otherwise
 * @note Used for:
 *      - WV 1.1 / 1.2
 * @note [OMA-WV-CSP_DataTypes-V1_1-20021001-A.pdf] - 4.1:
 *       "An integer is a number from 0-4294967295 expressed in decimal format."
 *
 * @warning Input 'data' parameter MUST be a static buffer, because its pointer
 *          is released without being freed.
 */
static WBXMLError decode_wv_integer(WBXMLBuffer **data)
{
    WB_ULONG i       = 0;
    WB_ULONG the_int = 0;
    WB_UTINY ch      = 0;
    WB_UTINY tmp[11];
  
    if ( (data == NULL) || (*data== NULL) )
        return WBXML_ERROR_INTERNAL;

    /* Get the integer */
    for ( i = 0; i < wbxml_buffer_len(*data); i++ ) {
        if (!wbxml_buffer_get_char(*data, i, &ch))
            return WBXML_ERROR_INTERNAL;
    
        the_int = (the_int << 8) | (ch & 0xff);
    }
  
    /* Check integer overflow */
    if ( the_int > 0xffffffff )
        return WBXML_ERROR_WV_INTEGER_OVERFLOW;
  
    sprintf((WB_TINY *)tmp, "%u", the_int);

    /* Reset buffer */
    wbxml_buffer_delete(*data, 0, wbxml_buffer_len(*data));

    /* Set data */
    if (!wbxml_buffer_append_cstr(*data, tmp))
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;

  return WBXML_OK;
}


/**
 * @brief Decode a WV Date and Time encoded in an Opaque
 * @param data The WV Date Time to decode
 * @return WBXML_OK if OK, another error code otherwise
 * @note Used for:
 *      - WV 1.1 / 1.2
 * @note 
 *  Encoded Format: (6 octets)
 *      - The first 2 bits are reserved, and both must be 0.
 *      - Year is encoded by 12 bits (0 to 4095)
 *      - Month is encoded by 4 bits (1 to 12)
 *      - Day is encoded by 5 bits (1 to 31)
 *      - Hour is encoded by 5 bits (0 to 23)
 *      - Minute is encoded by 6 bits (0 to 59)
 *      - Second is encoded by 6 bits (0 to 59)
 *      - Time zone is encoded in 1 byte [ISO8601].
 *
 *      eg:
 *          Binary:  00 011111010001 1010 10011 01001 110010 011111 01011010
 *          Octets:  (-------)(-------)(--------)(-------)(-------) (------)
 *
 *  Decoded Format:
 *      eg: 20011019T095031Z or 20011019T095031
 *
 * @warning Input 'data' parameter MUST be a static buffer, because its pointer
 *          is released without being freed. 
 */
static WBXMLError decode_wv_datetime(WBXMLBuffer **data)
{
    WB_UTINY *data_ptr = NULL;
    WB_TINY   the_year[5], the_month[3],  the_date[3], 
              the_hour[3], the_minute[3], the_second[3],
              result[17];
    WB_ULONG the_value = 0;
    WBXMLError ret = WBXML_OK;
  
    /** @todo Test decode_wv_datetime() ! */
  
    if ((data == NULL) || (*data == NULL))
        return WBXML_ERROR_INTERNAL;
  
    if (wbxml_buffer_len(*data) != 6)
        return WBXML_ERROR_WV_DATETIME_FORMAT;


    data_ptr = wbxml_buffer_get_cstr(*data);
  
    /* Get Year */
    the_value = (WB_ULONG) (((data_ptr[0] & 0x3F) << 6) + ((data_ptr[1] >> 2) & 0x3F));
    sprintf(the_year, "%u", the_value);
  
    /* Get Month */
    the_value = (WB_ULONG) (((data_ptr[1] & 0x03) << 2) | ((data_ptr[2] >> 6) & 0x03));
    sprintf(the_month, "%02u", the_value);
  
    /* Get Day */
    the_value = (WB_ULONG) ((data_ptr[2] >> 1) & 0x1F);
    sprintf(the_date, "%02u", the_value);
  
    /* Get Hour */
    the_value = (WB_ULONG) (((data_ptr[2] & 0x01) << 4) | ((data_ptr[3] >> 4) & 0x0F));
    sprintf(the_hour, "%02u", the_value);
  
    /* Get Minute */
    the_value = (WB_ULONG) (((data_ptr[3] & 0x0F) << 2) | ((data_ptr[4] >> 6) & 0x03));
    sprintf(the_minute, "%02u", the_value);
  
    /* Get Second */
    the_value = (WB_ULONG) (data_ptr[4] & 0x3F);
    sprintf(the_second, "%02u", the_value);
  
    /* Get Time Zone */
    if (data_ptr[5] == 0) {
        /* This is a bug in the WBXML document.
         * If timezone UTC aka Zulu is used then a 'Z' must be set.
         */
        sprintf((WB_TINY *) result,
                "%s%s%sT%s%s%sZ",
                the_year, the_month, the_date, the_hour, the_minute, the_value ? the_second : "");
    } else if (data_ptr[5] < 'A' ||
               data_ptr[5] > 'Z' ||
               data_ptr[5] == 'J')
    {
	/* This is a bug in the WBXML document.
	 * The timezone byte is set and wrong.
         * There is no way to recover cleanly from this.
         * Therefore no timezone is set.
         */
        sprintf((WB_TINY *) result,
                "%s%s%sT%s%s%s",
                the_year, the_month, the_date, the_hour, the_minute, the_value ? the_second : "");
    }
    else {
        sprintf((WB_TINY *) result,
                "%s%s%sT%s%s%s%c",
                the_year, the_month, the_date, the_hour, the_minute, the_value ? the_second : "", data_ptr[5]);
    }
  
    /* Reset buffer */
    wbxml_buffer_delete(*data, 0, wbxml_buffer_len(*data));

    /* Set data */
    if (!wbxml_buffer_append_cstr(*data, result)) {
        ret = WBXML_ERROR_NOT_ENOUGH_MEMORY;
    }
  
    return WBXML_OK;
}

#endif /* WBXML_SUPPORT_WV */
