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
 * @file wbxml_errors.h
 * @ingroup wbxml_errors
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/11/18
 *
 * @brief WBXML Error Codes Handling
 */

#ifndef WBXML_ERRORS_H
#define WBXML_ERRORS_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include "wbxml_config.h"
#include "wbxml_defines.h"

/** @addtogroup wbxml_errors
 *  @{ 
 */

/**
 * @brief The WBXML Parser Errors enumeration
 */
typedef enum WBXMLError_e {
    /* Generic Errors */
    WBXML_OK = 0,       /**< No Error */
    WBXML_NOT_ENCODED = 1,  /**< Not an error; just a special internal return code */
    WBXML_ERROR_ATTR_TABLE_UNDEFINED = 10,
    WBXML_ERROR_BAD_DATETIME =         11,
    WBXML_ERROR_BAD_PARAMETER =        12,    
    WBXML_ERROR_INTERNAL =             13,
    WBXML_ERROR_LANG_TABLE_UNDEFINED = 14,
    WBXML_ERROR_NOT_ENOUGH_MEMORY =    15,
    WBXML_ERROR_NOT_IMPLEMENTED =      16,
    WBXML_ERROR_TAG_TABLE_UNDEFINED =  17,
    WBXML_ERROR_B64_ENC =              18,
    WBXML_ERROR_B64_DEC =              19,
#if defined( WBXML_SUPPORT_WV )
    WBXML_ERROR_WV_DATETIME_FORMAT = 20,
#endif /* WBXML_SUPPORT_WV */
    WBXML_ERROR_NO_CHARSET_CONV =   30,
    WBXML_ERROR_CHARSET_STR_LEN =   31,
    WBXML_ERROR_CHARSET_UNKNOWN =   32,
    WBXML_ERROR_CHARSET_CONV_INIT = 33,
    WBXML_ERROR_CHARSET_CONV =      34,
    WBXML_ERROR_CHARSET_NOT_FOUND = 35,
    /* WBXML Parser Errors */    
    WBXML_ERROR_ATTR_VALUE_TABLE_UNDEFINED =                  40,
    WBXML_ERROR_BAD_LITERAL_INDEX =                           41,
    WBXML_ERROR_BAD_NULL_TERMINATED_STRING_IN_STRING_TABLE =  42,
    WBXML_ERROR_BAD_OPAQUE_LENGTH =                           43,
    WBXML_ERROR_EMPTY_WBXML =                                 44,
    WBXML_ERROR_END_OF_BUFFER =                               45,
    WBXML_ERROR_ENTITY_CODE_OVERFLOW =                        46,
    WBXML_ERROR_EXT_VALUE_TABLE_UNDEFINED =                   47,
    WBXML_ERROR_INVALID_STRTBL_INDEX =                        48,
    WBXML_ERROR_LITERAL_NOT_NULL_TERMINATED_IN_STRING_TABLE = 49,
    WBXML_ERROR_NOT_NULL_TERMINATED_INLINE_STRING =           50,
    WBXML_ERROR_NULL_PARSER =                                 51,
    WBXML_ERROR_NULL_STRING_TABLE =                           52,
    WBXML_ERROR_STRING_EXPECTED =                             53,
    WBXML_ERROR_STRTBL_LENGTH =                               54,   
    WBXML_ERROR_UNKNOWN_ATTR =            60,
    WBXML_ERROR_UNKNOWN_ATTR_VALUE =      61,
    WBXML_ERROR_UNKNOWN_EXTENSION_TOKEN = 62,
    WBXML_ERROR_UNKNOWN_EXTENSION_VALUE = 63,
    WBXML_ERROR_UNKNOWN_PUBLIC_ID =       64,
    WBXML_ERROR_UNKNOWN_TAG =             65,
    WBXML_ERROR_UNVALID_MBUINT32 = 70,
#if defined( WBXML_SUPPORT_WV )
    WBXML_ERROR_WV_INTEGER_OVERFLOW = 80,
#endif /* WBXML_SUPPORT_WV */
    /* WBXML Encoder Errors */
    WBXML_ERROR_ENCODER_APPEND_DATA = 90,
    WBXML_ERROR_STRTBL_DISABLED =      100,
    WBXML_ERROR_UNKNOWN_XML_LANGUAGE = 101,
    WBXML_ERROR_XML_NODE_NOT_ALLOWED = 102,
    WBXML_ERROR_XML_NULL_ATTR_NAME =   103,
    WBXML_ERROR_XML_PARSING_FAILED =   104,
#if defined( WBXML_SUPPORT_SYNCML )
    WBXML_ERROR_XML_DEVINF_CONV_FAILED = 110,
#endif /* WBXML_SUPPORT_WV */
    WBXML_ERROR_NO_XMLPARSER =           120,
    WBXML_ERROR_XMLPARSER_OUTPUT_UTF16 = 121,
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
