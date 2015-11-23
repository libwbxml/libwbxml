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
 * @file wbxml_buffers.h 
 * @ingroup wbxml_buffers
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 02/03/12
 *
 * @brief Generic Buffers Functions
 *
 * @note Original idea: Kannel Project (http://kannel.3glab.org/)
 */

#ifndef WBXML_BUFFERS_H
#define WBXML_BUFFERS_H

#include <stdio.h>

#include "wbxml.h"
#include "wbxml_lists.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * @brief WBXML Generic Buffer
 */
typedef struct WBXMLBuffer_s WBXMLBuffer;


/** @addtogroup wbxml_buffers  
 *  @{ 
 */

/**
 * @brief Create a Buffer
 * @param data The initial data for buffer
 * @param len Size of data
 * @param malloc_block Size of the initial malloc block (tune this parameter to avoid too many reallocations)
 * @return The newly created Buffer, or NULL if not enought memory
 * @warning Do NOT use this function directly, use wbxml_buffer_create() macro instead
 */
WBXML_DECLARE(WBXMLBuffer *) wbxml_buffer_create_real(const WB_UTINY *data, WB_ULONG len, WB_ULONG malloc_block);

/** Wrapper around wbxml_buffer_create_real() to track Memory */
#define wbxml_buffer_create(a,b,c) \
  wbxml_mem_cleam(wbxml_buffer_create_real((const WB_UTINY *)a,b,c))

/** Wrapper around wbxml_buffer_create() when creating buffer with a C String (NULL Terminated) */
#define wbxml_buffer_create_from_cstr(a) \
  wbxml_buffer_create((const WB_UTINY *)a,WBXML_STRLEN(a),WBXML_STRLEN(a))

/**
 * @brief Create a static Buffer
 * @param data Buffer data
 * @param len  Data lenght
 * @return The newly created Buffer, or NULL if not enough memory
 * @note A static buffer can't be modified, so do not use functions dedeicated to dynamic buffers
 *       as wbxml_buffer_insert() or wbxml_buffer_append()
 * @warning Do NOT use this function directly, use wbxml_buffer_sta_create() macro instead
 */
WBXML_DECLARE(WBXMLBuffer *) wbxml_buffer_sta_create_real(const WB_UTINY *data, WB_ULONG len);

/** Wrapper around wbxml_buffer_sta_create_real() to track Memory */
#define wbxml_buffer_sta_create(a,b) \
  wbxml_mem_cleam(wbxml_buffer_sta_create_real((const WB_UTINY *)a,b))

/** Wrapper around wbxml_buffer_sta_create() when creating static buffer with a C String (NULL Terminated) */
#define wbxml_buffer_sta_create_from_cstr(a) \
  wbxml_buffer_sta_create((const WB_UTINY *)a,WBXML_STRLEN(a))

/**
 * @brief Destroy a Buffer
 * @param buff The Buffer to destroy
 */
WBXML_DECLARE(void) wbxml_buffer_destroy(WBXMLBuffer *buff);

/**
 * @brief Destroy a Buffer (used for wbxml_list_destroy())
 * @param buff The Buffer to destroy
 */
WBXML_DECLARE_NONSTD(void) wbxml_buffer_destroy_item(void *buff);

/**
 * Duplicate a Buffer
 *
 * Even if a static buffer is provided, the duplicated buffer is
 * a dynamic buffer.
 *
 * @param buff The Buffer to duplicate
 * @return The duplicated buffer, or NULL if not enough memory
 */
WBXML_DECLARE(WBXMLBuffer *) wbxml_buffer_duplicate(WBXMLBuffer *buff);

/**
 * @brief Get data length of a buffer
 * @param buff The Buffer
 * @return The Buffer data length
 */
WBXML_DECLARE(WB_ULONG) wbxml_buffer_len(WBXMLBuffer *buff);

/**
 * @brief Get a byte from a Buffer
 * @param buff The Buffer
 * @param pos Byte position in buffer
 * @param result The resulting char
 * @return TRUE if OK, or FALSE if error
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_get_char(WBXMLBuffer *buff, WB_ULONG pos, WB_UTINY *result);

/**
 * @brief Set a byte in a dynamic Buffer
 * @param buff The Buffer
 * @param pos Byte position in buffer
 * @param ch The character to set
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_set_char(WBXMLBuffer *buff, WB_ULONG pos, WB_UTINY ch);

/**
 * @brief Get pointer to internal buffer data
 * @param buff The Buffer
 * @return Pointer to buffer data, or "" if buffer is NULL or empty
 */
WBXML_DECLARE(WB_UTINY *) wbxml_buffer_get_cstr(WBXMLBuffer *buff);

/**
 * @brief Insert a Buffer into a dynamic Buffer
 * @param to The Buffer to modify
 * @param buff The Buffer to insert
 * @param pos The position of insertion in 'to'
 * @return TRUE if data inserted, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_insert(WBXMLBuffer *to, WBXMLBuffer *buff, WB_ULONG pos);

/**
 * @brief Insert a C String into a dynamic Buffer
 * @param to The Buffer to modify
 * @param str The BC String to insert
 * @param pos The position of insertion in 'to'
 * @return TRUE if data inserted, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_insert_cstr(WBXMLBuffer *to, const WB_UTINY *str, WB_ULONG pos);

/**
 * @brief Append a Buffer to a dynamic Buffer
 * @param dest The destination Buffer
 * @param buff The Buffer to append
 * @return TRUE if buffer appended, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_append(WBXMLBuffer *dest, WBXMLBuffer *buff);


/**
 * @brief Append data to a dynamic Buffer
 * @param buff The Buffer
 * @param data Data to append
 * @param len Data length
 * @return TRUE if data appended, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_append_data_real(WBXMLBuffer *buff, const WB_UTINY *data, WB_ULONG len);

/** Wrapper around wbxml_buffer_append_data_real() to avoid Casts in code */
#define wbxml_buffer_append_data(a,b,c) wbxml_buffer_append_data_real(a,(const WB_UTINY *)b,c)

/**
 * @brief Append a C String (NULL terminated) to a dynamic Buffer
 * @param buff The Buffer
 * @param data String to append
 * @return TRUE if data appended, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_append_cstr_real(WBXMLBuffer *buff, const WB_UTINY *data);

/** Wrapper around wbxml_buffer_append_cstr_real() to avoid Casts in code */
#define wbxml_buffer_append_cstr(a,b) wbxml_buffer_append_cstr_real(a,(const WB_UTINY *)b)


/**
 * @brief Append a byte to a dynamic Buffer
 * @param buff The Buffer
 * @param ch Byte to append
 * @return TRUE if byte appended, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_append_char(WBXMLBuffer *buff, WB_UTINY ch);

/**
 * @brief Append a Multibyte Integer to a dynamic Buffer
 * @param buff The Buffer
 * @param value The value to append
 * @return TRUE if value appended, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_append_mb_uint_32(WBXMLBuffer *buff, WB_ULONG value);

/**
 * @brief Delete a range of Bytes in a  dynamicBuffer
 * @param buff The Buffer
 * @param pos Position where to start deletion
 * @param len Number of bytes to delete
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_delete(WBXMLBuffer *buff, WB_ULONG pos, WB_ULONG len);

/**
 * @brief Shrink all spaces in a  dynamicBuffer
 * @param buff The Buffer to shrink
 * @note Replace every consecutive sequence of spaces into one unique whitespace
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_shrink_blanks(WBXMLBuffer *buff);

/**
 * @brief Remove whitespaces at beginning and end of a dynamic Buffer
 * @param buff The Buffer to strip
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_strip_blanks(WBXMLBuffer *buff);

/**
 * @brief Compare two Buffers
 * @param buff1
 * @param buff2
 * @return 0 if they are equal, negative if `buff1' is less than `buff2' and positive if greater
 */
WBXML_DECLARE(WB_LONG) wbxml_buffer_compare(WBXMLBuffer *buff1, WBXMLBuffer *buff2);

/**
 * @brief Compare a WBXML Buffer with a C String
 * @param buff The WBXML Buffer
 * @param str  The C String
 * @return 0 if they are equal, negative if `buff' is less than `str' and positive if greater
 */
WBXML_DECLARE(WB_LONG) wbxml_buffer_compare_cstr(WBXMLBuffer *buff, const WB_TINY *str);

/**
 * @brief Split a Buffer into words at whitespace
 * @param buff The buffer to split
 * @return The List of splitted Words, or NULL if not enough memory
 * @warning Do NOT use this function directly, use wbxml_buffer_split_words() macro instead
 */
WBXML_DECLARE(WBXMLList *) wbxml_buffer_split_words_real(WBXMLBuffer *buff);
#define wbxml_buffer_split_words(a) wbxml_mem_cleam(wbxml_buffer_split_words_real(a))

/**
 * @brief Search a char in Buffer
 * @param to The buffer to search into
 * @param ch The char to search
 * @param pos Position to start searching in 'to' buffer
 * @param result The start position of char in 'to' buffer
 * @return TRUE if char successfully found in 'to' buffer, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_search_char(WBXMLBuffer *to, const WB_UTINY ch, WB_ULONG pos, WB_ULONG *result);

/**
 * @brief Search a Buffer in another Buffer
 * @param to The buffer to search into
 * @param search The buffer to search
 * @param pos Position to start searching in 'to' buffer
 * @param result The start position of 'search' buffer in 'to' buffer
 * @return TRUE if successfully found 'search' in 'to' buffer, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_search(WBXMLBuffer *to, WBXMLBuffer *search, WB_ULONG pos, WB_ULONG *result);

/**
 * @brief Search a C String in a WBXMLBuffer Buffer
 * @param to The buffer to search into
 * @param search The C String to search
 * @param pos Position to start searching in 'to' buffer
 * @param result The start position of 'search' buffer in 'to' buffer
 * @return TRUE if successfully found 'search' in 'to' buffer, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_search_cstr(WBXMLBuffer *to, const WB_UTINY *search, WB_ULONG pos, WB_ULONG *result);

/**
 * @brief Check if a buffer contains only Whitespaces
 * @param buffer The buffer to check
 * @return TRUE if it contains only whitespaces, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_contains_only_whitespaces(WBXMLBuffer *buffer);

/**
 * @brief Convert an Hexa dynamic buffer to Binary
 * @param buffer The buffer to convert
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_hex_to_binary(WBXMLBuffer *buffer);

/**
 * @brief Convert an Binary dynamic buffer to Hexa
 * @param buffer The buffer to convert
 * @param uppercase Do we convert to Uppercase Hexa ?
 * @return TRUE if converted, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_binary_to_hex(WBXMLBuffer *buffer, WB_BOOL uppercase);

/**
 * @brief Convert base64 encoded data to binary data
 * @param buffer The buffer to convert
 * @return TRUE if converted, FALSE otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_buffer_decode_base64(WBXMLBuffer *buffer);

/**
 * @brief Convert binary data to base64 encoded data
 * @param buffer The buffer to convert
 * @return TRUE if converted, FALSE otherwise
 */
WBXML_DECLARE(WBXMLError) wbxml_buffer_encode_base64(WBXMLBuffer *buffer);

/**
 * @brief Remove trailing Zeros from a dynamic Buffer
 * @param buffer The buffer
 */
WBXML_DECLARE(WB_BOOL) wbxml_buffer_remove_trailing_zeros(WBXMLBuffer *buffer);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_BUFFERS_H */
