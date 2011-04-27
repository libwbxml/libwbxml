/*
 * libwbxml, the WBXML Library.
 * Copyright (C) 2002-2008 Aymerick Jehanne <aymerick@jehanne.org>
 * Copyright (C) 2011 Michael Bell <michael.bell@opensync.org>
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
 * @file wbxml_conv.c
 * @ingroup wbxml_conv
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 03/02/23
 *
 * @brief WBXML Convertion Library (XML to WBXML, and WBXML to XML)
 */

#include "wbxml_conv.h"
#include "wbxml_tree.h"
#include "wbxml_log.h"

/****************************
 *    converter objects     *
 ****************************
 */

struct WBXMLConvWBXML2XML_s {
    WBXMLGenXMLType gen_type;    /**< WBXML_GEN_XML_COMPACT | WBXML_GEN_XML_INDENT | WBXML_GEN_XML_CANONICAL (Default: WBXML_GEN_XML_INDENT) */
    WBXMLLanguage lang;          /**< Force document Language (overwrite document Public ID) */
    WBXMLCharsetMIBEnum charset; /**< Set document Language (does not overwrite document character set) */
    WB_UTINY indent;             /**< Indentation Delta, when using WBXML_GEN_XML_INDENT Generation Type (Default: 0) */
    WB_BOOL keep_ignorable_ws;   /**< Keep Ignorable Whitespaces (Default: FALSE) */
};

struct WBXMLConvXML2WBXML_s {
    WBXMLVersion wbxml_version; /**< WBXML Version */
    WB_BOOL keep_ignorable_ws;  /**< Keep Ignorable Whitespaces (Default: FALSE) */
    WB_BOOL use_strtbl;         /**< Generate String Table (Default: TRUE) */
    WB_BOOL produce_anonymous;  /**< Produce an anonymous document (Default: FALSE) */
};

/****************************
 *     Public Functions     *
 ****************************
 */

WBXML_DECLARE(WBXMLError) wbxml_conv_wbxml2xml_create(WBXMLConvWBXML2XML **conv)
{
    *conv = (WBXMLConvWBXML2XML *) wbxml_malloc(sizeof(WBXMLConvWBXML2XML));
    if (conv == NULL) {
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;
    }

    (*conv)->gen_type = WBXML_GEN_XML_INDENT;
    (*conv)->lang     = WBXML_LANG_UNKNOWN;
    (*conv)->charset  = WBXML_CHARSET_UNKNOWN;
    (*conv)->indent   = 0;
    (*conv)->keep_ignorable_ws = FALSE;

    return WBXML_OK;
}

/**
 * @brief Set the XML generation type (default: WBXML_GEN_XML_INDENT).
 * @param conv     [in] the converter
 * @param gen_type [in] generation type
 */
WBXML_DECLARE(void) wbxml_conv_wbxml2xml_set_gen_type(WBXMLConvWBXML2XML *conv, WBXMLGenXMLType gen_type)
{
    conv->gen_type = gen_type;
}

/**
 * @brief Set the used WBXML language.
 *        The language is usually detected by the specified public ID in the document.
 *        If the public ID is set then it overrides the language.
 * @param conv [in] the converter
 * @param lang [in] language (e.g. SYNCML12)
 */
WBXML_DECLARE(void) wbxml_conv_wbxml2xml_set_language(WBXMLConvWBXML2XML *conv, WBXMLLanguage lang)
{
    conv->lang = lang;
}

/**
 * @brief Set the used character set.
 *        The default character set is UTF-8.
 *        If the document specifies a character set by it own
 *        then this character set overrides the parameter charset.
 * @param conv    [in] the converter
 * @param charset [in] the character set
 */
WBXML_DECLARE(void) wbxml_conv_wbxml2xml_set_charset(WBXMLConvWBXML2XML *conv, WBXMLCharsetMIBEnum charset)
{
    conv->charset = charset;
}

/**
 * @brief Set the indent of the generated XML document (please see EXPAT default).
 * @param conv   [in] the converter
 * @param indent [in] the number of blanks
 */
WBXML_DECLARE(void) wbxml_conv_wbxml2xml_set_indent(WBXMLConvWBXML2XML *conv, WB_UTINY indent)
{
    conv->indent = indent;
}

/**
 * @brief Enable whitespace preservation (default: FALSE).
 * @param conv     [in] the converter
 */
WBXML_DECLARE(void) wbxml_conv_wbxml2xml_enable_preserve_whitespaces(WBXMLConvWBXML2XML *conv)
{
    conv->keep_ignorable_ws = TRUE;
}

/**
 * @brief Convert WBXML to XML
 * @param conv      [in] the converter
 * @param wbxml     [in] WBXML Document to convert
 * @param wbxml_len [in] Length of WBXML Document
 * @param xml       [out] Resulting XML Document
 * @param xml_len   [out] XML Document length
 * @return WBXML_OK if conversion succeeded, an Error Code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_conv_wbxml2xml_run(WBXMLConvWBXML2XML *conv,
                                                   WB_UTINY  *wbxml,
                                                   WB_ULONG   wbxml_len,
                                                   WB_UTINY **xml,
                                                   WB_ULONG  *xml_len)
{
    WBXMLGenXMLParams params;
    WBXMLTree *wbxml_tree = NULL;
    WB_ULONG   dummy_len = 0;
    WBXMLError ret = WBXML_OK;

    /* Copy options */
    params.gen_type          = conv->gen_type;
    params.lang              = conv->lang;
    params.charset           = conv->charset;
    params.keep_ignorable_ws = conv->keep_ignorable_ws;
    params.indent            = conv->indent;

    /* Check Parameters (we allow 'xml_len' to be NULL for backward compatibility) */
    if ((wbxml == NULL) || (wbxml_len == 0) || (xml == NULL))
        return WBXML_ERROR_BAD_PARAMETER;

    if (xml_len == NULL)
        xml_len = &dummy_len;

    *xml = NULL;
    *xml_len = 0;

    /* Parse WBXML to WBXML Tree */
    ret = wbxml_tree_from_wbxml(wbxml, wbxml_len, conv->lang, conv->charset, &wbxml_tree);
    if (ret != WBXML_OK) {
        WBXML_ERROR((WBXML_CONV, "wbxml2xml conversion failed - WBXML Parser Error: %s",
                                 wbxml_errors_string(ret)));

        return ret;
    }
    else {
        /* Convert Tree to XML */
        ret = wbxml_tree_to_xml(wbxml_tree, xml, xml_len, &params);
        if (ret != WBXML_OK) {
            WBXML_ERROR((WBXML_CONV, "wbxml2xml conversion failed - WBXML Encoder Error: %s",
                                     wbxml_errors_string(ret)));
        }

        /* Clean-up */
        wbxml_tree_destroy(wbxml_tree);

        return ret;
    }
}

/**
 * @brief Destroy the converter object.
 * @param [in] the converter
 */
WBXML_DECLARE(void) wbxml_conv_wbxml2xml_destroy(WBXMLConvWBXML2XML *conv)
{
    wbxml_free(conv);
}

/**
 * @brief Create a new WBXML to XML converter with the default configuration.
 * @param conv [out] a reference to the pointer of the new converter
 * @return WBXML_OK if conversion succeeded, an Error Code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_conv_xml2wbxml_create(WBXMLConvXML2WBXML **conv)
{
    *conv = (WBXMLConvXML2WBXML *) wbxml_malloc(sizeof(WBXMLConvXML2WBXML));
    if (conv == NULL) {
        return WBXML_ERROR_NOT_ENOUGH_MEMORY;
    }

    (*conv)->wbxml_version     = WBXML_VERSION_13;
    (*conv)->keep_ignorable_ws = FALSE;
    (*conv)->use_strtbl        = TRUE;
    (*conv)->produce_anonymous = FALSE;

    return WBXML_OK;
}

/**
 * @brief Set the WBXML version (default: 1.3).
 * @param conv   [in] the converter
 * @param indent [in] the number of blanks
 */
WBXML_DECLARE(void) wbxml_conv_xml2wbxml_set_version(WBXMLConvXML2WBXML *conv,
                                                     WBXMLVersion wbxml_version)
{
    conv->wbxml_version = wbxml_version;
}

/**
 * @brief Enable whitespace preservation (default: FALSE/DISABLED).
 * @param conv     [in] the converter
 */
WBXML_DECLARE(void) wbxml_conv_xml2wbxml_enable_preserve_whitespaces(WBXMLConvXML2WBXML *conv)
{
    conv->keep_ignorable_ws = TRUE;
}

/**
 * @brief Disable string table (default: TRUE/ENABLED).
 * @param conv     [in] the converter
 */
WBXML_DECLARE(void) wbxml_conv_xml2wbxml_disable_string_table(WBXMLConvXML2WBXML *conv)
{
    conv->use_strtbl = FALSE;
}

/**
 * @brief Disable public ID (default: TRUE/ENABLED).
 * @param conv     [in] the converter
 */
WBXML_DECLARE(void) wbxml_conv_xml2wbxml_disable_public_id(WBXMLConvXML2WBXML *conv)
{
    conv->produce_anonymous = TRUE;
}

/**
 * @brief Convert XML to WBXML
 * @param conv      [in] the converter
 * @param xml       [in] XML Document to convert
 * @param xml_len   [in] Length of XML Document
 * @param wbxml     [out] Resulting WBXML Document
 * @param wbxml_len [out] Length of resulting WBXML Document
 * @return WBXML_OK if conversion succeeded, an Error Code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_conv_xml2wbxml_run(WBXMLConvXML2WBXML *conv,
                                                   WB_UTINY  *xml,
                                                   WB_ULONG   xml_len,
                                                   WB_UTINY **wbxml,
                                                   WB_ULONG  *wbxml_len)
{
    WBXMLTree *wbxml_tree = NULL;
    WBXMLError ret = WBXML_OK;
    WBXMLGenWBXMLParams params;

    /* Check Parameters */
    if ((xml == NULL) || (xml_len == 0) || (wbxml == NULL) || (wbxml_len == NULL))
        return WBXML_ERROR_BAD_PARAMETER;

    /* copy options */
    params.wbxml_version     = conv->wbxml_version;
    params.keep_ignorable_ws = conv->keep_ignorable_ws;
    params.use_strtbl        = conv->use_strtbl;
    params.produce_anonymous = conv->produce_anonymous;

    *wbxml = NULL;
    *wbxml_len = 0;

    /* Parse XML to WBXML Tree */
    ret = wbxml_tree_from_xml(xml, xml_len, &wbxml_tree);
    if (ret != WBXML_OK) {
        WBXML_ERROR((WBXML_CONV, "xml2wbxml conversion failed - Error: %s",
                                  wbxml_errors_string(ret)));

        return ret;
    }
    else {
        /* Convert Tree to WBXML */
        ret = wbxml_tree_to_wbxml(wbxml_tree, wbxml, wbxml_len, &params);
        if (ret != WBXML_OK) {
            WBXML_ERROR((WBXML_CONV, "xml2wbxml conversion failed - WBXML Encoder Error: %s",
                                     wbxml_errors_string(ret)));
        }

        /* Clean-up */
        wbxml_tree_destroy(wbxml_tree);

        return ret;
    }
}


/**
 * @brief Destroy the converter object.
 * @param [in] the converter
 */
WBXML_DECLARE(void) wbxml_conv_xml2wbxml_destroy(WBXMLConvXML2WBXML *conv)
{
    wbxml_free(conv);
}

/**************************************
 * Public Functions - DEPRECATED in API
 */

WBXML_DECLARE(WBXMLError) wbxml_conv_wbxml2xml_withlen(WB_UTINY  *wbxml,
                                                       WB_ULONG   wbxml_len,
                                                       WB_UTINY **xml,
                                                       WB_ULONG  *xml_len,
                                                       WBXMLGenXMLParams *params)
{
    WBXMLConvWBXML2XML *conv = NULL;
    WBXMLError ret = WBXML_OK;

    ret = wbxml_conv_wbxml2xml_create(&conv);
    if (ret != WBXML_OK)
        return ret;

    wbxml_conv_wbxml2xml_set_gen_type(conv, params->gen_type);
    wbxml_conv_wbxml2xml_set_language(conv, params->lang);
    wbxml_conv_wbxml2xml_set_charset(conv, params->charset);
    wbxml_conv_wbxml2xml_set_indent(conv, params->indent);
    if (params->keep_ignorable_ws)
        wbxml_conv_wbxml2xml_enable_preserve_whitespaces(conv);
    ret = wbxml_conv_wbxml2xml_run(conv, wbxml, wbxml_len, xml, xml_len);
    wbxml_conv_wbxml2xml_destroy(conv);
    return ret;
}

WBXML_DECLARE(WBXMLError) wbxml_conv_xml2wbxml_withlen(WB_UTINY  *xml,
                                                       WB_ULONG   xml_len,
                                                       WB_UTINY **wbxml,
                                                       WB_ULONG  *wbxml_len,
                                                       WBXMLGenWBXMLParams *params)
{
    WBXMLConvXML2WBXML *conv = NULL;
    WBXMLError ret = WBXML_OK;

    ret = wbxml_conv_xml2wbxml_create(&conv);
    if (ret != WBXML_OK)
        return ret;

    wbxml_conv_xml2wbxml_set_version(conv, params->wbxml_version);
    if (params->keep_ignorable_ws)
        wbxml_conv_xml2wbxml_enable_preserve_whitespaces(conv);
    if (!params->use_strtbl)
        wbxml_conv_xml2wbxml_disable_string_table(conv);
    if (params->produce_anonymous)
        wbxml_conv_xml2wbxml_disable_public_id(conv);
    ret = wbxml_conv_xml2wbxml_run(conv, xml, xml_len, wbxml, wbxml_len);
    wbxml_conv_xml2wbxml_destroy(conv);
    return ret;
}
