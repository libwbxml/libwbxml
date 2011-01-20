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
 * @file wbxml_mem.c
 * @ingroup wbxml_mem
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/11/24
 *
 * @brief Memory Functions
 */

#include "wbxml_mem.h"


/***************************************************
 *    Public Functions
 */

WBXML_DECLARE(void *) wbxml_malloc(size_t size)
{
#ifdef WBXML_USE_LEAKTRACKER
    return lt_malloc(size);
#else
    return malloc(size);
#endif
}


WBXML_DECLARE(void) wbxml_free(void *memblock)
{
#ifdef WBXML_USE_LEAKTRACKER
    lt_free(memblock);
#else
    free(memblock);
#endif
}


WBXML_DECLARE(void *) wbxml_realloc(void *memblock, size_t size)
{
#ifdef WBXML_USE_LEAKTRACKER
    return lt_realloc(memblock, size);
#else
    return realloc(memblock, size);
#endif
}


WBXML_DECLARE(char *) wbxml_strdup(const char *str)
{
#ifdef WBXML_USE_LEAKTRACKER
    return lt_strdup(str);
#else
    return strdup(str);
#endif
}
