# Try and find libmozldap.
# As soon as libmozldap has been found, the following variables will be defined:
#
# LIBMOZLDAP_FOUND (this is or is not #defined)
# MOZLDAP_INCLUDE_DIR:DIRPATH
# MOZLDAP_LIBRARY:FILEPATH
#
#
# Copyright (c) 2009 Juergen Leising <jleising@users.sourceforge.net>
#
# Redistribution and use is allowed according to the terms of the New
# BSD license.
# For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#


MESSAGE(STATUS "checking for libmozldap...")

# Prepare for using pkg-config
INCLUDE( FindPkgConfig )

IF ( LibMozLdap_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( LibMozLdap_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "" )
ENDIF ( LibMozLdap_FIND_REQUIRED )

FIND_PROGRAM( PKGCONFIG_EXECUTABLE NAMES pkg-config )



# Search for the header files and the libraries by means of pkg-config
IF ( PKG_CONFIG_FOUND )
	MESSAGE (STATUS "  Trying to invoke pkg-config...")
	# PKG_SEARCH_MODULE ( LIBMOZLDAP ${_pkgconfig_REQUIRED} mozldap )
	PKG_CHECK_MODULES ( LIBMOZLDAP ${_pkgconfig_REQUIRED} mozldap )
	IF ( LIBMOZLDAP_FOUND )
		MESSAGE (STATUS "    pkg-config found mozldap.")
	ELSE ( LIBMOZLDAP_FOUND ) 
		MESSAGE (STATUS "    pkg-config did NOT find mozldap.")
	ENDIF ( LIBMOZLDAP_FOUND )
ENDIF ( PKG_CONFIG_FOUND )
 



# Manually searching for header and library.
# Only, if it has not been found, yet.  Which would also be the case,
# if pkg-config could not have been found.
IF ( NOT MOZLDAP_INCLUDE_DIR )
	MESSAGE (STATUS "  Falling back to searching for mozldap/ldap.h without pkg-config" )
	FIND_PATH(MOZLDAP_INCLUDE_DIR NAMES mozldap/ldap.h
                          PATHS /include /usr/include /usr/local/include /usr/share/include /opt/include 
                          DOC "Try and find the header file mozldap/ldap.h.")
ENDIF ( NOT MOZLDAP_INCLUDE_DIR )


IF ( NOT LIBMOZLDAP_LIBRARIES )
	MESSAGE (STATUS "  Falling back to searching for libldap60 and libssldap60 without pkg-config" )

	FIND_LIBRARY(MOZLDAP_LIBRARY NAMES ldap60
                          PATHS /usr/lib /lib /usr/local/lib /usr/share/lib /opt/lib /opt/share/lib /var/lib /usr/lib64 /lib64 /usr/local/lib64 /usr/share/lib64 /opt/lib64 /opt/share/lib64 /var/lib64
                          DOC "Try and find libldap60 from Mozilla.")

	FIND_LIBRARY(MOZSSLDAP_LIBRARY NAMES ssldap60
                          PATHS /usr/lib /lib /usr/local/lib /usr/share/lib /opt/lib /opt/share/lib /var/lib /usr/lib64 /lib64 /usr/local/lib64 /usr/share/lib64 /opt/lib64 /opt/share/lib64 /var/lib64
                          DOC "Try and find libssldap60 from Mozilla.")

	SET ( LIBMOZLDAP_LIBRARIES ${MOZLDAP_LIBRARY} ${MOZSSLDAP_LIBRARY} )

ENDIF ( NOT LIBMOZLDAP_LIBRARIES )





# Reviewing the results
IF (MOZLDAP_INCLUDE_DIR AND MOZLDAP_LIBRARY)
	SET( LIBMOZLDAP_FOUND 1 )
  get_filename_component(MOZLDAP_LIBRARY_DIRS ${MOZLDAP_LIBRARY} PATH)
  MESSAGE(STATUS "  Found ${MOZLDAP_LIBRARY}")
ELSE (MOZLDAP_INCLUDE_DIR AND MOZLDAP_LIBRARY)
	IF ( LibMozLdap_FIND_REQUIRED )
	  MESSAGE( FATAL_ERROR "  Could NOT find libldap60 from Mozilla.  The ldap plugin needs this library.")
	ELSE ( LibMozLdap_FIND_REQUIRED )
		MESSAGE( STATUS "  Could NOT find libldap60 from Mozilla." )
		MESSAGE( STATUS "  LIBMOZLDAP_INCLUDE_DIR  = ${LIBMOZLDAP_INCLUDE_DIR}" )
		MESSAGE( STATUS "  LIBMOZLDAP_INCLUDE_DIRS = ${LIBMOZLDAP_INCLUDE_DIRS}" )
		MESSAGE( STATUS "  LIBMOZLDAP_LIBRARY = ${LIBMOZLDAP_LIBRARY}" )
		MESSAGE( STATUS "  LIBMOZLDAP_LIBRARY_DIRS = ${LIBMOZLDAP_LIBRARY_DIRS}" )
		MESSAGE( STATUS "  LIBMOZLDAP_LIBDIR = ${LIBMOZLDAP_LIBDIR}" )
	

	ENDIF ( LibMozLdap_FIND_REQUIRED )
ENDIF (MOZLDAP_INCLUDE_DIR AND MOZLDAP_LIBRARY)

