/*
 * Copyright (C) 2008 Michael Bell <michael.bell@opensync.org>
 */

#ifndef WBXML_CONFIG_H
#define WBXML_CONFIG_H

/** WBXML Parser Lib Version */
#define WBXML_LIB_VERSION "${PACKAGE_VERSION}"

/* Define to 1 if you would like to enable debug, warning and error messages */
#cmakedefine WBXML_LIB_VERBOSE

/* supported document types */
#cmakedefine WBXML_ENCODER_USE_STRTBL
#cmakedefine WBXML_SUPPORT_WML
#cmakedefine WBXML_SUPPORT_WTA
#cmakedefine WBXML_SUPPORT_SI
#cmakedefine WBXML_SUPPORT_SL
#cmakedefine WBXML_SUPPORT_CO
#cmakedefine WBXML_SUPPORT_PROV
#cmakedefine WBXML_SUPPORT_EMN
#cmakedefine WBXML_SUPPORT_DRMREL
#cmakedefine WBXML_SUPPORT_OTA_SETTINGS
#cmakedefine WBXML_SUPPORT_SYNCML
#cmakedefine WBXML_SUPPORT_WV
#cmakedefine WBXML_SUPPORT_AIRSYNC
#cmakedefine WBXML_SUPPORT_CONML

#endif /* WBXML_CONFIG_H */
