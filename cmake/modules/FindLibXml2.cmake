# - Try to find libxml2 
# Find libxml2 headers, libraries and the answer to all questions.
#
#  LIBXML2_FOUND               True if libxml2 got found
#  LIBXML2_INCLUDE_DIRS        Location of libxml2 headers 
#  LIBXML2_LIBRARIES           List of libraries to use libxml2
#  LIBXML2_DEFINITIONS         Definitions to compile libxml2
#
# Copyright (c) 2006, Alexander Neundorf, <neundorf@kde.org>
# Copyright (c) 2007 Alban Browaeys <prahal@yahoo.com>
# Copyright (c) 2008 Bjoern Ricks <bjoern.ricks@googlemail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

INCLUDE( FindPkgConfig )
# Take care about libxml2.pc settings
IF ( LibXml2_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( LibXml2_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( LibXml2_FIND_REQUIRED )

IF ( LIBXML2_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBXML2 ${_pkgconfig_REQUIRED} libxml-2.0>=${LIBXML2_MIN_VERSION} )
ELSE ( LIBXML2_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBXML2 ${_pkgconfig_REQUIRED} libxml-2.0 )
ENDIF ( LIBXML2_MIN_VERSION )


# Look for libxml-2.0 include dir and libraries w/o pkgconfig
IF ( NOT LIBXML2_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _libxml2_include_DIR libxml/xpath.h PATH_SUFFIXES libxml2 
		PATHS
		/opt/local/include/
		/sw/include/
		/usr/local/include/
		/usr/include/
	)
	FIND_LIBRARY( _libxml2_link_DIR NAMES xml2 libxml2 libxml
		PATHS
		/opt/local/lib
		/sw/lib
		/usr/lib
		/usr/local/lib
		/usr/lib64
		/usr/local/lib64
		/opt/lib64
	)
	IF ( _libxml2_include_DIR AND _libxml2_link_DIR )
		SET ( _libxml2_FOUND TRUE )
	ENDIF ( _libxml2_include_DIR AND _libxml2_link_DIR )


	IF ( _libxml2_FOUND )
		SET ( LIBXML2_INCLUDE_DIRS ${_libxml2_include_DIR} )
		SET ( LIBXML2_LIBRARIES ${_libxml2_link_DIR} )
	ENDIF ( _libxml2_FOUND )

	# Report results
	IF ( LIBXML2_LIBRARIES AND LIBXML2_INCLUDE_DIRS AND _libxml2_FOUND )	
		SET( LIBXML2_FOUND 1 )
		IF ( NOT LibXml2_FIND_QUIETLY )
			MESSAGE( STATUS "Found libxml2: ${LIBXML2_LIBRARIES} ${LIBXML2_INCLUDE_DIRS}" )
		ENDIF ( NOT LibXml2_FIND_QUIETLY )
	ELSE ( LIBXML2_LIBRARIES AND LIBXML2_INCLUDE_DIRS AND _libxml2_FOUND )	
		IF ( LibXml2_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find libxml2" )
		ELSE ( LibXml2_FIND_REQUIRED )
			IF ( NOT LibXml2_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find libxml2" )	
			ENDIF ( NOT LibXml2_FIND_QUIETLY )
		ENDIF ( LibXml2_FIND_REQUIRED )
	ENDIF ( LIBXML2_LIBRARIES AND LIBXML2_INCLUDE_DIRS AND _libxml2_FOUND )	

ENDIF ( NOT LIBXML2_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( LIBXML2_LIBRARIES LIBXML2_INCLUDE_DIRS )

