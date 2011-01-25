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
 * @file wbxml_charset.h
 * @ingroup wbxml_charset
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 04/03/24
 *
 * @brief Charset Functions
 */

#ifndef WBXML_CHARSET_H
#define WBXML_CHARSET_H

#include "wbxml.h"
#include "wbxml_buffers.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
  
/** @addtogroup wbxml_charset 
 *  @{ 
 */


/**
 * @brief Get a Charset MIBEnum given a Charset Name
 * @param name     [in]  Charset Name to search
 * @param mib_enum [out] MIBEnum if found
 * @return Return TRUE if Charset found, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_charset_get_mib(const WB_TINY       *name,
                                             WBXMLCharsetMIBEnum *mib_enum);

/**
 * @brief Get a Charset Name given a Charset MIBEnum
 * @param mib_enum [in]  MIBEnum to search
 * @param name     [out] Charset Name if found
 * @return Return TRUE if Charset found, FALSE otherwise
 */
WBXML_DECLARE(WB_BOOL) wbxml_charset_get_name(WBXMLCharsetMIBEnum   mib_enum,
                                              const WB_TINY       **name);
  
/**
 * Charset Convertion function
 *
 * Input is a normal pointer to buffer to convert.
 *
 * Result is a WBXML Buffer. If 'in_charset' and 'out_charset' are
 * identical, and are even ASCII or UTF-8, this will be a static
 * buffer pointing to input buffer.
 *
 * The 'io_bytes' parameter is decremented each time a byte is correctly
 * converted from 'in_buf', so that it reflects the number of bytes that
 * have been converted from 'in_buf'.
 *
 * @param in_buf      Buffer to convert
 * @param io_bytes    Number of bytes in buffer
 * @param in_charset  Original charset
 * @param out_buf     Resulting converted Buffer
 * @param out_charset Destination charset
 */
WBXML_DECLARE(WBXMLError) wbxml_charset_conv(const WB_TINY        *in_buf,
                                             WB_ULONG             *io_bytes,
                                             WBXMLCharsetMIBEnum   in_charset,
                                             WBXMLBuffer         **out_buf,
                                             WBXMLCharsetMIBEnum   out_charset);

/**
 * Charset Convertion function, for unknown length strings
 *
 * This is a wrapper around wbxml_charset_conv(), but to convert
 * a buffer that have an unknown length. This function first try to find
 * the buffer length, by finding its charset specific termination code
 * (eg: '\0', '\0\0'), then it calls the wbxml_charset_conv() function.
 *
 * Set the maximum possible length of input buffer into 'io_bytes'. A check
 * is done if length found is higher than input 'io_bytes' value.
 *
 * WARNING : 'io_bytes' is then set to the real length of input buffer (this is
 * a different behaviour than with wbxml_charset_conv()).
 *
 * @param in_buf      Buffer to convert
 * @param io_bytes    Number of bytes in buffer
 * @param in_charset  Original charset
 * @param out_buf     Resulting converted Buffer
 * @param out_charset Destination charset
 */
WBXML_DECLARE(WBXMLError) wbxml_charset_conv_term(const WB_TINY        *in_buf,
                                                  WB_ULONG             *io_bytes,
                                                  WBXMLCharsetMIBEnum   in_charset,
                                                  WBXMLBuffer         **out_buf,
                                                  WBXMLCharsetMIBEnum   out_charset);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_CHARSET_H */
