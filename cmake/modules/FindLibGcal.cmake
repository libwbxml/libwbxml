# - Try to find libgcal
# Find libgcal headers, libraries and the answer to all questions.
#
#  LIBGCAL_FOUND               True if libgcal got found
#  LIBGCAL_INCLUDE_DIRS         Location of libgcal headers
#  LIBGCAL_LIBRARIES           List of libaries to use libgcal
#  LIBGCAL_DEFINITIONS         Definitions to compile libgcal
#
# Copyright (c) 2006, Alexander Neundorf, <neundorf@kde.org>
# Copyright (c) 2007 Alban Browaeys <prahal@yahoo.com>
# Copyright (c) 2008 Adenilson Cavalcanti <savagobr@yahoo.com>
#  Adapted this to scan for libgcal
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

INCLUDE( FindPkgConfig )
# Take care about libgcal.pc settings
IF ( Libgcal_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( Libgcal_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( Libgcal_FIND_REQUIRED )

IF ( LIBGCAL_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBGCAL ${_pkgconfig_REQUIRED} libgcal>=${LIBGCAL_MIN_VERSION} )
ELSE ( LIBGCAL_MIN_VERSION )
	pkg_search_module( LIBGCAL ${_pkgconfig_REQUIRED} libgcal )
ENDIF ( LIBGCAL_MIN_VERSION )


# Look for libgcal include dir and libraries w/o pkgconfig
IF ( NOT LIBGCAL_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _libgcal_include_DIR gcal.h
		PATHS
		/opt/local/include/
		/sw/include/
		/usr/local/include/
		/usr/include/
	)
	FIND_LIBRARY( _libgcal_link_DIR NAME libgcal
		PATHS
		/opt/local/lib
		/sw/lib
		/usr/lib
		/usr/local/lib
		/usr/lib64
		/usr/local/lib64
		/opt/lib64
	)
	IF ( _libgcal_include_DIR AND _libgcal_link_DIR )
		SET ( _libgcal_FOUND TRUE )
	ENDIF ( _libgcal_include_DIR AND _libgcal_link_DIR )


	IF ( _libgcal_FOUND )
		SET ( LIBGCAL_INCLUDE_DIRS ${_libgcal_include_DIR} )
		SET ( LIBGCAL_LIBRARIES ${_libgcal_link_DIR} )
	ENDIF ( _libgcal_FOUND )

	# Report results
	IF ( LIBGCAL_LIBRARIES AND LIBGCAL_INCLUDE_DIRS AND _libgcal_FOUND )
		SET( LIBGCAL_FOUND 1 )
		IF ( NOT Libgcal_FIND_QUIETLY )
			MESSAGE( STATUS "Found libgcal: ${LIBGCAL_LIBRARIES} ${LIBGCAL_INCLUDE_DIRS}" )
		ENDIF ( NOT Libgcal_FIND_QUIETLY )
	ELSE ( LIBGCAL_LIBRARIES AND LIBGCAL_INCLUDE_DIRS AND _libgcal_FOUND )
		IF ( Libgcal_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find libgcal" )
		ELSE ( Libgcal_FIND_REQUIRED )
			IF ( NOT Libgcal_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find libgcal" )
			ENDIF ( NOT Libgcal_FIND_QUIETLY )
		ENDIF ( Libgcal_FIND_REQUIRED )
	ENDIF ( LIBGCAL_LIBRARIES AND LIBGCAL_INCLUDE_DIRS AND _libgcal_FOUND )

ENDIF ( NOT LIBGCAL_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( LIBGCAL_LIBRARIES LIBGCAL_INCLUDE_DIRS )

