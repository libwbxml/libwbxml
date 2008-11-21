/*
 * Leaktrack, a Memory Leack Tracker.
 * Copyright (C) 2002-2008 Aymerick Jehanne <aymerick@jehanne.org>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *  
 * GPL v2: http://www.gnu.org/licenses/gpl.txt
 * 
 * Contact: aymerick@jehanne.org
 * Home: http://libwbxml.aymerick.com
 */

/** 
 * @file leaktrack.h
 * @ingroup leaktrack
 *
 * @brief This is a simple malloc()-wrapper. It does not return NULLs but
 * 	  instead panics.
 *
 * @note We have two wrappers. One that just checks for allocation failures and
 *		panics if they happen and one that tries to find allocation problems,
 * 		such as using an area after it has been freed.
 *		 Use of native or check wrapper can be modified in config.h
 *
 * @warning Do NOT use check or native wrapper directly. Instead use this macros:
 *	- lt_init_mem()
 *	- lt_shutdown_mem()
 *	- lt_malloc()
 *	- lt_free()
 *	- lt_realloc()
 *	- lt_strdup()
 *
 * @note Code adapted from Kannel project (http://www.kannel.org/)
 */ 
 
#ifndef LEAKTRACK_H
#define LEAKTRACK_H

#include <stdlib.h>
#include <stddef.h>


/* For DLL exported functions */
#ifdef WIN32
#define LT_DECLARE(type) __declspec(dllexport) type __stdcall
#define LT_DECLARE_NONSTD(type) __declspec(dllexport) type
#else
#define LT_DECLARE(type) type
#define LT_DECLARE_NONSTD(type) type
#endif /* WIN32 */


/* Define one of these depending on which malloc wrapper you want to use. */
/* #define LEAKTRACK_LEAKTRACK_USE_MEM_NATIVE 1 */
/* #define LEAKTRACK_USE_MEM_CHECK 1 */
#define LEAKTRACK_USE_MEM_SLOW 1

/* Define if your compiler supports the __func__ magic symbol. This is part of C99. */
#undef HAVE___FUNC__

/* Define if your compiler supports the __FUNCTION__ magic symbol. */
#undef HAVE___FUNCTION__

/* Make sure __func__ does something useful. */
#if defined(HAVE___FUNC__)
    /* Nothing to do. Life is so wonderful. */
#elif defined(HAVE___FUNCTION__)
    #define __func__ __FUNCTION__
#else
    #define __func__ "unknown"
#endif


/* Native Functions */
LT_DECLARE(void *) lt_native_malloc(size_t size);
LT_DECLARE(void *) lt_native_realloc(void *ptr, size_t size);
LT_DECLARE(void)   lt_native_free(void *ptr);
LT_DECLARE(char *) lt_native_strdup(const char *str);

/* Check Functions */
LT_DECLARE(void)   lt_check_init_mem(int slow_flag);
LT_DECLARE(void)   lt_check_shutdown(void);
LT_DECLARE(void *) lt_check_malloc(size_t size, const char *filename, long line, const char *function);
LT_DECLARE(void *) lt_check_realloc(void *p, size_t size, const char *filename, long line, const char *function);
LT_DECLARE(void)   lt_check_free(void *p, const char *filename, long line, const char *function);
LT_DECLARE(char *) lt_check_strdup(const char *str, const char *filename, long line, const char *function);
LT_DECLARE(void *) lt_check_claim_area(void *p, const char *filename, long line, const char *function);
LT_DECLARE(void)   lt_check_check_leaks(void);
LT_DECLARE(int)    lt_check_is_allocated(void *p);
LT_DECLARE(long)   lt_check_area_size(void *p);

/* "slow" == "checking" with a small variation */
#if LEAKTRACK_USE_MEM_SLOW
#define LEAKTRACK_USE_MEM_CHECK 1
#endif


#if LEAKTRACK_USE_MEM_NATIVE

/* Native wrapper */
#define lt_init_mem()
#define lt_check_leaks()
#define lt_malloc(size) (lt_native_malloc(size))
#define lt_realloc(ptr, size) (lt_native_realloc(ptr, size))
#define lt_free(ptr) (lt_native_free(ptr))
#define lt_strdup(str) (lt_native_strdup(str))
#define lt_assert_allocated(ptr, file, line, function)
#define lt_claim_area(ptr) (ptr)
#define lt_claim_area_for(ptr, file, line, func) (ptr)
#define lt_shutdown_mem()

#elif LEAKTRACK_USE_MEM_CHECK

/* Check wrapper */
#ifdef LEAKTRACK_USE_MEM_SLOW
#define lt_init_mem() (lt_check_init_mem(1))
#else
#define lt_init_mem() (lt_check_init_mem(0))
#endif

#define lt_check_leaks() (lt_check_check_leaks())
#define lt_malloc(size) (lt_check_malloc(size, __FILE__, __LINE__, __func__))
#define lt_realloc(ptr, size) (lt_check_realloc(ptr, size, __FILE__, __LINE__, __func__))
#define lt_free(ptr) (lt_check_free(ptr, __FILE__, __LINE__, __func__))
#define lt_strdup(str) (lt_check_strdup(str, __FILE__, __LINE__, __func__))
#define lt_assert_allocated(ptr, file, line, function) (lt_assert_place(lt_check_is_allocated(ptr), file, line, function))
#define lt_claim_area(ptr) (lt_check_claim_area(ptr, __FILE__, __LINE__, __func__))
#define lt_claim_area_for(ptr, file, line, func) (lt_check_claim_area(ptr, file, line, func))	
#define lt_shutdown_mem() (lt_check_shutdown())

#else

/* Unknown wrapper */
#error "Unknown malloc wrapper."

#endif


/* Make sure no-one uses the unwrapped functions by mistake */
#define malloc(n)	    do_not_call_malloc_directly
#define calloc(a, b)	do_not_use_calloc
#define realloc(p, n)	do_not_call_realloc_directly
#define free(p)	    	do_not_call_free_directly

#endif
