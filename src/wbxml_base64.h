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
 * @file wbxml_base64.h 
 * @ingroup wbxml_base64
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 01/11/03
 *
 * @brief Base64 encoding/decoding functions
 *
 * @note Code adapted from APR library (http://apr.apache.org/) 
 */

#ifndef WBXML_BASE64_H
#define WBXML_BASE64_H

#include "wbxml.h"

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/** @addtogroup wbxml_base64 
 *  @{ 
 */

/**
 * @brief Encode a buffer to Base64
 * @param buffer The buffer to encode
 * @param len    Buffer length
 * @return The new base64 encoded Buffer (must be freed by caller), or NULL if not enough memory
 */
WBXML_DECLARE(WB_UTINY *) wbxml_base64_encode(const WB_UTINY *buffer, WB_LONG len);

/**
 * @brief Decode a Base64 encoded buffer
 * @param buffer The buffer to decode
 * @param len    Buffer length. If len is negative, assume buffer is terminated
 *               by a non-Base64 character (such as NUL).
 * @param result Resulting decoded buffer
 * @return Length of resulting decoded buffer ('0' if no decoded)
 * @note Be aware that if return value is '0', then 'result' param will be NULL, else 'result' param
 *       has to be freed by caller.
 */
WBXML_DECLARE(WB_LONG) wbxml_base64_decode(const WB_UTINY *buffer, WB_LONG len, WB_UTINY **result);

/** @} */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* WBXML_BASE64_H */
