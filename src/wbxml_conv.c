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
 * @file wbxml_conv.c
 * @ingroup wbxml_conv
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 03/02/23
 *
 * @brief WBXML Convertion Library (XML to WBXML, and WBXML to XML)
 */

#include "wbxml.h"


/************************************
 * Public Functions
 */

WBXML_DECLARE(WBXMLError) wbxml_conv_wbxml2xml_withlen(WB_UTINY  *wbxml,
                                                       WB_ULONG   wbxml_len,
                                                       WB_UTINY **xml,
                                                       WB_ULONG  *xml_len,
                                                       WBXMLGenXMLParams *params)
{
    WBXMLTree *wbxml_tree = NULL;
    WB_ULONG   dummy_len = 0;
    WBXMLError ret = WBXML_OK;

    /* Check Parameters (we allow 'xml_len' to be NULL for backward compatibility) */
    if ((wbxml == NULL) || (wbxml_len == 0) || (xml == NULL))
        return WBXML_ERROR_BAD_PARAMETER;

    if (xml_len == NULL)
        xml_len = &dummy_len;

    *xml = NULL;
    *xml_len = 0;

    /* Parse WBXML to WBXML Tree */
    ret = wbxml_tree_from_wbxml(wbxml, wbxml_len, params ? params->lang : WBXML_LANG_UNKNOWN, &wbxml_tree);
    if (ret != WBXML_OK) {
        WBXML_ERROR((WBXML_CONV, "wbxml2xml conversion failed - WBXML Parser Error: %s",
                                 wbxml_errors_string(ret)));

        return ret;
    }
    else {
        /* Convert Tree to XML */
        ret = wbxml_tree_to_xml(wbxml_tree, xml, xml_len, params);
        if (ret != WBXML_OK) {
            WBXML_ERROR((WBXML_CONV, "wbxml2xml conversion failed - WBXML Encoder Error: %s",
                                     wbxml_errors_string(ret)));
        }

        /* Clean-up */
        wbxml_tree_destroy(wbxml_tree);

        return ret;
    }
}


WBXML_DECLARE(WBXMLError) wbxml_conv_xml2wbxml_withlen(WB_UTINY  *xml,
                                                       WB_ULONG   xml_len,
                                                       WB_UTINY **wbxml,
                                                       WB_ULONG  *wbxml_len,
                                                       WBXMLGenWBXMLParams *params)
{
    WBXMLTree *wbxml_tree = NULL;
    WBXMLError ret = WBXML_OK;

    /* Check Parameters */
    if ((xml == NULL) || (xml_len == 0) || (wbxml == NULL) || (wbxml_len == NULL))
        return WBXML_ERROR_BAD_PARAMETER;

    *wbxml = NULL;
    *wbxml_len = 0;

    /* Parse XML to WBXML Tree */
    ret = wbxml_tree_from_xml(xml, xml_len, &wbxml_tree);
    if (ret != WBXML_OK) {
        WBXML_ERROR((WBXML_CONV, "xml2wbxml conversion failed - Error: %s",
                                  wbxml_errors_string(ret)));

        return ret;
    }
    else {
        /* Convert Tree to WBXML */
        ret = wbxml_tree_to_wbxml(wbxml_tree, wbxml, wbxml_len, params);
        if (ret != WBXML_OK) {
            WBXML_ERROR((WBXML_CONV, "xml2wbxml conversion failed - WBXML Encoder Error: %s",
                                     wbxml_errors_string(ret)));
        }

        /* Clean-up */
        wbxml_tree_destroy(wbxml_tree);

        return ret;
    }
}
