# - Try to find GNOKII
# Find GNOKII headers, libraries and the answer to all questions.
#
#  GNOKII_FOUND               True if GNOKII got found
#  GNOKII_INCLUDE_DIRS        Location of GNOKII headers 
#  GNOKII_LIBRARIES           List of libaries to use GNOKII
#  GNOKII_DEFINITIONS         Definitions to compile GNOKII 
#
#  Copyright (c) 2007 Daniel Gollub <gollub@b1-systems.de>
#  Copyright (c) 2008 Bjoern Ricks  <bjoern.ricks@googlemail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#	

INCLUDE( FindPkgConfig )

IF ( GNOKII_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE( GNOKII_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "" )	
ENDIF ( GNOKII_FIND_REQUIRED )

IF ( GNOKII_MIN_VERSION )
	PKG_SEARCH_MODULE( GNOKII ${_pkgconfig_REQUIRED} gnokii>=${GNOKII_MIN_VERSION} )
ELSE ( GNOKII_MIN_VERSION )
	PKG_SEARCH_MODULE( GNOKII ${_pkgconfig_REQUIRED} gnokii )
ENDIF ( GNOKII_MIN_VERSION )


IF( NOT GNOKII_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( GNOKII_INCLUDE_DIRS gnokii.h )
	FIND_LIBRARY( GNOKII_LIBRARIES gnokii)

	# Report results
	IF ( GNOKII_LIBRARIES AND GNOKII_INCLUDE_DIRS )	
		SET( GNOKII_FOUND 1 )
		IF ( NOT GNOKII_FIND_QUIETLY )
			MESSAGE( STATUS "Found GNOKII: ${GNOKII_LIBRARIES}" )
		ENDIF ( NOT GNOKII_FIND_QUIETLY )
	ELSE ( GNOKII_LIBRARIES AND GNOKII_INCLUDE_DIRS )	
		IF ( GNOKII_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find GNOKII" )
		ELSE ( GNOKII_FIND_REQUIRED )
			IF ( NOT GNOKII_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find GNOKII" )	
			ENDIF ( NOT GNOKII_FIND_QUIETLY )
		ENDIF ( GNOKII_FIND_REQUIRED )
	ENDIF ( GNOKII_LIBRARIES AND GNOKII_INCLUDE_DIRS )
ENDIF( NOT GNOKII_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( GNOKII_LIBRARIES GNOKII_INCLUDE_DIRS )

