# Try and find libgssapiv2.
# As soon as libgssapiv2 has been found, the following variables will be defined:
#
# LIBGSSAPIV2_FOUND
# GSSAPIV2_LIBRARY:FILEPATH
#
# Copyright (c) 2009 Juergen Leising <jleising@users.sourceforge.net>
#
# Redistribution and use is allowed according to the terms of the New
# BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#


MESSAGE(STATUS "checking for libgssapiv2...")

# No header files required for the ldap plugin.

FIND_LIBRARY(GSSAPIV2_LIBRARY NAMES gssapiv2 
                              PATHS /usr/lib /lib /usr/local/lib /usr/share/lib /opt/lib /opt/share/lib /var/lib /usr/lib/sasl2 /lib/sasl2 /usr/local/lib/sasl2 /usr/share/lib/sasl2 /opt/lib/sasl2 /opt/share/lib/sasl2 /var/lib/sasl2 /usr/lib64 /lib64 /usr/local/lib64 /usr/share/lib64 /opt/lib64 /opt/share/lib64 /var/lib64 /usr/lib64/sasl2 /lib64/sasl2 /usr/local/lib64/sasl2 /usr/share/lib64/sasl2 /opt/lib64/sasl2 /opt/share/lib64/sasl2 /var/lib64/sasl2
                              DOC "Try and find libgssapiv2")

IF (GSSAPIV2_LIBRARY)
	SET (LIBGSSAPIV2_FOUND 1)
  get_filename_component(GSSAPIV2_LIBRARY_DIRS ${GSSAPIV2_LIBRARY} PATH)
  MESSAGE(STATUS "  Found ${GSSAPIV2_LIBRARY}")
ELSE (GSSAPIV2_LIBRARY)
	IF ( LibGSSAPIV2_FIND_REQUIRED )	
		MESSAGE( FATAL_ERROR "  Could NOT find libgssapiv2. The ldap plugin needs this library.")
	ELSE ( LibGSSAPIV2_FIND_REQUIRED )
	  MESSAGE( STATUS "  Could NOT find libgssapiv2. The SASL authentication mechanism GSSAPI (and KERBEROS V5) won't work, therefore. Not a fatal error, however. The ldap plugin itself does NOT need it.")
	ENDIF ( LibGSSAPIV2_FIND_REQUIRED )
ENDIF (GSSAPIV2_LIBRARY)

