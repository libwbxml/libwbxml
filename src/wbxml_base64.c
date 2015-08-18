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
 * @file wbxml_base64.c
 * @ingroup wbxml_base64
 *
 * @author Aymerick Jehanne <aymerick@jehanne.org>
 * @date 01/11/03
 *
 * @brief Base64 encoding/decoding functions
 *
 * @note Code adapted from APR library (http://apr.apache.org/) 
 */

#include "wbxml_base64.h"
#include "wbxml_mem.h"


/* aaaack but it's fast and const should make it shared text page. */
static const unsigned char pr2six[256] =
{
    /* ASCII table */
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 62, 64, 64, 64, 63,
    52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 64, 64, 64, 64, 64, 64,
    64,  0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14,
    15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 64, 64, 64, 64, 64,
    64, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
    41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64,
    64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64, 64
};

/** Base64 table */
static const char basis_64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";


/**********************************
 *    Public functions
 */

/* Function adapted from APR library (http://apr.apache.org/) */
WBXML_DECLARE(WB_UTINY *) wbxml_base64_encode(const WB_UTINY *buffer, WB_LONG len)
{
    WB_LONG i = 0;
    WB_UTINY *p = NULL, *result = NULL;

    if ((buffer == NULL) || (len <= 0))
        return NULL;

    /* Malloc result buffer */
    if ((result = wbxml_malloc(((len + 2) / 3 * 4) + 1 + 1)) == NULL)
        return NULL;

    p = result;
    for (i = 0; i < len - 2; i += 3) {
        *p++ = basis_64[(buffer[i] >> 2) & 0x3F];
        *p++ = basis_64[((buffer[i] & 0x3) << 4) |
                        ((int) (buffer[i + 1] & 0xF0) >> 4)];
        *p++ = basis_64[((buffer[i + 1] & 0xF) << 2) |
                        ((int) (buffer[i + 2] & 0xC0) >> 6)];
        *p++ = basis_64[buffer[i + 2] & 0x3F];
    }
    if (i < len) {
        *p++ = basis_64[(buffer[i] >> 2) & 0x3F];
        if (i == (len - 1)) {
            *p++ = basis_64[((buffer[i] & 0x3) << 4)];
            *p++ = '=';
        }
        else {
            *p++ = basis_64[((buffer[i] & 0x3) << 4) |
                            ((int) (buffer[i + 1] & 0xF0) >> 4)];
            *p++ = basis_64[((buffer[i + 1] & 0xF) << 2)];
        }
        *p++ = '=';
    }

    *p++ = '\0';

    return result;
}


/* Function adapted from APR library (http://apr.apache.org/) */
WBXML_DECLARE(WB_LONG) wbxml_base64_decode(const WB_UTINY *buffer, WB_LONG len, WB_UTINY **result)
{
    WB_LONG nbytesdecoded = 0, nprbytes = 0;
    const WB_UTINY *bufin = NULL;
	const WB_UTINY *end = (len >= 0) ? (buffer + len) : NULL;
    WB_UTINY *bufout = NULL;

    if ((buffer == NULL) || (result == NULL))
        return 0;

    /* Initialize output buffer */
    *result = NULL;

    bufin = buffer;   
    while (bufin != end && pr2six[*bufin] <= 63)
		bufin++;
    
	nprbytes = bufin - buffer;

    nbytesdecoded = ((nprbytes + 3) / 4) * 3;
    
    /* Malloc result buffer */
    if ((*result = wbxml_malloc(nbytesdecoded + 1)) == NULL)
        return 0;

    bufout = *result;
    bufin = buffer;

    while (nprbytes > 4) 
    {
        *(bufout++) = (WB_UTINY) (pr2six[*bufin] << 2 | pr2six[bufin[1]] >> 4);
        *(bufout++) = (WB_UTINY) (pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >> 2);
        *(bufout++) = (WB_UTINY) (pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
        bufin += 4;
        nprbytes -= 4;
    }

    /* Note: (nprbytes == 1) would be an error, so just ingore that case */
    if (nprbytes > 1) {
        *(bufout++) = (WB_UTINY) (pr2six[*bufin] << 2 | pr2six[bufin[1]] >> 4);
    }
    if (nprbytes > 2) {
        *(bufout++) = (WB_UTINY) (pr2six[bufin[1]] << 4 | pr2six[bufin[2]] >> 2);
    }
    if (nprbytes > 3) {
        *(bufout++) = (WB_UTINY) (pr2six[bufin[2]] << 6 | pr2six[bufin[3]]);
    }

    nbytesdecoded -= (4 - nprbytes) & 3;
    
    return nbytesdecoded;
}
