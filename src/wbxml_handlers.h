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
 * @file wbxml_handlers.h
 * @ingroup wbxml_parser
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/06/09
 *
 * @brief WBXML Parser Handlers
 */

#ifndef WBXML_HANDLERS_H
#define WBXML_HANDLERS_H

#include "wbxml.h"
#include "wbxml_tables.h"
#include "wbxml_elt.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup wbxml_parser 
 *  @{ 
 */

/**
 * @brief Start Document Handler
 * @param ctx User data
 * @param charset Charset (The MIBenum from IANA character-sets assignements. See "http://www.iana.org/assignments/character-sets")
 * @param lang Language Table for this Document (cf: wbxml_table.[h|c])
 */
typedef void (*WBXMLStartDocumentHandler)(void *ctx, WBXMLCharsetMIBEnum charset, const WBXMLLangEntry *lang);

/**
 * @brief End Document handler
 * @param ctx User data
 */
typedef void (*WBXMLEndDocumentHandler)(void *ctx);

/**
 * @brief Start Element handler
 * @param ctx User data
 * @param localName The local tag name
 * @param atts The attributes attached to the element
 * @param empty Set to TRUE if this is an empty element
 */
typedef void (*WBXMLStartElementHandler)(void *ctx, WBXMLTag *localName, WBXMLAttribute **atts);

/**
 * @brief End Element handler
 * @param ctx User data
 * @param localName The local tag name
 * @param empty Set to TRUE if this is an empty element
 */
typedef void (*WBXMLEndElementHandler)(void *ctx, WBXMLTag *localName);

/**
 * @brief Characters handler
 * @param ctx User data
 * @param ch The characters
 * @param start The start position in the array
 * @param length The number of characters to read from the array
 */
typedef void (*WBXMLCharactersHandler)(void *ctx, WB_UTINY *ch, WB_ULONG start, WB_ULONG length);

/**
 * @brief Processing Instruction Handler
 * @param ctx User data
 * @param target The processing instruction target.
 * @param data The processing instruction data, or null if  none was supplied. The data does
 *            not include any whitespace separating it from the target
 */
typedef void (*WBXMLProcessingInstructionHandler)(void *ctx, const WB_UTINY *target, WB_UTINY *data);

/**
 * @brief WBXMLContentHandler structure
 */
typedef struct WBXMLContentHandler_s {
    WBXMLStartDocumentHandler start_document_clb;       /**< Start Document Handler */
    WBXMLEndDocumentHandler end_document_clb;           /**< End Document handler */
    WBXMLStartElementHandler start_element_clb;         /**< Start Element handler */
    WBXMLEndElementHandler end_element_clb;             /**< End Element handler */
    WBXMLCharactersHandler characters_clb;              /**< Characters handler */
    WBXMLProcessingInstructionHandler pi_clb;           /**< Processing Instruction Handler */
} WBXMLContentHandler;

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_HANDLERS_H */
