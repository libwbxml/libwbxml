# - Try to find bonobo2 
# Find bonobo2 headers, libraries and the answer to all questions.
#
#  BONOBO2_FOUND               True if bonobo2 got found
#  BONOBO2_INCLUDEDIR          Location of bonobo2 headers 
#  BONOBO2_LIBRARIES           List of libaries to use bonobo2
#  BONOBO2_DEFINITIONS         Definitions to compile bonobo2 
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
# Take care about libbonobo-2.0.pc settings
IF ( BONOBO2_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( BONOBO2_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( BONOBO2_FIND_REQUIRED )

IF ( BONOBO2_MIN_VERSION )
	pkg_search_module( BONOBO2 ${_pkgconfig_REQUIRED} libbonobo-2.0>=${BONOBO2_MIN_VERSION} )
ELSE ( BONOBO2_MIN_VERSION )
	pkg_search_module( BONOBO2 ${_pkgconfig_REQUIRED} libbonobo-2.0 )
ENDIF ( BONOBO2_MIN_VERSION )


# Look for libbonobo2 include dir and libraries w/o pkgconfig
IF ( NOT BONOBO2_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _bonobo2_include_DIR libbonobo.h PATH_SUFFIXES libbonobo-2.0 
		PATHS
		/opt/local/include/
		/sw/include/
		/usr/local/include/
		/usr/include/
	)
	FIND_LIBRARY( _bonobo2_link_DIR bonobo-2 
		PATHS
		/opt/local/lib
		/sw/lib
		/usr/lib
		/usr/local/lib
		/usr/lib64
		/usr/local/lib64
		/opt/lib64
	)
	IF ( _bonobo2_include_DIR AND _bonobo2_link_DIR )
		SET ( _bonobo2_FOUND TRUE )
	ENDIF ( _bonobo2_include_DIR AND _bonobo2_link_DIR )


	IF ( _bonobo2_FOUND )
		SET ( BONOBO2_INCLUDE_DIRS ${_bonobo2_include_DIR} )
		SET ( BONOBO2_LIBRARIES ${_bonobo2_link_DIR} )
	ENDIF ( _bonobo2_FOUND )

	# Handle dependencies
	IF ( NOT BONOBOACTIVATION2_FOUND )
		FIND_PACKAGE( BONOBOACTIVATION2 REQUIRED)
		IF ( BONOBOACTIVATION2_FOUND )
			SET ( BONOBO2_INCLUDE_DIRS ${BONOBO2_INCLUDE_DIRS} ${BONOBOACTIVATION2_INCLUDE_DIRS} )
			SET ( BONOBO2_LIBRARIES ${BONOBO2_LIBRARIES} ${BONOBOACTIVATION2_LIBRARIES} )
		ENDIF ( BONOBOACTIVATION2_FOUND )
	ENDIF ( NOT BONOBOACTIVATION2_FOUND )
	IF ( NOT ORBIT2_FOUND )
		FIND_PACKAGE( ORBit2 REQUIRED)
		IF ( ORBIT2_FOUND )
			SET ( BONOBO2_INCLUDE_DIRS ${BONOBO2_INCLUDE_DIRS} ${ORBIT2_INCLUDE_DIRS} )
			SET ( BONOBO2_LIBRARIES ${BONOBO2_LIBRARIES} ${ORBIT2_LIBRARIES} )
		ENDIF ( ORBIT2_FOUND )
	ENDIF ( NOT ORBIT2_FOUND )
        IF ( NOT GLIB2_FOUND )
                FIND_PACKAGE( GLIB2 REQUIRED)

                IF ( GMODULE2_FOUND )
                        SET ( BONOBO2_INCLUDE_DIRS ${BONOBO2_INCLUDE_DIRS} ${GMODULE2_INCLUDE_DIR} )
                        SET ( BONOBO2_LIBRARIES ${BONOBO2_LIBRARIES} ${GMODULE2_LIBRARY} )
                ENDIF ( GMODULE2_FOUND )
                IF ( GLIB2_FOUND )
                        SET ( BONOBO2_INCLUDE_DIRS ${BONOBO2_INCLUDE_DIRS} ${GLIB2_INCLUDE_DIR} ${GLIBCONFIG_INCLUDE_DIR} )
                        SET ( BONOBO2_LIBRARIES ${BONOBO2_LIBRARIES} ${GLIB2_LIBRARY} )
                ENDIF ( GLIB2_FOUND )
        ENDIF ( NOT GLIB2_FOUND )



	# Report results
	IF ( BONOBO2_LIBRARIES AND BONOBO2_INCLUDE_DIRS AND _bonobo2_FOUND )	
		SET( BONOBO2_FOUND 1 )
		IF ( NOT BONOBO2_FIND_QUIETLY )
			MESSAGE( STATUS "Found bonobo2: ${BONOBO2_LIBRARIES} ${BONOBO2_INCLUDE_DIRS}" )
		ENDIF ( NOT BONOBO2_FIND_QUIETLY )
	ELSE ( BONOBO2_LIBRARIES AND BONOBO2_INCLUDE_DIRS AND _bonobo2_FOUND )	
		IF ( BONOBO2_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find bonobo2" )
		ELSE ( BONOBO2_FIND_REQUIRED )
			IF ( NOT BONOBO2_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find bonobo2" )	
			ENDIF ( NOT BONOBO2_FIND_QUIETLY )
		ENDIF ( BONOBO2_FIND_REQUIRED )
	ENDIF ( BONOBO2_LIBRARIES AND BONOBO2_INCLUDE_DIRS AND _bonobo2_FOUND )	

ENDIF ( NOT BONOBO2_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( BONOBO2_LIBRARIES BONOBO2_INCLUDE_DIRS )

