# ======================================================
# This file is part of the mozilla-sync plugin for OpenSync
# See http://www.KaarPoSoft.dk/bluezync
# $Id: FindThunderbirdXpcom.cmake 5886 2009-10-22 15:20:12Z henrik $
# ======================================================

# The purpose of this CMake file is to find Thunderbird and Sunbird files and versions.
# It should work with Icedove and Iceowl as well

# First we look for a Thunderbird package
PKG_SEARCH_MODULE ( THUNDERBIRD_XPCOM thunderbird-xpcom icedove-xpcom )

IF ( THUNDERBIRD_XPCOM_FOUND )

	# If we found the Thunderbird package, look for one of the includes, just to be sure
	FIND_PATH ( THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR mozilla-config.h
		PATHS ${THUNDERBIRD_XPCOM_INCLUDE_DIRS} )
	IF( NOT THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR )
		MESSAGE ( FATAL_ERROR "*** *** Found Thunderbird package, but not mozilla-config.h" )
	ENDIF ( NOT THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR )
	# We also need NSPR, so let's make sure it is there
	FIND_PATH ( NSPR_MAIN_INCLUDE_DIR nspr.h
		PATHS ${THUNDERBIRD_XPCOM_INCLUDE_DIRS} )
	IF( NOT NSPR_MAIN_INCLUDE_DIR )
		MESSAGE ( FATAL_ERROR "*** *** Found Thunderbird package, but not nspr.h" )
	ENDIF ( NOT NSPR_MAIN_INCLUDE_DIR )

ELSE( THUNDERBIRD_XPCOM_FOUND )

	# We did not find a Thunderbird package, so let us look for the files manually 
	MESSAGE ( STATUS "  did not find thunderbird package; now looking for thunderbird files" )
	FIND_PATH (THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR mozilla-config.h
		PATH_SUFFIXES thunderbird icedove
		PATHS
		/opt/local/include/
		/sw/include/
		/usr/local/include/
		/usr/include/
		/usr/lib64/mozilla-thunderbird/include/
	)
	IF ( NOT THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR )
		MESSAGE ( FATAL_ERROR "*** *** Did not find Thunderbird include directory with mozilla-config.h" )
	ENDIF ( NOT THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR )
	FIND_PATH ( NSPR_MAIN_INCLUDE_DIR nspr.h
		PATH_SUFFIXES nspr nspr4 thunderbird/nspr
		PATHS
		/opt/local/include/
		/sw/include/
		/usr/local/include/
		/usr/include/
	)
	IF( NOT NSPR_MAIN_INCLUDE_DIR )
		MESSAGE ( FATAL_ERROR "*** *** Found Thunderbird include directory, but not nspr.h" )
	ENDIF ( NOT NSPR_MAIN_INCLUDE_DIR )
	# Usually all the libraries are in one directory, so let us try to find it
	FIND_LIBRARY ( _xpcom_lib NAMES xpcom libxpcom
		PATH_SUFFIXES thunderbird icedove
		PATHS
		/opt/local/lib
		/sw/lib
		/usr/lib
		/usr/local/lib
		/usr/lib64
		/usr/local/lib64
		/opt/lib64
	)

	IF ( WIN32 AND NOT _xpcom_lib )
		GET_FILENAME_COMPONENT ( _tbdir "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\thunderbird.exe]" PATH CACHE)
	FIND_LIBRARY ( _xpcom_lib NAMES xpcom libxpcom
		PATHS "${_tbdir}"
	)
	ENDIF ( WIN32 AND NOT _xpcom_lib )

	IF ( NOT _xpcom_lib )
		MESSAGE ( FATAL_ERROR "*** *** Found Thunderbird, but not the xpcom library" )
	ENDIF ( NOT _xpcom_lib )
	# We got the actual library, but we need the directory
	GET_FILENAME_COMPONENT ( THUNDERBIRD_XPCOM_LIBRARY_DIRS "${_xpcom_lib}" PATH )
	# Usually the only library we need is the xpcom
	SET ( THUNDERBIRD_XPCOM_LIBRARIES "xpcom" )

	IF ( WIN32 )
		SET ( THUNDERBIRD_XPCOM_LIBRARIES "xpcom;xpcom_compat;xpcom_core;xpistub" )
	ENDIF ( WIN32 )

	# For Thunderbird 3.0 we need to link the glue library
	EXEC_PROGRAM ( thunderbird ARGS "--version"
		OUTPUT_VARIABLE THUNDERBIRD_XPCOM_VERSION
		RETURN_VALUE _THUNDERBIRD_XPCOM_VERSION_RET )

	IF ( _THUNDERBIRD_XPCOM_VERSION_RET )
		EXEC_PROGRAM ( icedove ARGS "--version"
			OUTPUT_VARIABLE THUNDERBIRD_XPCOM_VERSION
			RETURN_VALUE _THUNDERBIRD_XPCOM_VERSION_RET )
	ENDIF ( _THUNDERBIRD_XPCOM_VERSION_RET )

	IF ( WIN32 AND _THUNDERBIRD_XPCOM_VERSION_RET )
		GET_FILENAME_COMPONENT ( _tb_exe "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\thunderbird.exe]" ABSOLUTE CACHE)
		EXEC_PROGRAM ( "${_tb_exe}" ARGS "--version"
			OUTPUT_VARIABLE THUNDERBIRD_XPCOM_VERSION
			RETURN_VALUE _THUNDERBIRD_XPCOM_VERSION_RET )
	ENDIF ( WIN32 AND  _THUNDERBIRD_XPCOM_VERSION_RET )

	IF (_THUNDERBIRD_XPCOM_VERSION_RET )
			MESSAGE ( FATAL_ERROR "*** *** Unable execute Thunderbird/Icedove to get its version" )
	ENDIF ( _THUNDERBIRD_XPCOM_VERSION_RET )

	STRING ( REGEX MATCH ".* ([0-9]\\.[0-9]).*" _THUNDERBIRD_XPCOM_VERSION_OK "${THUNDERBIRD_XPCOM_VERSION}" )
	IF ( _THUNDERBIRD_XPCOM_VERSION_OK )
		STRING (REGEX REPLACE ".* ([0-9]\\.[0-9]).*" "\\1" THUNDERBIRD_XPCOM_VERSION "${THUNDERBIRD_XPCOM_VERSION}" )
	ENDIF ( _THUNDERBIRD_XPCOM_VERSION_OK )

ENDIF( THUNDERBIRD_XPCOM_FOUND )

STRING ( REGEX MATCH ".*([0-9]\\.[0-9]).*" _THUNDERBIRD_XPCOM_VERSION_OK "${THUNDERBIRD_XPCOM_VERSION}" )
IF ( _THUNDERBIRD_XPCOM_VERSION_OK )
	# Thunderbird main version
	STRING (REGEX REPLACE "^([0-9]+)\\..*$" "\\1" THUNDERBIRD_VERSION_MAIN "${THUNDERBIRD_XPCOM_VERSION}" )
ELSE ( _THUNDERBIRD_XPCOM_VERSION_OK )
	MESSAGE ( STATUS "Unable to interpret Thunderbird version [${THUNDERBIRD_XPCOM_VERSION}]; continuing anyway" )
ENDIF ( _THUNDERBIRD_XPCOM_VERSION_OK )

# Thunderbird 3
IF ( THUNDERBIRD_VERSION_MAIN STREQUAL "3" )
	SET ( THUNDERBIRD_XPCOM_LIBRARIES "xpcomglue_s;xpcom" )
	IF ( WIN32 )
		SET ( THUNDERBIRD_XPCOM_LIBRARIES "xpcomglue_s;xpcom;nspr4" )
	ENDIF ( WIN32 )
ENDIF ( THUNDERBIRD_VERSION_MAIN STREQUAL "3" )

# So, by now we should have the following variables set:
MESSAGE ( STATUS "    THUNDERBIRD_XPCOM_VERSION ${THUNDERBIRD_XPCOM_VERSION}" )
MESSAGE ( STATUS "    THUNDERBIRD_VERSION_MAIN ${THUNDERBIRD_VERSION_MAIN}" )
MESSAGE ( STATUS "    THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR ${THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR}" )
MESSAGE ( STATUS "    NSPR_MAIN_INCLUDE_DIR ${NSPR_MAIN_INCLUDE_DIR}" )
MESSAGE ( STATUS "    THUNDERBIRD_XPCOM_LIBRARY_DIRS ${THUNDERBIRD_XPCOM_LIBRARY_DIRS}" )
MESSAGE ( STATUS "    THUNDERBIRD_XPCOM_LIBRARIES ${THUNDERBIRD_XPCOM_LIBRARIES}" )

# Those are the include directories we actually need
SET ( XPCOM_INCLUDE_DIRS 
	${NSPR_MAIN_INCLUDE_DIR}
	${THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR}
	${THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR}/addrbook
	${THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR}/extensions
	${THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR}/rdf
	${THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR}/string
	${THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR}/xpcom_obsolete
	${THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR}/xpcom
	${THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR}/xulapp
)


# ----------------------------------------

# Now look for a Subird package
PKG_SEARCH_MODULE ( SUNBIRD sunbird-xpcom iceowl-xpcom  )

IF ( SUNBIRD_FOUND )

	# If we found the Thunderbird package, let us try to find the main include dir
	MESSAGE ( "  SUNBIRD_INCLUDE_DIRS ${SUNBIRD_INCLUDE_DIRS}" )
	# ---------- We just need the first directory, which should be the main directory
	# The rest will point to xpcom and friends; and we do not want that.
	# But, let's also handle the special case of only one direcory reported, just in case
	STRING ( REGEX MATCH ";" _SEVERAL_INCLUDE_DIRS "${SUNBIRD_INCLUDE_DIRS}" )
	IF ( _SEVERAL_INCLUDE_DIRS )
		MESSAGE ( "SEVERAL")
		STRING ( REGEX REPLACE "([^;]*);.*" "\\1" SUNBIRD_MAIN_INCLUDE_DIR "${SUNBIRD_INCLUDE_DIRS}" )
	ELSE ( _SEVERAL_INCLUDE_DIRS )
		SET ( SUNBIRD_MAIN_INCLUDE_DIR "${SUNBIRD_INCLUDE_DIRS}" )
	ENDIF ( _SEVERAL_INCLUDE_DIRS )

ELSE( SUNBIRD_FOUND )

	# We did not find a Sunbird package, so let us look for the files manually 
	MESSAGE ( STATUS "  did not find sunbird package; now looking for sunbird files" )
	FIND_PATH ( SUNBIRD_MAIN_INCLUDE_DIR calbase/calIICSService.h
		PATH_SUFFIXES sunbird iceowl
		PATHS
		/opt/local/include/
		/sw/include/
		/usr/local/include/
		/usr/include/
	)
	IF ( NOT SUNBIRD_MAIN_INCLUDE_DIR )
		MESSAGE ( FATAL_ERROR "*** *** Did not find Sunbird include directory with mozilla-config.h" )
	ENDIF ( NOT SUNBIRD_MAIN_INCLUDE_DIR )

	# We need the Sunbird version number
	EXEC_PROGRAM ( sunbird ARGS "--version"
		OUTPUT_VARIABLE SUNBIRD_VERSION
		RETURN_VALUE _SUNBIRD_VERSION_RET )
	IF ( _SUNBIRD_VERSION_RET )

	EXEC_PROGRAM ( iceowl ARGS "--version"
		OUTPUT_VARIABLE SUNBIRD_VERSION
		RETURN_VALUE _SUNBIRD_VERSION_RET )
	ENDIF ( _SUNBIRD_VERSION_RET )

	IF ( WIN32 AND _SUNBIRD_VERSION_RET )
		GET_FILENAME_COMPONENT ( _sb_exe "[HKEY_LOCAL_MACHINE\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\sunbird.exe]" ABSOLUTE CACHE)
		EXEC_PROGRAM ( "${_sb_exe}" ARGS "--version"
			OUTPUT_VARIABLE SUNBIRD_VERSION
			RETURN_VALUE _SUNBIRD_VERSION_RET )
	ENDIF ( WIN32 AND _SUNBIRD_VERSION_RET )

	IF ( _SUNBIRD_VERSION_RET )
		MESSAGE ( FATAL_ERROR "*** *** Unable execute sunbird/iceowl to get its version" )
	ENDIF ( _SUNBIRD_VERSION_RET )

	STRING ( REGEX MATCH ".* ([0-9]\\.[0-9]).*" _SUNBIRD_VERSION_OK "${SUNBIRD_VERSION}" )
	IF ( _SUNBIRD_VERSION_OK )
		STRING (REGEX REPLACE ".* ([0-9]\\.[0-9]).*" "\\1" SUNBIRD_VERSION "${SUNBIRD_VERSION}" )
	ENDIF ( _SUNBIRD_VERSION_OK )

ENDIF ( SUNBIRD_FOUND )

STRING ( REGEX MATCH ".*([0-9]\\.[0-9]).*" _SUNBIRD_VERSION_OK "${SUNBIRD_VERSION}" )
IF ( _SUNBIRD_VERSION_OK )
	# Sunbird main version
	STRING (REGEX REPLACE "^([0-9]+)\\..*$" "\\1" SUNBIRD_VERSION_MAIN "${SUNBIRD_VERSION}" )
ELSE ( _SUNBIRD_VERSION_OK )
	MESSAGE ( FATAL_ERROR "*** ***Unable to interpret Sunbird version [${_SUNBIRD_VERSION}]" )
ENDIF ( _SUNBIRD_VERSION_OK )



# ----------------------------------------

# So, by now we should have the following variables set:
MESSAGE ( STATUS "     SUNBIRD_MAIN_INCLUDE_DIR ${SUNBIRD_MAIN_INCLUDE_DIR}" )
MESSAGE ( STATUS "     SUNBIRD_VERSION ${SUNBIRD_VERSION}" )

# Set the final output variables
SET ( XPCOM_INCLUDE_DIRS "${XPCOM_INCLUDE_DIRS};${SUNBIRD_MAIN_INCLUDE_DIR}" )
SET ( XPCOM_LIBRARY_DIRS "${THUNDERBIRD_XPCOM_LIBRARY_DIRS}" )
SET ( XPCOM_LIBRARIES "${THUNDERBIRD_XPCOM_LIBRARIES}" )

# And here is what we found out:
MESSAGE ( STATUS "Found xpcom (thunderbird and sunbird):" )
MESSAGE ( STATUS "  THUNDERBIRD_XPCOM_VERSION=[${THUNDERBIRD_XPCOM_VERSION}]" )
MESSAGE ( STATUS "  SUNBIRD_VERSION=[${SUNBIRD_VERSION}]" )
MESSAGE ( STATUS "  THUNDERBIRD_VERSION_MAIN=[${THUNDERBIRD_VERSION_MAIN}]" )
MESSAGE ( STATUS "  SUNBIRD_VERSION_MAIN=[${SUNBIRD_VERSION_MAIN}]" )
MESSAGE ( STATUS "  XPCOM_INCLUDE_DIRS ${XPCOM_INCLUDE_DIRS}" )
MESSAGE ( STATUS "  XPCOM_LIBRARY_DIRS ${XPCOM_LIBRARY_DIRS}" )
MESSAGE ( STATUS "  XPCOM_LIBRARIES ${XPCOM_LIBRARIES}" )
MESSAGE ( STATUS "  SUNBIRD_VERSION ${SUNBIRD_VERSION}" )
