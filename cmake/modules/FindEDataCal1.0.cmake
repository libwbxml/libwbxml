# - Try to find libedatacal1.0 components
# Find libedatacal 1.0 headers, libraries and the answer to all questions.
#
#  LIBEDATACAL1.0_FOUND               True if libedatacal1.0 got found
#  LIBEDATACAL1.0_INCLUDE_DIRS         Location of libedatacal1.0 headers 
#  LIBEDATACAL1.0_LIBRARIES           List of libaries to use libedatacal1.0
#  LIBEDATACAL1.0_DEFINITIONS         Definitions to compile libedatacal1.0 
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
# Take care about libedata-cal-1.0.pc settings
IF ( EDataCal1.0_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( EDataCal1.0_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( EDataCal1.0_FIND_REQUIRED )

pkg_search_module( LIBEDATACAL1.0 ${_pkgconfig_REQUIRED} libedata-cal-1.0 )


# Look for libedatacal1.0 include dir and libraries w/o pkg-config.
IF ( NOT LIBEDATACAL1.0_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _libedatacal1.0_include_DIR libedata-cal/e-data-cal.h 
			PATH_SUFFIXES evolution-data-server-1.12 evolution-data-server-1.10 evolution-data-server-1.8 evolution-data-server-1.6 evolution-data-server-1.4 evolution-data-server-1.0
			PATHS
			/opt/local/include/
			/sw/include/
			/usr/local/include/
			/usr/include/ 
	)
	FIND_LIBRARY( _libedatacal1.0_link_DIR edata-cal-1.0
			PATHS
			/opt/local/lib
			/sw/lib
			/usr/lib
			/usr/local/lib
			/usr/lib64
			/usr/local/lib64
			/opt/lib64 
	)

        IF ( _libedatacal1.0_include_DIR AND _libedatacal1.0_link_DIR )
                SET ( _libedatacal1.0_FOUND TRUE )
        ENDIF ( _libedatacal1.0_include_DIR AND _libedatacal1.0_link_DIR )


        IF ( _libedatacal1.0_FOUND )
                SET ( LIBEDATACAL1.0_INCLUDE_DIRS ${_libedatacal1.0_include_DIR} )
                SET ( LIBEDATACAL1.0_LIBRARIES ${_libedatacal1.0_link_DIR} )
        ENDIF ( _libedatacal1.0_FOUND )

        # Handle dependencies
	IF ( NOT LIBECAL1.0_FOUND )
		FIND_PACKAGE ( ECal1.0 REQUIRED )
                IF ( LIBECAL1.0_FOUND )
                        SET ( LIBEDATACAL1.0_INCLUDE_DIRS ${LIBEDATACAL1.0_INCLUDE_DIRS} ${LIBECAL1.0_INCLUDE_DIRS} )
                        SET ( LIBEDATACAL1.0_LIBRARIES ${LIBEDATACAL1.0_LIBRARIES} ${LIBECAL1.0_LIBRARIES} )
                ENDIF ( LIBECAL1.0_FOUND )		
	ENDIF ( NOT LIBECAL1.0_FOUND )
	IF ( NOT GNOMEVFS2_FOUND )
		FIND_PACKAGE ( GnomeVfs2 REQUIRED )
                IF ( GNOMEVFS2_FOUND )
                        SET ( LIBEDATACAL1.0_INCLUDE_DIRS ${LIBEDATACAL1.0_INCLUDE_DIRS} ${GNOMEVFS2_INCLUDE_DIRS} )
                        SET ( LIBEDATACAL1.0_LIBRARIES ${LIBEDATACAL1.0_LIBRARIES} ${GNOMEVFS2_LIBRARIES} )
                ENDIF ( GNOMEVFS2_FOUND )		
	ENDIF ( NOT GNOMEVFS2_FOUND )
	IF ( NOT LIBEDATASERVER1.0_FOUND )
		FIND_PACKAGE ( EDataServer1.0 REQUIRED )
                IF ( LIBEDATASERVER1.0_FOUND )
                        SET ( LIBEDATACAL1.0_INCLUDE_DIRS ${LIBEDATACAL1.0_INCLUDE_DIRS} ${LIBEDATASERVER1.0_INCLUDE_DIRS} )
                        SET ( LIBEDATACAL1.0_LIBRARIES ${LIBEDATACAL1.0_LIBRARIES} ${LIBEDATASERVER1.0_LIBRARIES} )
                ENDIF ( LIBEDATASERVER1.0_FOUND )		
	ENDIF ( NOT LIBEDATASERVER1.0_FOUND )
	IF ( NOT LIBGNOME2_FOUND )
		FIND_PACKAGE ( LibGnome2 REQUIRED )
                IF ( LIBGNOME2_FOUND )
                        SET ( LIBEDATACAL1.0_INCLUDE_DIRS ${LIBEDATACAL1.0_INCLUDE_DIRS} ${LIBGNOME2_INCLUDE_DIRS} )
                        SET ( LIBEDATACAL1.0_LIBRARIES ${LIBEDATACAL1.0_LIBRARIES} ${LIBGNOME2_LIBRARIES} )
                ENDIF ( LIBGNOME2_FOUND )		
	ENDIF ( NOT LIBGNOME2_FOUND )
	IF ( NOT BONOBO2_FOUND )
		SET ( BONOBO2_MIN_VERSION "2.4.2" )
		FIND_PACKAGE ( BONOBO2 REQUIRED )
                IF ( BONOBO2_FOUND )
                        SET ( LIBEDATACAL1.0_INCLUDE_DIRS ${LIBEDATACAL1.0_INCLUDE_DIRS} ${BONOBO2_INCLUDE_DIRS} )
                        SET ( LIBEDATACAL1.0_LIBRARIES ${LIBEDATACAL1.0_LIBRARIES} ${BONOBO2_LIBRARIES} )
                ENDIF ( BONOBO2_FOUND )		
	ENDIF ( NOT BONOBO2_FOUND )

	# Report results
	IF ( LIBEDATACAL1.0_LIBRARIES AND LIBEDATACAL1.0_INCLUDE_DIRS AND _libedatacal1.0_FOUND )
		SET( LIBEDATACAL1.0_FOUND 1 )
		IF ( NOT EDataCal1.0_FIND_QUIETLY )
			MESSAGE( STATUS "Found libedatacal-1.0: ${LIBEDATACAL1.0_LIBRARIES}" )
		ENDIF ( NOT EDataCal1.0_FIND_QUIETLY )
	ELSE ( LIBEDATACAL1.0_LIBRARIES AND LIBEDATACAL1.0_INCLUDE_DIRS AND _libedatacal1.0_FOUND )	
		IF ( EDataCal1.0_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find libedatacal-1.0" )
		ELSE ( EDataCal1.0_FIND_REQUIRED )
			IF ( NOT EDataCal1.0_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find libedatacal-1.0" )	
			ENDIF ( NOT EDataCal1.0_FIND_QUIETLY )
		ENDIF ( EDataCal1.0_FIND_REQUIRED )
	ENDIF ( LIBEDATACAL1.0_LIBRARIES AND LIBEDATACAL1.0_INCLUDE_DIRS AND _libedatacal1.0_FOUND )	

ENDIF ( NOT LIBEDATACAL1.0_FOUND AND NOT PKG_CONFIG_FOUND )
# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( LIBEDATACAL1.0_LIBRARIES LIBEDATACAL1.0_INCLUDE_DIRS )

