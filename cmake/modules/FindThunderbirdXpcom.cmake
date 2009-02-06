# ======================================================
# This file is part of the mozilla-sync plugin for OpenSync
# See http://www.KaarPoSoft.dk/bluezync
# $Id: FindThunderbirdXpcom.cmake 4886 2008-12-31 18:03:43Z bricks $
# ======================================================

# ---------- First we look for thunderbird
PKG_SEARCH_MODULE(THUNDERBIRDXPCOM REQUIRED thunderbird-xpcom icedove-xpcom )

# ---------- If we found thunderbird all is fine, set the required directories
IF( THUNDERBIRDXPCOM_FOUND )

	MESSAGE( STATUS "THUNDERBIRDXPCOM_INCLUDE_DIRS ${THUNDERBIRDXPCOM_INCLUDE_DIRS}" )

	MESSAGE( STATUS "-- Found thunderbird-xpcom" )
	#If we found the thunderbird package, look for one of the includes, just to be sure
	FIND_PATH(_LIBTBXPCOM_INCLUDE_DIR mozilla-config.h
		PATHS ${THUNDERBIRDXPCOM_INCLUDE_DIRS} )
	IF( NOT _LIBTBXPCOM_INCLUDE_DIR )
		MESSAGE( FATAL_ERROR "Found thunderbird-xpcom, but not mozilla-config.h" )
	ENDIF ( NOT _LIBTBXPCOM_INCLUDE_DIR )

	SET( XPCOM_INCLUDE_DIRS 
		${_LIBTBXPCOM_INCLUDE_DIR}
		${_LIBTBXPCOM_INCLUDE_DIR}/xpcom
		${_LIBTBXPCOM_INCLUDE_DIR}/nspr
		${_LIBTBXPCOM_INCLUDE_DIR}/necko
		${_LIBTBXPCOM_INCLUDE_DIR}/rdf
		${_LIBTBXPCOM_INCLUDE_DIR}/string
		${_LIBTBXPCOM_INCLUDE_DIR}/addrbook
		${_LIBTBXPCOM_INCLUDE_DIR}/js
		${_LIBTBXPCOM_INCLUDE_DIR}/xpcom_obsolete
		${_LIBTBXPCOM_INCLUDE_DIR}/xulapp
		${_LIBTBXPCOM_INCLUDE_DIR}/extensions
		${THUNDERBIRDXPCOM_INCLUDE_DIRS}
	)
		# xpcom_obsolete is needed because nsIABDirectory pulls in nsFileSpec.h
		# However, in thunderbird-addressbook.cpp we define _FILESPEC_H_
		# so we avoid any dependencies on obsolete
		# Hope mozilla gets this fixed ASAP.

	SET( _LIBDIRS ${THUNDERBIRDXPCOM_LIBRARY_DIRS} )

# ---------- If we did *NOT* find thunderbird, we must look for xulrunner and nspr (for openSUSE)
ELSE( THUNDERBIRDXPCOM_FOUND )

	# If we did not find thunderbird package, let's try xulrunner.
	# This is needed on OpenSUSE, where there is no thunderbird-devel package
	PKGCONFIG( xulrunner-xpcom
		_LIBXULRUNNERIncDir _LIBXULRUNNERLinkDir _LIBXULRUNNERLinkFlags _LIBXULRUNNERCflags )
	IF( NOT _LIBXULRUNNERIncDir )
		MESSAGE( FATAL_ERROR "Did not find thunderbird-xpcom, nor xulrunner-xpcom" )
	ENDIF( NOT _LIBXULRUNNERIncDir )

	FIND_PATH( _LIBXULRUNNER_INCLUDE_DIR nsXPCOM.h
		PATHS ${_LIBXULRUNNERIncDir} )
	IF( NOT _LIBXULRUNNER_INCLUDE_DIR )
		MESSAGE( FATAL_ERROR "Found xulrunner-xpcom, but not nsXPCOM.h" )
	ENDIF( NOT _LIBXULRUNNER_INCLUDE_DIR )

	# xulrunner-xpcom also needs nspr
	PKGCONFIG( nspr
		_LIBSNPRIncDir _LIBSNPRLinkDir _LIBSNPRLinkFlags _LIBSNPRCflags )
	IF( NOT _LIBSNPRIncDir )
		MESSAGE( FATAL_ERROR "Found xulrunner-xpcom, but not nspr" )
	ENDIF( NOT _LIBSNPRIncDir )

	FIND_PATH( _LIBSNPR_INCLUDE_DIR prtypes.h
		PATHS ${_LIBSNPRIncDir} )
	IF( NOT _LIBSNPR_INCLUDE_DIR )
		MESSAGE( FATAL_ERROR "Found nspr, but not prtypes.h" )
	ENDIF( NOT _LIBSNPR_INCLUDE_DIR )

	FIND_PATH( _TB_AB_INCLUDE_DIR nsIAbDirectory.h
		PATHS "/usr/src/debug/mozilla/dist/include/addrbook" )
	IF( NOT _TB_AB_INCLUDE_DIR )
		MESSAGE( FATAL_ERROR "Found xulrunner-xpcom and nspr, but not the thunderbird headers" )
	ENDIF( NOT _TB_AB_INCLUDE_DIR )

	SET( XPCOM_INCLUDE_DIRS 
		${_LIBXULRUNNER_INCLUDE_DIR}
		${_LIBXULRUNNER_INCLUDE_DIR}/xpcom
		${_LIBSNPR_INCLUDE_DIR}
		${_LIBXULRUNNER_INCLUDE_DIR}/rdf
		${_LIBXULRUNNER_INCLUDE_DIR}/string
		${_TB_AB_INCLUDE_DIR}
		${_LIBXULRUNNER_INCLUDE_DIR}/xpcom_obsolete
	)

	SET( _LIBDIRS ${THUNDERBIRDXPCOM_LIBRARY_DIRS} )

ENDIF( THUNDERBIRDXPCOM_FOUND )

#SET( EXTRA_INC_PATHS "/usr/src/debug/mozilla/dist/include/xpcom" PATH )

MESSAGE( STATUS "XPCOM_INCLUDE_DIRS ${XPCOM_INCLUDE_DIRS}" )

FIND_PATH(THUNDERBIRD_EXTENSION_DIR extensions
	PATHS ${_LIBDIRS} )

MESSAGE( STATUS "THUNDERBIRD_EXTENSION_DIR ${THUNDERBIRD_EXTENSION_DIR}" )

# ---------- Find the xpcom library, and make sure it is not under xulrunner
FIND_LIBRARY( LIBTBXPCOM_XPCOM
	NAMES xpcom
	PATHS ${_LIBDIRS} ENV LD_LIBRARY_PATH )
IF( NOT LIBTBXPCOM_XPCOM )
	MESSAGE( FATAL_ERROR "Could not find xpcom library" )
ENDIF( NOT LIBTBXPCOM_XPCOM )

STRING(REGEX MATCH ".*xulrunner.*" _XULRUNNER ${LIBTBXPCOM_XPCOM})
IF( _XULRUNNER )
	MESSAGE( FATAL_ERROR
	"Found xpcom library under xulrunner; should have been under thunderbird. Check LD_LIBRARY_PATH" )
ENDIF( _XULRUNNER )


# ---------- GRE_DIR needed just to put it into the test scripts
GET_FILENAME_COMPONENT(GRE_DIR ${LIBTBXPCOM_XPCOM} PATH)
MESSAGE( STATUS "GRE_DIR ${GRE_DIR}" )


# ---------- Ensure we found NSPR library
FIND_LIBRARY( LIBTBXPCOM_NSPR4
	NAMES nspr4
	PATHS ${_LIBDIRS} ENV LD_LIBRARY_PATH )
IF( NOT LIBTBXPCOM_NSPR4 )
	MESSAGE( FATAL_ERROR "Could not find nspr library" )
ENDIF( NOT LIBTBXPCOM_NSPR4 )



# ---------- Find sunbird include directory

PKG_SEARCH_MODULE( SUNBIRD REQUIRED sunbird-xpcom iceowl-xpcom  )

IF( SUNBIRD_FOUND )
	MESSAGE( "-- Found sunbird" )
	MESSAGE( "SUNBIRD_INCLUDE_DIRS ${SUNBIRD_INCLUDE_DIRS}" )

	# ---------- We just need the first directory, which should be the main directory
	# The rest will point to xpcom and friends; and we do not want that.
	# But, let's also handle the special case of only one direcory reported, just in case

	STRING(REGEX MATCH ";" _SEVERAL_INCLUDE_DIRS "${SUNBIRD_INCLUDE_DIRS}" )
	IF( _SEVERAL_INCLUDE_DIRS )
		MESSAGE( "SEVERAL")
		STRING(REGEX REPLACE "([^;]*);.*" "\\1" SUNBIRD_MAIN_INCLUDE_DIR "${SUNBIRD_INCLUDE_DIRS}" )
	ELSE( _SEVERAL_INCLUDE_DIRS )
		SET( SUNBIRD_MAIN_INCLUDE_DIR "${SUNBIRD_INCLUDE_DIRS}" )
	ENDIF( _SEVERAL_INCLUDE_DIRS )
	#MESSAGE( "SUNBIRD_MAIN_INCLUDE_DIR ${SUNBIRD_MAIN_INCLUDE_DIR}" )

	FIND_FILE(_SUNBIRD_CALENDAR calbase/calICalendar.h ${SUNBIRD_MAIN_INCLUDE_DIR} )
	IF( NOT _SUNBIRD_CALENDAR )
		MESSAGE( FATAL_ERROR "Found sunbird, but not calICalendar.h" )
	ENDIF ( NOT _SUNBIRD_CALENDAR )


	SET ( XPCOM_INCLUDE_DIRS "${XPCOM_INCLUDE_DIRS};${SUNBIRD_MAIN_INCLUDE_DIR}" )
	MESSAGE( "XPCOM_INCLUDE_DIRS ${XPCOM_INCLUDE_DIRS}" )

ELSE( SUNBIRD_FOUND )
	MESSAGE( FATAL_ERROR "Could not find sunbird library" )
ENDIF( SUNBIRD_FOUND )

MESSAGE ( STATUS "SUNBIRD_VERSION [${SUNBIRD_VERSION}]" )

MARK_AS_ADVANCED( THUNDERBIRDXPCOM_INCLUDE_DIRS THUNDERBIRDXPCOM_LIBRARIES )
