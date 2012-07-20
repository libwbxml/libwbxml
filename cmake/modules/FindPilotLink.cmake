# - Try to find PilotLink
# Find PilotLink headers, libraries and the answer to all questions.
#
#  PILOTLINK_FOUND               True if PilotLink got found
#  PILOTLINK_INCLUDE_DIRS        Location of PilotLink headers 
#  PILOTLINK_LIBRARIES           List of libaries to use PilotLink
#  PILOTLINK_DEFINITIONS         Definitions to compile PilotLink 
#
#  Copyright (c) 2007 Daniel Gollub <gollub@b1-systems.de>
#  Copyright (c) 2008 Bjoern Ricks <bjoern.ricks@googlemail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

INCLUDE( FindPkgConfig )

IF ( PilotLink_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE( PilotLink_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "" )	
ENDIF ( PilotLink_FIND_REQUIRED )

IF ( PILOTLINK_MIN_VERSION )
	PKG_SEARCH_MODULE( PILOTLINK ${_pkgconfig_REQUIRED} pilot-link>=${PILOTLINK_MIN_VERSION} )
ELSE ( PILOTLINK_MIN_VERSION )
	PKG_SEARCH_MODULE( PILOTLINK ${_pkgconfig_REQUIRED} pilot-link )
ENDIF ( PILOTLINK_MIN_VERSION )


IF( NOT PILOTLINK_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( PILOTLINK_INCLUDE_DIRS pilot-link )
	FIND_LIBRARY( PILOTLINK_LIBRARIES pisock)

	# Report results
	IF ( PILOTLINK_LIBRARIES AND PILOTLINK_INCLUDE_DIRS )	
		SET( PILOTLINK_FOUND 1 )
		IF ( NOT PilotLink_FIND_QUIETLY )
			MESSAGE( STATUS "Found PilotLink: ${PILOTLINK_LIBRARIES}" )
		ENDIF ( NOT PilotLink_FIND_QUIETLY )
	ELSE ( PILOTLINK_LIBRARIES AND PILOTLINK_INCLUDE_DIRS )	
		IF ( PilotLink_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find PilotLink" )
		ELSE ( PilotLink_FIND_REQUIRED )
			IF ( NOT PilotLink_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find PilotLink" )	
			ENDIF ( NOT PilotLink_FIND_QUIETLY )
		ENDIF ( PilotLink_FIND_REQUIRED )
	ENDIF ( PILOTLINK_LIBRARIES AND PILOTLINK_INCLUDE_DIRS )	
ENDIF( NOT PILOTLINK_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( PILOTLINK_LIBRARIES PILOTLINK_INCLUDE_DIRS )

