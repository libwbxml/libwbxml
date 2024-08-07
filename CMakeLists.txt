cmake_minimum_required(VERSION 3.5)
PROJECT( libwbxml C )

SET( LIBWBXML_VERSION_MAJOR "0" )
SET( LIBWBXML_VERSION_MINOR "11" )
SET( LIBWBXML_VERSION_PATCH "10" )
IF( LIBWBXML_VERSION_BETA )
    IF( LIBWBXML_VERSION_BETA VERSION_GREATER 90 )
        MATH( EXPR LIBWBXML_VERSION_MINOR "${LIBWBXML_VERSION_MINOR} - 1" )
        SET( LIBWBXML_VERSION_PATCH ${LIBWBXML_VERSION_BETA})
    ELSE( LIBWBXML_VERSION_BETA VERSION_GREATER 90 )
        SET( LIBWBXML_VERSION_PATCH "beta${LIBWBXML_VERSION_BETA}" )
    ENDIF( LIBWBXML_VERSION_BETA VERSION_GREATER 90 )
ENDIF( LIBWBXML_VERSION_BETA )
SET( LIBWBXML_VERSION "${LIBWBXML_VERSION_MAJOR}.${LIBWBXML_VERSION_MINOR}.${LIBWBXML_VERSION_PATCH}" )

# The most recent interface number that this library implements.
#UPDATE: If any interface have been added, removed or changed since
#UPDATE: the last update increment CURRENT.
SET( LIBWBXML_LIBVERSION_CURRENT 2 )

# The implementation number of the CURRENT interface.
# UPDATE: Increment only if the library code has changed at all, since
# UPDATE: last release.
# UPDATE: Set REVISION to 0 if any interface have been added, removed or
# UPDATE: changed since the last update.
SET( LIBWBXML_LIBVERSION_REVISION 1 )

# The difference between the newest and the oldest interfaces.
# UPDATE: If any interface have been added since the last public
# UPDATE: release, then increment.
# UPDATE: If any interface have been removed since the last release
# UPDATE: reset to 0.
SET( LIBWBXML_LIBVERSION_AGE 1 )

# The range of implemention CURRENT - AGE is the SOVERSION
MATH( EXPR LIBWBXML_LIBVERSION_SOVERSION "${LIBWBXML_LIBVERSION_CURRENT} - ${LIBWBXML_LIBVERSION_AGE}" )

SET( LIBWBXML_LIBVERSION_VERSION "${LIBWBXML_LIBVERSION_SOVERSION}.${LIBWBXML_LIBVERSION_AGE}.${LIBWBXML_LIBVERSION_REVISION}" )

# this hack protects the SO versioning of the library
# it makes the exposing of internal header files possible and safe
# usual library version: 2.6.1
# special library version: 20601.0.0
IF( WBXML_INSTALL_FULL_HEADERS )

    # calculate big major version
    MATH( EXPR LIBWBXML_LIBVERSION_SOVERSION "10000 * ${LIBWBXML_LIBVERSION_SOVERSION} + 100 * ${LIBWBXML_LIBVERSION_AGE} + ${LIBWBXML_LIBVERSION_REVISION}" )

    # build a x.0.0 version
    SET( LIBWBXML_LIBVERSION_VERSION "${LIBWBXML_LIBVERSION_SOVERSION}.0.0" )

ENDIF( WBXML_INSTALL_FULL_HEADERS )

# TODO: Move to external file/macro
SET( CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" )

SET( LIB_SUFFIX "" CACHE STRING "The library directory suffix. 32bit empty string, 64 for 64bit." )
SET( LIB_INSTALL_DIR  "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE INTERNAL "libary location" )
SET( LIBDATA_INSTALL_DIR  "${CMAKE_INSTALL_PREFIX}/lib${LIB_SUFFIX}" CACHE PATH "The library data directory" )
SET( BIN_INSTALL_DIR  "${CMAKE_INSTALL_PREFIX}/bin" CACHE INTERNAL "binary location" )
SET( SHARE_INSTALL_DIR  "${CMAKE_INSTALL_PREFIX}/share" CACHE INTERNAL "data location" )
SET( INCLUDE_INSTALL_DIR  "${CMAKE_INSTALL_PREFIX}/include" CACHE INTERNAL "headers location" )
SET( LIBEXEC_INSTALL_DIR "${CMAKE_INSTALL_PREFIX}/libexec" CACHE INTERNAL "libexec location" )

#MESSAGE(STATUS "CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}" )

SET( LIBWBXML_LIBRARIES_DIR "${LIB_INSTALL_DIR}" CACHE PATH "wbxml library location" )
SET( LIBWBXML_INCLUDE_DIR "${INCLUDE_INSTALL_DIR}/libwbxml-${LIBWBXML_LIBVERSION_SOVERSION}.${LIBWBXML_LIBVERSION_AGE}" CACHE PATH "libwbxml headers location" )
SET( LIBWBXML_BIN_DIR "${BIN_INSTALL_DIR}" CACHE PATH "wbxml binaries location" )
SET( LIBWBXML_DATA_DIR "${CMAKE_INSTALL_PREFIX}/share" CACHE PATH "wbxml data location" )
SET( LIBWBXML_EXEC_INSTALL_DIR "${BIN_INSTALL_DIR}" CACHE PATH "wbxml binary location" )

# find header files and type size
INCLUDE( CheckTypeSize )
INCLUDE( CheckIncludeFiles )
INCLUDE( Documentation )
INCLUDE( AddDocumentation )

CHECK_INCLUDE_FILES( limits.h HAVE_LIMITS_H )
CHECK_INCLUDE_FILES( ctype.h HAVE_CTYPE_H )
CHECK_INCLUDE_FILES( stdlib.h HAVE_STDLIB_H )
CHECK_INCLUDE_FILES( stdio.h HAVE_STDIO_H )
CHECK_INCLUDE_FILES( stdarg.h HAVE_STDARG_H )
CHECK_INCLUDE_FILES( assert.h HAVE_ASSERT_H )

# ensure out od source build
INCLUDE( MacroEnsureOutOfSourceBuild )
MACRO_ENSURE_OUT_OF_SOURCE_BUILD("${CMAKE_PROJECT_NAME} doesn't allow to build within the source directory. Please, create a seperate build directory and run 'cmake ${PROJECT_SOURCE_DIR} [options]'!")

# FIXME: popt is embedded into the source code
# popt is not used
# zlib is not used
# nsl is part of libc6

# Expat support
FIND_PACKAGE( Expat )
IF( NOT EXPAT_FOUND )
    # cmake introduced a bug in version 3.27
    FIND_PACKAGE( PkgConfig )
    IF(PKGCONFIG_FOUND)
        PKG_CHECK_MODULES( EXPAT expat )
    ENDIF(PKGCONFIG_FOUND)
ENDIF ( NOT EXPAT_FOUND )
IF( EXPAT_FOUND )
    SET( HAVE_EXPAT 1 )
ENDIF( EXPAT_FOUND )

# Testing support
FIND_PACKAGE( PkgConfig )
IF(PKGCONFIG_FOUND)
    PKG_CHECK_MODULES( CHECK check )
ENDIF(PKGCONFIG_FOUND)
IF(CHECK_FOUND)
	OPTION( ENABLE_UNIT_TEST "enable unit tests" ON )
	ENABLE_TESTING()
ENDIF(CHECK_FOUND)

# Character conversion support
FIND_PACKAGE( Iconv )
SET( WBXML_SUPPORT_ICONV OFF )
IF( ICONV_FOUND )
    SET( HAVE_ICONV 1 )
    SET( WBXML_SUPPORT_ICONV ON )
ENDIF( ICONV_FOUND )

# look for getopt implementation in unistd.h

INCLUDE(CheckFunctionExists)
INCLUDE(CheckIncludeFile)

CHECK_INCLUDE_FILE( "unistd.h" LIBWBXML_TOOLS_UNISTD_H )
IF( ${LIBWBXML_TOOLS_UNISTD_H} )
	SET( CMAKE_REQUIRED_INCLUDES ${LIBWBXML_TOOLS_UNISTD_H} )
	CHECK_FUNCTION_EXISTS( getopt LIBWBXML_POSIX_GETOPT )
ELSE( ${LIBWBXML_TOOLS_UNISTD_H} )
	SET( LIBWBXML_POSIX_GETOPT OFF )
ENDIF( ${LIBWBXML_TOOLS_UNISTD_H} )
IF( LIBWBXML_POSIX_GETOPT )
	OPTION( FOUND_POSIX_GETOPT "POSIX getopt" ON )
ELSE( LIBWBXML_POSIX_GETOPT )
	OPTION( FOUND_POSIX_GETOPT "POSIX getopt" OFF )
ENDIF( LIBWBXML_POSIX_GETOPT )

# look for the commands required for testing

FIND_PROGRAM( PERL_PROGRAM "perl" )
FIND_PROGRAM( DIFF_PROGRAM "diff" )

IF( PERL_PROGRAM )
	SET( ENABLE_PERL ON )
ELSE( PERL_PROGRAM )
	SET( ENABLE_PERL OFF )
ENDIF( PERL_PROGRAM )

IF( DIFF_PROGRAM )
	SET( ENABLE_DIFF ON )
ELSE( DIFF_PROGRAM )
	SET( ENABLE_DIFF OFF )
ENDIF( DIFF_PROGRAM )

OPTION( BUILD_SHARED_LIBS "Build wbxml as shared library" ON )
OPTION( BUILD_STATIC_LIBS "Build wbxml as static library" OFF )
OPTION( WBXML_LIB_VERBOSE "verbose mode" OFF )
OPTION( WBXML_ENCODER_USE_STRTBL "enable string tables" ON )
OPTION( WBXML_SUPPORT_WML "enable WML support" ON )
OPTION( WBXML_SUPPORT_WTA "enable WTA support" ON )
OPTION( WBXML_SUPPORT_SI "enable SI support" ON )
OPTION( WBXML_SUPPORT_SL "enable SL support" ON )
OPTION( WBXML_SUPPORT_CO "enable CO support" ON )
OPTION( WBXML_SUPPORT_PROV "enable PROV support" ON )
OPTION( WBXML_SUPPORT_EMN "enable EMN support" ON )
OPTION( WBXML_SUPPORT_DRMREL "enable DRMREL support" ON )
OPTION( WBXML_SUPPORT_OTA_SETTINGS "enable OTA_SETTINGS support" ON )
OPTION( WBXML_SUPPORT_SYNCML "enable SYNCML support" ON )
OPTION( WBXML_SUPPORT_WV "enable WV support" ON )
OPTION( WBXML_SUPPORT_AIRSYNC "enable AIRSYNC support" ON )
OPTION( WBXML_SUPPORT_CONML "enable Nokia ConML support" ON )
OPTION( WBXML_INSTALL_FULL_HEADERS "install internal headers" OFF )

SET( PACKAGE "libwbxml" )
SET( PACKAGE_BUGREPORT " " )
SET( PACKAGE_NAME "libwbxml" )
SET( PACKAGE_TARNAME "${PACKAGE_NAME}" )
SET( PACKAGE_STRING "${PACKAGE_NAME} ${LIBWBXML_VERSION}" )
SET( PACKAGE_VERSION "${LIBWBXML_VERSION}" )
SET( VERSION "${LIBWBXML_VERSION}" )

CONFIGURE_FILE( "src/wbxml_config.h.cmake" "${CMAKE_CURRENT_BINARY_DIR}/wbxml_config.h")
CONFIGURE_FILE( "src/wbxml_config_internals.h.cmake" "${CMAKE_CURRENT_BINARY_DIR}/wbxml_config_internals.h")
CONFIGURE_FILE( "libwbxml2.pc.cmake" "${CMAKE_CURRENT_BINARY_DIR}/libwbxml2.pc" @ONLY)

# add uninstall target
CONFIGURE_FILE(	"${CMAKE_SOURCE_DIR}/cmake/modules/cmake_uninstall.cmake.in" "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake" IMMEDIATE @ONLY)

ADD_CUSTOM_TARGET(uninstall "${CMAKE_COMMAND}" -P "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake")

ADD_SUBDIRECTORY( src )
ADD_SUBDIRECTORY( tools )
ADD_SUBDIRECTORY( cmake )

MARK_AS_ADVANCED( CLEAR BUILD_DOCUMENTATION )
#IF ( BUILD_DOCUMENTATION )
#	IF ( DOXYGEN_DOT_EXECUTABLE )
#		SET( HAVE_DOT "YES" )
#	ENDIF ( DOXYGEN_DOT_EXECUTABLE )
#
#	# configure tools documentation
#	CONFIGURE_FILE( "tools/Doxyfile.in" "${CMAKE_CURRENT_BINARY_DIR}/tools/Doxyfile" @ONLY)
#	ADD_CUSTOM_TARGET( DoxygenDocTools ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/tools/Doxyfile )
#
#	# configure library documentation
#	CONFIGURE_FILE( "libsyncml/Doxyfile.in" "${CMAKE_CURRENT_BINARY_DIR}/libsyncml/Doxyfile" @ONLY)
#	ADD_CUSTOM_TARGET( DoxygenDocLibrary ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/libsyncml/Doxyfile )
#
#	# configure general doxygen target
#	CONFIGURE_FILE( "misc/doxygen.css" "${CMAKE_CURRENT_BINARY_DIR}/misc/doxygen.css" @ONLY)
#	# WARNING: Do not use DEPENDS of ADD_CUSTOM_TARGET here
#	ADD_CUSTOM_TARGET( DoxygenDoc )
#	ADD_DEPENDENCIES( DoxygenDoc DoxygenDocLibrary DoxygenDocTools )
#ENDIF ( BUILD_DOCUMENTATION )
OPTION( ENABLE_INSTALL_DOC "install documentation" ON )
IF( ENABLE_INSTALL_DOC )
	ADD_DOCUMENTATION( TEXT FILE ${CMAKE_SOURCE_DIR}/BUGS )
	ADD_DOCUMENTATION( TEXT FILE ${CMAKE_SOURCE_DIR}/ChangeLog )
	ADD_DOCUMENTATION( TEXT FILE ${CMAKE_SOURCE_DIR}/COPYING )
	ADD_DOCUMENTATION( TEXT FILE ${CMAKE_SOURCE_DIR}/GNU-LGPL )
	ADD_DOCUMENTATION( TEXT FILE ${CMAKE_SOURCE_DIR}/INSTALL )
	ADD_DOCUMENTATION( TEXT FILE ${CMAKE_SOURCE_DIR}/README )
	ADD_DOCUMENTATION( TEXT FILE ${CMAKE_SOURCE_DIR}/References )
	ADD_DOCUMENTATION( TEXT FILE ${CMAKE_SOURCE_DIR}/THANKS )
	ADD_DOCUMENTATION( TEXT FILE ${CMAKE_SOURCE_DIR}/TODO )
ENDIF( ENABLE_INSTALL_DOC )

# todo: add requires in pc file
INSTALL( FILES "${CMAKE_CURRENT_BINARY_DIR}/libwbxml2.pc" DESTINATION "${LIBDATA_INSTALL_DIR}/pkgconfig/" )
# status output
INCLUDE( ShowStatus )
MESSAGE( STATUS "==================================================" )
SHOW_STATUS( WBXML_LIB_VERBOSE "verbose mode\t\t\t" )
SHOW_STATUS( FOUND_POSIX_GETOPT "POSIX getopt\t\t\t" )
SHOW_STATUS( ENABLE_UNIT_TEST "unit tests\t\t\t" )
SHOW_STATUS( ENABLE_PERL "perl binary (test generated XML)" )
SHOW_STATUS( ENABLE_DIFF "diff binary (test generated XML)" )
SHOW_STATUS( WBXML_ENCODER_USE_STRTBL "enable string tables\t\t" )
SHOW_STATUS( WBXML_SUPPORT_WML "enable WML support\t\t" )
SHOW_STATUS( WBXML_SUPPORT_WTA "enable WTA support\t\t" )
SHOW_STATUS( WBXML_SUPPORT_SI "enable SI support\t\t" )
SHOW_STATUS( WBXML_SUPPORT_SL "enable SL support\t\t" )
SHOW_STATUS( WBXML_SUPPORT_CO "enable CO support\t\t" )
SHOW_STATUS( WBXML_SUPPORT_PROV "enable PROV support\t\t" )
SHOW_STATUS( WBXML_SUPPORT_EMN "enable EMN support\t\t" )
SHOW_STATUS( WBXML_SUPPORT_DRMREL "enable DRMREL support\t" )
SHOW_STATUS( WBXML_SUPPORT_OTA_SETTINGS "enable OTA_SETTINGS support\t" )
SHOW_STATUS( WBXML_SUPPORT_SYNCML "enable SYNCML support\t" )
SHOW_STATUS( WBXML_SUPPORT_WV "enable WV support\t\t" )
SHOW_STATUS( WBXML_SUPPORT_AIRSYNC "enable AIRSYNC support\t" )
SHOW_STATUS( WBXML_SUPPORT_CONML "enable Nokia ConML support\t" )
SHOW_STATUS( BUILD_DOCUMENTATION "build dynamic documentation\t" )
SHOW_STATUS( WBXML_SUPPORT_ICONV "enable iconv support\t\t" )
SHOW_STATUS( ENABLE_INSTALL_DOC "install documentation\t" )
SHOW_STATUS( WBXML_INSTALL_FULL_HEADERS "install internal headers\t" )

# fatal error detection
IF ( FATAL_ERROR_EXPAT )
	MESSAGE( STATUS "==================================================" )
	MESSAGE( STATUS "FATAL ERROR(S) DETECTED ... DETAILS FOLLOW:" )
	MESSAGE( STATUS "==================================================" )
	IF ( FATAL_ERROR_EXPAT )
		MESSAGE( STATUS "${FATAL_ERROR_EXPAT}" )
	ENDIF ( FATAL_ERROR_EXPAT )
	MESSAGE( STATUS "==================================================" )
ENDIF ( FATAL_ERROR_EXPAT )

### CPack ########################################

IF( RELEASE_CANDIDATE )
	SET( LIBWBXML_VERSION "${LIBWBXML_VERSION}-RC${RELEASE_CANDIDATE}" )
ENDIF( RELEASE_CANDIDATE )

find_program(CCACHE_FOUND ccache)
if(CCACHE_FOUND)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE ccache)
    set_property(GLOBAL PROPERTY RULE_LAUNCH_LINK ccache)
endif(CCACHE_FOUND)

# ADD_SUBDIRECTORY( wbxmlTestSuite )

SET( CPACK_GENERATOR "TGZ;TBZ2" ) # This line is need for a CMake (Version 2.4.7) Bug - Fixed in CVS 
SET( CPACK_SOURCE_GENERATOR "TGZ;TBZ2") 
SET( CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${LIBWBXML_VERSION}" ) 
SET( CPACK_SET_DESTDIR ON )
INCLUDE( CPack )

### CTest ########################################

ADD_SUBDIRECTORY( test/tools )
IF(CHECK_FOUND)
    ADD_SUBDIRECTORY( test/api )
ENDIF(CHECK_FOUND)
ADD_SUBDIRECTORY( test/fuzz )
