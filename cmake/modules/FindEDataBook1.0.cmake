# - Try to find libedatabook1.0 components
# Find libedatabook 1.0 headers, libraries and the answer to all questions.
#
#  LIBEDATABOOK1.0_FOUND               True if libedatabook1.0 got found
#  LIBEDATABOOK1.0_INCLUDE_DIRS         Location of libedatabook1.0 headers 
#  LIBEDATABOOK1.0_LIBRARIES           List of libaries to use libedatabook1.0
#  LIBEDATABOOK1.0_DEFINITIONS         Definitions to compile libedatabook1.0 
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
# Take care about libedata-book-1.0.pc settings
IF ( EDataBook1.0_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( EDataBook1.0_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( EDataBook1.0_FIND_REQUIRED )

pkg_search_module( LIBEDATABOOK1.0 ${_pkgconfig_REQUIRED} libedata-book-1.0 )


# Look for libedatabook1.0 include dir and libraries w/o pkg-config.
IF ( NOT LIBEDATABOOK1.0_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _libedatabook1.0_include_DIR libedata-book/e-data-book.h 
			PATH_SUFFIXES evolution-data-server-1.12 evolution-data-server-1.10 evolution-data-server-1.8 evolution-data-server-1.6 evolution-data-server-1.4 evolution-data-server-1.0
			PATHS
			/opt/local/include/
			/sw/include/
			/usr/local/include/
			/usr/include/ 
	)
	FIND_LIBRARY( _libedatabook1.0_link_DIR edata-book-1.0
			PATHS
			/opt/local/lib
			/sw/lib
			/usr/lib
			/usr/local/lib
			/usr/lib64
			/usr/local/lib64
			/opt/lib64 
	)

        IF ( _libedatabook1.0_include_DIR AND _libedatabook1.0_link_DIR )
                SET ( _libedatabook1.0_FOUND TRUE )
        ENDIF ( _libedatabook1.0_include_DIR AND _libedatabook1.0_link_DIR )


        IF ( _libedatabook1.0_FOUND )
                SET ( LIBEDATABOOK1.0_INCLUDE_DIRS ${_libedatabook1.0_include_DIR} )
                SET ( LIBEDATABOOK1.0_LIBRARIES ${_libedatabook1.0_link_DIR} )
        ENDIF ( _libedatabook1.0_FOUND )

        # Handle dependencies
	IF ( NOT LIBEBOOK1.0_FOUND )
		FIND_PACKAGE ( EBook1.0 REQUIRED )
                IF ( LIBEBOOK1.0_FOUND )
                        SET ( LIBEDATABOOK1.0_INCLUDE_DIRS ${LIBEDATABOOK1.0_INCLUDE_DIRS} ${LIBEBOOK1.0_INCLUDE_DIRS} )
                        SET ( LIBEDATABOOK1.0_LIBRARIES ${LIBEDATABOOK1.0_LIBRARIES} ${LIBEBOOK1.0_LIBRARIES} )
                ENDIF ( LIBEBOOK1.0_FOUND )		
	ENDIF ( NOT LIBEBOOK1.0_FOUND )
	IF ( NOT LIBEDATASERVER1.0_FOUND )
		FIND_PACKAGE ( EDataServer1.0 REQUIRED )
                IF ( LIBEDATASERVER1.0_FOUND )
                        SET ( LIBEDATABOOK1.0_INCLUDE_DIRS ${LIBEDATABOOK1.0_INCLUDE_DIRS} ${LIBEDATASERVER1.0_INCLUDE_DIRS} )
                        SET ( LIBEDATABOOK1.0_LIBRARIES ${LIBEDATABOOK1.0_LIBRARIES} ${LIBEDATASERVER1.0_LIBRARIES} )
                ENDIF ( LIBEDATASERVER1.0_FOUND )		
	ENDIF ( NOT LIBEDATASERVER1.0_FOUND )
	IF ( NOT LIBGNOME2_FOUND )
		FIND_PACKAGE ( LibGnome2 REQUIRED )
                IF ( LIBGNOME2_FOUND )
                        SET ( LIBEDATABOOK1.0_INCLUDE_DIRS ${LIBEDATABOOK1.0_INCLUDE_DIRS} ${LIBGNOME2_INCLUDE_DIRS} )
                        SET ( LIBEDATABOOK1.0_LIBRARIES ${LIBEDATABOOK1.0_LIBRARIES} ${LIBGNOME2_LIBRARIES} )
                ENDIF ( LIBGNOME2_FOUND )		
	ENDIF ( NOT LIBGNOME2_FOUND )
	IF ( NOT BONOBO2_FOUND )
		SET ( BONOBO2_MIN_VERSION "2.4.2" )
		FIND_PACKAGE ( BONOBO2 REQUIRED )
                IF ( BONOBO2_FOUND )
                        SET ( LIBEDATABOOK1.0_INCLUDE_DIRS ${LIBEDATABOOK1.0_INCLUDE_DIRS} ${BONOBO2_INCLUDE_DIRS} )
                        SET ( LIBEDATABOOK1.0_LIBRARIES ${LIBEDATABOOK1.0_LIBRARIES} ${BONOBO2_LIBRARIES} )
                ENDIF ( BONOBO2_FOUND )		
	ENDIF ( NOT BONOBO2_FOUND )

	# Report results
	IF ( LIBEDATABOOK1.0_LIBRARIES AND LIBEDATABOOK1.0_INCLUDE_DIRS AND _libedatabook1.0_FOUND )
		SET( LIBEDATABOOK1.0_FOUND 1 )
		IF ( NOT EDataBook1.0_FIND_QUIETLY )
			MESSAGE( STATUS "Found libedatabook-1.0: ${LIBEDATABOOK1.0_LIBRARIES}" )
		ENDIF ( NOT EDataBook1.0_FIND_QUIETLY )
	ELSE ( LIBEDATABOOK1.0_LIBRARIES AND LIBEDATABOOK1.0_INCLUDE_DIRS AND _libedatabook1.0_FOUND )	
		IF ( EDataBook1.0_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find libedatabook-1.0" )
		ELSE ( EDataBook1.0_FIND_REQUIRED )
			IF ( NOT EDataBook1.0_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find libedatabook-1.0" )	
			ENDIF ( NOT EDataBook1.0_FIND_QUIETLY )
		ENDIF ( EDataBook1.0_FIND_REQUIRED )
	ENDIF ( LIBEDATABOOK1.0_LIBRARIES AND LIBEDATABOOK1.0_INCLUDE_DIRS AND _libedatabook1.0_FOUND )	

ENDIF ( NOT LIBEDATABOOK1.0_FOUND AND NOT PKG_CONFIG_FOUND )
# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( LIBEDATABOOK1.0_LIBRARIES LIBEDATABOOK1.0_INCLUDE_DIRS )

