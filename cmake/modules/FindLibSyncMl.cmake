# - Try to find libsyncml
# Find libsyncml headers, libraries and the answer to all questions.
#
#  LIBSYNCML_FOUND               True if libsyncml got found
#  LIBSYNCML_INCLUDE_DIRS         Location of libsyncml headers 
#  LIBSYNCML_LIBRARIES           List of libaries to use libsyncml
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

# Take care about libsyncml-x.y.pc settings
IF ( LibSyncMl_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( LibSyncMl_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( LibSyncMl_FIND_REQUIRED )

# determine API generation

SET( LIBSYNCML_PC "libsyncml-1.0" )
PKG_SEARCH_MODULE( LIBSYNCML ${_pkgconfig_REQUIRED} libsyncml-3.0 )
IF ( LIBSYNCML_FOUND )
	SET ( LIBSYNCML_FOUND FALSE )
	SET( LIBSYNCML_PC "libsyncml-3.0" )
ENDIF ( LIBSYNCML_FOUND )

# check for libsyncml-x.y.pc

IF ( LIBSYNCML_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBSYNCML ${_pkgconfig_REQUIRED} ${LIBSYNCML_PC}>=${LIBSYNCML_MIN_VERSION} )
ELSE( LIBSYNCML_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBSYNCML ${_pkgconfig_REQUIRED} ${LIBSYNCML_PC} )
ENDIF ( LIBSYNCML_MIN_VERSION )


# Look for libsyncml include dir and libraries without pkg-config...
IF ( NOT LIBSYNCML_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _libsyncml_include_DIR libsyncml/syncml.h 
			PATH_SUFFIXES ${LIBSYNCML_PC}
			PATHS
			/opt/local/include/
			/sw/include/
			/usr/local/include/
			/usr/include/ 
	)

	FIND_LIBRARY( _libsyncml_link_DIR syncml 
			PATHS
			/opt/local/lib
			/sw/lib
			/usr/lib
			/usr/local/lib
			/usr/lib64
			/usr/local/lib64
			/opt/lib64 
	)

	IF ( _libsyncml_include_DIR AND _libsyncml_link_DIR )
		SET ( _libsyncml_FOUND TRUE )
	ENDIF ( _libsyncml_include_DIR AND _libsyncml_link_DIR )

	IF ( _libsyncml_FOUND )
		SET ( LIBSYNCML_INCLUDE_DIRS ${_libsyncml_include_DIR} )
		SET ( LIBSYNCML_LIBRARIES ${_libsyncml_link_DIR} )
	ENDIF ( _libsyncml_FOUND )

	# Handle dependencies
	IF( NOT LIBSOUP2_FOUND )
		SET ( LIBSOUP2_MIN_VERSION "2.2.91" )
		FIND_PACKAGE( LibSoup2 )
		IF ( LIBSOUP2_FOUND )
			SET ( LIBSYNCML_INCLUDE_DIRS ${LIBSYNCML_INCLUDE_DIRS} ${LIBSOUP2_INCLUDE_DIRS} )
			SET ( LIBSYNCML_LIBRARIES ${LIBSYNCML_LIBRARIES} ${LIBSOUP2_LIBRARIES} )
		ENDIF( LIBSOUP2_FOUND )
	ENDIF( NOT LIBSOUP2_FOUND )
	IF( NOT OPENOBEX_FOUND )
		SET ( OPENOBEX_MIN_VERSION "1.1" )
		FIND_PACKAGE( OpenObex )
		IF ( OPENOBEX_FOUND )
			SET ( LIBSYNCML_INCLUDE_DIRS ${LIBSYNCML_INCLUDE_DIRS} ${OPENOBEX_INCLUDE_DIRS} )
			SET ( LIBSYNCML_LIBRARIES ${LIBSYNCML_LIBRARIES} ${OPENOBEX_LIBRARIES} )
		ENDIF( OPENOBEX_FOUND )
	ENDIF( NOT OPENOBEX_FOUND )
	IF( NOT LIBWBXML2_FOUND )
		FIND_PACKAGE( LibWbxml2 REQUIRED )
		IF ( LIBWBXML2_FOUND )
			SET ( LIBSYNCML_INCLUDE_DIRS ${LIBSYNCML_INCLUDE_DIRS} ${LIBWBXML2_INCLUDE_DIRS} )
			SET ( LIBSYNCML_LIBRARIES ${LIBSYNCML_LIBRARIES} ${LIBWBXML2_LIBRARIES} )
		ENDIF( LIBWBXML2_FOUND )
	ENDIF( NOT LIBWBXML2_FOUND )
	IF( NOT BLUEZ_FOUND )
		FIND_PACKAGE( BlueZ )
		IF ( BLUEZ_FOUND )
			SET ( LIBSYNCML_INCLUDE_DIRS ${LIBSYNCML_INCLUDE_DIRS} ${BLUEZ_INCLUDE_DIRS} )
			SET ( LIBSYNCML_LIBRARIES ${LIBSYNCML_LIBRARIES} ${BLUEZ_LIBRARIES} )
		ENDIF( BLUEZ_FOUND )
	ENDIF( NOT BLUEZ_FOUND )
	IF( NOT LIBXML2_FOUND )
		FIND_PACKAGE( LibXml2 REQUIRED )
		IF ( LIBXML2_FOUND )
			SET ( LIBSYNCML_INCLUDE_DIRS ${LIBSYNCML_INCLUDE_DIRS} ${LIBXML2_INCLUDE_DIRS} )
			SET ( LIBSYNCML_LIBRARIES ${LIBSYNCML_LIBRARIES} ${LIBXML2_LIBRARIES} )
		ENDIF( LIBXML2_FOUND )
	ENDIF( NOT LIBXML2_FOUND )
	IF ( NOT GLIB2_FOUND )
                FIND_PACKAGE( GLIB2 REQUIRED)

                IF ( GOBJECT2_FOUND )
                        SET ( LIBSYNCML_INCLUDE_DIRS ${LIBSYNCML_INCLUDE_DIRS} ${GOBJECT2_INCLUDE_DIR} )
                        SET ( LIBSYNCML_LIBRARIES ${LIBSYNCML_LIBRARIES} ${GOBJECT2_LIBRARY} )
                ENDIF ( GOBJECT2_FOUND )
                IF ( GTHREAD2_FOUND )
                        SET ( LIBSYNCML_INCLUDE_DIRS ${LIBSYNCML_INCLUDE_DIRS} ${GTHREAD2_INCLUDE_DIR} )
                        SET ( LIBSYNCML_LIBRARIES ${LIBSYNCML_LIBRARIES} ${GTHREAD2_LIBRARY} )
                ENDIF ( GTHREAD2_FOUND )
                IF ( GLIB2_FOUND )
                        SET ( LIBSYNCML_INCLUDE_DIRS ${LIBSYNCML_INCLUDE_DIRS} ${GLIB2_INCLUDE_DIRS} ${GLIBCONFIG_INCLUDE_DIR} )
                        SET ( LIBSYNCML_LIBRARIES ${LIBSYNCML_LIBRARIES} ${GLIB2_LIBRARIES} )
                ENDIF ( GLIB2_FOUND )
        ENDIF ( NOT GLIB2_FOUND )


	# Report results
	IF ( LIBSYNCML_LIBRARIES AND LIBSYNCML_INCLUDE_DIRS )	
		SET( LIBSYNCML_FOUND 1 )
		IF ( NOT LibSyncMl_FIND_QUIETLY )
			MESSAGE( STATUS "Found libsyncml: ${LIBSYNCML_LIBRARIES}" )
		ENDIF ( NOT LibSyncMl_FIND_QUIETLY )
	ELSE ( LIBSYNCML_LIBRARIES AND LIBSYNCML_INCLUDE_DIRS )	
		IF ( LibSyncMl_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find libsyncml" )
		ELSE ( LibSyncMl_FIND_REQUIRED )
			IF ( NOT LibSyncMl_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find libsyncml" )	
			ENDIF ( NOT LibSyncMl_FIND_QUIETLY )
		ENDIF ( LibSyncMl_FIND_REQUIRED )
	ENDIF ( LIBSYNCML_LIBRARIES AND LIBSYNCML_INCLUDE_DIRS )	

ENDIF ( NOT LIBSYNCML_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( LIBSYNCML_LIBRARIES LIBSYNCML_INCLUDE_DIRS )

