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
 * @file wbxml.h
 * @ingroup wbxml
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/11/11
 *
 * @brief WBXML Library Main Header
 */

#ifndef WBXML_DEFINES_H
#define WBXML_DEFINES_H

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
#define WBXML_STRNCASECMP(a,b,c) _strnicmp((const WB_TINY*)a,(const WB_TINY*)b,c)
#else
#define WBXML_STRCASECMP(a,b) strcasecmp((const WB_TINY*)a,(const WB_TINY*)b)
#define WBXML_STRNCASECMP(a,b,c) strncasecmp((const WB_TINY*)a,(const WB_TINY*)b,c)
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

#if __GNUC__ - 0 > 3 || (__GNUC__ - 0 == 3 && __GNUC_MINOR__ - 0 >= 2)
  /* gcc >= 3.2 */
# define LIBWBXML_DEPRECATED __attribute__ ((deprecated))
#elif defined(_MSC_VER) && (_MSC_VER >= 1300) && (_MSC_VER < 1400)
  /* msvc >= 7 */
# define LIBWBXML_DEPRECATED __declspec(deprecated)
#elif defined(_MSV_VER) && (_MSC_VER >= 1400)
  /* MS Visual Studio 2005 */
# define LIBWBXML_DEPRECATED
#else
# define LIBWBXML_DEPRECATED
#endif

/** Backward compatibility flag */
#define WBXML_BACKWARD_COMPAT

#if defined( WBXML_BACKWARD_COMPAT )

/* 0.9.2 */
#define WBXML_ENCODER_XML_GEN_COMPACT   WBXML_GEN_XML_COMPACT
#define WBXML_ENCODER_XML_GEN_INDENT    WBXML_GEN_XML_INDENT
#define WBXML_ENCODER_XML_GEN_CANONICAL WBXML_GEN_XML_CANONICAL

#define WBXMLEncoderXMLGenType   WBXMLGenXMLType     LIBWBXML_DEPRECATED
#define WBXMLConvWBXML2XMLParams WBXMLGenXMLParams   LIBWBXML_DEPRECATED
#define WBXMLConvXML2WBXMLParams WBXMLGenWBXMLParams LIBWBXML_DEPRECATED

// #define WBXMLTag      WBXMLTagName
// #define WBXMLTagEntry WBXMLTagNameEntry

#endif /* WBXML_BACKWARD_COMPAT */

/** @} */

#endif /* WBXML_DEFINES_H */
