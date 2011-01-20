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
 * @file wbxml_tree_clb_wbxml.c
 * @ingroup wbxml_tree
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 03/02/22
 *
 * @brief WBXML Tree Callbacks for WBXML Parser
 */

#include "wbxml_tree_clb_wbxml.h"
#include "wbxml_tree.h"


/***************************************************
 *  Public Functions
 */

void wbxml_tree_clb_wbxml_start_document(void *ctx, WBXMLCharsetMIBEnum charset, const WBXMLLangEntry *lang)
{
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;

    if (tree_ctx->error != WBXML_OK)
        return;

    tree_ctx->tree->lang = lang;
    tree_ctx->tree->orig_charset = charset;
}


void wbxml_tree_clb_wbxml_end_document(void *ctx)
{
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;

    if (tree_ctx->error != WBXML_OK)
        return;
}


void wbxml_tree_clb_wbxml_start_element(void *ctx, WBXMLTag *element, WBXMLAttribute **attrs, WB_BOOL empty)
{
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;

    (void) empty; /* avoid warning about unused parameter */

    if (tree_ctx->error != WBXML_OK)
        return;

    /* Add a new Node to tree */
    tree_ctx->current = wbxml_tree_add_elt_with_attrs(tree_ctx->tree,
                                                      tree_ctx->current,
                                                      element,
                                                      attrs);
    if (tree_ctx->current == NULL) {
        tree_ctx->error = WBXML_ERROR_INTERNAL;
    }
}


void wbxml_tree_clb_wbxml_end_element(void *ctx, WBXMLTag *element, WB_BOOL empty)
{
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;

    (void) empty; /* avoid warning about unused parameter */

    if (tree_ctx->error != WBXML_OK)
        return;

    if (tree_ctx->current == NULL) {
        tree_ctx->error = WBXML_ERROR_INTERNAL;
        return;
    }

    if (tree_ctx->current->parent == NULL) {
        /* This must be the Root Element */
        if (tree_ctx->current != tree_ctx->tree->root) {
            tree_ctx->error = WBXML_ERROR_INTERNAL;
        }
    }
    else {
#if defined ( WBXML_SUPPORT_SYNCML )
        /* Have we added a CDATA section ? 
         * If so, we assume that now that we have reached an end of Element, 
         * the CDATA section ended, and so we go back to parent.
         */
        if ((tree_ctx->current != NULL) && (tree_ctx->current->type == WBXML_TREE_CDATA_NODE))
            tree_ctx->current = tree_ctx->current->parent;
#endif /* WBXML_SUPPORT_SYNCML */

        /* Go back one step upper in the tree */
        tree_ctx->current = tree_ctx->current->parent;
    }
}


void wbxml_tree_clb_wbxml_characters(void *ctx, WB_UTINY *ch, WB_ULONG start, WB_ULONG length)
{
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;
#if defined ( WBXML_SUPPORT_SYNCML )
    WBXMLTree *tmp_tree = NULL;
#endif /* WBXML_SUPPORT_SYNCML */

    if (tree_ctx->error != WBXML_OK)
        return;

#if defined ( WBXML_SUPPORT_SYNCML )
    /* Specific treatment for SyncML */
    switch (wbxml_tree_node_get_syncml_data_type(tree_ctx->current)) {
    case WBXML_SYNCML_DATA_TYPE_WBXML:
        /* Deal with Embedded SyncML Documents - Parse WBXML */
        if (wbxml_tree_from_wbxml(ch + start, length, WBXML_LANG_UNKNOWN, tree_ctx->tree->orig_charset, &tmp_tree) != WBXML_OK) {
            /* Not parsable ? Just add it as a Text Node... */
            goto text_node;
        }

        /* Add Tree Node */
        if (wbxml_tree_add_tree(tree_ctx->tree,
                                tree_ctx->current,
                                tmp_tree) == NULL)
        {
            tree_ctx->error = WBXML_ERROR_INTERNAL;
            wbxml_tree_destroy(tmp_tree);
        }

        /* Return !! */
        return;
        break;

    case WBXML_SYNCML_DATA_TYPE_CLEAR:
    case WBXML_SYNCML_DATA_TYPE_DIRECTORY_VCARD:
    case WBXML_SYNCML_DATA_TYPE_VCALENDAR:
    case WBXML_SYNCML_DATA_TYPE_VCARD:
    case WBXML_SYNCML_DATA_TYPE_VOBJECT:
        /*
         * Add a CDATA section node
         *
         * Example:
         * <Add>
         *   <CmdID>6</CmdID>
         *   <Meta><Type xmlns='syncml:metinf'>text/x-vcard</Type></Meta>
         *   <Item>
         *     <Source>
         *         <LocURI>pas-id-3F4B790300000000</LocURI>
         *     </Source>         
         *     <Data><![CDATA[BEGIN:VCARD
         *  VERSION:2.1
         *  X-EVOLUTION-FILE-AS:Ximian, Inc.
         *  N:
         *  LABEL;WORK;ENCODING=QUOTED-PRINTABLE:401 Park Drive  3 West=0ABoston, MA
         *  02215=0AUSA
         *  TEL;WORK;VOICE:(617) 236-0442
         *  TEL;WORK;FAX:(617) 236-8630
         *  EMAIL;INTERNET:[EMAIL PROTECTED]
         *  URL:www.ximian.com/
         *  ORG:Ximian, Inc.
         *  NOTE:Welcome to the Ximian Addressbook.
         *  UID:pas-id-3F4B790300000000
         *  END:VCARD
         *  ]]>
         *     </Data>
         *   </Item>
         * </Add>
         *
         * The end of CDATA section is assumed to be reached when parsing the end 
         * of </Data> element.
         */

        /* Add new CDATA Node */
        tree_ctx->current = wbxml_tree_add_cdata(tree_ctx->tree, tree_ctx->current);
        if (tree_ctx->current == NULL) {
            tree_ctx->error = WBXML_ERROR_INTERNAL;
            return;
        }

        /* Now we can add the Text Node */
        break;

    default:
        /* NOP */
        break;
    } /* switch */

text_node:

#endif /* WBXML_SUPPORT_SYNCML */

    /* Add Text Node */
    if (wbxml_tree_add_text(tree_ctx->tree,
                            tree_ctx->current,
                            (const WB_UTINY*) ch + start,
                            length) == NULL)
    {
        tree_ctx->error = WBXML_ERROR_INTERNAL;
    }
}


void wbxml_tree_clb_wbxml_pi(void *ctx, const WB_UTINY *target, WB_UTINY *data)
{
    /** @todo wbxml_tree_clb_pi() */
}
