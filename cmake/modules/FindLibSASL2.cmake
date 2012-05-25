# Try and find libsasl2.
# As soon as libsasl2 has been found, the following variables will be defined:
#
# LIBSASL2_FOUND
# SASL2_INCLUDE_DIR
# SASL2_LIBRARY:FILEPATH
#
# Copyright (c) 2009 Juergen Leising <jleising@users.sourceforge.net>
#
# Redistribution and use is allowed according to the terms of the New
# BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

MESSAGE(STATUS "checking for libsasl2...")

FIND_PATH(SASL2_INCLUDE_DIR NAMES sasl/sasl.h
                             PATHS /include /usr/include /usr/local/include /usr/share/include /opt/include 
                             DOC "Try and find the header file sasl/sasl.h")

FIND_LIBRARY(SASL2_LIBRARY NAMES sasl2
                           PATHS /usr/lib /lib /usr/local/lib /usr/share/lib /opt/lib /opt/share/lib /var/lib
                           DOC "Try and find libsasl2")

IF (SASL2_INCLUDE_DIR AND SASL2_LIBRARY)
	SET (LIBSASL2_FOUND 1)
  get_filename_component(SASL2_LIBRARY_DIRS ${SASL2_LIBRARY} PATH)
  MESSAGE(STATUS "  Found ${SASL2_LIBRARY}")
ELSE (SASL2_INCLUDE_DIR AND SASL2_LIBRARY)
	IF ( LibSASL2_FIND_REQUIRED	)
	  MESSAGE( FATAL_ERROR "  Could NOT find libsasl2. The ldap plugin needs this library." )
	ELSE ( LibSASL2_FIND_REQUIRED )
		MESSAGE( STATUS "  Could NOT find libsasl2.")
	ENDIF ( LibSASL2_FIND_REQUIRED )
ENDIF (SASL2_INCLUDE_DIR AND SASL2_LIBRARY)


