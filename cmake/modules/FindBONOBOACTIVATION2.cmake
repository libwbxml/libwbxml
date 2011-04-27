# - Try to find bonobo-activation-2 
# Find bonobo-activation-2 headers, libraries and the answer to all questions.
#
#  BONOBOACTIVATION2_FOUND               True if bonobo-activation-2 got found
#  BONOBOACTIVATION2_INCLUDEDIR          Location of bonobo-activation-2 headers 
#  BONOBOACTIVATION2_LIBRARIES           List of libaries to use bonobo-activation-2
#  BONOBOACTIVATION2_DEFINITIONS         Definitions to compile bonobo-activation-2 
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
# Take care about bonobo-activation-2.0.pc settings
IF ( BONOBOACTIVATION2_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( BONOBOACTIVATION2_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( BONOBOACTIVATION2_FIND_REQUIRED )

IF ( BONOBOACTIVATION2_MIN_VERSION )
	pkg_search_module( BONOBOACTIVATION2 ${_pkgconfig_REQUIRED} bonobo-activation-2.0>=${BONOBOACTIVATION2_MIN_VERSION} )
ELSE ( BONOBOACTIVATION2_MIN_VERSION )
	pkg_search_module( BONOBOACTIVATION2 ${_pkgconfig_REQUIRED} bonobo-activation-2.0 )
ENDIF ( BONOBOACTIVATION2_MIN_VERSION )


# Look for bonoboactivation2 include dir and libraries w/o pkgconfig
IF ( NOT BONOBOACTIVATION2_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _bonoboactivation2_include_DIR bonobo-activation/bonobo-activation.h PATH_SUFFIXES bonobo-activation-2.0 
		PATHS
		/opt/local/include/
		/sw/include/
		/usr/local/include/
		/usr/include/
	)
	FIND_LIBRARY( _bonoboactivation2_link_DIR bonobo-activation 
		PATHS
		/opt/local/lib
		/sw/lib
		/usr/lib
		/usr/local/lib
		/usr/lib64
		/usr/local/lib64
		/opt/lib64
	)

	IF ( _bonoboactivation2_include_DIR AND _bonoboactivation2_link_DIR )
		SET ( _bonoboactivation2_FOUND TRUE )
	ENDIF ( _bonoboactivation2_include_DIR AND _bonoboactivation2_link_DIR )


	IF ( _bonoboactivation2_FOUND )
		SET ( BONOBOACTIVATION2_INCLUDE_DIRS ${_bonoboactivation2_include_DIR} )
		SET ( BONOBOACTIVATION2_LIBRARIES ${_bonoboactivation2_link_DIR} )
	ENDIF ( _bonoboactivation2_FOUND )

	# Handle dependencies
	IF ( NOT ORBIT2_FOUND )
		FIND_PACKAGE( ORBit2 REQUIRED)
		IF ( ORBIT2_FOUND )
			SET ( BONOBOACTIVATION2_INCLUDE_DIRS ${BONOBOACTIVATION2_INCLUDE_DIRS} ${ORBIT2_INCLUDE_DIRS} )
			SET ( BONOBOACTIVATION2_LIBRARIES ${BONOBOACTIVATION2_LIBRARIES} ${ORBIT2_LIBRARIES} )
		ENDIF ( ORBIT2_FOUND )
	ENDIF ( NOT ORBIT2_FOUND )
        IF ( NOT GLIB2_FOUND )
                FIND_PACKAGE( GLIB2 REQUIRED)

                IF ( GMODULE2_FOUND )
                        SET ( BONOBOACTIVATION2_INCLUDE_DIRS ${BONOBOACTIVATION2_INCLUDE_DIRS} ${GMODULE2_INCLUDE_DIR} )
                        SET ( BONOBOACTIVATION2_LIBRARIES ${BONOBOACTIVATION2_LIBRARIES} ${GMODULE2_LIBRARY} )
                ENDIF ( GMODULE2_FOUND )
                IF ( GLIB2_FOUND )
                        SET ( BONOBOACTIVATION2_INCLUDE_DIRS ${BONOBOACTIVATION2_INCLUDE_DIRS} ${GLIB2_INCLUDE_DIR} ${GLIBCONFIG_INCLUDE_DIR} )
                        SET ( BONOBOACTIVATION2_LIBRARIES ${BONOBOACTIVATION2_LIBRARIES} ${GLIB2_LIBRARY} )
                ENDIF ( GLIB2_FOUND )
        ENDIF ( NOT GLIB2_FOUND )


	# Report results
	IF ( BONOBOACTIVATION2_LIBRARIES AND BONOBOACTIVATION2_INCLUDE_DIRS AND _bonoboactivation2_FOUND )	
		SET( BONOBOACTIVATION2_FOUND 1 )
		IF ( NOT BONOBOACTIVATION2_FIND_QUIETLY )
			MESSAGE( STATUS "Found bonobo-activation2: ${BONOBOACTIVATION2_LIBRARIES} ${BONOBOACTIVATION2_INCLUDE_DIRS}" )
		ENDIF ( NOT BONOBOACTIVATION2_FIND_QUIETLY )
	ELSE ( BONOBOACTIVATION2_LIBRARIES AND BONOBOACTIVATION2_INCLUDE_DIRS AND _bonoboactivation2_FOUND )	
		IF ( BONOBOACTIVATION2_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find bonobo-activation2" )
		ELSE ( BONOBOACTIVATION2_FIND_REQUIRED )
			IF ( NOT BONOBOACTIVATION2_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find bonobo-activation2" )	
			ENDIF ( NOT BONOBOACTIVATION2_FIND_QUIETLY )
		ENDIF ( BONOBOACTIVATION2_FIND_REQUIRED )
	ENDIF ( BONOBOACTIVATION2_LIBRARIES AND BONOBOACTIVATION2_INCLUDE_DIRS AND _bonoboactivation2_FOUND )	

ENDIF ( NOT BONOBOACTIVATION2_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( BONOBOACTIVATION2_LIBRARIES BONOBOACTIVATION2_INCLUDE_DIRS )

