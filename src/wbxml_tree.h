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
 * @file wbxml_tree.h
 * @ingroup wbxml_tree
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 03/02/16
 *
 * @brief WBXML Tree
 */

#ifndef WBXML_TREE_H
#define WBXML_TREE_H

#include "wbxml.h"
#include "wbxml_elt.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <wbxml_config.h>

/** @addtogroup wbxml_tree
 *  @{ 
 */


/****************************************************
 *	WBXML Tree Structures
 */
  

/**
 * @brief WBXML Tree Node Type
 */
typedef enum WBXMLTreeNodeType_e
{
    WBXML_TREE_ELEMENT_NODE = 0, /**< Element Node */
    WBXML_TREE_TEXT_NODE,        /**< Text Node */
    WBXML_TREE_CDATA_NODE,       /**< CDATA Node */
    WBXML_TREE_PI_NODE,          /**< PI Node */
    WBXML_TREE_TREE_NODE         /**< WBXML Tree Node */
} WBXMLTreeNodeType;

/**
 * @brief WBXML Tree Node structure
 */
typedef struct WBXMLTreeNode_s
{
    WBXMLTreeNodeType   type;       /**< Node Type */
    WBXMLTag            *name;      /**< Node Name (if type is 'WBXML_TREE_ELEMENT_NODE') */
    WBXMLList           *attrs;     /**< Node Attributes (if type is 'WBXML_TREE_ELEMENT_NODE') */
    WBXMLBuffer         *content;   /**< Node Content (if  type is 'WBXML_TREE_TEXT_NODE')  */
    struct WBXMLTree_s  *tree;      /**< Node Tree (if  type is 'WBXML_TREE_TREE_NODE') */
    
    struct WBXMLTreeNode_s  *parent;    /**< Parent Node */
    struct WBXMLTreeNode_s  *children;  /**< Children Node */
    struct WBXMLTreeNode_s  *next;      /**< Next sibling Node */
    struct WBXMLTreeNode_s  *prev;      /**< Previous sibling Node */
} WBXMLTreeNode;


/**
 * @brief WBXML Tree structure
 * 
 * This structure is created when parsing a WBXML or XML document, thanks to
 * the functions wbxml_tree_from_wbxml() and wbxml_tree_from_xml().
 *
 * It represents the parsed document, and have this fields:
 *   - lang: the language table of the parsed document (in wbxml_tables.c)
 *   - root: the root element of the Tree representing the parsed document
 *   - orig_charset: the original charset encoding of the parsed document
 *
 * @note All the strings inside the WBXML Tree are encoded into UTF-8
 */
typedef struct WBXMLTree_s
{    
    const WBXMLLangEntry *lang;         /**< Language Table */
    WBXMLTreeNode        *root;         /**< Root Element */
    WBXMLCharsetMIBEnum   orig_charset; /**< Charset encoding of original document */
    WB_UTINY              cur_code_page;/**< Last seen code page */
} WBXMLTree;


/** 
 * WBXML Tree Clb Context Structure
 * @note Used by WBXML Tree Callbacks ('wbxml_tree_clb_wbxml.h' and 'wbxml_tree_clb_xml.h')
 */
typedef struct WBXMLTreeClbCtx_s {
    /* For XML and WBXML Clb */
    WBXMLTree     *tree;          /**< The WBXML Tree we are constructing */
    WBXMLTreeNode *current;       /**< Current Tree Node */
    WBXMLError     error;         /**< Error while parsing Document */
    /* For XML Clb */
    WB_ULONG       skip_lvl;      /**< Used to skip a whole XML node (used for SyncML) */
    WB_LONG        skip_start;    /**< Starting Skipping position in XML Document (used for SyncML) */
    WB_UTINY      *input_buff;    /**< Pointer to Input Buffer */
#if defined( HAVE_EXPAT )
    XML_Parser     xml_parser;    /**< Pointer to Expat XML Parser */
    WB_BOOL        expat_utf16;   /**< Is Expat compiled to output UTF-16 ? */
#endif /* HAVE_EXPAT */ 
} WBXMLTreeClbCtx;


#if defined ( WBXML_SUPPORT_SYNCML )
/**
 * SyncML Data Type (the type of data inside <Data> element)
 */
typedef enum WBXMLSyncMLDataType_e {
    WBXML_SYNCML_DATA_TYPE_NORMAL = 0,      /**< Not specific Data Type */
    WBXML_SYNCML_DATA_TYPE_WBXML,           /**< application/vnd.syncml-devinf+wbxml (WBXML Document) */
    WBXML_SYNCML_DATA_TYPE_CLEAR,			/**< text/clear */
    WBXML_SYNCML_DATA_TYPE_DIRECTORY_VCARD, /**< text/directory;profile=vCard */
    WBXML_SYNCML_DATA_TYPE_VCARD,           /**< text/x-vcard */
    WBXML_SYNCML_DATA_TYPE_VCALENDAR,       /**< text/x-vcalendar */
    WBXML_SYNCML_DATA_TYPE_VOBJECT          /**< Hack: we assume that any <Data> inside a <Replace> or <Add> Item is a vObjec (vCard / vCal / ...) */
} WBXMLSyncMLDataType;
#endif /* WBXML_SUPPORT_SYNCML */


/****************************************************
 *  WBXML Tree Building Functions
 */

/**
 * @brief Parse a WBXML document, using internal callbacks (in wbxml_tree_clb_wbxml.c), and construct a WBXML Tree
 * @param wbxml     [in]  The WBXML document to parse
 * @param wbxml_len [in]  The WBXML document length
 * @param lang      [in]  Can be used to force parsing of a given Language (set it to WBXML_LANG_UNKNOWN if you don't want to force anything)
 * @param tree      [out] The resulting WBXML Tree 
 * @result Return WBXML_OK if no error, an error code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_tree_from_wbxml(WB_UTINY *wbxml,
                                                WB_ULONG wbxml_len,
                                                WBXMLLanguage lang,
                                                WBXMLCharsetMIBEnum charset,
                                                WBXMLTree **tree);

/**
 * @brief Convert a WBXML Tree to a WBXML document
 * @param tree      [in]  The WBXML Tree to convert
 * @param wbxml     [out] The resulting WBXML document
 * @param wbxml_len [out] The resulting WBXML document length
 * @param params    [in]  Parameters (if NULL, default values are used)
 * @result Return WBXML_OK if no error, an error code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_tree_to_wbxml(WBXMLTree *tree,
                                              WB_UTINY **wbxml,
                                              WB_ULONG  *wbxml_len,
                                              WBXMLGenWBXMLParams *params);

/**
 * @brief Parse an XML document, using internal callbacks (in wbxml_tree_clb_xml.c), and construct a WBXML Tree
 * @param xml     [in]  The XML document to parse
 * @param xml_len [in]  Length of the XML document
 * @param tree    [out] The resulting WBXML Tree 
 * @result Return WBXML_OK if no error, an error code otherwise
 * @note Needs 'HAVE_EXPAT' compile flag
 */
WBXML_DECLARE(WBXMLError) wbxml_tree_from_xml(WB_UTINY *xml,
                                              WB_ULONG xml_len,
                                              WBXMLTree **tree);

/**
 * @brief Convert a WBXML Tree to an XML document
 * @param tree    [in]  The WBXML Tree to convert
 * @param xml     [out] The resulting XML document
 * @param xml_len [out] The resulting XML document length
 * @param params  [in]  Parameters (if NULL, default values are used)
 * @result Return WBXML_OK if no error, an error code otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_tree_to_xml(WBXMLTree *tree,
                                            WB_UTINY **xml,
                                            WB_ULONG  *xml_len,
                                            WBXMLGenXMLParams *params);

/** @todo Libxml support ! */
#if defined( HAVE_LIBXML )

/**
 * @brief Parse a LibXML document, and construct the corresponding WBXML Tree
 * @param libxml_doc [in]  The LibXML document to parse
 * @param tree       [out] The resulting WBXML Tree 
 * @result Return WBXML_OK if no error, an error code otherwise
 * @note Needs 'HAVE_LIBXML' compile flag
 */
WBXML_DECLARE(WBXMLError) wbxml_tree_from_libxml_doc(xmlDocPtr libxml_doc,
                                                     WBXMLTree **tree);

/**
 * @brief Parse a WBXML Tree, and construct the corresponding LibXML document
 * @param tree       [in]  The WBXML Tree to parse
 * @param libxml_doc [out] The resulting LibXML document
 * @result Return WBXML_OK if no error, an error code otherwise
 * @note Needs 'HAVE_LIBXML' compile flag
 */
WBXML_DECLARE(WBXMLError) wbxml_tree_to_libxml_doc(WBXMLTree *tree,
                                                   xmlDocPtr *libxml_doc);

#endif /* HAVE_LIBXML */


/****************************************************
 *	WBXML Tree Functions
 */

/**
 * @brief Create a Tree Node structure
 * @param type Node type
 * @return The newly created Tree Node, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_node_create(WBXMLTreeNodeType type);

/**
 * @brief Destroy a Tree Node structure
 * @param node The Tree Node structure to destroy
 * @note The Node is freed, but not extracted from its WBXML Tree (use wbxml_tree_extract_node() before)
 */
WBXML_DECLARE(void) wbxml_tree_node_destroy(WBXMLTreeNode *node);

/**
 * @brief Destroy a Tree Node structure (used for wbxml_list_destroy())
 * @param node The Tree Node structure to destroy
 */
WBXML_DECLARE(void) wbxml_tree_node_destroy_item(void *node);

/**
 * @brief Destroy a Tree Node structure, and all its children
 * @param node The Tree Node structure to destroy
 * @note The Node (and its sub-tree) is freed, but not extracted from its WBXML Tree (use wbxml_tree_extract_node() before)
 */
WBXML_DECLARE(void) wbxml_tree_node_destroy_all(WBXMLTreeNode *node);

/**
 * @brief Create a Tree Node structure, given the XML node name
 * @param lang_table Language table
 * @param name       XML node name
 * @return The newly created Tree Node, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_node_create_xml_elt(const WBXMLLangEntry *lang_table,
                                                              const WB_UTINY *name);

/**
 * @brief Create a Tree Node structure, given the XML node name and text content
 * @param lang_table Language table
 * @param name       XML node name
 * @param text       Text content
 * @param len        Text content length
 * @return The newly created Tree Node, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_node_create_xml_elt_with_text(const WBXMLLangEntry *lang_table,
                                                                        const WB_UTINY *name,
                                                                        const WB_UTINY *text,
                                                                        WB_ULONG len);

/**
 * @brief Create a Text Node structure
 * @param text       Text content
 * @param len        Text content length
 * @return The newly created Tree Node, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_node_create_text(const WB_UTINY *text,
                                                           WB_ULONG len);

/**
 * @brief Create a CDATA Node structure
 * @param text       Text content
 * @param len        Text content length
 * @return The newly created Tree Node, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_node_create_cdata(const WB_UTINY *text,
                                                            WB_ULONG len);

/**
 * @brief Create a Tree Node structure
 * @param root Root node for this Tree
 * @param lang Language table to use
 * @param orig_charset Original charset
 * @return The newly created Tree Node, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_node_create_tree(WBXMLTreeNode *root,
                                                           WBXMLLanguage lang,
                                                           WBXMLCharsetMIBEnum orig_charset);

/**
 * @brief Add a Child node
 * @param parent Parent node
 * @param node   Child node to add
 * @return TRUE if added or FALSE if error
 */
WBXML_DECLARE(WB_BOOL) wbxml_tree_node_add_child(WBXMLTreeNode *parent,
                                                 WBXMLTreeNode *node);

/**
 * @brief Extract a node
 * @param node Node to extract
 * @return TRUE if extracted or FALSE if error
 */
WBXML_DECLARE(WBXMLError) wbxml_tree_node_extract(WBXMLTreeNode *node);

/**
 * @brief Add a WBXML Attribute to a Tree Node structure
 * @param node The Tree Node to modify
 * @param attr The WBXML Attribute to add
 * @return WBXML_OK if no error, an error code otherwise
 * @note This is only meanfull for an element node
 */
WBXML_DECLARE(WBXMLError) wbxml_tree_node_add_attr(WBXMLTreeNode *node,
                                                   WBXMLAttribute *attr);

/**
 * @brief Add a WBXML Attributes list to a Tree Node structure
 * @param node  The Tree Node to modify
 * @param attrs The WBXML Attributes to add
 * @return WBXML_OK if no error, an error code otherwise
 * @note This is only meanfull for an element node
 */
WBXML_DECLARE(WBXMLError) wbxml_tree_node_add_attrs(WBXMLTreeNode *node,
                                                    WBXMLAttribute **attrs);

/**
 * @brief Add an XML Attribute to a Tree Node structure
 * @param lang_table Language table
 * @param node The Tree Node to modify
 * @param name The XML Attribute name
 * @param value The XML Attribute value
 * @return WBXML_OK if no error, an error code otherwise
 * @note This is only meanfull for an element node
 */
WBXML_DECLARE(WBXMLError) wbxml_tree_node_add_xml_attr(const WBXMLLangEntry *lang_table,
                                                       WBXMLTreeNode *node,
                                                       const WB_UTINY *name,
                                                       const WB_UTINY *value);

/**
 * @brief Add an XML Attributes list to a Tree Node structure
 * @param lang_table Language table
 * @param node  The Tree Node to modify
 * @param attrs The XML Attributes to add
 * @return WBXML_OK if no error, an error code otherwise
 * @note This is only meanfull for an element node
 */
WBXML_DECLARE(WBXMLError) wbxml_tree_node_add_xml_attrs(const WBXMLLangEntry *lang_table,
                                                        WBXMLTreeNode *node,
                                                        const WB_UTINY **attrs);

/**
 * @brief Get an Element Node, given the Element Name
 * @param node   The Tree Node where to start searching
 * @param name   The Element Name we are searching
 * @param recurs If FALSE, only search into direct childs of 'node'
 * @return The found Tree Node, or NULL if not found
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_node_elt_get_from_name(WBXMLTreeNode *node,
                                                                 const char *name,
                                                                 WB_BOOL recurs);

#if defined ( WBXML_SUPPORT_SYNCML )

/**
 * @brief Get the SyncML Data Type of this Tree Node
 * @param node The Tree Node
 * @return The SyncML Data Type of this Tree Node (cf: WBXMLSyncMLDataType enum)
 * @note If no specific Data Type is found, this function returns 'WBXML_SYNCML_DATA_TYPE_NORMAL'
 */
WBXML_DECLARE(WBXMLSyncMLDataType) wbxml_tree_node_get_syncml_data_type(WBXMLTreeNode *node);

#endif /* WBXML_SUPPORT_SYNCML */

/**
 * @brief Check if a node have an Element Node in its children list
 * @param node The Tree Node
 * @return YES if one of the node children is an Element, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_tree_node_have_child_elt(WBXMLTreeNode *node);

/**
 * @brief Get all children from node
 * @param node The Tree Node
 * @return A list of all children belonging to this node, or NULL if no children found
 */
WBXML_DECLARE(WBXMLList*) wbxml_tree_node_get_all_children(WBXMLTreeNode *node);


/**
 * @brief Create a Tree structure
 * @param lang Tree Language
 * @param orig_charset Original tree charset
 * @return The newly created Tree, or NULL if not enough memory
 * @note The 'orig_charset' is used for further Tree encoding, it does NOT set
 *       the internal Tree representation charset (UTF8 is always used).
 */
WBXML_DECLARE(WBXMLTree *) wbxml_tree_create(WBXMLLanguage lang,
                                             WBXMLCharsetMIBEnum orig_charset);

/**
 * @brief Destroy a Tree structure, and all its nodes
 * @param tree The Tree structure to destroy
 */
WBXML_DECLARE(void) wbxml_tree_destroy(WBXMLTree *tree);

/**
 * @brief Add a Node to a Tree
 * @param tree   The Tree to modify
 * @param parent Parent of the new Node (ie: Position where to add the new Node in Tree)
 * @param node   The new Tree Node to add
 * @return TRUE is added, or FALSE if error.
 * @note If 'parent' is NULL: if 'tree' already have a Root Element this function returns FALSE, else 'node' becomes the Root Element of 'tree'
 */
WBXML_DECLARE(WB_BOOL) wbxml_tree_add_node(WBXMLTree *tree,
                                           WBXMLTreeNode *parent,
                                           WBXMLTreeNode *node);

/**
 * @brief Extract a Tree Node from its WBXML Tree
 * @param tree  The Tree to modify
 * @param node  The Tree Node to extract
 * @return WBXML_OK if no error, an error code otherwise
 * @note The node is extracted but not freed
 */
WBXML_DECLARE(WBXMLError) wbxml_tree_extract_node(WBXMLTree *tree,
                                                  WBXMLTreeNode *node);

/**
 * @brief Add an Element Node to Tree, given its WBXML Tag
 * @param tree   The Tree to modify
 * @param parent Parent of the new Node (ie: Position where to add the new Node in Tree)
 * @param tag    Element to add
 * @return The newly created node, or NULL if error.
 * @note If 'parent' is NULL: if 'tree' already have a Root Element this function returns NULL, else 'node' becomes the Root Element of 'tree'
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_add_elt(WBXMLTree *tree,
                                                  WBXMLTreeNode *parent,
                                                  WBXMLTag *tag);

/**
 * @brief Add a Tag Element Node to Tree, with its WBXML Attributes
 * @param tree   The Tree to modify
 * @param parent Parent of the new Node (ie: Position where to add the new Node in Tree)
 * @param tag    Element to add
 * @param attrs  Element attributes
 * @return The newly created node, or NULL if error.
 * @note If 'parent' is NULL: if 'tree' already have a Root Element this function returns NULL, else 'node' becomes the Root Element of 'tree'
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_add_elt_with_attrs(WBXMLTree *tree,
                                                             WBXMLTreeNode *parent,
                                                             WBXMLTag *tag,
                                                             WBXMLAttribute **attrs);

/**
 * @brief Add an Element Node to a Tree, given its XML Name
 * @param tree   The Tree to modify
 * @param parent Parent of the new Node (ie: Position where to add the new Node in Tree)
 * @param name   XML element name to add
 * @return The newly created node, or NULL if error.
 * @note If 'parent' is NULL: if 'tree' already have a Root Element this function returns NULL, else 'node' becomes the Root Element of 'tree'
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_add_xml_elt(WBXMLTree *tree,
                                                      WBXMLTreeNode *parent,
                                                      WB_UTINY *name);

/**
 * @brief Add an Element Node to Tree, with its WBXML Attributes, given there XML values
 * @param tree   The Tree to modify
 * @param parent Parent of the new Node (ie: Position where to add the new Node in Tree)
 * @param name   XML element name to add
 * @param attrs  XML element attributes
 * @return The newly created node, or NULL if error.
 * @note If 'parent' is NULL: if 'tree' already have a Root Element this function returns NULL, else 'node' becomes the Root Element of 'tree'
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_add_xml_elt_with_attrs(WBXMLTree *tree,
                                                                 WBXMLTreeNode *parent,
                                                                 WB_UTINY *name,
                                                                 const WB_UTINY **attrs);

/**
 * @brief Add a Text Node to Tree
 * @param tree   The Tree to modify
 * @param parent Parent of the new Node (ie: Position where to add the new Node in Tree)
 * @param text   Text to add
 * @param len    Text length
 * @return The newly created node, or NULL if error.
 * @note If 'parent' is NULL: if 'tree' already have a Root Element this function returns NULL, else 'node' becomes the Root Element of 'tree'
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_add_text(WBXMLTree *tree,
                                                   WBXMLTreeNode *parent,
                                                   const WB_UTINY *text,
                                                   WB_ULONG len);

/**
 * @brief Add CDATA Node to Tree
 * @param tree   The Tree to modify
 * @param parent Parent of the new Node (ie: Position where to add the new Node in Tree)
 * @return The newly created node, or NULL if error.
 * @note If 'parent' is NULL: if 'tree' already have a Root Element this function returns NULL, else 'node' becomes the Root Element of 'tree'
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_add_cdata(WBXMLTree *tree,
                                                    WBXMLTreeNode *parent);

/** @todo wbxml_tree_add_cdata_with_text() */

/**
 * @brief Add a Tree Node to Tree
 * @param tree     The Tree to modify
 * @param parent   Parent of the new Node (ie: Position where to add the new Node in Tree)
 * @param new_tree The new Tree to add (will be freed when destroying the main Tree, so caller must not free it)
 * @return The newly created node, or NULL if error.
 * @note If 'parent' is NULL: if 'tree' already have a Root Element this function returns NULL, else 'node' becomes the Root Element of 'tree'
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_add_tree(WBXMLTree *tree,
                                                   WBXMLTreeNode *parent,
                                                   WBXMLTree *new_tree);

/**
 * @brief Add an Element Node to a Tree, given its XML Name, its attributes and a text content
 * @param tree   The Tree to modify
 * @param parent Parent of the new Node (ie: Position where to add the new Node in Tree)
 * @param name   XML element name to add
 * @param attrs  XML element attributes
 * @param text   Text content for this new element
 * @param len    Text content length
 * @return The newly created node, or NULL if error.
 * @note If 'parent' is NULL: if 'tree' already have a Root Element this function returns NULL, else 'node' becomes the Root Element of 'tree'
 */
WBXML_DECLARE(WBXMLTreeNode *) wbxml_tree_add_xml_elt_with_attrs_and_text(WBXMLTree *tree,
                                                                          WBXMLTreeNode *parent,
                                                                          WB_UTINY *name,
                                                                          const WB_UTINY **attrs,
                                                                          const WB_UTINY *text,
                                                                          WB_ULONG len);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_TREE_H */
