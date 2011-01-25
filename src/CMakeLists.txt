LINK_DIRECTORIES( ${EXPAT_LIBRARY_DIRS} )

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${EXPAT_INCLUDE_DIRS} )

SET( libwbxml_LIB_SRCS
	wbxml_base64.c
	wbxml_buffers.c
	wbxml_charset.c
	wbxml_conv.c
	wbxml_elt.c
	wbxml_encoder.c
	wbxml_errors.c
	wbxml_lists.c
	wbxml_log.c
	wbxml_mem.c
	wbxml_parser.c
	wbxml_tables.c
	wbxml_tree.c
	wbxml_tree_clb_wbxml.c
	wbxml_tree_clb_xml.c
)

ADD_LIBRARY( wbxml2 SHARED ${libwbxml_LIB_SRCS} )

SET_TARGET_PROPERTIES( wbxml2 PROPERTIES SOVERSION ${LIBWBXML_LIBVERSION_SOVERSION} )
SET_TARGET_PROPERTIES( wbxml2 PROPERTIES VERSION ${LIBWBXML_LIBVERSION_VERSION} )
TARGET_LINK_LIBRARIES( wbxml2 ${EXPAT_LIBRARIES} )

INSTALL( TARGETS wbxml2
   RUNTIME DESTINATION ${LIBWBXML_BIN_DIR}
   LIBRARY DESTINATION ${LIBWBXML_LIBRARIES_DIR}
   ARCHIVE DESTINATION ${LIBWBXML_LIBRARIES_DIR}
)

INSTALL( FILES
	wbxml.h
	${CMAKE_CURRENT_BINARY_DIR}/../wbxml_config.h
	wbxml_conv.h
	wbxml_defines.h
	wbxml_errors.h
	DESTINATION ${LIBWBXML_INCLUDE_DIR}/wbxml
)

