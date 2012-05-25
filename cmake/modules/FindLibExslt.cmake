# - Try to find libexslt
# Find libexslt headers, libraries and the answer to all questions.
#
#  LIBEXSLT_FOUND               True if libexslt got found
#  LIBEXSLT_INCLUDE_DIRS         Location of libexslt headers 
#  LIBEXSLT_LIBRARIES           List of libaries to use libexslt
#
#  Copyright (c) 2008 Daniel Gollub <gollub@b1-systems.de>
#  Copyright (c) 2008 Bjoern Ricks <bjoern.ricks@googlemail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

INCLUDE( FindPkgConfig )

# Take care about libexslt.pc settings
IF ( LibExslt_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( LibExslt_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( LibExslt_FIND_REQUIRED )

IF ( LIBEXSLT_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBEXSLT ${_pkgconfig_REQUIRED} libexslt >= ${LIBEXSLT_MIN_VERSION} )
ELSE( LIBEXSLT_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBEXSLT ${_pkgconfig_REQUIRED} libexslt )
ENDIF ( LIBEXSLT_MIN_VERSION )


# Look for libexslt include dir and libraries without pkg-config...
IF ( NOT LIBEXSLT_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _libexslt_include_DIR libexslt/exslt.h 
			PATHS
			/opt/local/include/
			/sw/include/
			/usr/local/include/
			/usr/include/ 
	)

	FIND_LIBRARY( _libexslt_link_DIR NAMES exslt libexslt
			PATHS
			/opt/local/lib
			/sw/lib
			/usr/lib
			/usr/local/lib
			/usr/lib64
			/usr/local/lib64
			/opt/lib64 
	)

	IF ( _libexslt_include_DIR AND _libexslt_link_DIR )
		SET ( _libexslt_FOUND TRUE )
	ENDIF ( _libexslt_include_DIR AND _libexslt_link_DIR )

	IF ( _libexslt_FOUND )
		SET ( LIBEXSLT_INCLUDE_DIRS ${_libexslt_include_DIR} )
		SET ( LIBEXSLT_LIBRARIES ${_libexslt_link_DIR} )
	ENDIF ( _libexslt_FOUND )

	# Report results
	IF ( LIBEXSLT_LIBRARIES AND LIBEXSLT_INCLUDE_DIRS )	
		SET( LIBEXSLT_FOUND 1 )
		IF ( NOT LibExslt_FIND_QUIETLY )
			MESSAGE( STATUS "Found libexslt: ${LIBEXSLT_LIBRARIES} ${LIBEXSLT_INCLUDE_DIRS}" )
		ENDIF ( NOT LibExslt_FIND_QUIETLY )
	ELSE ( LIBEXSLT_LIBRARIES AND LIBEXSLT_INCLUDE_DIRS )	
		IF ( LibExslt_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find libexslt" )
		ELSE ( LibExslt_FIND_REQUIRED )
			IF ( NOT LibExslt_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find libexslt" )	
			ENDIF ( NOT LibExslt_FIND_QUIETLY )
		ENDIF ( LibExslt_FIND_REQUIRED )
	ENDIF ( LIBEXSLT_LIBRARIES AND LIBEXSLT_INCLUDE_DIRS )	

ENDIF ( NOT LIBEXSLT_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( LIBEXSLT_LIBRARIES LIBEXSLT_INCLUDE_DIRS )

