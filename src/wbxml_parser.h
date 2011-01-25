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
 * @file wbxml_parser.h
 * @ingroup wbxml_parser
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/03/12
 *
 * @brief WBXML Parser - Parse a WBXML document and call user defined Callbacks
 */

#ifndef WBXML_PARSER_H
#define WBXML_PARSER_H

#include "wbxml.h"
#include "wbxml_handlers.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup wbxml_parser 
 *  @{ 
 */

/** 
 * Default charset of the WBXML document. Used only in this case :
 *  - No charset found in WBXML document
 *  - No charset was indicated thanks to the function 'wbxml_parser_set_meta_charset()'
 */
#define WBXML_PARSER_DEFAULT_CHARSET WBXML_CHARSET_UTF_8


typedef struct WBXMLParser_s WBXMLParser;

/**
 * @brief Create a WBXML Parser
 * @return Return the newly created WBXMLParser, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLParser *) wbxml_parser_create(void);

/**
 * @brief Destroy a WBXML Parser
 * @param parser The WBXMLParser to destroy
 */
WBXML_DECLARE(void) wbxml_parser_destroy(WBXMLParser *parser);

/**
 * @brief Parse a WBXML document, using User Defined callbacks
 * @param parser The WBXML Parser to use for parsing 
 * @param wbxml The WBXML document to parse
 * @param wbxml_len The WBXML document length
 * @brief Return WBXML_OK if no error, an error code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_parser_parse(WBXMLParser *parser, WB_UTINY *wbxml, WB_ULONG wbxml_len);

/**
 * @brief Set User Data for a WBXML Parser
 * @param parser The WBXML Parser
 * @param user_data User data (returned as a parameter in every Content Handler callbacks)
 */
WBXML_DECLARE(void) wbxml_parser_set_user_data(WBXMLParser *parser, void *user_data);

/**
 * @brief Set Content Handler for a WBXML Parser
 * @param parser The WBXML Parser
 * @param content_handler The Content Handler structure
 */
WBXML_DECLARE(void) wbxml_parser_set_content_handler(WBXMLParser *parser, WBXMLContentHandler *content_handler);

/**
 * @brief Set Main WBXML Languages Table
 * @param parser The WBXML Parser
 * @param main_table The Main WBXML Languages Table to set
 */
WBXML_DECLARE(void) wbxml_parser_set_main_table(WBXMLParser *parser, const WBXMLLangEntry *main_table);

/**
 * @brief Force to parse the Document of a given Language
 * @param parser The WBXML Parser
 * @param lang The Language
 * @return TRUE if Language is set, FALSE otherwise
 * @note This permits to force the WBXML Parser to parse a WBXML Document of a given LanguageD.
 *       If this fonction is used, the internal Public ID of the WBXML Document is ignored.
 *       It is sometimes needed for documents that don't have any WBXML Public ID.
 */
WBXML_DECLARE(WB_BOOL) wbxml_parser_set_language(WBXMLParser *parser, WBXMLLanguage lang);

/**
 * @brief Set additionnal meta-information to help determining the Charset Encoding of the Document to parse
 * @param parser The WBXML Parser
 * @param charset The Charset MIBEnum
 * @return TRUE if Charset is set, FALSE otherwise
 * @note This information is only used if the Charset Encoding is not specified in WBXML Document:
 *       "The binary XML format contains a representation of the XML document character encoding.
 *        This is the WBXML equivalent of the XML document format encoding attribute,
 *        which is specified in the ?xml processing instruction ... In the case of
 *        an unknown encoding, transport meta-information should be used to determine the character
 *        encoding. If transport meta-information is unavailable, the default encoding of UTF-8
 *        should be assumed."
 */
WBXML_DECLARE(WB_BOOL) wbxml_parser_set_meta_charset(WBXMLParser *parser, WBXMLCharsetMIBEnum charset);

/**
 * @brief Get WBXML Public ID
 * @param parser The WBXML Parser
 * @return The WBXML Public ID of current parsing document
 */
WBXML_DECLARE(WB_ULONG) wbxml_parser_get_wbxml_public_id(WBXMLParser *parser);

/**
 * @brief Get XML Public ID
 * @param parser The WBXML Parser
 * @return The XML Public ID of current parsing document, or NULL if not found
 */
WBXML_DECLARE(const WB_UTINY *) wbxml_parser_get_xml_public_id(WBXMLParser *parser);

/**
 * @brief Get WBXML Version
 * @param parser The WBXML Parser
 * @return The WBXML Version of current parsing document
 */
WBXML_DECLARE(WBXMLVersion) wbxml_parser_get_wbxml_version(WBXMLParser *parser);

/**
 * @brief Return current parsing position in WBXML
 * @param parser The WBXML Parser
 * @return The parsing position in WBXML
 */
WBXML_DECLARE(WB_LONG) wbxml_parser_get_current_byte_index(WBXMLParser *parser);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_PARSER_H */
