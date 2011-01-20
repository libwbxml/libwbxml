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
 * @file wbxml_elt.c
 * @ingroup wbxml_elt
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 03/02/22
 *
 * @brief WBXML Elements
 */

#include "wbxml_elt.h"


/** For an unknown XML Name */
#define WBXML_ELT_UNKNOWN_NAME ((WB_UTINY *)"unknown")



/***************************************************
 *    Public Functions
 */
 
/* WBXMLTag */

WBXML_DECLARE(WBXMLTag *) wbxml_tag_create(WBXMLValueType type)
{
    WBXMLTag *result = NULL;
    
    if ((result = (WBXMLTag *) wbxml_malloc(sizeof(WBXMLTag))) == NULL)
        return NULL;

    result->type = type;
    result->u.token = NULL;
    result->u.literal = NULL;

    return result;
}


WBXML_DECLARE(WBXMLTag *) wbxml_tag_create_token(const WBXMLTagEntry *value)
{
    WBXMLTag *result = NULL;

    if ((result = wbxml_tag_create(WBXML_VALUE_TOKEN)) == NULL)
        return NULL;

    result->u.token = value;

    return result;
}


WBXML_DECLARE(WBXMLTag *) wbxml_tag_create_literal(WB_UTINY *value)
{
    WBXMLTag *result = NULL;

    if ((result = wbxml_tag_create(WBXML_VALUE_LITERAL)) == NULL)
        return NULL;

    if (value == NULL)
        result->u.literal = NULL;
    else {
        result->u.literal = wbxml_buffer_create(value, WBXML_STRLEN(value), WBXML_STRLEN(value));
        if (result->u.literal == NULL) {
            wbxml_tag_destroy(result);
            return NULL;
        }
    }

    return result;
}


WBXML_DECLARE(void) wbxml_tag_destroy(WBXMLTag *tag)
{
    if (tag == NULL)
        return;

    if (tag->type == WBXML_VALUE_LITERAL)
        wbxml_buffer_destroy(tag->u.literal);

    wbxml_free(tag);
}


WBXML_DECLARE(WBXMLTag *) wbxml_tag_duplicate(WBXMLTag *tag)
{
    WBXMLTag *result = NULL;

    if (tag == NULL)
        return NULL;

    if ((result = (WBXMLTag *) wbxml_malloc(sizeof(WBXMLTag))) == NULL)
        return NULL;

    result->type = tag->type;

    switch (result->type) {
    case WBXML_VALUE_TOKEN:
        result->u.token = tag->u.token;
        break;
    case WBXML_VALUE_LITERAL:
        result->u.literal = wbxml_buffer_duplicate(tag->u.literal);
        break;
    default:
        /* Must Never Happen ! */
        wbxml_free(result);
        return NULL;
    }

    return result;
}


WBXML_DECLARE(const WB_UTINY *) wbxml_tag_get_xml_name(WBXMLTag *tag)
{
    if (tag == NULL)
        return WBXML_ELT_UNKNOWN_NAME;

    switch (tag->type) {
    case WBXML_VALUE_TOKEN:
        return (const WB_UTINY *) tag->u.token->xmlName;
        break;
    case WBXML_VALUE_LITERAL:
        return (const WB_UTINY *) wbxml_buffer_get_cstr(tag->u.literal);
    default:
        return WBXML_ELT_UNKNOWN_NAME;
    }
}


/* WBXMLAttributeName */

WBXML_DECLARE(WBXMLAttributeName *) wbxml_attribute_name_create(WBXMLValueType type)
{
    WBXMLAttributeName *result = NULL;
    
    if ((result = (WBXMLAttributeName *) wbxml_malloc(sizeof(WBXMLAttributeName))) == NULL)
        return NULL;

    result->type = type;
    result->u.token = NULL;
    result->u.literal = NULL;

    return result;
}


WBXML_DECLARE(WBXMLAttributeName *) wbxml_attribute_name_create_token(const WBXMLAttrEntry *value)
{
    WBXMLAttributeName *result = NULL;

    if ((result = wbxml_attribute_name_create(WBXML_VALUE_TOKEN)) == NULL)
        return NULL;

    result->u.token = value;

    return result;
}


WBXML_DECLARE(WBXMLAttributeName *) wbxml_attribute_name_create_literal(WB_UTINY *value)
{
    WBXMLAttributeName *result = NULL;

    if ((result = wbxml_attribute_name_create(WBXML_VALUE_LITERAL)) == NULL)
        return NULL;

    if (value == NULL)
        result->u.literal = NULL;
    else {
        result->u.literal = wbxml_buffer_create(value, WBXML_STRLEN(value), WBXML_STRLEN(value));
        if (result->u.literal == NULL) {
            wbxml_attribute_name_destroy(result);
            return NULL;
        }
    }

    return result;
}


WBXML_DECLARE(void) wbxml_attribute_name_destroy(WBXMLAttributeName *name)
{
    if (name == NULL)
        return;

    if (name->type == WBXML_VALUE_LITERAL)
        wbxml_buffer_destroy(name->u.literal);

    wbxml_free(name);
}


WBXML_DECLARE(WBXMLAttributeName *) wbxml_attribute_name_duplicate(WBXMLAttributeName *name)
{
    WBXMLAttributeName *result = NULL;

    if (name == NULL)
        return NULL;

    if ((result = (WBXMLAttributeName *) wbxml_malloc(sizeof(WBXMLAttributeName))) == NULL)
        return NULL;

    result->type = name->type;

    switch (result->type) {
    case WBXML_VALUE_TOKEN:
        result->u.token = name->u.token;
        break;
    case WBXML_VALUE_LITERAL:
        result->u.literal = wbxml_buffer_duplicate(name->u.literal);
        break;
    default:
        /* Must Never Happen ! */
        wbxml_free(result);
        return NULL;
    }

    return result;
}


WBXML_DECLARE(const WB_UTINY *) wbxml_attribute_name_get_xml_name(WBXMLAttributeName *name)
{
    if (name == NULL)
        return WBXML_ELT_UNKNOWN_NAME;

    switch (name->type) {
    case WBXML_VALUE_TOKEN:
        return (const WB_UTINY *) name->u.token->xmlName;
        break;
    case WBXML_VALUE_LITERAL:
        return (const WB_UTINY *) wbxml_buffer_get_cstr(name->u.literal);
    default:
        return WBXML_ELT_UNKNOWN_NAME;
    }
}


/* WBXMLAttribute */

WBXML_DECLARE(WBXMLAttribute *) wbxml_attribute_create(void)
{
    WBXMLAttribute *result = NULL;
    
    if ((result = (WBXMLAttribute *) wbxml_malloc(sizeof(WBXMLAttribute))) == NULL)
        return NULL;

    result->name = NULL;
    result->value = NULL;

    return result;
}


WBXML_DECLARE(void) wbxml_attribute_destroy(WBXMLAttribute *attr)
{
    if (attr == NULL)
        return;

    wbxml_attribute_name_destroy(attr->name);
    wbxml_buffer_destroy(attr->value);     

    wbxml_free(attr);
}


WBXML_DECLARE_NONSTD(void) wbxml_attribute_destroy_item(void *attr)
{
    wbxml_attribute_destroy((WBXMLAttribute *) attr);
}


WBXML_DECLARE(WBXMLAttribute *) wbxml_attribute_duplicate(WBXMLAttribute *attr)
{
    WBXMLAttribute *result = NULL;

    if (attr == NULL)
        return NULL;

    if ((result = (WBXMLAttribute *) wbxml_malloc(sizeof(WBXMLAttribute))) == NULL)
        return NULL;

    result->name = wbxml_attribute_name_duplicate(attr->name);
    result->value = wbxml_buffer_duplicate(attr->value);

    return result;
}


WBXML_DECLARE(const WB_UTINY *) wbxml_attribute_get_xml_name(WBXMLAttribute *attr)
{
    if (attr == NULL)
        return WBXML_ELT_UNKNOWN_NAME;

    return wbxml_attribute_name_get_xml_name(attr->name);
}


WBXML_DECLARE(const WB_UTINY *) wbxml_attribute_get_xml_value(WBXMLAttribute *attr)
{
    if ((attr == NULL) || (attr->value == NULL))
        return WBXML_UTINY_NULL_STRING;

    return wbxml_buffer_get_cstr(attr->value);
}
