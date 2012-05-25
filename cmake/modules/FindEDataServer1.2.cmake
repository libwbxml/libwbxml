# - Try to find libedataserver1.2 components
# Find libedataserver 1.2 headers, libraries and the answer to all questions.
#
#  LIBEDATASERVER1.2_FOUND               True if libedataserver1.2 got found
#  LIBEDATASERVER1.2_INCLUDE_DIRS         Location of libedataserver1.2 headers 
#  LIBEDATASERVER1.2_LIBRARIES           List of libaries to use libedataserver1.2
#  LIBEDATASERVER1.2_DEFINITIONS         Definitions to compile libedataserver1.2 
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
# Take care about libedataserver-1.2.pc settings
IF ( EDataServer1.2_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( EDataServer1.2_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( EDataServer1.2_FIND_REQUIRED )

pkg_search_module( LIBEDATASERVER1.2 ${_pkgconfig_REQUIRED} libedataserver-1.2 )


# Look for libedataserver1.2 include dir and libraries w/o pkg-config.
IF ( NOT LIBEDATASERVER1.2_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _libedataserver1.2_include_DIR libedataserver/e-account.h 
			PATH_SUFFIXES evolution-data-server-1.12 evolution-data-server-1.10 evolution-data-server-1.8 evolution-data-server-1.6 evolution-data-server-1.4 evolution-data-server-1.2
			PATHS
			/opt/local/include/
			/sw/include/
			/usr/local/include/
			/usr/include/ 
	)
	FIND_LIBRARY( _libedataserver1.2_link_DIR edataserver-1.2
			PATHS
			/opt/local/lib
			/sw/lib
			/usr/lib
			/usr/local/lib
			/usr/lib64
			/usr/local/lib64
			/opt/lib64 
	)

        IF ( _libedataserver1.2_include_DIR AND _libedataserver1.2_link_DIR )
                SET ( _libedataserver1.2_FOUND TRUE )
        ENDIF ( _libedataserver1.2_include_DIR AND _libedataserver1.2_link_DIR )


        IF ( _libedataserver1.2_FOUND )
                SET ( LIBEDATASERVER1.2_INCLUDE_DIRS ${_libedataserver1.2_include_DIR} )
                SET ( LIBEDATASERVER1.2_LIBRARIES ${_libedataserver1.2_link_DIR} )
        ENDIF ( _libedataserver1.2_FOUND )


        # Handle dependencies
	IF ( NOT GCONF2_FOUND )
		FIND_PACKAGE ( GConf2 REQUIRED )
                IF ( GCONF2_FOUND )
                        SET ( LIBEDATASERVER1.2_INCLUDE_DIRS ${LIBEDATASERVER1.2_INCLUDE_DIRS} ${GCONF2_INCLUDE_DIRS} )
                        SET ( LIBEDATASERVER1.2_LIBRARIES ${LIBEDATASERVER1.2_LIBRARIES} ${GCONF2_LIBRARIES} )
                ENDIF ( GCONF2_FOUND )		
	ENDIF ( NOT GCONF2_FOUND )
	IF ( NOT BONOBO2_FOUND )
		SET ( BONOBO2_MIN_VERSION "2.4.2" )
		FIND_PACKAGE ( BONOBO2 REQUIRED )
                IF ( BONOBO2_FOUND )
                        SET ( LIBEDATASERVER1.2_INCLUDE_DIRS ${LIBEDATASERVER1.2_INCLUDE_DIRS} ${BONOBO2_INCLUDE_DIRS} )
                        SET ( LIBEDATASERVER1.2_LIBRARIES ${LIBEDATASERVER1.2_LIBRARIES} ${BONOBO2_LIBRARIES} )
                ENDIF ( BONOBO2_FOUND )		
	ENDIF ( NOT BONOBO2_FOUND )
	IF ( NOT ORBIT2_FOUND )
		SET ( ORBIT2_MIN_VERSION "2.9.8" )
		FIND_PACKAGE ( ORBit2 REQUIRED )
                IF ( ORBIT2_FOUND )
                        SET ( LIBEDATASERVER1.2_INCLUDE_DIRS ${LIBEDATASERVER1.2_INCLUDE_DIRS} ${ORBIT2_INCLUDE_DIRS} )
                        SET ( LIBEDATASERVER1.2_LIBRARIES ${LIBEDATASERVER1.2_LIBRARIES} ${ORBIT2_LIBRARIES} )
                ENDIF ( ORBIT2_FOUND )		
	ENDIF ( NOT ORBIT2_FOUND )
	IF ( NOT LIBXML2_FOUND )
		FIND_PACKAGE ( LibXml2 REQUIRED )
                IF ( LIBXML2_FOUND )
                        SET ( LIBEDATASERVER1.2_INCLUDE_DIRS ${LIBEDATASERVER1.2_INCLUDE_DIRS} ${LIBXML2_INCLUDE_DIRS} )
                        SET ( LIBEDATASERVER1.2_LIBRARIES ${LIBEDATASERVER1.2_LIBRARIES} ${LIBXML2_LIBRARIES} )
                ENDIF ( LIBXML2_FOUND )		
	ENDIF ( NOT LIBXML2_FOUND )
	IF ( NOT GLIB2_FOUND )
		FIND_PACKAGE ( GLIB2 REQUIRED )
                IF ( GLIB2_FOUND )
                        SET ( LIBEDATASERVER1.2_INCLUDE_DIRS ${LIBEDATASERVER1.2_INCLUDE_DIRS} ${GLIB2_INCLUDE_DIRS} ${GLIBCONFIG_INCLUDE_DIR} )
                        SET ( LIBEDATASERVER1.2_LIBRARIES ${LIBEDATASERVER1.2_LIBRARIES} ${GLIB2_LIBRARIES} )
                ENDIF ( GLIB2_FOUND )		
	ENDIF ( NOT GLIB2_FOUND )

	# Report results
	IF ( LIBEDATASERVER1.2_LIBRARIES AND LIBEDATASERVER1.2_INCLUDE_DIRS AND _libedataserver1.2_FOUND )
		SET( LIBEDATASERVER1.2_FOUND 1 )
		IF ( NOT LibEDataServer1.2_FIND_QUIETLY )
			MESSAGE( STATUS "Found libedataserver-1.2: ${LIBEDATASERVER1.2_LIBRARIES}" )
		ENDIF ( NOT LibEDataServer1.2_FIND_QUIETLY )
	ELSE ( LIBEDATASERVER1.2_LIBRARIES AND LIBEDATASERVER1.2_INCLUDE_DIRS AND _libedataserver1.2_FOUND )	
		IF ( LibEDataServer1.2_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find libedataserver-1.2" )
		ELSE ( LibEDataServer1.2_FIND_REQUIRED )
			IF ( NOT LibEDataServer1.2_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find libedataserver-1.2" )	
			ENDIF ( NOT LibEDataServer1.2_FIND_QUIETLY )
		ENDIF ( LibEDataServer1.2_FIND_REQUIRED )
	ENDIF ( LIBEDATASERVER1.2_LIBRARIES AND LIBEDATASERVER1.2_INCLUDE_DIRS AND _libedataserver1.2_FOUND )	

ENDIF ( NOT LIBEDATASERVER1.2_FOUND AND NOT PKG_CONFIG_FOUND )
# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( LIBEDATASERVER1.2_LIBRARIES LIBEDATASERVER1.2_INCLUDE_DIRS )

