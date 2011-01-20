/*
 * libwbxml, the WBXML Library.
 * Copyright (C) 2002-2008 Aymerick Jehanne <aymerick@jehanne.org>
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
 * @file wbxml.h
 * @ingroup wbxml
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/11/11
 *
 * @brief WBXML Library Main Header
 */

#ifndef WBXML_H
#define WBXML_H

#include <wbxml_config.h>

#if defined( __SYMBIAN32__ )
/* For basic Symbian Types */
#include <e32def.h>
#endif /* __SYMBIAN32__ */

/*
 * This sytem includes are here instead of the *.c files because
 * we want them to be included AFTER 'e32def.h' on Symbian. If not so,
 * a lot of Warnings are displayed ('NULL' : macro redefinition)
 */
#include <stdlib.h>
#include <string.h>


/** @addtogroup wbxml
 *  @{ 
 */

/* WBXML Lib basic types redefinition */
#define WB_BOOL unsigned char
#define WB_UTINY unsigned char
#define WB_TINY char
#define WB_ULONG unsigned int
#define WB_LONG int

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL
#define NULL 0
#endif

/* Define NULL string */
#define WBXML_UTINY_NULL_STRING ((WB_UTINY *)"")

/* WBXML Lib string functions */
#define WBXML_STRLEN(a) strlen((const WB_TINY*)a)
#define WBXML_STRCMP(a,b) strcmp((const WB_TINY*)a,(const WB_TINY*)b)
#define WBXML_STRNCMP(a,b,c) strncmp((const WB_TINY*)a,(const WB_TINY*)b,c)
#define WBXML_STRSTR(a,b) strstr((const WB_TINY*)a,(const WB_TINY*)b)
#if defined( WIN32 )
#define WBXML_STRCASECMP(a,b) _stricmp((const WB_TINY*)a,(const WB_TINY*)b)
#else
#define WBXML_STRCASECMP(a,b) strcasecmp((const WB_TINY*)a,(const WB_TINY*)b)
#endif /* WIN32 */

#define WBXML_ISDIGIT(a) isdigit(a)

/* For DLL exported functions */
#if defined( __SYMBIAN32__ )
#define WBXML_DECLARE(type) EXPORT_C type
#define WBXML_DECLARE_NONSTD(type) EXPORT_C type
#else  /* __SYMBIAN32__ */
#if defined( WIN32 )
#define WBXML_DECLARE(type) __declspec(dllexport) type __stdcall
#define WBXML_DECLARE_NONSTD(type) __declspec(dllexport) type
#else  /* WIN32 */
#define WBXML_DECLARE(type) type
#define WBXML_DECLARE_NONSTD(type) type
#endif /* WIN32 */
#endif /* __SYMBIAN32__ */

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
    WBXML_LANG_AIRSYNC = 2401,         /**< AirSync */
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


/** @} */

#endif /* WBXML_H */
