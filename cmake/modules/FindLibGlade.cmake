# - Try to find LIBGLADE
# Find LIBGLADE headers, libraries and the answer to all questions.
#
#  LIBGLADE_FOUND               True if LIBGLADE got found
#  LIBGLADE_INCLUDE_DIR         Location of LIBGLADE headers 
#  LIBGLADE_LIBRARIES           List of libaries to use LIBGLADE
#  LIBGLADE_DEFINITIONS         Definitions to compile LIBGLADE 
#
#  Copyright (c) 2007 Daniel Gollub <gollub@b1-systems.de>
#  Copyright (c) 2008 Daniel Friedrich <daniel.friedrich@opensync.org>
#  Copyright (c) 2008 Bjoern Ricks <bjoern.ricks@googlemail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

INCLUDE( FindPkgConfig )

IF ( LibGlade_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE( LibGlade_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "" )	
ENDIF ( LibGlade_FIND_REQUIRED )

IF ( LIBGLADE_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBGLADE ${_pkgconfig_REQUIRED} libglade-2.0>=${LIBGLADE_MIN_VERSION} )
ELSE ( LIBGLADE_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBGLADE ${_pkgconfig_REQUIRED} libglade-2.0 )
ENDIF ( LIBGLADE_MIN_VERSION )


IF( NOT LIBGLADE_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH(LIBGLADE_INCLUDE_DIRS glade/glade.h )
	FIND_LIBRARY( LIBGLADE_LIBRARIES glade-2.0)

	# Report results
	IF ( LIBGLADE_LIBRARIES AND LIBGLADE_INCLUDE_DIRS )	
		SET( LIBGLADE_FOUND 1 )
		IF ( NOT LIBGLADE_FIND_QUIETLY )
			MESSAGE( STATUS "Found LIBGLADE: ${LIBGLADE_LIBRARIES}" )
		ENDIF ( NOT LIBGLADE_FIND_QUIETLY )
	ELSE ( LIBGLADE_LIBRARIES AND LIBGLADE_INCLUDE_DIRS )	
		IF ( LibGlade_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find LIBGLADE" )
		ELSE ( LibGlade_FIND_REQUIRED )
			IF ( NOT LIBGLADE_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find LIBGLADE" )	
			ENDIF ( NOT LIBGLADE_FIND_QUIETLY )
		ENDIF ( LibGlade_FIND_REQUIRED )
	ENDIF ( LIBGLADE_LIBRARIES AND LIBGLADE_INCLUDE_DIRS )
ENDIF( NOT LIBGLADE_FOUND AND NOT PKG_CONFIG_FOUND )	

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( LIBGLADE_LIBRARIES LIBGLADE_INCLUDE_DIRS )
