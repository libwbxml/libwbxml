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
 * @file wbxml_elt.h
 * @ingroup wbxml_elt
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 03/02/22
 *
 * @brief WBXML Elements
 */

#ifndef WBXML_ELT_H
#define WBXML_ELT_H

#include "wbxml.h"
#include "wbxml_buffers.h"
#include "wbxml_tables.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup wbxml_elt 
 *  @{ 
 */

/**
 * @brief WBXML Value Type
 */
typedef enum WBXMLValueType_e {
    WBXML_VALUE_TOKEN = 0, /**< WBXML Token value */
    WBXML_VALUE_LITERAL    /**< WBXML Literal value */
} WBXMLValueType;


/** @brief WBXML Tag structure */
typedef struct WBXMLTag_s {
    WBXMLValueType type;   /**< Tag Type (Token or Literal) */
    union {
        const WBXMLTagEntry *token;   /**< Token Tag (MUST be const structure, ie from wbxml_tables.c) */
        WBXMLBuffer         *literal; /**< Literal Tag (MUST be dynamically allocated WBXMLBuffer) */
    } u;
} WBXMLTag;


/** @brief WBXML Attribute Name structure */
typedef struct WBXMLAttributeName_s {
    WBXMLValueType type;   /**< Attribute Name Type (Token or Literal) */
    union {
        const WBXMLAttrEntry *token;   /**< Token Attribute Name (MUST be const structure, ie from wbxml_tables.c) */
        WBXMLBuffer          *literal; /**< Literal Attribute Name (MUST be dynamically allocated WBXMLBuffer) */
    } u;
} WBXMLAttributeName;


/** 
 * @brief WBXML Attribute structure 
 * @note The 'value' part contain the FULL attribute value
 *  For example, with the attribute: url="http://127.0.0.1/"
 *  If the 'name' part is this:
 *      - name->u.token->wbxmlCodePage: 0x00
 *      - name->u.token->wbxmlToken : 0x4b
 *      - name->u.token->xmlName : "url"
 *      - name->u.token->xmlValue: "http://"
 *
 *  Then, 'value' is still: "http://127.0.0.1/"
 *
 *  Of course (in this example) it should be better to have the wbxmlToken 0x4a ("url" / NULL). So you mustn't take into
 *  account the 'xmlValue' field for 'name' to get the Attribute Value of this Attribute.
 */
typedef struct WBXMLAttribute_s {
    WBXMLAttributeName *name;  /**< Attribute Name */
    WBXMLBuffer        *value; /**< Full Attribute Value */
} WBXMLAttribute;


/****************************************************
 *    WBXML Elt Functions
 */

/* WBXMLTag */

/**
 * @brief Create a Tag structure
 * @param type WBXML Value Type
 * @return The newly created Tag, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLTag *) wbxml_tag_create(WBXMLValueType type);

/**
 * @brief Additional function to create directly a Token Tag structure
 * @param value The WBXMLTagEntry value
 * @return The newly created Tag, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLTag *) wbxml_tag_create_token(const WBXMLTagEntry *value);

/**
 * @brief Additional function to create directly a Literal Tag structure
 * @param value The Literal value
 * @return The newly created Tag, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLTag *) wbxml_tag_create_literal(WB_UTINY *value);

/**
 * @brief Destroy a Tag structure
 * @param tag The Tag structure to destroy
 */
WBXML_DECLARE(void) wbxml_tag_destroy(WBXMLTag *tag);

/**
 * @brief Duplicate a Tag structure
 * @param tag The Tag structure to duplicate
 * @return The duplicated Tag structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLTag *) wbxml_tag_duplicate(WBXMLTag *tag);

/**
 * @brief Get the XML Name of a WBXML Tag
 * @param tag The WBXML Tag
 * @return The XML Name, or "unknown" if not found
 */
WBXML_DECLARE(const WB_UTINY *) wbxml_tag_get_xml_name(WBXMLTag *tag);


/* WBXMLAttributeName */

/**
 * @brief Create an Attribute Name structure
 * @param type WBXML Value Type
 * @return The newly created Attribute Name, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLAttributeName *) wbxml_attribute_name_create(WBXMLValueType type);

/**
 * @brief Additional function to create directly a Token Attribute Name structure
 * @param value The WBXMLTagEntry value
 * @return The newly created Attribute Name, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLAttributeName *) wbxml_attribute_name_create_token(const WBXMLAttrEntry *value);

/**
 * @brief Additional function to create directly a Literal Attribute Name structure
 * @param value The Literal value
 * @return The newly created Attribute Name, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLAttributeName *) wbxml_attribute_name_create_literal(WB_UTINY *value);

/**
 * @brief Destroy an Attribute Name structure
 * @param name The Attribute Name structure to destroy
 */
WBXML_DECLARE(void) wbxml_attribute_name_destroy(WBXMLAttributeName *name);

/**
 * @brief Duplicate a Attribute Name structure
 * @param name The Attribute Name structure to duplicate
 * @return The duplicated Attribute Name structure, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLAttributeName *) wbxml_attribute_name_duplicate(WBXMLAttributeName *name);

/**
 * @brief Get the XML Name of a WBXML Attribute Name
 * @param name The WBXML Attribute Name
 * @return The XML Name, or "unknown" if not found
 */
WBXML_DECLARE(const WB_UTINY *) wbxml_attribute_name_get_xml_name(WBXMLAttributeName *name);


/* WBXMLAttribute */

/**
 * @brief Create an Attribute structure
 * @return The newly created Attribute, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLAttribute *) wbxml_attribute_create(void);

/**
 * @brief Destroy an Attribute structure
 * @param attr The Attribute structure to destroy
 */
WBXML_DECLARE(void) wbxml_attribute_destroy(WBXMLAttribute *attr);

/**
 * @brief Destroy an Attribute structure (used for wbxml_list_destroy())
 * @param attr The Attribute structure to destroy
 */
WBXML_DECLARE_NONSTD(void) wbxml_attribute_destroy_item(void *attr);

/**
 * @brief Duplicate an Attribute structure
 * @param attr The Attribute structure to duplicate
 * @return The duplicated Attribute, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLAttribute *) wbxml_attribute_duplicate(WBXMLAttribute *attr);

/**
 * @brief Get the XML Attribute Name of a WBXML Attribute
 * @param attr The WBXML Attribute
 * @return The XML Attribute Name, or "unknown" if not found
 */
WBXML_DECLARE(const WB_UTINY *) wbxml_attribute_get_xml_name(WBXMLAttribute *attr);

/**
 * @brief Get the XML Attribute Value of a WBXML Attribute
 * @param attr The WBXML Attribute
 * @return The XML Attribute Value, or "" if none
 */
WBXML_DECLARE(const WB_UTINY *) wbxml_attribute_get_xml_value(WBXMLAttribute *attr);


/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_ELT_H */
