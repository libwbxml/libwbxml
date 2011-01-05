/*
 * Copyright (C) 2008 Michael Bell <michael.bell@opensync.org>
 */

#ifndef WBXML_CONFIG_INTERNALS_H
#define WBXML_CONFIG_INTERNALS_H

/* These are the public details of the configuration. */
#include "wbxml_config.h"

/* Define to 1 if you have the <dlfcn.h> header file. */
#cmakedefine HAVE_DLFCN_H

/* Define to 1 if you don't have `vprintf' but do have `_doprnt.' */
#cmakedefine HAVE_DOPRNT

/* Define to 1 if you have the <expat.h> header file. */
/* Define to 1 if you have the `expat' library (-lexpat). */
#cmakedefine HAVE_EXPAT

/* Define to 1 if you have the `iconv' library (sometimes in libc). */
#cmakedefine HAVE_ICONV

/* Define to 1 if you have the <inttypes.h> header file. */
#cmakedefine HAVE_INTTYPES_H

/* Define to 1 if you have the `nsl' library (-lnsl). */
#cmakedefine HAVE_LIBNSL

/* Define to 1 if you have the `popt' library (-lpopt). */
#cmakedefine HAVE_LIBPOPT

/* Define to 1 if you have the `z' library (-lz). */
#cmakedefine HAVE_LIBZ

/* Define to 1 if you have the <limits.h> header file. */
#cmakedefine HAVE_LIMITS_H

/* Define to 1 if you have the <memory.h> header file. */
#cmakedefine HAVE_MEMORY_H

/* Define to 1 if you have the <stdint.h> header file. */
#cmakedefine HAVE_STDINT_H

/* Define to 1 if you have the <stdlib.h> header file. */
#cmakedefine HAVE_STDLIB_H

/* Define to 1 if you have the <strings.h> header file. */
#cmakedefine HAVE_STRINGS_H

/* Define to 1 if you have the <string.h> header file. */
#cmakedefine HAVE_STRING_H

/* Define to 1 if you have the <sys/stat.h> header file. */
#cmakedefine HAVE_SYS_STAT_H

/* Define to 1 if you have the <sys/types.h> header file. */
#cmakedefine HAVE_SYS_TYPES_H

/* Define to 1 if you have the <unistd.h> header file. */
#cmakedefine HAVE_UNISTD_H

/* Define to 1 if you have the `vprintf' function. */
#cmakedefine HAVE_VPRINTF

/* Name of package */
#cmakedefine PACKAGE "${PACKAGE}"

/* Define to the address where bug reports for this package should be sent. */
#cmakedefine PACKAGE_BUGREPORT "${PACKAGE_BUGREPORT}"

/* Define to the full name of this package. */
#cmakedefine PACKAGE_NAME "${PACKAGE_NAME}"

/* Define to the full name and version of this package. */
#cmakedefine PACKAGE_STRING "${PACKAGE_STRING}"

/* Define to the one symbol short name of this package. */
#cmakedefine PACKAGE_TARNAME "${PACKAGE_TARNAME}"

/* Define to the version of this package. */
#cmakedefine PACKAGE_VERSION "${PACKAGE_VERSION}"

/* Define to 1 if you have the ANSI C header files. */
#cmakedefine STDC_HEADERS 1

/* Version number of package */
#cmakedefine VERSION "${VERSION}"

/* Define to empty if `const' does not conform to ANSI C. */
#cmakedefine const

/* Define to `unsigned int' if <sys/types.h> does not define. */
#cmakedefine size_t

/* Includes */
#if defined( HAVE_EXPAT)
#include <expat.h>
#endif /* HAVE_EXPAT */

#if defined( HAVE_ICONV )
#include <iconv.h>
#endif /* HAVE_ICONV */


#endif /* WBXML_CONFIG_INTERNALS_H */
