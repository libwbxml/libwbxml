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
 * @file wbxml_mem.h
 * @ingroup wbxml_mem
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/07/01
 *
 * @brief Memory Functions
 */

#ifndef WBXML_MEM_H
#define WBXML_MEM_H

#include "wbxml.h"

#ifdef WBXML_USE_LEAKTRACKER
#include "leaktrack.h"
#include "lt_log.h"
#define wbxml_mem_cleam(ptr) (lt_claim_area(ptr))
#else  /* WBXML_USE_LEAKTRACKER */
#define wbxml_mem_cleam(ptr) (ptr)
#endif /* WBXML_USE_LEAKTRACKER */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup wbxml_mem  
 *  @{ 
 */

/**
 * @brief Alloc a Memory Block
 * @param size Size of Memory to alloc
 * @return The newly mlloced Memory Block, or NULL if not enough memory
 */
WBXML_DECLARE(void *) wbxml_malloc(size_t size);

/**
 * @brief Free a Memory Block
 * @param memblock The Memory Block to free
 */
WBXML_DECLARE(void) wbxml_free(void *memblock);

/**
 * @brief Realloc a Memory Block
 * @param memblock The Memory Block to realloc
 * @param size Size of Memory to realloc
 * @return The newly realloced Memory Block, or NULL if not enough memory
 */
WBXML_DECLARE(void *) wbxml_realloc(void *memblock, size_t size);

/**
 * @brief Duplicate a C String
 * @param str The C String to duplicate
 * @return The newly duplicated C String, or NULL if not enough memory
 */
WBXML_DECLARE(char *) wbxml_strdup(const char *str);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_MEM_H */
