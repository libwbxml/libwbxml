prefix=@CMAKE_INSTALL_PREFIX@
exec_prefix=${prefix}/@LIBWBXML_EXEC_INSTALL_DIR@
libdir=${prefix}/@LIBWBXML_LIBRARIES_DIR@
includedir=${prefix}/@LIBWBXML_INCLUDE_DIR@

Name: libwbxml2
Description: C wbxml library
Version: @LIBWBXML_VERSION@
Requires: expat >= 2.0
Libs: -L${libdir} -lwbxml2
Cflags: -I${includedir}
