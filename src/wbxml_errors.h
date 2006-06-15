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
 * @file wbxml_errors.h
 * @ingroup wbxml_errors
 *
 * @author Aymerick Jehanne <libwbxml@aymerick.com>
 * @date 02/11/18
 *
 * @brief WBXML Error Codes Handling
 */

#ifndef WBXML_ERRORS_H
#define WBXML_ERRORS_H


#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup wbxml_errors
 *  @{ 
 */

/**
 * @brief The WBXML Parser Errors enumeration
 */
typedef enum WBXMLError_e {
    /* Generic Errors */
    WBXML_OK = 0,       /**< No Error */
    WBXML_NOT_ENCODED,  /**< Not an error; just a special internal return code */
    WBXML_ERROR_ATTR_TABLE_UNDEFINED,
    WBXML_ERROR_BAD_DATETIME,
    WBXML_ERROR_BAD_PARAMETER,    
    WBXML_ERROR_INTERNAL,
    WBXML_ERROR_LANG_TABLE_UNDEFINED,
    WBXML_ERROR_NOT_ENOUGH_MEMORY,
    WBXML_ERROR_NOT_IMPLEMENTED,
    WBXML_ERROR_TAG_TABLE_UNDEFINED,
    WBXML_ERROR_B64_ENC,
#if defined( WBXML_SUPPORT_WV )
    WBXML_ERROR_WV_DATETIME_FORMAT,
#endif /* WBXML_SUPPORT_WV */
    WBXML_ERROR_NO_CHARSET_CONV,
    WBXML_ERROR_CHARSET_STR_LEN,
    /* WBXML Parser Errors */    
    WBXML_ERROR_ATTR_VALUE_TABLE_UNDEFINED,
    WBXML_ERROR_BAD_LITERAL_INDEX,
    WBXML_ERROR_BAD_NULL_TERMINATED_STRING_IN_STRING_TABLE,
    WBXML_ERROR_BAD_OPAQUE_LENGTH,
    WBXML_ERROR_EMPTY_WBXML,
    WBXML_ERROR_END_OF_BUFFER,
    WBXML_ERROR_ENTITY_CODE_OVERFLOW,
    WBXML_ERROR_EXT_VALUE_TABLE_UNDEFINED,
    WBXML_ERROR_INVALID_STRTBL_INDEX,
    WBXML_ERROR_LITERAL_NOT_NULL_TERMINATED_IN_STRING_TABLE,
    WBXML_ERROR_NOT_NULL_TERMINATED_INLINE_STRING,
    WBXML_ERROR_NULL_PARSER,
    WBXML_ERROR_NULL_STRING_TABLE,
    WBXML_ERROR_STRING_EXPECTED,
    WBXML_ERROR_STRTBL_LENGTH,   
    WBXML_ERROR_UNKNOWN_ATTR,
    WBXML_ERROR_UNKNOWN_ATTR_VALUE,
    WBXML_ERROR_UNKNOWN_EXTENSION_TOKEN,
    WBXML_ERROR_UNKNOWN_EXTENSION_VALUE,
    WBXML_ERROR_UNKNOWN_PUBLIC_ID,
    WBXML_ERROR_UNKNOWN_TAG,
    WBXML_ERROR_UNVALID_MBUINT32,
#if defined( WBXML_SUPPORT_WV )
    WBXML_ERROR_WV_INTEGER_OVERFLOW,
#endif /* WBXML_SUPPORT_WV */
    /* WBXML Encoder Errors */
    WBXML_ERROR_ENCODER_APPEND_DATA,
    WBXML_ERROR_STRTBL_DISABLED,
    WBXML_ERROR_UNKNOWN_XML_LANGUAGE,
    WBXML_ERROR_XML_NODE_NOT_ALLOWED,
    WBXML_ERROR_XML_NULL_ATTR_NAME,
    WBXML_ERROR_XML_PARSING_FAILED,
#if defined( WBXML_SUPPORT_SYNCML )
    WBXML_ERROR_XML_DEVINF_CONV_FAILED,
#endif /* WBXML_SUPPORT_WV */
    WBXML_ERROR_NO_XMLPARSER,
    WBXML_ERROR_XMLPARSER_OUTPUT_UTF16
} WBXMLError;


/**
 * @brief Return a String describing an Error Code
 * @param error_code WBXML error code
 * @return The error description
 */
WBXML_DECLARE(const WB_UTINY *) wbxml_errors_string(WBXMLError error_code);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_ERRORS_H */
