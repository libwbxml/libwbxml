# - Try to find OpenObex
# Find OpenObex headers, libraries and the answer to all questions.
#
#  OPENOBEX_FOUND               True if OpenObex got found
#  OPENOBEX_INCLUDE_DIRS         Location of OpenObex headers 
#  OPENOBEX_LIBRARIES           List of libaries to use OpenObex
#
# Copyright (c) 2007 Daniel Gollub <dgollub@suse.de>
# Copyright (c) 2007 Bjoern Ricks  <b.ricks@fh-osnabrueck.de>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

INCLUDE( FindPkgConfig )

IF ( OpenObex_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE( OpenObex_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "" )	
ENDIF ( OpenObex_FIND_REQUIRED )

IF ( OPENOBEX_MIN_VERSION )
	PKG_SEARCH_MODULE( OPENOBEX openobex>=${OPENOBEX_MIN_VERSION} ${_pkgconfig_REQUIRED} )
ELSE ( OPENOBEX_MIN_VERSION )
	PKG_SEARCH_MODULE( OPENOBEX openobex ${_pkgconfig_REQUIRED} )
ENDIF ( OPENOBEX_MIN_VERSION )

IF( NOT OPENOBEX_FOUND AND NOT PKG_CONFIG_FOUND )
	# Fallback if pkg-config doesn't exist
	#MESSAGE( STATUS "FALLBACK" )
	FIND_PATH( OPENOBEX_INCLUDE_DIRS openobex/obex.h
		PATHS
		/opt/local/include/
		/sw/include/
		/usr/local/include/
		/usr/include/ )


	FIND_LIBRARY( OPENOBEX_LIBRARIES openobex
		PATHS
		/opt/local/lib
		/sw/lib
		/usr/lib
		/usr/local/lib
		/usr/lib64
		/usr/local/lib64
		/opt/lib64 )


	# Report results
	IF ( OPENOBEX_LIBRARIES AND OPENOBEX_INCLUDE_DIRS )	
		SET( OPENOBEX_FOUND 1 )
		IF ( NOT OpenObex_FIND_QUIETLY )
			MESSAGE( STATUS "Found OpenObex: ${OPENOBEX_LIBRARIES}" )
		ENDIF ( NOT OpenObex_FIND_QUIETLY )
	ELSE ( OPENOBEX_LIBRARIES AND OPENOBEX_INCLUDE_DIRS )	
		IF ( OpenObex_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find OpenObex" )
		ELSE ( OpenObex_FIND_REQUIRED )
			IF ( NOT OpenObex_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find OpenObex" )	
			ENDIF ( NOT OpenObex_FIND_QUIETLY )
		ENDIF ( OpenObex_FIND_REQUIRED )
	ENDIF ( OPENOBEX_LIBRARIES AND OPENOBEX_INCLUDE_DIRS )	
ENDIF( NOT OPENOBEX_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( OPENOBEX_LIBRARIES OPENOBEX_INCLUDE_DIRS )

