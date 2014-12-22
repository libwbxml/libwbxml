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
 * @file wbxml_tree_clb_wbxml.h
 * @ingroup wbxml_tree
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 03/02/22
 *
 * @brief WBXML Tree Callbacks for WBXML Parser
 */

#ifndef WBXML_TREE_CLB_WBXML_H
#define WBXML_TREE_CLB_WBXML_H

#include "wbxml.h"
#include "wbxml_elt.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup wbxml_tree
 *  @{ 
 */

/**
 * @brief Start Document Callback
 * @param ctx User data
 * @param charset Charset (IANA code)
 * @param lang Language Table for this Document (cf: wbxml_table.[h|c])
 */
void wbxml_tree_clb_wbxml_start_document(void *ctx, WBXMLCharsetMIBEnum charset, const WBXMLLangEntry *lang);

/**
 * @brief End Document Callback
 * @param ctx User data
 */
void wbxml_tree_clb_wbxml_end_document(void *ctx);

/**
 * @brief Start Element Callback
 * @param ctx User data
 * @param element The Tag Element
 * @param atts The attributes attached to the element
 */
void wbxml_tree_clb_wbxml_start_element(void *ctx, WBXMLTag *element, WBXMLAttribute **atts);

/**
 * @brief End Element Callback
 * @param ctx User data
 * @param element The Tag Element
 */
void wbxml_tree_clb_wbxml_end_element(void *ctx, WBXMLTag *element);

/**
 * @brief Characters Callback
 * @param ctx User data
 * @param ch The characters
 * @param start The start position in the array
 * @param length The number of characters to read from the array
 */
void wbxml_tree_clb_wbxml_characters(void *ctx, WB_UTINY *ch, WB_ULONG start, WB_ULONG length);

/**
 * @brief Processing Instruction Callback
 * @param ctx User data
 * @param target The processing instruction target.
 * @param data The processing instruction data, or null if  none was supplied. The data does
 *            not include any whitespace separating it from the target
 */
void wbxml_tree_clb_wbxml_pi(void *ctx, const WB_UTINY *target, WB_UTINY *data);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_TREE_CLB_WBXML_H */
