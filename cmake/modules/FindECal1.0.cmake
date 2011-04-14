# - Try to find libecal1.0 components
# Find libecal 1.0 headers, libraries and the answer to all questions.
#
#  LIBECAL1.0_FOUND               True if libecal1.0 got found
#  LIBECAL1.0_INCLUDE_DIRS         Location of libecal1.0 headers 
#  LIBECAL1.0_LIBRARIES           List of libaries to use libecal1.0
#  LIBECAL1.0_DEFINITIONS         Definitions to compile libecal1.0 
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
# Take care about libecal-1.0.pc settings
IF ( ECal1.0_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( ECal1.0_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( ECal1.0_FIND_REQUIRED )

pkg_search_module( LIBECAL1.0 ${_pkgconfig_REQUIRED} libecal-1.0 )


# Look for libecal1.0 include dir and libraries w/o pkg-config.
IF ( NOT LIBECAL1.0_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _libecal1.0_include_DIR libecal/e-cal.h 
			PATH_SUFFIXES evolution-data-server-1.12 evolution-data-server-1.10 evolution-data-server-1.8 evolution-data-server-1.6 evolution-data-server-1.4 evolution-data-server-1.0
			PATHS
			/opt/local/include/
			/sw/include/
			/usr/local/include/
			/usr/include/ 
	)
	FIND_LIBRARY( _libecal1.0_link_DIR ecal-1.0
			PATHS
			/opt/local/lib
			/sw/lib
			/usr/lib
			/usr/local/lib
			/usr/lib64
			/usr/local/lib64
			/opt/lib64 
	)

        IF ( _libecal1.0_include_DIR AND _libecal1.0_link_DIR )
                SET ( _libecal1.0_FOUND TRUE )
        ENDIF ( _libecal1.0_include_DIR AND _libecal1.0_link_DIR )


        IF ( _libecal1.0_FOUND )
                SET ( LIBECAL1.0_INCLUDE_DIRS ${_libecal1.0_include_DIR} )
                SET ( LIBECAL1.0_LIBRARIES ${_libecal1.0_link_DIR} )
        ENDIF ( _libecal1.0_FOUND )

        # Handle dependencies
	IF ( NOT LIBEDATASERVER1.0_FOUND )
		FIND_PACKAGE ( EDataServer1.0 REQUIRED )
                IF ( LIBEDATASERVER1.0_FOUND )
                        SET ( LIBECAL1.0_INCLUDE_DIRS ${LIBECAL1.0_INCLUDE_DIRS} ${LIBEDATASERVER1.0_INCLUDE_DIRS} )
                        SET ( LIBECAL1.0_LIBRARIES ${LIBECAL1.0_LIBRARIES} ${LIBEDATASERVER1.0_LIBRARIES} )
                ENDIF ( LIBEDATASERVER1.0_FOUND )		
	ENDIF ( NOT LIBEDATASERVER1.0_FOUND )
	IF ( NOT LIBGNOME2_FOUND )
		FIND_PACKAGE ( LibGnome2 REQUIRED )
                IF ( LIBGNOME2_FOUND )
                        SET ( LIBECAL1.0_INCLUDE_DIRS ${LIBECAL1.0_INCLUDE_DIRS} ${LIBGNOME2_INCLUDE_DIRS} )
                        SET ( LIBECAL1.0_LIBRARIES ${LIBECAL1.0_LIBRARIES} ${LIBGNOME2_LIBRARIES} )
                ENDIF ( LIBGNOME2_FOUND )		
	ENDIF ( NOT LIBGNOME2_FOUND )
	IF ( NOT BONOBO2_FOUND )
		FIND_PACKAGE ( BONOBO2 REQUIRED )
                IF ( BONOBO2_FOUND )
                        SET ( LIBECAL1.0_INCLUDE_DIRS ${LIBECAL1.0_INCLUDE_DIRS} ${BONOBO2_INCLUDE_DIRS} )
                        SET ( LIBECAL1.0_LIBRARIES ${LIBECAL1.0_LIBRARIES} ${BONOBO2_LIBRARIES} )
                ENDIF ( BONOBO2_FOUND )		
	ENDIF ( NOT BONOBO2_FOUND )

	# Report results
	IF ( LIBECAL1.0_LIBRARIES AND LIBECAL1.0_INCLUDE_DIRS AND _libecal1.0_FOUND )
		SET( LIBECAL1.0_FOUND 1 )
		IF ( NOT ECal1.0_FIND_QUIETLY )
			MESSAGE( STATUS "Found libecal-1.0: ${LIBECAL1.0_LIBRARIES}" )
		ENDIF ( NOT ECal1.0_FIND_QUIETLY )
	ELSE ( LIBECAL1.0_LIBRARIES AND LIBECAL1.0_INCLUDE_DIRS AND _libecal1.0_FOUND )	
		IF ( ECal1.0_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find libecal-1.0" )
		ELSE ( ECal1.0_FIND_REQUIRED )
			IF ( NOT ECal1.0_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find libecal-1.0" )	
			ENDIF ( NOT ECal1.0_FIND_QUIETLY )
		ENDIF ( ECal1.0_FIND_REQUIRED )
	ENDIF ( LIBECAL1.0_LIBRARIES AND LIBECAL1.0_INCLUDE_DIRS AND _libecal1.0_FOUND )	

ENDIF ( NOT LIBECAL1.0_FOUND AND NOT PKG_CONFIG_FOUND )
# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( LIBECAL1.0_LIBRARIES LIBECAL1.0_INCLUDE_DIRS )

