/*
 * libwbxml, the WBXML Library.
 * Copyright (C) 2002-2008 Aymerick Jehanne <aymerick@jehanne.org>
 * Copyright (C) 2011,2014 Michael Bell <michael.bell@web.de>
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
 * @file wbxml_lists.h 
 * @ingroup wbxml_lists
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/12/06
 *
 * @brief Generic Lists Functions
 */

#ifndef WBXML_LISTS_H
#define WBXML_LISTS_H

#include "wbxml_mem.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


/**
 * @brief WBXML Generic List
 */
typedef struct WBXMLList_s WBXMLList;


/** @addtogroup wbxml_lists  
 *  @{ 
 */

/**
 * @brief A List Element Cleaner Function prototype
 */
typedef void WBXMLListEltCleaner(void *item);

/**
 * @brief Create a List
 * @return The newly created List, or NULL if not enough memory
 * @warning Do NOT use this function directly, use wbxml_list_create() macro instead
 */
WBXML_DECLARE(WBXMLList *) wbxml_list_create_real(void);
#define wbxml_list_create() wbxml_mem_cleam(wbxml_list_create_real())

/**
 * @brief Destroy a List
 * @param list The List to destroy
 * @param destructor The function to destroy an element from list (if NULL, items are not destroyed from list)
 */
WBXML_DECLARE(void) wbxml_list_destroy(WBXMLList *list, WBXMLListEltCleaner *destructor);

/**
 * @brief Get list length
 * @param list The List
 * @return The List length
 */
WBXML_DECLARE(WB_ULONG) wbxml_list_len(WBXMLList *list);

/**
 * @brief Append an element at end of list
 * @param list The List
 * @param elt The element to append which must be not null.
 * @return TRUE if element appended, FALSE if not enough memory
 */
WBXML_DECLARE(WB_BOOL) wbxml_list_append(WBXMLList *list, void *elt);

/**
 * @brief Append an element to a list
 * @param list The List
 * @param elt The element to insert which must be not null.
 * @param pos The index where to insert this element
 * @return TRUE if element appended, FALSE if not enough memory
 */
WBXML_DECLARE(WB_BOOL) wbxml_list_insert(WBXMLList *list, void *elt, WB_ULONG pos);

/**
 * @brief Get an Element from list
 * @param list The List
 * @param index Index of element to get (index in start starts at '0')
 * @return The element, or NULL if not found
 */
WBXML_DECLARE(void *) wbxml_list_get(WBXMLList *list, WB_ULONG index);

/**
 * @brief Extract first element of a List
 * @param list The List
 * @return The element extracted, or NULL if not found
 * @note The element is removed from this list
 */
WBXML_DECLARE(void *) wbxml_list_extract_first(WBXMLList *list);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_LISTS_H */
