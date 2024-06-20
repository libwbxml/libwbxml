
# Standard header and include paths were already defined.

include(CMakePackageConfigHelpers)
include(GNUInstallDirs)

configure_package_config_file(
    libwbxml2-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/libwbxml2-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libwbxml2
    PATH_VARS
        LIBWBXML_LIBRARIES_DIR
        LIBWBXML_INCLUDE_DIR
)

# Please note: All libwbxml releases of the 0.11 series are downward compatible until v0.11.0.
write_basic_package_version_file("${CMAKE_CURRENT_BINARY_DIR}/libwbxml2-config-version.cmake"
  VERSION "${LIBWBXML_VERSION}"
  COMPATIBILITY SameMinorVersion )

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/libwbxml2-config.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/libwbxml2-config-version.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/libwbxml2 )

