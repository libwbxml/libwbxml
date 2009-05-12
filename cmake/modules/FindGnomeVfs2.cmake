# - Try to find gnomevfs2 
# Find gnomevfs2 headers, libraries and the answer to all questions.
#
#  GNOMEVFS2_FOUND               True if gnomevfs2 got found
#  GNOMEVFS2_INCLUDEDIR          Location of gnomevfs2 headers 
#  GNOMEVFS2_LIBRARIES           List of libaries to use gnomevfs2
#  GNOMEVFS2_DEFINITIONS         Definitions to compile gnomevfs2 
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
# Take care about gnome-vfs-2.0.pc settings
IF ( GnomeVfs2_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE ( GnomeVfs2_FIND_REQUIRED )
  SET( _pkgconfig_REQUIRED "" )
ENDIF ( GnomeVfs2_FIND_REQUIRED )

pkg_search_module( GNOMEVFS2 ${_pkgconfig_REQUIRED} gnome-vfs-2.0 )


# Look for gnomevfs2 include dir and libraries w/o pkgconfig
IF ( NOT GNOMEVFS2_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( _gnomevfs2_include_DIR libgnomevfs/gnome-vfs.h PATH_SUFFIXES gnome-vfs-2.0 
		PATHS
		/opt/local/include/
		/sw/include/
		/usr/local/include/
		/usr/include/
	)
	FIND_PATH( _gnomevfs2_filesize_include_DIR gnome-vfs-file-size.h 
		PATHS
		/opt/gnome/lib64/gnome-vfs-2.0/include
		/opt/gnome/lib/gnome-vfs-2.0/include
		/opt/lib/gnome-vfs-2.0/include
		/opt/local/lib/gnome-vfs-2.0/include
		/sw/lib/gnome-vfs-2.0/include
		/usr/lib64/gnome-vfs-2.0/include
		/usr/lib/gnome-vfs-2.0/include
	)
	FIND_LIBRARY( _gnomevfs2_link_DIR gnomevfs-2
		PATHS
		/opt/local/lib
		/sw/lib
		/usr/lib
		/usr/local/lib
		/usr/lib64
		/usr/local/lib64
		/opt/lib64
	)
	IF ( _gnomevfs2_include_DIR AND _gnomevfs2_filesize_include_DIR AND _gnomevfs2_link_DIR )
		SET ( _gnomevfs2_FOUND TRUE )
	ENDIF ( _gnomevfs2_include_DIR AND _gnomevfs2_filesize_include_DIR AND _gnomevfs2_link_DIR )


	IF ( _gnomevfs2_FOUND )
		SET ( GNOMEVFS2_INCLUDE_DIRS ${_gnomevfs2_include_DIR} ${_gnomevfs2_filesize_include_DIR} )
		SET ( GNOMEVFS2_LIBRARIES ${_gnomevfs2_link_DIR} )
	ENDIF ( _gnomevfs2_FOUND )

	# Handle dependencies
	IF ( NOT GCONF2_FOUND )
		FIND_PACKAGE( GConf2 REQUIRED)
		IF ( GCONF2_FOUND )
			SET ( GNOMEVFS2_INCLUDE_DIRS ${GNOMEVFS2_INCLUDE_DIRS} ${GCONF2_INCLUDE_DIRS} )
			SET ( GNOMEVFS2_LIBRARIES ${GNOMEVFS2_LIBRARIES} ${GCONF2_LIBRARIES} )
		ENDIF ( GCONF2_FOUND )
	ENDIF ( NOT GCONF2_FOUND )
        IF ( NOT GLIB2_FOUND )
                FIND_PACKAGE( GLIB2 REQUIRED)

                IF ( GTHREAD2_FOUND )
                        SET ( GNOMEVFS2_INCLUDE_DIRS ${GNOMEVFS2_INCLUDE_DIRS} ${GTHREAD2_INCLUDE_DIR} )
                        SET ( GNOMEVFS2_LIBRARIES ${GNOMEVFS2_LIBRARIES} ${GTHREAD2_LIBRARY} )
                ENDIF ( GTHREAD2_FOUND )
                IF ( GMODULE2_FOUND )
                        SET ( GNOMEVFS2_INCLUDE_DIRS ${GNOMEVFS2_INCLUDE_DIRS} ${GMODULE2_INCLUDE_DIR} )
                        SET ( GNOMEVFS2_LIBRARIES ${GNOMEVFS2_LIBRARIES} ${GMODULE2_LIBRARY} )
                ENDIF ( GMODULE2_FOUND )
                IF ( GOBJECT2_FOUND )
                        SET ( GNOMEVFS2_INCLUDE_DIRS ${GNOMEVFS2_INCLUDE_DIRS} ${GOBJECT2_INCLUDE_DIR} )
                        SET ( GNOMEVFS2_LIBRARIES ${GNOMEVFS2_LIBRARIES} ${GOBJECT2_LIBRARY} )
                ENDIF ( GOBJECT2_FOUND )
                IF ( GLIB2_FOUND )
                        SET ( GNOMEVFS2_INCLUDE_DIRS ${GNOMEVFS2_INCLUDE_DIRS} ${GLIB2_INCLUDE_DIR} ${GLIBCONFIG_INCLUDE_DIR} )
                        SET ( GNOMEVFS2_LIBRARIES ${GNOMEVFS2_LIBRARIES} ${GLIB2_LIBRARY} )
                ENDIF ( GLIB2_FOUND )
        ENDIF ( NOT GLIB2_FOUND )


	# Report results
	IF ( GNOMEVFS2_LIBRARIES AND GNOMEVFS2_INCLUDE_DIRS AND _gnomevfs2_FOUND )	
		SET( GNOMEVFS2_FOUND 1 )
		IF ( NOT GnomeVfs2_FIND_QUIETLY )
			MESSAGE( STATUS "Found gnomevfs2: ${GNOMEVFS2_LIBRARIES} ${GNOMEVFS2_INCLUDE_DIRS}" )
		ENDIF ( NOT GnomeVfs2_FIND_QUIETLY )
	ELSE ( GNOMEVFS2_LIBRARIES AND GNOMEVFS2_INCLUDE_DIRS AND _gnomevfs2_FOUND )	
		IF ( GnomeVfs2_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find gnomevfs2" )
		ELSE ( GnomeVfs2_FIND_REQUIRED )
			IF ( NOT GnomeVfs2_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find gnomevfs2" )	
			ENDIF ( NOT GnomeVfs2_FIND_QUIETLY )
		ENDIF ( GnomeVfs2_FIND_REQUIRED )
	ENDIF ( GNOMEVFS2_LIBRARIES AND GNOMEVFS2_INCLUDE_DIRS AND _gnomevfs2_FOUND )	

ENDIF ( NOT GNOMEVFS2_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( GNOMEVFS2_LIBRARIES GNOMEVFS2_INCLUDE_DIRS )

