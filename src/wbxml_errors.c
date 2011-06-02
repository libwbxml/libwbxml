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
 * @file wbxml_errors.c
 * @ingroup wbxml_errors
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/11/18
 *
 * @brief WBXML Error Codes Handling
 */

#include "wbxml_errors.h"
#include <stdio.h>


/**
 * @brief Error Code item
 */
typedef struct WBXMLErrorCodeItem_s {
    WBXMLError     code;    /**< Error Code */
    const WB_TINY *string;  /**< Error Description */
} WBXMLErrorCodeItem;


/**
 * @brief Error Code table
 */
static const WBXMLErrorCodeItem error_table [] = {
    /* Generic Errors */
    { WBXML_OK,                                 "No Error" },
    { WBXML_NOT_ENCODED,                        "Not Encoded" },
    { WBXML_ERROR_ATTR_TABLE_UNDEFINED,         "Attribute Table Undefined" },
    { WBXML_ERROR_BAD_DATETIME,                 "Bad %Datetime Format" },
    { WBXML_ERROR_BAD_PARAMETER,                "Bad Parameter" },
    { WBXML_ERROR_INTERNAL,                     "Internal Error" },
    { WBXML_ERROR_LANG_TABLE_UNDEFINED,         "Languages Table Undefined" },
    { WBXML_ERROR_NOT_ENOUGH_MEMORY,            "Not Enough Memory" },
    { WBXML_ERROR_NOT_IMPLEMENTED,              "Not Implemented" },
    { WBXML_ERROR_TAG_TABLE_UNDEFINED,          "Tag Table Undefined" },
    { WBXML_ERROR_B64_ENC,                      "Failed to encode Base64" },
    { WBXML_ERROR_B64_DEC,                      "Failed to decode Base64" },
#if defined( WBXML_SUPPORT_WV )
    { WBXML_ERROR_WV_DATETIME_FORMAT,           "Bad Wireless-Village Date and Time Format" },
#endif /* WBXML_SUPPORT_WV */
    { WBXML_ERROR_NO_CHARSET_CONV,              "No built-in charset convertor (Compiled without libiconv)" },
    { WBXML_ERROR_CHARSET_STR_LEN,              "Bad string length, can't convert" },
    /* WBXML Parser Errors */
    { WBXML_ERROR_ATTR_VALUE_TABLE_UNDEFINED,   "Attribute Value Table Undefined" },
    { WBXML_ERROR_BAD_LITERAL_INDEX,            "Bad Literal Index" },
    { WBXML_ERROR_BAD_NULL_TERMINATED_STRING_IN_STRING_TABLE,    "Not NULL Terminated String in String Table" },
    { WBXML_ERROR_BAD_OPAQUE_LENGTH,            "Bad Opaque Length" },
    { WBXML_ERROR_EMPTY_WBXML,                  "Empty WBXML" },    
    { WBXML_ERROR_END_OF_BUFFER,                "Unexpected End Of WBXML Buffer" },
    { WBXML_ERROR_ENTITY_CODE_OVERFLOW,         "Entity Code Overflow" },
    { WBXML_ERROR_EXT_VALUE_TABLE_UNDEFINED,    "Extension Value Table Undefined" },
    { WBXML_ERROR_INVALID_STRTBL_INDEX,         "Invalid String Table Index" },
    { WBXML_ERROR_LITERAL_NOT_NULL_TERMINATED_IN_STRING_TABLE,    "Literal Not NULL Terminated in String Table" },
    { WBXML_ERROR_NOT_NULL_TERMINATED_INLINE_STRING,             "Not NULL Terminated Inline String" },
    { WBXML_ERROR_NULL_PARSER,                  "Null Parser" },
    { WBXML_ERROR_NULL_STRING_TABLE,            "No String Table In Document" },
    { WBXML_ERROR_STRING_EXPECTED,              "String Expected" },
    { WBXML_ERROR_STRTBL_LENGTH,                "Bad String Table Length" },
    { WBXML_ERROR_UNKNOWN_ATTR,                 "Unknown Attribute" },
    { WBXML_ERROR_UNKNOWN_ATTR_VALUE,           "Unknown Attribute Value" },
    { WBXML_ERROR_UNKNOWN_EXTENSION_TOKEN,      "Unknown Extension Token" },
    { WBXML_ERROR_UNKNOWN_EXTENSION_VALUE,      "Unknown Extension Value token" },
    { WBXML_ERROR_UNKNOWN_PUBLIC_ID,            "Unknown Public ID" },    
    { WBXML_ERROR_UNKNOWN_TAG,                  "Unknown Tag" },
    { WBXML_ERROR_UNVALID_MBUINT32,             "Unvalid MultiByte UINT32" },
#if defined( WBXML_SUPPORT_WV )
    { WBXML_ERROR_WV_INTEGER_OVERFLOW,          "Wireless-Village Integer Overflow" },
#endif /* WBXML_SUPPORT_WV */
    /* WBXML Encoder Errors */
    { WBXML_ERROR_ENCODER_APPEND_DATA,          "Can't append data to output buffer" },
    { WBXML_ERROR_STRTBL_DISABLED,              "String Table generation disabled: can't encode Literal" },
    { WBXML_ERROR_UNKNOWN_XML_LANGUAGE,		"The XML language is unknown." },
    { WBXML_ERROR_XML_NODE_NOT_ALLOWED,         "XML Node Type not allowed" },
    { WBXML_ERROR_XML_NULL_ATTR_NAME,           "NULL XML Attribute Name" },
    { WBXML_ERROR_XML_PARSING_FAILED,           "Parsing of XML Document Failed" },
#if defined( WBXML_SUPPORT_SYNCML )
    { WBXML_ERROR_XML_DEVINF_CONV_FAILED,       "The conversion of a XML DevInf document failed" },
#endif /* WBXML_SUPPORT_WV */
    { WBXML_ERROR_NO_XMLPARSER,                 "Can't parse XML (Compiled without Expat): XML to WBXML conversion not possible" },
    { WBXML_ERROR_XMLPARSER_OUTPUT_UTF16,       "XML Parser (Expat) is outputting UTF-16, so you have two choices :\n"
                                              "  - Get the iconv library (http://www.gnu.org/software/libiconv/)\n"
                                              "  - Use a version of Expat that output UTF-8" },
    { WBXML_ERROR_CHARSET_UNKNOWN,              "The character set is unknown."},
    { WBXML_ERROR_CHARSET_CONV_INIT,            "The converter for the character set cannot be initialized."},
    { WBXML_ERROR_CHARSET_CONV,                 "The character conversion failed."},
    { WBXML_ERROR_CHARSET_NOT_FOUND,            "The character set cannot be found."}
};

#define ERROR_TABLE_SIZE ((WB_ULONG) (sizeof(error_table) / sizeof(error_table[0])))


/***************************************************
 *    Public Functions
 */

WBXML_DECLARE(const WB_UTINY *) wbxml_errors_string(WBXMLError error_code)
{
    WB_ULONG i;

    for (i=0; i < ERROR_TABLE_SIZE; i++) {
        if (error_table[i].code == error_code)
            return (const WB_UTINY *)error_table[i].string;
    }

    fprintf(stderr, "PACKAGE_NAME: Unknown error code %d.\n", error_code);

    return (const WB_UTINY *)"Unknown Error Code";
}
