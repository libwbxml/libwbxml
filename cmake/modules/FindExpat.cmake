# - Try to find Expat 
# Find Expat headers, libraries and the answer to all questions.
#
#  EXPAT_FOUND               True if Expat got found
#  EXPAT_INCLUDE_DIRS        Location of Expat headers 
#  EXPAT_LIBRARIES           List of libraries to use Expat 
#
#  Copyright (c) 2008 Bjoern Ricks <bjoern.ricks@googlemail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

# WARNING: Currently Expat doesn't provide a .pc file
#          Therefore it is not possible to use FindPkgConfig and to require a min version

#INCLUDE( FindPkgConfig )

#IF ( EXPAT_FIND_REQUIRED )
#	SET( _pkgconfig_REQUIRED "REQUIRED" )
#ELSE( EXPAT_FIND_REQUIRED )
#	SET( _pkgconfig_REQUIRED "" )	
#ENDIF ( EXPAT_FIND_REQUIRED )

#IF ( EXPAT_MIN_VERSION )
#	PKG_SEARCH_MODULE( EXPAT ${_pkgconfig_REQUIRED} expat>=${EXPAT_MIN_VERSION} )
#ELSE ( EXPAT_MIN_VERSION )
#	PKG_SEARCH_MODULE( EXPAT ${_pkgconfig_REQUIRED} expat )
#ENDIF ( EXPAT_MIN_VERSION )


#IF( NOT EXPAT_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( EXPAT_INCLUDE_DIRS expat.h)
	FIND_LIBRARY( EXPAT_LIBRARIES expat )

	# Report results
	IF ( EXPAT_LIBRARIES AND EXPAT_INCLUDE_DIRS )	
		SET( EXPAT_FOUND 1 )
		IF ( NOT EXPAT_FIND_QUIETLY )
			MESSAGE( STATUS "Found Expat: ${EXPAT_LIBRARIES}" )
		ENDIF ( NOT EXPAT_FIND_QUIETLY )
	ELSE ( EXPAT_LIBRARIES AND EXPAT_INCLUDE_DIRS )	
		IF ( EXPAT_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find Expat" )
		ELSE ( EXPAT_FIND_REQUIRED )
			IF ( NOT EXPAT_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find Expat" )	
			ENDIF ( NOT EXPAT_FIND_QUIETLY )
		ENDIF ( EXPAT_FIND_REQUIRED )
	ENDIF ( EXPAT_LIBRARIES AND EXPAT_INCLUDE_DIRS )
#ENDIF( NOT EXPAT_FOUND AND NOT PKG_CONFIG_FOUND )

MARK_AS_ADVANCED( EXPAT_LIBRARIES EXPAT_INCLUDE_DIRS )