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
 * @file wbxml_conv.h
 * @ingroup wbxml_conv
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 03/02/23
 *
 * @brief WBXML Convertion Library (XML to WBXML, and WBXML to XML)
 */

#ifndef WBXML_CONV_H
#define WBXML_CONV_H

#include "wbxml.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup wbxml_conv
 *  @{
 */

/** WBXML Versions (WBXML tokens) */
typedef enum WBXMLVersion_e {
    WBXML_VERSION_UNKNOWN = -1, /**< Unknown WBXML Version */
    WBXML_VERSION_10 = 0x00,    /**< WBXML 1.0 Token */
    WBXML_VERSION_11 = 0x01,    /**< WBXML 1.1 Token */
    WBXML_VERSION_12 = 0x02,    /**< WBXML 1.2 Token */
    WBXML_VERSION_13 = 0x03     /**< WBXML 1.3 Token */
} WBXMLVersion;


/*
 * Possible Compilation Flags:
 * ---------------------------
 *
 *      WBXML_SUPPORT_WML
 *      WBXML_SUPPORT_WTA
 *      WBXML_SUPPORT_SI
 *      WBXML_SUPPORT_SL
 *      WBXML_SUPPORT_CO
 *      WBXML_SUPPORT_PROV
 *      WBXML_SUPPORT_EMN
 *      WBXML_SUPPORT_DRMREL
 *      WBXML_SUPPORT_OTA_SETTINGS
 *      WBXML_SUPPORT_SYNCML
 *      WBXML_SUPPORT_WV 
 *      WBXML_SUPPORT_AIRSYNC 
 *      WBXML_SUPPORT_CONML 
 */


/** Supported WBXML Languages */
typedef enum WBXMLLanguage_e {
    WBXML_LANG_UNKNOWN = 0,     /**< Unknown / Not Specified */

    /* WAP */
#if defined( WBXML_SUPPORT_WML )
    WBXML_LANG_WML10 = 1101,           /**< WML 1.0 */
    WBXML_LANG_WML11 = 1102,           /**< WML 1.1 */
    WBXML_LANG_WML12 = 1103,           /**< WML 1.2 */
    WBXML_LANG_WML13 = 1104,           /**< WML 1.3 */
#endif /* WBXML_SUPPORT_WML */

#if defined( WBXML_SUPPORT_WTA )
    WBXML_LANG_WTA10     = 1201,           /**< WTA 1.0 */
    WBXML_LANG_WTAWML12  = 1202,        /**< WTAWML 1.2 */
    WBXML_LANG_CHANNEL11 = 1203,       /**< CHANNEL 1.1 */
    WBXML_LANG_CHANNEL12 = 1204,       /**< CHANNEL 1.2 */ 
#endif /* WBXML_SUPPORT_WTA */

#if defined( WBXML_SUPPORT_SI )
    WBXML_LANG_SI10 = 1301,            /**< SI 1.0 */
#endif /* WBXML_SUPPORT_SI */

#if defined( WBXML_SUPPORT_SL )
    WBXML_LANG_SL10 = 1401,            /**< SL 1.0 */
#endif /* WBXML_SUPPORT_SL */

#if defined( WBXML_SUPPORT_CO )
    WBXML_LANG_CO10 = 1501,            /**< CO 1.0 */
#endif /* WBXML_SUPPORT_CO */

#if defined( WBXML_SUPPORT_PROV )
    WBXML_LANG_PROV10 = 1601,          /**< PROV 1.0 */
#endif /* WBXML_SUPPORT_PROV */

#if defined( WBXML_SUPPORT_EMN )
    WBXML_LANG_EMN10 = 1701,           /**< EMN 1.0 */
#endif /* WBXML_SUPPORT_EMN */

#if defined( WBXML_SUPPORT_DRMREL )
    WBXML_LANG_DRMREL10 = 1801,        /**< DRMREL 1.0 */
#endif /* WBXML_SUPPORT_DRMREL */

#if defined( WBXML_SUPPORT_OTA_SETTINGS )
    /* Ericsson / Nokia OTA Settings v7.0 */
    WBXML_LANG_OTA_SETTINGS = 1901,    /**< OTA Settings */
#endif /* WBXML_SUPPORT_OTA_SETTINGS */

    /* SyncML */
#if defined( WBXML_SUPPORT_SYNCML )
    WBXML_LANG_SYNCML_SYNCML10 = 2001, /**< SYNCML 1.0 */
    WBXML_LANG_SYNCML_DEVINF10 = 2002, /**< DEVINF 1.0 */
    WBXML_LANG_SYNCML_METINF10 = 2003, /**< METINF 1.0 */    
    
    WBXML_LANG_SYNCML_SYNCML11 = 2101, /**< SYNCML 1.1 */
    WBXML_LANG_SYNCML_DEVINF11 = 2102, /**< DEVINF 1.1 */
    WBXML_LANG_SYNCML_METINF11 = 2103, /**< METINF 1.1 */
    
    WBXML_LANG_SYNCML_SYNCML12 = 2201, /**< SYNCML 1.2 */
    WBXML_LANG_SYNCML_DEVINF12 = 2202, /**< DEVINF 1.2 */
    WBXML_LANG_SYNCML_METINF12 = 2203, /**< METINF 1.2 */
    WBXML_LANG_SYNCML_DMDDF12  = 2204, /**< DMDDF  1.2 */
#endif /* WBXML_SUPPORT_SYNCML */

    /* Wireless-Village */
#if defined( WBXML_SUPPORT_WV )
    WBXML_LANG_WV_CSP11 = 2301,        /**< WV CSP 1.1 */
    WBXML_LANG_WV_CSP12 = 2302,        /**< WV CSP 1.2 */
#endif /* WBXML_SUPPORT_WV */

    /* Microsoft AirSync */
#if defined( WBXML_SUPPORT_AIRSYNC )
    WBXML_LANG_AIRSYNC    = 2401,      /**< AirSync */
    WBXML_LANG_ACTIVESYNC = 2402,      /**< ActiveSync */
#endif /* WBXML_SUPPORT_AIRSYNC */

    /* Nokia ConML */
#if defined( WBXML_SUPPORT_CONML )
    WBXML_LANG_CONML = 2501            /**< ConML */
#endif /* WBXML_SUPPORT_CONML */
} WBXMLLanguage;


/** Supported WBXML Charsets MIBEnum */
typedef enum WBXMLCharsetMIBEnum_e {
  WBXML_CHARSET_UNKNOWN         = 0,       /**< Unknown Charset */
  WBXML_CHARSET_US_ASCII        = 3,       /**< US-ASCII */
  WBXML_CHARSET_ISO_8859_1      = 4,       /**< ISO-8859-1 */
  WBXML_CHARSET_ISO_8859_2      = 5,       /**< ISO-8859-2 */
  WBXML_CHARSET_ISO_8859_3      = 6,       /**< ISO-8859-3 */
  WBXML_CHARSET_ISO_8859_4      = 7,       /**< ISO-8859-4 */
  WBXML_CHARSET_ISO_8859_5      = 8,       /**< ISO-8859-5 */
  WBXML_CHARSET_ISO_8859_6      = 9,       /**< ISO-8859-6 */
  WBXML_CHARSET_ISO_8859_7      = 10,      /**< ISO-8859-7 */
  WBXML_CHARSET_ISO_8859_8      = 11,      /**< ISO-8859-8 */
  WBXML_CHARSET_ISO_8859_9      = 12,      /**< ISO-8859-9 */
  WBXML_CHARSET_SHIFT_JIS       = 17,      /**< Shift_JIS */
  WBXML_CHARSET_UTF_8           = 106,     /**< UTF-8 */
  WBXML_CHARSET_ISO_10646_UCS_2 = 1000,    /**< ISO-10646-UCS-2 */
  WBXML_CHARSET_UTF_16          = 1015,    /**< UTF-16 */
  WBXML_CHARSET_BIG5            = 2026     /**< Big5 */
} WBXMLCharsetMIBEnum;


/**
 * @brief Type of XML Generation
 * @note Canonical Form is defined here: http://www.jclark.com/xml/canonxml.html
 */
typedef enum WBXMLGenXMLType_e {
    WBXML_GEN_XML_COMPACT   = 0,  /**< Compact XML generation */
    WBXML_GEN_XML_INDENT    = 1,  /**< Indented XML generation */
    WBXML_GEN_XML_CANONICAL = 2   /**< Canonical XML generation */
} WBXMLGenXMLType;


/**
 * @brief Parameters when generating an XML document
 */
typedef struct WBXMLGenXMLParams_s {
    WBXMLGenXMLType gen_type;    /**< WBXML_GEN_XML_COMPACT | WBXML_GEN_XML_INDENT | WBXML_GEN_XML_CANONICAL (Default: WBXML_GEN_XML_INDENT) */
    WBXMLLanguage lang;          /**< Force document Language (overwrite document Public ID) */
    WBXMLCharsetMIBEnum charset; /**< Set document Language (does not overwrite document character set) */
    WB_UTINY indent;             /**< Indentation Delta, when using WBXML_GEN_XML_INDENT Generation Type (Default: 0) */
    WB_BOOL keep_ignorable_ws;   /**< Keep Ignorable Whitespaces (Default: FALSE) */
} WBXMLGenXMLParams;

/**
 * @brief Parameters when generating a WBXML document
 */
typedef struct WBXMLGenWBXMLParams_s {
    WBXMLVersion wbxml_version; /**< WBXML Version */
    WB_BOOL keep_ignorable_ws;  /**< Keep Ignorable Whitespaces (Default: FALSE) */
    WB_BOOL use_strtbl;         /**< Generate String Table (Default: TRUE) */
    WB_BOOL produce_anonymous;  /**< Produce an anonymous document (Default: FALSE) */
} WBXMLGenWBXMLParams;

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
 * @return WBXML_OK if conversion succeeded, an Error Code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_conv_wbxml2xml_withlen(WB_UTINY  *wbxml,
                                                       WB_ULONG   wbxml_len,
                                                       WB_UTINY **xml,
                                                       WB_ULONG  *xml_len,
                                                       WBXMLGenXMLParams *params) LIBWBXML_DEPRECATED;

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
 * @return WBXML_OK if conversion succeeded, an Error Code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_conv_xml2wbxml_withlen(WB_UTINY  *xml,
                                                       WB_ULONG   xml_len,
                                                       WB_UTINY **wbxml,
                                                       WB_ULONG  *wbxml_len,
                                                       WBXMLGenWBXMLParams *params) LIBWBXML_DEPRECATED;

/**
 * @description This is a container for the WBXML to XML conversion parameters.
 *              An object style is used because it is much better expandable
 *              in terms of downward binary compatibility.
 */
typedef struct WBXMLConvWBXML2XML_s WBXMLConvWBXML2XML;

/**
 * @brief Create a new WBXML to XML converter with the default configuration.
 * @param conv [out] a reference to the pointer of the new converter
 * @return WBXML_OK if conversion succeeded, an Error Code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_conv_wbxml2xml_create(WBXMLConvWBXML2XML **conv);

/**
 * @brief Set the XML generation type (default: WBXML_GEN_XML_INDENT).
 * @param conv     [in] the converter
 * @param gen_type [in] generation type
 */
WBXML_DECLARE(void) wbxml_conv_wbxml2xml_set_gen_type(WBXMLConvWBXML2XML *conv, WBXMLGenXMLType gen_type);

/**
 * @brief Set the used WBXML language.
 *        The language is usually detected by the specified public ID in the document.
 *        If the public ID is set then it overrides the language.
 * @param conv [in] the converter
 * @param lang [in] language (e.g. SYNCML12)
 */
WBXML_DECLARE(void) wbxml_conv_wbxml2xml_set_language(WBXMLConvWBXML2XML *conv, WBXMLLanguage lang);

/**
 * @brief Set the used character set.
 *        The default character set is UTF-8.
 *        If the document specifies a character set by it own
 *        then this character set overrides the parameter charset.
 * @param conv    [in] the converter
 * @param charset [in] the character set
 */
WBXML_DECLARE(void) wbxml_conv_wbxml2xml_set_charset(WBXMLConvWBXML2XML *conv, WBXMLCharsetMIBEnum charset);

/**
 * @brief Set the indent of the generated XML document (please see EXPAT default).
 * @param conv   [in] the converter
 * @param indent [in] the number of blanks
 */
WBXML_DECLARE(void) wbxml_conv_wbxml2xml_set_indent(WBXMLConvWBXML2XML *conv, WB_UTINY indent);

/**
 * @brief Enable whitespace preservation (default: FALSE).
 * @param conv     [in] the converter
 */
WBXML_DECLARE(void) wbxml_conv_wbxml2xml_enable_preserve_whitespaces(WBXMLConvWBXML2XML *conv);

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
                                                   WB_UTINY  *xml,
                                                   WB_ULONG   xml_len,
                                                   WB_UTINY **wbxml,
                                                   WB_ULONG  *wbxml_len);

/**
 * @brief Destroy the converter object.
 * @param [in] the converter
 */
WBXML_DECLARE(void) wbxml_conv_wbxml2xml_destroy(WBXMLConvWBXML2XML *conv);

/**
 * @description This is a container for the XML to WBXML conversion parameters.
 *              An object style is used because it is much better expandable
 *              in terms of downward binary compatibility.
 */
typedef struct WBXMLConvXML2WBXML_s WBXMLConvXML2WBXML;

/**
 * @brief Create a new WBXML to XML converter with the default configuration.
 * @param conv [out] a reference to the pointer of the new converter
 * @return WBXML_OK if conversion succeeded, an Error Code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_conv_xml2wbxml_create(WBXMLConvXML2WBXML **conv);

/**
 * @brief Set the WBXML version (default: 1.3).
 * @param conv   [in] the converter
 * @param indent [in] the number of blanks
 */
WBXML_DECLARE(void) wbxml_conv_xml2wbxml_set_version(WBXMLConvXML2WBXML *conv,
                                                     WBXMLVersion wbxml_version);

/**
 * @brief Enable whitespace preservation (default: FALSE/DISABLED).
 * @param conv     [in] the converter
 */
WBXML_DECLARE(void) wbxml_conv_xml2wbxml_enable_preserve_whitespaces(WBXMLConvXML2WBXML *conv);

/**
 * @brief Disable string table (default: TRUE/ENABLED).
 * @param conv     [in] the converter
 */
WBXML_DECLARE(void) wbxml_conv_xml2wbxml_disable_string_table(WBXMLConvXML2WBXML *conv);

/**
 * @desription: Disable public ID (default: TRUE/ENABLED).
 *              Usually you don't want to produce WBXML documents which are
 *              really anonymous. You want a known public ID or a DTD name
 *              to determine the document type. Some specifications like
 *              Microsoft's ActiveSync explicitely require fully anonymous
 *              WBXML documents. If you need this then you must disable
 *              the public ID mechanism.
 * @param conv     [in] the converter
 */
WBXML_DECLARE(void) wbxml_conv_xml2wbxml_disable_public_id(WBXMLConvXML2WBXML *conv);

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
                                                   WB_ULONG  *wbxml_len);

/**
 * @brief Destroy the converter object.
 * @param [in] the converter
 */
WBXML_DECLARE(void) wbxml_conv_xml2wbxml_destroy(WBXMLConvXML2WBXML *conv);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_CONV_H */
