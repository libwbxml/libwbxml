# Try and find libgcrypt.
# As soon as libgcrypt has been found, the following variables will be defined:
#
# LIBGCRYPT_FOUND
# GCRYPT_INCLUDE_DIR
# GCRYPT_LIBRARY:FILEPATH
#
# Copyright (c) 2009 Juergen Leising <jleising@users.sourceforge.net>
#
# Redistribution and use is allowed according to the terms of the New
# BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

MESSAGE(STATUS "checking for libgcrypt...")

FIND_PATH(GCRYPT_INCLUDE_DIR NAMES gcrypt.h 
                             PATHS /include /usr/include /usr/local/include /usr/share/include /opt/include 
                             DOC "Try and find the header file gcrypt.h")

FIND_LIBRARY(GCRYPT_LIBRARY NAMES gcrypt
                            PATHS /usr/lib /lib /usr/local/lib /usr/share/lib /opt/lib /opt/share/lib /var/lib /usr/lib64 /lib64 /usr/local/lib64 /usr/share/lib64 /opt/lib64 /opt/share/lib64 /var/lib64
                            DOC "Try and find libgcrypt")

IF (GCRYPT_INCLUDE_DIR AND GCRYPT_LIBRARY)
	SET (LIBGCRYPT_FOUND 1)
  get_filename_component(GCRYPT_LIBRARY_DIRS ${GCRYPT_LIBRARY} PATH)
  MESSAGE(STATUS "  Found ${GCRYPT_LIBRARY}")
ELSE (GCRYPT_INCLUDE_DIR AND GCRYPT_LIBRARY)
	IF ( LibGCrypt_FIND_REQUIRED )
	  MESSAGE( FATAL_ERROR "  Could NOT find libgcrypt. The ldap plugin needs this library." )
	ELSE ( LibGCrypt_FIND_REQUIRED )
		MESSAGE ( STATUS "  Could NOT find libgcrypt.")
	ENDIF ( LibGCrypt_FIND_REQUIRED )
ENDIF (GCRYPT_INCLUDE_DIR AND GCRYPT_LIBRARY)


