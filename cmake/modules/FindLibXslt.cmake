# - Try to find LibXslt
# Once done this will define
#
#  LIBXSLT_FOUND - system has LibXslt
#  LIBXSLT_INCLUDE_DIRS - the LibXslt include directory
#  LIBXSLT_LIBRARIES - Link these to LibXslt
#  LIBXSLT_DEFINITIONS - Compiler switches required for using LibXslt
#
#  Copyright (c) 2006, Alexander Neundorf, <neundorf@kde.org>
#  Copyright (c) 2008 Bjoern Ricks <bjoern.ricks@googlemail.com>
#
#  Redistribution and use is allowed according to the terms of the New
#  BSD license.
#  For details see the accompanying COPYING-CMAKE-SCRIPTS file.
#	

INCLUDE( FindPkgConfig )

IF ( LibXslt_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "REQUIRED" )
ELSE( LibXslt_FIND_REQUIRED )
	SET( _pkgconfig_REQUIRED "" )	
ENDIF ( LibXslt_FIND_REQUIRED )

IF ( LIBXSLT_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBXSLT ${_pkgconfig_REQUIRED} libxslt>=${LIBXSLT_MIN_VERSION} )
ELSE ( LIBXSLT_MIN_VERSION )
	PKG_SEARCH_MODULE( LIBXSLT ${_pkgconfig_REQUIRED} libxslt )
ENDIF ( LIBXSLT_MIN_VERSION )


IF( NOT LIBXSLT_FOUND AND NOT PKG_CONFIG_FOUND )
	FIND_PATH( LIBXSLT_INCLUDE_DIRS libxslt/xslt.h )
	FIND_LIBRARY( LIBXSLT_LIBRARIES xslt libxslt )

	# Report results
	IF ( LIBXSLT_LIBRARIES AND LIBXSLT_INCLUDE_DIRS )	
		SET( LIBXSLT_FOUND 1 )
		IF ( NOT LibXslt_FIND_QUIETLY )
			MESSAGE( STATUS "Found LibXslt: ${LIBXSLT_LIBRARIES}" )
		ENDIF ( NOT LibXslt_FIND_QUIETLY )
	ELSE ( LIBXSLT_LIBRARIES AND LIBXSLT_INCLUDE_DIRS )	
		IF ( LibXslt_FIND_REQUIRED )
			MESSAGE( SEND_ERROR "Could NOT find LibXslt" )
		ELSE ( LibXslt_FIND_REQUIRED )
			IF ( NOT LibXslt_FIND_QUIETLY )
				MESSAGE( STATUS "Could NOT find LibXslt" )	
			ENDIF ( NOT LibXslt_FIND_QUIETLY )
		ENDIF ( LibXslt_FIND_REQUIRED )
	ENDIF ( LIBXSLT_LIBRARIES AND LIBXSLT_INCLUDE_DIRS )	
ENDIF( NOT LIBXSLT_FOUND AND NOT PKG_CONFIG_FOUND )

# Hide advanced variables from CMake GUIs
MARK_AS_ADVANCED( LIBXSLT_LIBRARIES LIBXSLT_INCLUDE_DIRS )
