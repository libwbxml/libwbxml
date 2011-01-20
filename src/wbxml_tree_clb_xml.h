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
 * @file wbxml_tree_clb_xml.h
 * @ingroup wbxml_tree
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 03/03/11
 *
 * @brief WBXML Tree Callbacks for XML Parser (Expat)
 */

#ifndef WBXML_TREE_CLB_XML_H
#define WBXML_TREE_CLB_XML_H

#include "wbxml.h"
#include <wbxml_config.h>

#if defined( HAVE_EXPAT )

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup wbxml_tree 
 *  @{ 
 */

/**
 * @brief XML Declarations Callback
 * @param ctx User data
 * @param version XML version
 * @param encoding XML encoding
 * @param standalone Value -1, 0, or 1 indicating respectively that there was no standalone parameter in the declaration, that it was given as no, or that it was given as yes.
 */
void wbxml_tree_clb_xml_decl(void *ctx, const XML_Char *version,
                             const XML_Char *encoding, int standalone);

/**
 * @brief Doctype Declaration Callback
 * @param ctx User data
 * @param doctypeName Doctype Name
 * @param sysid System ID
 * @param pubid Public ID
 * @param has_internal_subset Non-zero if the DOCTYPE declaration has an internal subset
 */
void wbxml_tree_clb_xml_doctype_decl(void *ctx, const XML_Char *doctypeName, 
                                     const XML_Char *sysid, const XML_Char *pubid, 
                                     int has_internal_subset);

/**
 * @brief Start Element Callback
 * @param ctx User data
 * @param localName The local tag name
 * @param attrs The attributes attached to the element
 */
void wbxml_tree_clb_xml_start_element(void *ctx, const XML_Char *localName, const XML_Char **attrs);

/**
 * @brief End Element Callback
 * @param ctx User data
 * @param localName The local tag name
 */
void wbxml_tree_clb_xml_end_element(void *ctx, const XML_Char *localName);

/**
 * @brief Start of CDATA Section Callback
 * @param ctx User data
 */
void wbxml_tree_clb_xml_start_cdata(void *ctx);

/**
 * @brief End of CDATA Section Callback
 * @param ctx User data
 */
void wbxml_tree_clb_xml_end_cdata(void *ctx);

/**
 * @brief Characters Callback
 * @param ctx User data
 * @param ch The characters array
 * @param len The number of characters to read from the array
 */
void wbxml_tree_clb_xml_characters(void *ctx, const XML_Char *ch, int len);

/**
 * @brief Processing Instruction Callback
 * @param ctx User data
 * @param target The processing instruction target.
 * @param data The processing instruction data, or null if  none was supplied. The data does
 *             not include any whitespace separating it from the target
 */
void wbxml_tree_clb_xml_pi(void *ctx, const XML_Char *target, const XML_Char *data);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* HAVE_EXPAT */

#endif /* WBXML_TREE_CLB_XML_H */
