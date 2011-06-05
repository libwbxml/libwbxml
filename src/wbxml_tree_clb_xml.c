/*
 * libwbxml, the WBXML Library.
 * Copyright (C) 2002-2008 Aymerick Jehanne <aymerick@jehanne.org>
 * Copyright (C) 2008-2011 Michael Bell <michael.bell@opensync.org>
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
 * @file wbxml_tree_clb_xml.c
 * @ingroup wbxml_tree
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 03/03/11
 *
 * @brief WBXML Tree Callbacks for XML Parser (Expat)
 */

#include "wbxml_config_internals.h"

#if defined( HAVE_EXPAT )

#include "wbxml_tree_clb_xml.h"
#include "wbxml_tree.h"
#include "wbxml_log.h"
#include "wbxml_charset.h"
#include "wbxml_base64.h"

/************************************
 *  Public Functions
 */

void wbxml_tree_clb_xml_decl(void           *ctx,
                             const XML_Char *version,
                             const XML_Char *encoding,
                             int             standalone)
{
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;

    (void) standalone; /* avoid warning about unused parameter */

    if (tree_ctx->expat_utf16) {
        /** @todo Convert from UTF-16 to UTF-8 */
    }

    /* This handler is called for XML declarations and also for text declarations discovered 
     * in external entities. The way to distinguish is that the version parameter will
     * be NULL for text declarations.
     */
    if (version != NULL) {
        if (encoding != NULL) {
            /* Get encoding */
            if (!wbxml_charset_get_mib((const WB_TINY*)encoding, &(tree_ctx->tree->orig_charset))) {
                WBXML_WARNING((WBXML_CONV, "Charset Encoding not supported: %s", encoding));
            }
        }
    }
}


void wbxml_tree_clb_xml_doctype_decl(void           *ctx, 
                                     const XML_Char *doctypeName, 
                                     const XML_Char *sysid,
                                     const XML_Char *pubid, 
                                     int             has_internal_subset)
{    
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;
    const WBXMLLangEntry *lang_table = NULL;

    (void) doctypeName;         /* avoid warning about unused parameter */
    (void) has_internal_subset; /* avoid warning about unused parameter */

    if (tree_ctx->expat_utf16) {
        /** @todo Convert from UTF-16 to UTF-8 */
    }

    /* Search for Language Table, given the XML Public ID and System ID */
    lang_table = wbxml_tables_search_table(wbxml_tables_get_main(), 
                                           (const WB_UTINY *) pubid, 
                                           (const WB_UTINY *) sysid, 
                                           NULL);

    if (lang_table != NULL) {
        /* Ho Yeah ! We got it ! */
        tree_ctx->tree->lang = lang_table;
    }
    else {
        /* We will try to find the Language Table, given the Root Element */
        WBXML_WARNING((WBXML_CONV, "Language Table NOT found, given the XML Public ID and System ID"));
    }
}


void wbxml_tree_clb_xml_start_element(void           *ctx,
                                      const XML_Char *localName,
                                      const XML_Char **attrs)
{
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;
    const WBXMLLangEntry *lang_table = NULL;

    WBXML_DEBUG((WBXML_PARSER, "Expat element start callback ('%s')", localName));

    if (tree_ctx->expat_utf16) {
        /** @todo Convert from UTF-16 to UTF-8 */
    }

    /* Check for Error */
    if (tree_ctx->error != WBXML_OK)
        return;

    /* Are we skipping a whole node ? */
    if (tree_ctx->skip_lvl > 0) {
        tree_ctx->skip_lvl++;
        return;
    }

    if (tree_ctx->current == NULL) {
        /* This is the Root Element */
        if (tree_ctx->tree->lang == NULL) {
            /* Language Table not already found: Search again */
            lang_table = wbxml_tables_search_table(wbxml_tables_get_main(), 
                                                   NULL, 
                                                   NULL, 
                                                   (const WB_UTINY *) localName);
        
            if (lang_table == NULL) {
                /* Damn, this is an unknown language for us... */
                tree_ctx->error = WBXML_ERROR_UNKNOWN_XML_LANGUAGE;
                return;
            }
            else {
                /* Well, we hope this was the Language we are searching for.. let's try with it :| */
                tree_ctx->tree->lang = lang_table;
            }
        }
    }

#if defined( WBXML_SUPPORT_SYNCML )

    /* If this is an embedded (not root) document, skip it
     * Actually SyncML DevInf and DM DDF are known as such
     * potentially embedded documents.
     */
    if ((
         (WBXML_STRCMP(localName, "syncml:devinf:DevInf") == 0) ||
         (WBXML_STRCMP(localName, "syncml:dmddf1.2:MgmtTree") == 0)
        )&&
        (tree_ctx->current != NULL))
    {
        tree_ctx->skip_start = XML_GetCurrentByteIndex(tree_ctx->xml_parser);

        /* Skip this node */
        tree_ctx->skip_lvl++;

        return;
    }

#endif /* WBXML_SUPPORT_SYNCML */

    /* Add Element Node */
    tree_ctx->current = wbxml_tree_add_xml_elt_with_attrs(tree_ctx->tree,
                                                          tree_ctx->current,
                                                          (WB_UTINY *) localName,
                                                          (const WB_UTINY**) attrs);

    if (tree_ctx->current == NULL) {
        tree_ctx->error = WBXML_ERROR_NOT_ENOUGH_MEMORY;
    }
}


void wbxml_tree_clb_xml_end_element(void           *ctx,
                                    const XML_Char *localName)
{
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;
#if defined( WBXML_SUPPORT_SYNCML )
    WBXMLBuffer *embed_doc = NULL;
    WBXMLBuffer *content = NULL;
    WBXMLTree *tree = NULL;
    WBXMLTreeNode *node = NULL;
    WBXMLError ret = WBXML_OK;
#endif /* WBXML_SUPPORT_SYNCML */

    WBXML_DEBUG((WBXML_PARSER, "Expat element end callback ('%s')", localName));

    /* If the node is flagged as binary node
     * then the data is base64 encoded in the XML document
     * and the data must be decoded in one step.
     */

    node = tree_ctx->current;
    if (node && node->type == WBXML_TREE_ELEMENT_NODE &&
        node->name->type == WBXML_VALUE_TOKEN &&
        node->name->u.token->options & WBXML_TAG_OPTION_BINARY)
    {
        if (node->content == NULL)
        {
            WBXML_DEBUG((WBXML_PARSER, "    Binary tag: No content => no conversion!"));
        } else {
            WBXML_DEBUG((WBXML_PARSER, "    Binary tag: Convert base64 data"));
            ret = wbxml_buffer_decode_base64(node->content);
            if (ret != WBXML_OK)
            {
                WBXML_DEBUG((WBXML_PARSER, "    Binary tag: Base64 decoder failed!"));
                tree_ctx->error = ret;
            } else {
                /* Add the buffer as a regular string node (since libwbxml doesn't
                 * offer a way to specify an opaque data node). The WBXML
                 * encoder is responsible for generating correct opaque data for
                 * nodes like this.
                 */
                if (wbxml_tree_add_text(tree_ctx->tree,
                                        tree_ctx->current,
                                        (const WB_UTINY*)wbxml_buffer_get_cstr(node->content),
                                        wbxml_buffer_len(node->content)) == NULL)
                {
                    WBXML_DEBUG((WBXML_PARSER, "    Binary tag: Cannot add base64 decoded node!"));
                    tree_ctx->error = WBXML_ERROR_INTERNAL;
                }
            }
            /* safe cleanup */
            content = node->content;
            node->content = NULL;
            wbxml_buffer_destroy(content);
        }
    }

    if (tree_ctx->expat_utf16) {
        /** @todo Convert from UTF-16 to UTF-8 */
    }

    /* Check for Error */
    if (tree_ctx->error != WBXML_OK)
        return;

    /* Are we skipping a whole node ? */
    if (tree_ctx->skip_lvl > 0) {
        if (tree_ctx->skip_lvl == 1)
        {
            /* End of skipped node */

#if defined( WBXML_SUPPORT_SYNCML )
            if (WBXML_STRCMP(localName, "syncml:devinf:DevInf") == 0 ||
	        WBXML_STRCMP(localName, "syncml:dmddf1.2:MgmtTree") == 0) {
		/* definitions first ... or some compilers don't like it */
		const WBXMLLangEntry *lang;

                /* Get embedded DevInf or DM DDF Document */
                embed_doc = wbxml_buffer_create(tree_ctx->input_buff + tree_ctx->skip_start, 
                                                 XML_GetCurrentByteIndex(tree_ctx->xml_parser) - tree_ctx->skip_start,
                                                 XML_GetCurrentByteIndex(tree_ctx->xml_parser) - tree_ctx->skip_start + 10);
                if (embed_doc == NULL) {
                    tree_ctx->error = WBXML_ERROR_NOT_ENOUGH_MEMORY;
                    wbxml_buffer_destroy(embed_doc);
                    return;
                }

                if (tree_ctx->expat_utf16) {
                    /** @todo Convert from UTF-16 to UTF-8 */
                }

                /* Check Buffer Creation and add the closing tag */
		if ((WBXML_STRCMP(localName, "syncml:devinf:DevInf") == 0 &&
		     (!wbxml_buffer_append_cstr(embed_doc, "</DevInf>")))
                    ||
		    (WBXML_STRCMP(localName, "syncml:dmddf1.2:MgmtTree") == 0 &&
		     (!wbxml_buffer_append_cstr(embed_doc, "</MgmtTree>"))))
                {
                    tree_ctx->error = WBXML_ERROR_NOT_ENOUGH_MEMORY;
                    wbxml_buffer_destroy(embed_doc);
                    return;
                }

                /* Add doctype to give the XML parser a chance */
		if (WBXML_STRCMP(localName, "syncml:dmddf1.2:MgmtTree") == 0 &&
		    tree_ctx->tree->lang->langID != WBXML_LANG_SYNCML_SYNCML12)
		{
                    tree_ctx->error = WBXML_ERROR_UNKNOWN_XML_LANGUAGE;
                    wbxml_buffer_destroy(embed_doc);
                    return;
		}
		switch(tree_ctx->tree->lang->langID)
		{
			case WBXML_LANG_SYNCML_SYNCML10:
				lang = wbxml_tables_get_table(WBXML_LANG_SYNCML_DEVINF10);
				break;
			case WBXML_LANG_SYNCML_SYNCML11:
				lang = wbxml_tables_get_table(WBXML_LANG_SYNCML_DEVINF11);
				break;
			case WBXML_LANG_SYNCML_SYNCML12:
				if (WBXML_STRCMP(localName, "syncml:dmddf1.2:MgmtTree") == 0) {
					lang = wbxml_tables_get_table(WBXML_LANG_SYNCML_DMDDF12);
				} else {
					lang = wbxml_tables_get_table(WBXML_LANG_SYNCML_DEVINF12);
				}
				break;
			default:
				tree_ctx->error = WBXML_ERROR_UNKNOWN_XML_LANGUAGE;
				return;
		}

		/* DOCTYPE in reverse order */
		if (!wbxml_buffer_insert_cstr(embed_doc,(WB_UTINY *) "\">\n", 0) ||                     /* > */
		    !wbxml_buffer_insert_cstr(embed_doc, (WB_UTINY *) lang->publicID->xmlDTD, 0) ||      /* DTD */
		    !wbxml_buffer_insert_cstr(embed_doc, (WB_UTINY *) "\" \"", 0) ||                     /* DTD */
		    !wbxml_buffer_insert_cstr(embed_doc, (WB_UTINY *) lang->publicID->xmlPublicID, 0) || /* Public ID */
		    !wbxml_buffer_insert_cstr(embed_doc, (WB_UTINY *) " PUBLIC \"", 0) ||                /*  PUBLIC " */
		    !wbxml_buffer_insert_cstr(embed_doc, (WB_UTINY *) lang->publicID->xmlRootElt, 0) ||  /* Root Element */
		    !wbxml_buffer_insert_cstr(embed_doc, (WB_UTINY *) "<!DOCTYPE ", 0))                  /* <!DOCTYPE */
		{
			tree_ctx->error = WBXML_ERROR_ENCODER_APPEND_DATA;
                	wbxml_buffer_destroy(embed_doc);
			return;
		}

                WBXML_DEBUG((WBXML_PARSER, "\t Embedded Doc : '%s'", wbxml_buffer_get_cstr(embed_doc)));

                /* Parse 'DevInf' Document */
                if ((ret = wbxml_tree_from_xml(wbxml_buffer_get_cstr(embed_doc),
                                               wbxml_buffer_len(embed_doc),
                                               &tree)) != WBXML_OK)
                {
                    tree_ctx->error = ret;
                    wbxml_buffer_destroy(embed_doc);
                    return;
                }

                /* Add Tree Node */
                tree_ctx->current = wbxml_tree_add_tree(tree_ctx->tree,
                                                        tree_ctx->current,
                                                        tree);
                if (tree_ctx->current == NULL)
                {
                    tree_ctx->error = WBXML_ERROR_INTERNAL;
                    wbxml_tree_destroy(tree);
                    wbxml_buffer_destroy(embed_doc);
                    return;
                }

                /* Clean-up */
                wbxml_buffer_destroy(embed_doc);
                tree_ctx->skip_lvl = 0;
            }
#endif /* WBXML_SUPPORT_SYNCML */
        }
        else {
            tree_ctx->skip_lvl--;
            return;
        }
    }

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
        /* Have we added a missing CDATA section ? 
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


void wbxml_tree_clb_xml_start_cdata(void *ctx)
{
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;

    /* Check for Error */
    if (tree_ctx->error != WBXML_OK)
        return;

    /* Are we skipping a whole node ? */
    if (tree_ctx->skip_lvl > 0)
        return;

    /* Add CDATA Node */
    tree_ctx->current = wbxml_tree_add_cdata(tree_ctx->tree, tree_ctx->current);
    if (tree_ctx->current == NULL) {
        tree_ctx->error = WBXML_ERROR_INTERNAL;
    }
}


void wbxml_tree_clb_xml_end_cdata(void *ctx)
{
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;

    /* Check for Error */
    if (tree_ctx->error != WBXML_OK)
        return;

    /* Are we skipping a whole node ? */
    if (tree_ctx->skip_lvl > 0)
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
        /* Go back one step upper in the tree */
        tree_ctx->current = tree_ctx->current->parent;
    }
}


void wbxml_tree_clb_xml_characters(void           *ctx,
                                   const XML_Char *ch,
                                   int             len)
{
    WBXMLTreeNode *node;
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;

    WBXML_DEBUG((WBXML_PARSER, "Expat text callback"));

    if (tree_ctx->expat_utf16) {
        /** @todo Convert from UTF-16 to UTF-8 */
    }

    /* Check for Error */
    if (tree_ctx->error != WBXML_OK)
        return;

    /* Are we skipping a whole node ? */
    if (tree_ctx->skip_lvl > 0)
        return;

#if defined ( WBXML_SUPPORT_SYNCML )
    /* Specific treatment for SyncML */
    switch (wbxml_tree_node_get_syncml_data_type(tree_ctx->current)) {
    case WBXML_SYNCML_DATA_TYPE_DIRECTORY_VCARD:
    case WBXML_SYNCML_DATA_TYPE_VCALENDAR:
    case WBXML_SYNCML_DATA_TYPE_VCARD:
    case WBXML_SYNCML_DATA_TYPE_VOBJECT:
        /* SyncML has some real design bugs
         * because the authors of the specification did not understand XML.
         *
         * There must be a hack to preserve the CRLFs of vFormat objects.
         * The only chance to do this is the detection of the vFormat itself
         * and the conversion of every LF to a CRLF.
         *
         * The line breaks are always in a single text node.
         * So a CR is appended to get a CRLF at the end.
         */

        if (len == 1 && ch[0] == '\n') /* line break - LF */
        {
            ch = "\r\n";
            len = 2;
        }

        /* Do not break here.
         * The CDATA handling is required for vFormat objects too.
         */
    case WBXML_SYNCML_DATA_TYPE_CLEAR:
        /*
         * Add a missing CDATA section node
         *
         * Example:
         * <Add>
         *   <CmdID>6</CmdID>
         *   <Meta><Type xmlns='syncml:metinf'>text/x-vcard</Type></Meta>
         *   <Item>
         *     <Source>
         *         <LocURI>pas-id-3F4B790300000000</LocURI>
         *     </Source>         
         *     <Data>BEGIN:VCARD
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
         *  END:VCARD</Data>
         *   </Item>
         * </Add>
         *
         * The end of CDATA section is assumed to be reached when parsing the end 
         * of </Data> element.
         *
         * This kind of document is erroneous, but we must handle it.
         * Normally, this should be:
         *
         *  ...
         *     <Data><!CDATA[[BEGIN:VCARD
         *  VERSION:2.1
         *  X-EVOLUTION-FILE-AS:Ximian, Inc.
         *  ...
         *  UID:pas-id-3F4B790300000000
         *  END:VCARD
         *  ]]></Data>
         *  ...
         */

        /* 
         * We add a missing CDATA section if we are not already in a CDATA section.
         *
         * We don't add a CDATA section if we have already added a CDATA section. This
         * permits to correctly handle good XML documents like this:
         *
         *  ...
         *     <Data><!CDATA[[BEGIN:VCARD
         *  VERSION:2.1
         *  X-EVOLUTION-FILE-AS:Ximian, Inc.
         *  ...
         *  UID:pas-id-3F4B790300000000
         *  END:VCARD
         *  ]]>
         *     </Data>
         *  ...
         *
         * In this example, the spaces beetwen "]]>" and "</Data>" must not be added
         * to a CDATA section. 
         */
        if ((tree_ctx->current != NULL) && 
            (tree_ctx->current->type != WBXML_TREE_CDATA_NODE) &&
            !((tree_ctx->current->children != NULL) && 
              (tree_ctx->current->children->type == WBXML_TREE_CDATA_NODE)))
        {
            /* Add CDATA Node */
            tree_ctx->current = wbxml_tree_add_cdata(tree_ctx->tree, tree_ctx->current);
            if (tree_ctx->current == NULL) {
                tree_ctx->error = WBXML_ERROR_INTERNAL;
                return;
            }
        }

        /* Now we can add the Text Node */
        break;

    default:
        /* NOP */
        break;
    } /* switch */
#endif /* WBXML_SUPPORT_SYNCML */

    /* We expect that "byte array" or BLOB types are 
     * encoded in Base 64 in the XML code, since they may contain binary data.
     */

    node = tree_ctx->current;
    if (node && node->type == WBXML_TREE_ELEMENT_NODE &&
        node->name->type == WBXML_VALUE_TOKEN &&
        node->name->u.token->options & WBXML_TAG_OPTION_BINARY)
    {
        WBXML_DEBUG((WBXML_PARSER, "    Binary tag: Caching base64 encoded data for later conversion."));
        if (node->content == NULL)
        {
            node->content = wbxml_buffer_create(ch, len, 1);
            if (node->content == NULL)
                tree_ctx->error = WBXML_ERROR_NOT_ENOUGH_MEMORY;
        } else {
            if (!wbxml_buffer_append_data(node->content, ch, len))
                tree_ctx->error = WBXML_ERROR_NOT_ENOUGH_MEMORY;
        }
        return;
    }

    /* Add Text Node */
    if (wbxml_tree_add_text(tree_ctx->tree,
                            tree_ctx->current,
                            (const WB_UTINY*) ch,
                            len) == NULL)
    {
        tree_ctx->error = WBXML_ERROR_INTERNAL;
    }
}


void wbxml_tree_clb_xml_pi(void           *ctx,
                           const XML_Char *target,
                           const XML_Char *data)
{
    WBXMLTreeClbCtx *tree_ctx = (WBXMLTreeClbCtx *) ctx;

    if (tree_ctx->expat_utf16) {
        /** @todo Convert from UTF-16 to UTF-8 */
    }

    /* Check for Error */
    if (tree_ctx->error != WBXML_OK)
        return;

    /* Are we skipping a whole node ? */
    if (tree_ctx->skip_lvl > 0)
        return;

    /** @todo wbxml2xml_clb_pi() */
}

#endif /* HAVE_EXPAT */
