# - Try to find OpenSync
# Find OpenSync headers, libraries and the answer to all questions.
#
#  OPENSYNC_FOUND               True if OpenSync got found
#  OPENSYNC_INCLUDE_DIRS         Location of OpenSync headers 
#  OPENSYNC_LIBRARIES           List of libaries to use OpenSync
#
# Copyright (c) 2007 Daniel Gollub <gollub@b1-systems.de>
# Copyright (c) 2007 Alban Browaeys <prahal@yahoo.com>
# Copyright (c) 2008 Bjoern Ricks <bjoern.ricks@googlemail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

# Take care about libopensync.pc settings
INCLUDE( FindPkgConfig )

IF ( OpenSync_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE( OpenSync_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "" )	
ENDIF ( OpenSync_FIND_REQUIRED )

IF ( OPENSYNC_MIN_VERSION )
	PKG_SEARCH_MODULE( OPENSYNC ${_pkgconfig_REQUIRED} libopensync1 >=${OPENSYNC_MIN_VERSION} )
ELSE ( OPENSYNC_MIN_VERSION )
	PKG_SEARCH_MODULE( OPENSYNC ${_pkgconfig_REQUIRED} libopensync1 )
ENDIF ( OPENSYNC_MIN_VERSION )

FIND_PROGRAM( PKGCONFIG_EXECUTABLE NAMES pkg-config )

IF ( PKGCONFIG_EXECUTABLE )
	EXEC_PROGRAM( ${PKGCONFIG_EXECUTABLE} ARGS libopensync1 --variable=datadir OUTPUT_VARIABLE _opensync_data_DIR )
	STRING( REGEX REPLACE "[\r\n]" " " _opensync_data_DIR "${_opensync_data_DIR}"  )
ENDIF ( PKGCONFIG_EXECUTABLE )

FIND_PATH( OPENSYNC_CMAKE_MODULES "OpenSyncInternal.cmake" PATHS "${_opensync_data_DIR}" PATH_SUFFIXES "cmake/modules" NO_DEFAULT_PATH) 
FIND_PATH( OPENSYNC_CMAKE_MODULES "OpenSyncInternal.cmake" PATH_SUFFIXES "cmake/modules" ) 

IF ( OPENSYNC_CMAKE_MODULES )
	SET( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${OPENSYNC_CMAKE_MODULES}" )
ELSE ( OPENSYNC_CMAKE_MODULES )
	IF ( OpenSync_FIND_REQUIRED )
		MESSAGE( FATAL_ERROR "OpenSync cmake modules not found. Have you installed opensync core or did you set your PKG_CONFIG_PATH if installing in a non system directory ?" )
	ENDIF ( OpenSync_FIND_REQUIRED )
ENDIF ( OPENSYNC_CMAKE_MODULES )


# Look for OpenSync include dir and libraries without pkg-config 
IF( NOT OPENSYNC_FOUND AND NOT PKG_CONFIG_FOUND )
	# Fallback if pkg-config doesn't exist
	FIND_PATH( OPENSYNC_INCLUDE_DIRS opensync/opensync.h PATH_SUFFIXES libopensync libopensync1
			PATHS
			/opt/local/include/
			/sw/include/
			/usr/local/include/
			/usr/include/ )

	FIND_LIBRARY( OPENSYNC_LIBRARIES opensync
			PATHS
			/opt/local/lib
			/sw/lib
			/usr/lib
			/usr/local/lib
			/usr/lib64
			/usr/local/lib64
			/opt/lib64 )

	# Report results
	IF ( OPENSYNC_LIBRARIES AND OPENSYNC_INCLUDE_DIRS )	
		SET( OPENSYNC_FOUND 1 )
		IF ( NOT OpenSync_FIND_QUIETLY )
			MESSAGE( STATUS "Found OpenSync: ${OPENSYNC_LIBRARIES}" )
		ENDIF ( NOT OpenSync_FIND_QUIETLY )
	ELSE ( OPENSYNC_LIBRARIES AND OPENSYNC_INCLUDE_DIRS )	
		IF ( OpenSync_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find OpenSync" )
		ELSE ( OpenSync_FIND_REQUIRED )
			IF ( NOT OpenSync_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find OpenSync" )	
			ENDIF ( NOT OpenSync_FIND_QUIETLY )
		ENDIF ( OpenSync_FIND_REQUIRED )
	ENDIF ( OPENSYNC_LIBRARIES AND OPENSYNC_INCLUDE_DIRS )	
ENDIF( NOT OPENSYNC_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( OPENSYNC_LIBRARIES OPENSYNC_INCLUDE_DIRS )

