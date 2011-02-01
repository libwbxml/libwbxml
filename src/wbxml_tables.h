/*
 * libwbxml, the WBXML Library.
 * Copyright (C) 2002-2008 Aymerick Jehanne <aymerick@jehanne.org>
 * Copyright (C) 2009-2011 Michael Bell <michael.bell@opensync.org>
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
 * @file wbxml_tables.h
 * @ingroup wbxml_tables
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/03/17
 *
 * @brief WBXML Tables
 */

#ifndef WBXML_TABLES_H
#define WBXML_TABLES_H

#include "wbxml.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup wbxml_tables 
 *  @{ 
 */

/****************************************************
 *    WBXML Public IDs (http://www.wapforum.org/wina)
 */

#define WBXML_PUBLIC_ID_UNKNOWN   0x01

/* WAP */
#define WBXML_PUBLIC_ID_WML10     0x02
#define WBXML_PUBLIC_ID_WTA10     0x03
#define WBXML_PUBLIC_ID_WML11     0x04
#define WBXML_PUBLIC_ID_SI10      0x05
#define WBXML_PUBLIC_ID_SL10      0x06
#define WBXML_PUBLIC_ID_CO10      0x07
#define WBXML_PUBLIC_ID_CHANNEL11 0x08
#define WBXML_PUBLIC_ID_WML12     0x09
#define WBXML_PUBLIC_ID_WML13     0x0A
#define WBXML_PUBLIC_ID_PROV10    0x0B
#define WBXML_PUBLIC_ID_WTAWML12  0x0C
#define WBXML_PUBLIC_ID_CHANNEL12 WBXML_PUBLIC_ID_UNKNOWN /**< I don't understand what is the Channel1.2 WBXML Public ID */
#define WBXML_PUBLIC_ID_EMN10     0x0D
#define WBXML_PUBLIC_ID_DRMREL10  0x0E

#define XML_PUBLIC_ID_WML10     "-//WAPFORUM//DTD WML 1.0//EN"
#define XML_PUBLIC_ID_WTA10     "-//WAPFORUM//DTD WTA 1.0//EN"
#define XML_PUBLIC_ID_WML11     "-//WAPFORUM//DTD WML 1.1//EN"
#define XML_PUBLIC_ID_SI10      "-//WAPFORUM//DTD SI 1.0//EN"
#define XML_PUBLIC_ID_SL10      "-//WAPFORUM//DTD SL 1.0//EN"
#define XML_PUBLIC_ID_CO10      "-//WAPFORUM//DTD CO 1.0//EN"
#define XML_PUBLIC_ID_CHANNEL11 "-//WAPFORUM//DTD CHANNEL 1.1//EN"
#define XML_PUBLIC_ID_WML12     "-//WAPFORUM//DTD WML 1.2//EN"
#define XML_PUBLIC_ID_WML13     "-//WAPFORUM//DTD WML 1.3//EN"
#define XML_PUBLIC_ID_PROV10    "-//WAPFORUM//DTD PROV 1.0//EN"
#define XML_PUBLIC_ID_WTAWML12  "-//WAPFORUM//DTD WTA-WML 1.2//EN"
#define XML_PUBLIC_ID_CHANNEL12 "-//WAPFORUM//DTD CHANNEL 1.2//EN"
#define XML_PUBLIC_ID_EMN10     "-//WAPFORUM//DTD EMN 1.0//EN"
#define XML_PUBLIC_ID_DRMREL10  "-//OMA//DTD DRMREL 1.0//EN"

/* Ericsson/Nokia OTA Settings v7.0 */
#define WBXML_PUBLIC_ID_OTA_SETTINGS WBXML_PUBLIC_ID_UNKNOWN
#define XML_PUBLIC_ID_OTA_SETTINGS   NULL                    /* No XML Public ID defined */

/* SyncML 1.0 */
#define WBXML_PUBLIC_ID_SYNCML_SYNCML10 0x0FD1
#define WBXML_PUBLIC_ID_SYNCML_DEVINF10 0x0FD2
#define WBXML_PUBLIC_ID_SYNCML_METINF10 WBXML_PUBLIC_ID_UNKNOWN /* No WBXML PublicID defined for SyncML Meta Info */

#define XML_PUBLIC_ID_SYNCML_SYNCML10 "-//SYNCML//DTD SyncML 1.0//EN"
#define XML_PUBLIC_ID_SYNCML_DEVINF10 "-//SYNCML//DTD DevInf 1.0//EN"
#define XML_PUBLIC_ID_SYNCML_METINF10 "-//SYNCML//DTD MetInf 1.0//EN"

/* SyncML 1.1 */
#define WBXML_PUBLIC_ID_SYNCML_SYNCML11 0x0FD3
#define WBXML_PUBLIC_ID_SYNCML_DEVINF11 0x0FD4
#define WBXML_PUBLIC_ID_SYNCML_METINF11 WBXML_PUBLIC_ID_UNKNOWN /* No WBXML PublicID defined for SyncML Meta Info */

#define XML_PUBLIC_ID_SYNCML_SYNCML11 "-//SYNCML//DTD SyncML 1.1//EN"
#define XML_PUBLIC_ID_SYNCML_DEVINF11 "-//SYNCML//DTD DevInf 1.1//EN"
#define XML_PUBLIC_ID_SYNCML_METINF11 "-//SYNCML//DTD MetInf 1.1//EN"

/* SyncML 1.2 */
#define WBXML_PUBLIC_ID_SYNCML_SYNCML12 0x1201
#define WBXML_PUBLIC_ID_SYNCML_METINF12 0x1202
#define WBXML_PUBLIC_ID_SYNCML_DEVINF12 0x1203
#define WBXML_PUBLIC_ID_SYNCML_DMDDF12 WBXML_PUBLIC_ID_UNKNOWN /* No WBXML PublicID defined for OMA DM DDF */

#define XML_PUBLIC_ID_SYNCML_SYNCML12 "-//SYNCML//DTD SyncML 1.2//EN"
#define XML_PUBLIC_ID_SYNCML_DEVINF12 "-//SYNCML//DTD DevInf 1.2//EN"
#define XML_PUBLIC_ID_SYNCML_METINF12 "-//SYNCML//DTD MetInf 1.2//EN"
#define XML_PUBLIC_ID_SYNCML_DMDDF12  "-//OMA//DTD-DM-DDF 1.2//EN"

/* OMA Wireless Village CSP 1.1 / 1.2 - @todo Check for CSP 1.0 */
#define WBXML_PUBLIC_ID_WV_CSP11 0x10
#define WBXML_PUBLIC_ID_WV_CSP12 WBXML_PUBLIC_ID_UNKNOWN
    
#define XML_PUBLIC_ID_WV_CSP11 "-//OMA//DTD WV-CSP 1.1//EN" /**< @todo Also defined as "-//WIRELESSVILLAGE//DTD CSP 1.1//EN" (so choose one) */
#define XML_PUBLIC_ID_WV_CSP12 "-//OMA//DTD WV-CSP 1.2//EN"

/* Microsoft AirSync */
#define WBXML_PUBLIC_ID_AIRSYNC WBXML_PUBLIC_ID_UNKNOWN
#define XML_PUBLIC_ID_AIRSYNC "-//AIRSYNC//DTD AirSync//EN"

#define WBXML_PUBLIC_ID_ACTIVESYNC WBXML_PUBLIC_ID_UNKNOWN
#define XML_PUBLIC_ID_ACTIVESYNC "-//MICROSOFT//DTD ActiveSync//EN"

/* Nokia ConML */
#define WBXML_PUBLIC_ID_CONML 0x8F
#define XML_PUBLIC_ID_CONML "-//CONML//DTD ConML//EN"

/****************************************************
 *    WBXML Encoding options
 */

#define WBXML_TAG_OPTION_UNKNOWN 0x0
#define WBXML_TAG_OPTION_BINARY  0x1
#define WBXML_TAG_OPTION_OPAQUE  0x2
#define WBXML_TAG_OPTION_CDATA   0x4

/* Example: CDATA|OPAQUE
 *   => XML:   <![CDATA ... ]]>
 *   => WBXML: create opaque encoding
 */

/****************************************************
 *    WBXML Tables Structures
 */

/**
 * @brief WBXML Public ID structure
 */
typedef struct WBXMLPublicIDEntry_s
{
    WB_ULONG       wbxmlPublicID; /**< WBXML Public ID */
    const WB_TINY *xmlPublicID;   /**< XML Public ID */
    const WB_TINY *xmlRootElt;    /**< XML Root Element */
    const WB_TINY *xmlDTD;        /**< XML DTD */

} WBXMLPublicIDEntry;


/**
 * @brief WBXML Application Token structure: Tag token
 *        The options are used to optionally define the
 *        handling of content.
 */
typedef struct WBXMLTagEntry_s
{    
    const WB_TINY *xmlName;       /**< XML Tag Name */    
    WB_UTINY       wbxmlCodePage; /**< WBXML Code Page */
    WB_UTINY       wbxmlToken;    /**< WBXML Tag Token */
    WB_ULONG       options;       /**< (WB)XML (Encoding) Options (optional bit mask)*/
} WBXMLTagEntry;


/**
 * @brief Name Space
 * @note For SyncML, where a WBXML Code Page is associated to an XML Name Space
 */
typedef struct WBXMLNameSpaceEntry_s
{    
    const WB_TINY *xmlNameSpace;  /**< XML Name Space */   
    WB_UTINY       wbxmlCodePage; /**< WBXML Code Page */
} WBXMLNameSpaceEntry;


/**
 * @brief WBXML Application Token structure: Attribute token
 */
typedef struct WBXMLAttrEntry_s
{
    const WB_TINY *xmlName;       /**< XML Attribute Name */
    const WB_TINY *xmlValue;      /**< XML Attribute Value (may be NULL) */
    WB_UTINY       wbxmlCodePage; /**< WBXML Code Page */
    WB_UTINY       wbxmlToken;    /**< WBXML Attribute Token */
} WBXMLAttrEntry;


/**
 * @brief WBXML Application Token structure: Attribute Value token
 */
typedef struct WBXMLAttrValueEntry_s
{
    const WB_TINY *xmlName;       /**< XML Attribute Value */
    WB_UTINY       wbxmlCodePage; /**< WBXML Code Page */
    WB_UTINY       wbxmlToken;    /**< WBXML Attribute Value Token */
} WBXMLAttrValueEntry;


/**
 * @brief WBXML Application Token structure: Extension Value token
 * @note For Wireless-Village, the content can be tokenized with Extension Tokens
 */
typedef struct WBXMLExtValueEntry_s
{
    const WB_TINY *xmlName;    /**< XML Extension Value */
    WB_UTINY       wbxmlToken; /**< WBXML Extension Value Token */
} WBXMLExtValueEntry;


/**
 * @brief Language structure
 */
typedef struct WBXMLLangEntry_s
{
    WBXMLLanguage              langID;         /**< Language ID */
    const WBXMLPublicIDEntry  *publicID;       /**< Public ID */
    const WBXMLTagEntry       *tagTable;       /**< Tags Table */
    const WBXMLNameSpaceEntry *nsTable;        /**< NameSpaces Table */
    const WBXMLAttrEntry      *attrTable;      /**< Attributes Table*/
    const WBXMLAttrValueEntry *attrValueTable; /**< Attributes Values Table */
    const WBXMLExtValueEntry  *extValueTable;  /**< Extensions Values Table */
} WBXMLLangEntry;


/**
 * @brief Get Main Table
 * @return The main array of WBXML Language Tables
 */
WBXML_DECLARE(const WBXMLLangEntry *) wbxml_tables_get_main(void);

/**
 * @brief Get a Language Table
 * @param lang Language to get
 * @return The Language Table, or NULL if unknown Language
 */
WBXML_DECLARE(const WBXMLLangEntry *) wbxml_tables_get_table(WBXMLLanguage lang);

/**
 * @brief Search for a Language Table
 * @param main_table Main Table Array to search in
 * @param public_id The Public ID to search [can be NULL]
 * @param system_id The System ID to search [can be NULL]
 * @param root The Root Element to search [can be NULL]
 * @return The Language Table found, or NULL if none found
 * @note This function try to find the correct Language Table thanks to the XML Public ID, then (if not found) by
 *       the XML System ID, and finally (if not found) by the Root XML Element
 */
WBXML_DECLARE(const WBXMLLangEntry *) wbxml_tables_search_table(const WBXMLLangEntry *main_table,
                                                                const WB_UTINY *public_id, 
                                                                const WB_UTINY *system_id,
                                                                const WB_UTINY *root);

/**
 * @brief Get the WBXML Public ID corresponding to given WBXML Language
 * @param main_table The Main Languages Table to search in
 * @param lang_id The Language ID
 * @return The WBXML Public ID (can be WBXML_PUBLIC_ID_UNKNOWN if Language doesn't have one, or if Language not found)
*/
WBXML_DECLARE(WB_ULONG) wbxml_tables_get_wbxml_publicid(const WBXMLLangEntry *main_table,
                                                        WBXMLLanguage lang_id);

/**
 * @brief Search for a Tag Entry in Language Table, given the XML Name of the Tag
 * @param lang_table The Language Table to search in
 * @param cur_code_page The current code page so that it can be searched first, or -1 to start from the first one.
 * @param xml_name The XML Name of the Tag to search
 * @return The Tag Entry of this XML Name in Language Table, or NULL if not found
 */
WBXML_DECLARE(const WBXMLTagEntry *) wbxml_tables_get_tag_from_xml(const WBXMLLangEntry *lang_table,
                                                                   const int cur_code_page,
                                                                   const WB_UTINY *xml_name);

/**
 * @brief Search for an Attribute Entry in Language Table, given the XML Name and Value of the Attribute
 * @param lang_table The Language Table to search in
 * @param xml_name The XML Name of the Attribute to search
 * @param xml_value The XML Value of the Attribute to search
 * @param value_left Is the WBXMLAttrEntry returned EXACTLY the Attribute we are searching ? (ie: is the Attribute Value
 *                   found matching the one we were looking for ?). If Yes, then this is NULL. If not, then this is the
 *                   attribute value part that we still have to encode.
 * @return The Attribute Entry of this XML Attribute Name in Language Table, or NULL if not found
 * @note Has the Attribut Value can be expressed in many ways in WBXML, this function is focused on
 *       searching for the ATTRIBUTE NAME !
 *       Thus, when Attribute Name is found in Table, we search for an Entry with the same Attribute Name / Attribute Value
 *       pair. If found the 'value_left' parameter is set to NULL. If not, we still return an Entry matching the Attribute Name,
 *       but the 'value_left' parameter is the Attribute Value part that is not included in the Attrbute Token.
 */
WBXML_DECLARE(const WBXMLAttrEntry *) wbxml_tables_get_attr_from_xml(const WBXMLLangEntry *lang_table,
                                                                     WB_UTINY *xml_name,
                                                                     WB_UTINY *xml_value,
                                                                     WB_UTINY **value_left);

/**
 * @brief Search for an Extension Token Entry in Language Table, given the XML Value of the Extension
 * @param lang_table The Language Table to search in
 * @param xml_value The XML Value of the Extension to search
 * @return The Extension Token Entry of this XML Value in Language Table, or NULL if not found
 */
WBXML_DECLARE(const WBXMLExtValueEntry *) wbxml_tables_get_ext_from_xml(const WBXMLLangEntry *lang_table,
                                                                        WB_UTINY *xml_value);

/**
 * @brief Check if an XML Attribute Value contains at least one Attribute Value defined in Language Attribute Values Table
 * @param lang_table The Language Table to search in
 * @param xml_value The XML Attribute Value to check
 * @return TRUE if this value contains an Attribute Value, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_tables_contains_attr_value_from_xml(const WBXMLLangEntry *lang_table,
                                                                 WB_UTINY *xml_value);

/**
 * @brief Get an XML NameSpace, given a WBXML Code Page
 * @param ns_table  The NameSpace Table
 * @param code_page The WBXML Code Page
 * @return The XML NameSpace, or NULL if not found
 */
WBXML_DECLARE(const WB_TINY *) wbxml_tables_get_xmlns(const WBXMLNameSpaceEntry *ns_table,
                                                      WB_UTINY code_page);

WBXML_DECLARE(WB_UTINY) wbxml_tables_get_code_page(const WBXMLNameSpaceEntry *ns_table,
                                                   const WB_TINY* xmlns);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_TABLES_H */
