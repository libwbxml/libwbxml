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
 * @file wbxml_lists.c
 * @ingroup wbxml_lists
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/12/06
 *
 * @brief Generic Lists Functions
 */

#include "wbxml.h"
#include "wbxml_lists.h"

/** Element of this list */
typedef struct WBXMLListElt_s
{
    void *item;                     /**< Element item */
    struct WBXMLListElt_s *next;    /**< Next Element */  
} WBXMLListElt;

/** The Generic List type */
struct WBXMLList_s
{
    WBXMLListElt *head;         /**< Head of the list */
    WBXMLListElt *tail;         /**< Tail of the list */
    WB_ULONG len;               /**< Number of elements in List */
};

/* Private functions prototypes */
static WBXMLListElt *wbxml_elt_create_real(void *item);
#define wbxml_elt_create(a) wbxml_mem_cleam(wbxml_elt_create_real(a))

static void wbxml_elt_destroy(WBXMLListElt *elt, WBXMLListEltCleaner *destructor);


/**********************************
 *    Public functions
 */

WBXML_DECLARE(WBXMLList *) wbxml_list_create_real(void)
{
    WBXMLList *list = NULL;
    
    if ((list = wbxml_malloc(sizeof(WBXMLList))) == NULL)
        return NULL;

    list->head = NULL;
    list->tail = NULL;
    list->len = 0;
    
    return list;    
}


WBXML_DECLARE(void) wbxml_list_destroy(WBXMLList *list, WBXMLListEltCleaner *destructor)
{
    WBXMLListElt *elt = NULL, *next = NULL;

    if (list == NULL)
        return;

    elt = list->head;

    while (elt != NULL) {
        next = elt->next;
        wbxml_elt_destroy(elt, destructor);
        elt = next;
    }

    wbxml_free(list);
}


WBXML_DECLARE(WB_ULONG) wbxml_list_len(WBXMLList *list)
{
    if (list == NULL)
        return 0;
    else
        return list->len;
}


WBXML_DECLARE(WB_BOOL) wbxml_list_append(WBXMLList *list, void *item)
{
    if (list == NULL)
        return FALSE;

    if (item == NULL)
        return FALSE;

    if (list->head == NULL) {
        /* Empty list */
        if ((list->head = wbxml_elt_create(item)) == NULL)
            return FALSE;

        list->tail = list->head;
    }
    else {
        /* Element is the new Tail */
        if ((list->tail->next = wbxml_elt_create(item)) == NULL)
            return FALSE;

        list->tail = list->tail->next;
    }

    list->len++;

    return TRUE;
}


WBXML_DECLARE(WB_BOOL) wbxml_list_insert(WBXMLList *list, void *item, WB_ULONG pos)
{
    WBXMLListElt *elt = NULL, *prev = NULL, *new_elt = NULL;
    WB_ULONG i = 0;

    if (list == NULL)
        return FALSE;

    if (item == NULL)
        return FALSE;

    if ((new_elt = wbxml_elt_create(item)) == NULL)
        return FALSE;

    /* Empty List */
    if (list->len == 0) {
        list->head = new_elt;
        list->tail = list->head;
    }
    else {
        /* Insert at Head */
        if (pos == 0) {
            /* New Head */
            new_elt->next = list->head;
            list->head = new_elt;
        }
        else {
            /* If position is greater than list length, just append it at tail */
            if (pos >= list->len) {
                list->tail->next = new_elt;
                list->tail = list->tail->next;
            }
            else {
                /* Insert Element */
                elt = list->head;

                for (i=0; i<pos; i++) {
                    prev = elt;
                    elt = elt->next;
                }

                prev->next = new_elt;
                new_elt->next = elt;
            }
        }
    }

    list->len++;

    return TRUE;
}


WBXML_DECLARE(void *) wbxml_list_get(WBXMLList *list, WB_ULONG index)
{
    WBXMLListElt *elt = NULL;
    WB_ULONG i = 0;

    if ((list == NULL) || (index >= wbxml_list_len(list)))
        return NULL;    

    /* We start to search from head */
    elt = list->head;

    for (i=0; i<index; i++)
        elt = elt->next;

    return elt->item;
}


WBXML_DECLARE(void *) wbxml_list_extract_first(WBXMLList *list)
{
    WBXMLListElt *elt = NULL;
    void *result = NULL;

    if ((list == NULL) || (wbxml_list_len(list) == 0))
        return NULL;

    elt = list->head;
    result = elt->item;

    if ((list->head = list->head->next) == NULL)
        list->tail = NULL;

    wbxml_elt_destroy(elt, NULL);

    list->len--;

    return result;
}


/**********************************
 *    Private functions
 */

/**
 * @brief Create a List Element
 * @param item Item of Element to create
 * @return The newly created Element, or NULL if not enough memory
 * @warning Do NOT use this function directly, use wbxml_list_create() macro instead
 */
static WBXMLListElt *wbxml_elt_create_real(void *item)
{
    WBXMLListElt *elt = NULL;

    if (item == NULL)
        return NULL;

    if ((elt = wbxml_malloc(sizeof(WBXMLListElt))) == NULL)
        return NULL;

    elt->item = item;
    elt->next = NULL;

    return elt;
}


/**
 * @brief Destroy a List Element
 * @param elt The element to destroy
 * @param destructor The Destructor Function to clean Element Item (can be NULL)
 */
static void wbxml_elt_destroy(WBXMLListElt *elt, WBXMLListEltCleaner *destructor)
{
    if (elt == NULL)
        return;

    if (destructor != NULL)
        destructor(elt->item);

    wbxml_free(elt);
}
