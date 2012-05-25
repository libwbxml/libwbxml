# - Try to find orbit 
# Find orbit headers, libraries and the answer to all questions.
#
#  ORBIT2_FOUND               True if orbit got found
#  ORBIT2_INCLUDEDIR          Location of orbit headers 
#  ORBIT2_LIBRARIES           List of libaries to use orbit 
#  ORBIT2_DEFINITIONS         Definitions to compile orbit 
#
# Copyright (c) 2007 Juha Tuomala <tuju@iki.fi>
# Copyright (c) 2007 Daniel Gollub <gollub@b1-systems.de>
# Copyright (c) 2007 Alban Browaeys <prahal@yahoo.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#

INCLUDE( FindPkgConfig )

# Take care about ORBit-2.0.pc settings
IF ( ORBit2_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( ORBit2_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( ORBit2_FIND_REQUIRED )

IF ( ORBIT2_MIN_VERSION )
	pkg_search_module( ORBIT2 ${_pkgconfig_REQUIRED} ORBit-2.0>=${ORBIT2_MIN_VERSION} )
ELSE ( ORBIT2_MIN_VERSION )
	pkg_search_module( ORBIT2 ${_pkgconfig_REQUIRED} ORBit-2.0 )
ENDIF ( ORBIT2_MIN_VERSION )


# Look for orbit include dir and libraries w/o pkgconfig
IF ( NOT ORBIT2_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _orbit2_include_DIR orbit/orbit.h PATH_SUFFIXES orbit-2.0 )
	FIND_LIBRARY( _orbit2_link_DIR ORBit-2)
	IF ( _orbit2_include_DIR AND _orbit2_link_DIR )
		SET ( _orbit2_FOUND TRUE )
	ENDIF ( _orbit2_include_DIR AND _orbit2_link_DIR )

	IF ( _orbit2_FOUND )
		SET ( ORBIT2_INCLUDE_DIRS ${_orbit2_include_DIR} )
		SET ( ORBIT2_LIBRARIES ${_orbit2_link_DIR} )
	ENDIF ( _orbit2_FOUND )

	IF ( NOT GLIB2_FOUND )
		FIND_PACKAGE( GLIB2 REQUIRED)

		IF ( GTHREAD2_FOUND )
			SET ( ORBIT2_INCLUDE_DIRS ${ORBIT2_INCLUDE_DIRS} ${GTHREAD2_INCLUDE_DIR} )
			SET ( ORBIT2_LIBRARIES ${ORBIT2_LIBRARIES} ${GTHREAD2_LIBRARY} )
		ENDIF ( GTHREAD2_FOUND )
		IF ( GOBJECT2_FOUND )
			SET ( ORBIT2_INCLUDE_DIRS ${ORBIT2_INCLUDE_DIRS} ${GOBJECT2_INCLUDE_DIR} )
			SET ( ORBIT2_LIBRARIES ${ORBIT2_LIBRARIES} ${GOBJECT2_LIBRARY} )
		ENDIF ( GOBJECT2_FOUND )
		IF ( GLIB2_FOUND )
			SET ( ORBIT2_INCLUDE_DIRS ${ORBIT2_INCLUDE_DIRS} ${GLIB2_INCLUDE_DIR} ${GLIBCONFIG_INCLUDE_DIR} )
			SET ( ORBIT2_LIBRARIES ${ORBIT2_LIBRARIES} ${GLIB2_LIBRARY} )
		ENDIF ( GLIB2_FOUND )
	ENDIF ( NOT GLIB2_FOUND )

	# Report results
	IF ( ORBIT2_LIBRARIES AND ORBIT2_INCLUDE_DIRS AND _orbit2_FOUND)	
		SET( ORBIT2_FOUND 1 )
		IF ( NOT ORBit2_FIND_QUIETLY )
			MESSAGE( STATUS "Found ORBit2: ${ORBIT2_LIBRARIES} ${ORBIT2_INCLUDE_DIRS}" )
		ENDIF ( NOT ORBit2_FIND_QUIETLY )
	ELSE ( ORBIT2_LIBRARIES AND ORBIT2_INCLUDE_DIRS AND _orbit2_FOUND )	
		IF ( ORBit2_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find ORBit2" )
		ELSE ( ORBit2_FIND_REQUIRED )
			IF ( NOT ORBit2_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find ORBit2" )	
			ENDIF ( NOT ORBit2_FIND_QUIETLY )
		ENDIF ( ORBit2_FIND_REQUIRED )
	ENDIF ( ORBIT2_LIBRARIES AND ORBIT2_INCLUDE_DIRS AND _orbit2_FOUND )	

	MARK_AS_ADVANCED( _orbit2_include_DIR _orbit2_link_DIR )

ENDIF ( NOT ORBIT2_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( ORBIT2_LIBRARIES ORBIT2_INCLUDE_DIRS )

