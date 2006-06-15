/*
 * libwbxml, the WBXML Library.
 * Copyright (C) 2002-2005 Aymerick Jehanne <aymerick@jehanne.org>
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
 * Contact: libwbxml@aymerick.com
 * Home: http://libwbxml.aymerick.com
 */

/**
 * @file wbxml_conv.h
 * @ingroup wbxml_conv
 *
 * @author Aymerick Jehanne <libwbxml@aymerick.com>
 * @date 03/02/23
 *
 * @brief WBXML Convertion Library (XML to WBXML, and WBXML to XML)
 */

#ifndef WBXML_CONV_H
#define WBXML_CONV_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup wbxml_conv
 *  @{
 */

/**
 * Wrapper around wbxml_conv_wbxml2_withlen()
 *
 * This macro is provided for backward compatibility. You can use it if you are
 * sure that the output XML document will be encoded in a charset that is NULL
 * terminated and that can't contains any NULL character in it. For example
 * this macro works for US-ASCII or UTF-8 encoded documents, but not for UTF-16
 * encoded documents.
 */
#define wbxml_conv_wbxml2xml(a,b,c,d) wbxml_conv_wbxml2xml_withlen(a,b,c,NULL,d)

/**
 * @brief Convert WBXML to XML
 * @param wbxml     [in] WBXML Document to convert
 * @param wbxml_len [in] Length of WBXML Document
 * @param xml       [out] Resulting XML Document
 * @param xml_len   [out] XML Document length
 * @param params    [in] Parameters (if NULL, default values are used)
 * @return WBXML_OK if convertion succeeded, an Error Code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_conv_wbxml2xml_withlen(WB_UTINY  *wbxml,
                                                       WB_ULONG   wbxml_len,
                                                       WB_UTINY **xml,
                                                       WB_ULONG  *xml_len,
                                                       WBXMLGenXMLParams *params);

/**
 * Wrapper around wbxml_conv_xml2wbxml_withlen()
 *
 * This macro is provided for backward compatibility. You can use it if you are
 * sure that the input XML document is encoded in a charset that is NULL terminated
 * and that can't contains any NULL character in it. For example this macro
 * works for US-ASCII or UTF-8 encoded documents, but not for UTF-16 encoded
 * documents.
 */
#define wbxml_conv_xml2wbxml(a,b,c,d) wbxml_conv_xml2wbxml_withlen(a,WBXML_STRLEN(a),b,c,d)

/**
 * @brief Convert XML to WBXML
 * @param xml       [in] XML Document to convert
 * @param xml_len   [in] Length of XML Document
 * @param wbxml     [out] Resulting WBXML Document
 * @param wbxml_len [out] Length of resulting WBXML Document
 * @param params    [in] Parameters (if NULL, default values are used)
 * @return WBXML_OK if convertion succeeded, an Error Code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_conv_xml2wbxml_withlen(WB_UTINY  *xml,
                                                       WB_ULONG   xml_len,
                                                       WB_UTINY **wbxml,
                                                       WB_ULONG  *wbxml_len,
                                                       WBXMLGenWBXMLParams *params);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_CONV_H */
