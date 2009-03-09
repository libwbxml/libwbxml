# ======================================================
# This file is part of the mozilla-sync plugin for OpenSync
# See http://www.KaarPoSoft.dk/bluezync
# $Id: FindThunderbirdXpcom.cmake 5061 2009-01-09 10:47:55Z henrik $
# ======================================================

# The purpose of this CMake file is to find Thunderbird and Sunbird files.
# At the end, we whould have the following variables set:
#	XPCOM_INCLUDE_DIRS
#	XPCOM_LIBRARY_DIRS
#	XPCOM_LIBRARIES
#	SUNBIRD_VERSION

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
	)
	IF ( NOT THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR )
		MESSAGE ( FATAL_ERROR "*** *** Did not find Thunderbird include directory with mozilla-config.h" )
	ENDIF ( NOT THUNDERBIRD_XPCOM_MAIN_INCLUDE_DIR )
	FIND_PATH ( NSPR_MAIN_INCLUDE_DIR nspr.h
		PATH_SUFFIXES nspr nspr4
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
	IF ( NOT _xpcom_lib )
		MESSAGE ( FATAL_ERROR "*** *** Found Thunderbird, but not the xpcom library" )
	ENDIF ( NOT _xpcom_lib )
	# We got the actual library, but we need the directory
	GET_FILENAME_COMPONENT ( THUNDERBIRD_XPCOM_LIBRARY_DIRS "${_xpcom_lib}" PATH )
	# Usually the only library we need is the xpcom
	SET ( THUNDERBIRD_XPCOM_LIBRARIES "xpcom" )

ENDIF( THUNDERBIRD_XPCOM_FOUND )

# So, by now we should have the following variables set:
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
		OUTPUT_VARIABLE _SUNBIRD_VERSION
		RETURN_VALUE _SUNBIRD_VERSION_RET )
	IF ( _SUNBIRD_VERSION_RET )

	EXEC_PROGRAM ( iceowl ARGS "--version"
		OUTPUT_VARIABLE _SUNBIRD_VERSION
		RETURN_VALUE _ICEOWL_VERSION_RET )
		IF ( _ICEOWL_VERSION_RET )
			MESSAGE ( FATAL_ERROR "*** *** Unable execute sunbird/iceowl to get its version" )
		ENDIF ( _ICEOWL_VERSION_RET )
	ENDIF ( _SUNBIRD_VERSION_RET )

	STRING ( REGEX MATCH ".*([0-9]\\.[0-9]).*" _SUNBIRD_VERSION_OK "${_SUNBIRD_VERSION}" )
	IF ( _SUNBIRD_VERSION_OK )
		STRING ( REGEX REPLACE ".*([0-9]\\.[0-9]).*" "\\1" SUNBIRD_VERSION "${_SUNBIRD_VERSION}" )
	ELSE ( _SUNBIRD_VERSION_OK )
		MESSAGE ( STATUS "sunbird --version returned ${_SUNBIRD_VERSION}" )
		MESSAGE ( FATAL_ERROR "*** *** Unable to interpret sunbird --version" )
	ENDIF ( _SUNBIRD_VERSION_OK )

ENDIF ( SUNBIRD_FOUND )

# So, by now we should have the following variables set:
MESSAGE ( STATUS "     SUNBIRD_MAIN_INCLUDE_DIR ${SUNBIRD_MAIN_INCLUDE_DIR}" )
MESSAGE ( STATUS "     SUNBIRD_VERSION ${SUNBIRD_VERSION}" )

# Set the final output variables
SET ( XPCOM_INCLUDE_DIRS "${XPCOM_INCLUDE_DIRS};${SUNBIRD_MAIN_INCLUDE_DIR}" )
SET ( XPCOM_LIBRARY_DIRS "${THUNDERBIRD_XPCOM_LIBRARY_DIRS}" )
SET ( XPCOM_LIBRARIES "${THUNDERBIRD_XPCOM_LIBRARIES}" )

# And here is what we found out:
MESSAGE ( STATUS "Found xpcom (thunderbird and sunbird):" )
MESSAGE ( STATUS "  XPCOM_INCLUDE_DIRS ${XPCOM_INCLUDE_DIRS}" )
MESSAGE ( STATUS "  XPCOM_LIBRARY_DIRS ${XPCOM_LIBRARY_DIRS}" )
MESSAGE ( STATUS "  XPCOM_LIBRARIES ${XPCOM_LIBRARIES}" )
MESSAGE ( STATUS "  SUNBIRD_VERSION ${SUNBIRD_VERSION}" )
