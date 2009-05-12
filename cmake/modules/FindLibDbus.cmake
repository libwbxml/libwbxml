# - Try to find LIBDBUS 
# Find LIBDBUS headers, libraries and the answer to all questions.
#
#  LIBDBUS_FOUND               True if libdbus got found
#  LIBDBUS_INCLUDE_DIRS        Location of libdbus headers 
#  LIBDBUS_LIBRARIES           List of libraries to use libdbus 
#
# Copyright (c) 2008 Bjoern Ricks <bjoern.ricks@googlemail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

INCLUDE( FindPkgConfig )

IF ( LibDbus_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE( LibDbus_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "" )	
ENDIF ( LibDbus_FIND_REQUIRED )

IF ( LIBDBUS_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBDBUS ${_pkgconfig_REQUIRED} dbus-1>=${LIBDBUS_MIN_VERSION} )
ELSE ( LIBDBUS_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBDBUS ${_pkgconfig_REQUIRED} dbus-1 )
ENDIF ( LIBDBUS_MIN_VERSION )


IF( NOT LIBDBUS_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( LIBDBUS_INCLUDE_DIRS dbus/dbus.h PATH_SUFFIXES dbus-1.0 dbus )
	FIND_LIBRARY( LIBDBUS_LIBRARIES dbus dbus-1)

	# Report results
	IF ( LIBDBUS_LIBRARIES AND LIBDBUS_INCLUDE_DIRS )	
		SET( LIBDBUS_FOUND 1 )
		IF ( NOT LIBDBUS_FIND_QUIETLY )
			MESSAGE( STATUS "Found libdbus: ${LIBDBUS_LIBRARIES}" )
		ENDIF ( NOT LIBDBUS_FIND_QUIETLY )
	ELSE ( LIBDBUS_LIBRARIES AND LIBDBUS_INCLUDE_DIRS )	
		IF ( LIBDBUS_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find libdbus" )
		ELSE ( LIBDBUS_FIND_REQUIRED )
			IF ( NOT LIBDBUS_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find libdbus" )	
			ENDIF ( NOT LIBDBUS_FIND_QUIETLY )
		ENDIF ( LIBDBUS_FIND_REQUIRED )
	ENDIF ( LIBDBUS_LIBRARIES AND LIBDBUS_INCLUDE_DIRS )
ENDIF( NOT LIBDBUS_FOUND AND NOT PKG_CONFIG_FOUND )

MARK_AS_ADVANCED( LIBDBUS_LIBRARIES LIBDBUS_INCLUDE_DIRS )