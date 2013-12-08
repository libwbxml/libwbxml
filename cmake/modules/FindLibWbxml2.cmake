# - Try to find libwbxml
# Find libwbxml headers, libraries and the answer to all questions.
#
#  LIBWBXML2_FOUND               True if libwbxml got found
#  LIBWBXML2_INCLUDE_DIRS        Location of libwbxml headers 
#  LIBWBXML2_LIBRARIES           List of libaries to use libwbxml
#
# Copyright (c) 2007 Daniel Gollub <gollub@b1-systems.de>
# Copyright (c) 2007 Bjoern Ricks  <b.ricks@fh-osnabrueck.de>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

INCLUDE( FindPkgConfig )

IF ( LibWbxml2_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE( LibWbxml2_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "" )	
ENDIF ( LibWbxml2_FIND_REQUIRED )

IF ( LIBWBXML2_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBWBXML2 libwbxml2>=${LIBWBXML2_MIN_VERSION} ${_pkgconfig_REQUIRED} )
ELSE ( LIBWBXML2_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBWBXML2 libwbxml2 ${_pkgconfig_REQUIRED} )
ENDIF ( LIBWBXML2_MIN_VERSION )


IF( NOT LIBWBXML2_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _libwbxml2_include_DIR wbxml.h
			PATHS
			/opt/local/include/
			/sw/include/
			/usr/local/include/
			/usr/include/ )
	FIND_LIBRARY( _libwbxml2_LIBRARY wbxml2
			PATHS
			/opt/local/lib
			/sw/lib
			/usr/lib
			/usr/local/lib
			/usr/lib64
			/usr/local/lib64
			/opt/lib64 )
	IF ( _libwbxml2_include_DIR AND _libwbxml2_LIBRARY )
		SET ( _libwbxml2_FOUND TRUE )
	ENDIF ( _libwbxml2_include_DIR AND _libwbxml2_LIBRARY )

	IF ( _libwbxml2_FOUND )
		SET ( LIBWBXML2_INCLUDE_DIRS ${_libwbxml2_include_DIR} )
		SET ( LIBWBXML2_LIBRARIES ${_libwbxml2_LIBRARY} )

		# find required libexpat
		IF( NOT EXPAT_FOUND )
			FIND_PACKAGE( Expat REQUIRED )
			IF ( EXPAT_FOUND )
				SET ( LIBWBXML2_INCLUDE_DIRS ${LIBWBXML2_INCLUDE_DIRS} ${EXPAT_INCLUDE_DIRS} )
				SET ( LIBWBXML2_LIBRARIES ${LIBWBXML2_LIBRARIES} ${EXPAT_LIBRARIES} )
			ENDIF( EXPAT_FOUND )
		ENDIF( NOT EXPAT_FOUND )
	ENDIF( _libwbxml2_FOUND )

	MARK_AS_ADVANCED( _libwbxml2_include_DIR _libwbxml2_LIBRARY )

	# Report results
	IF ( LIBWBXML2_LIBRARIES AND LIBWBXML2_INCLUDE_DIRS AND _libwbxml2_FOUND )	
		SET( LIBWBXML_FOUND 1 )
		IF ( NOT LibWbxml2_FIND_QUIETLY )
			MESSAGE( STATUS "Found libwbxml2: ${_libwbxml2_LIBRARY}" )
		ENDIF ( NOT LibWbxml2_FIND_QUIETLY )
	ELSE ( LIBWBXML2_LIBRARIES AND LIBWBXML2_INCLUDE_DIRS AND _libwbxml2_FOUND )	
		IF ( LibWbxml2_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find libwbxml2" )
		ELSE ( LibWbxml2_FIND_REQUIRED )
			IF ( NOT LibWbxml2_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find libwbxml2" )	
			ENDIF ( NOT LibWbxml2_FIND_QUIETLY )
		ENDIF ( LibWbxml2_FIND_REQUIRED )
	ENDIF ( LIBWBXML2_LIBRARIES AND LIBWBXML2_INCLUDE_DIRS AND _libwbxml2_FOUND )
ENDIF( NOT LIBWBXML2_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( LIBWBXML2_LIBRARIES LIBWBXML2_INCLUDE_DIRS )

