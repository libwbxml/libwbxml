
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

ENABLE_TESTING()
FIND_PACKAGE(Check REQUIRED)

INCLUDE_DIRECTORIES( ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR} ${CHECK_INCLUDE_DIRS} )

## Test private API

FOREACH( SRC_FILE lists buffers base64 conv encoder_internals )

    ADD_EXECUTABLE(test_wbxml_${SRC_FILE} test_wbxml_${SRC_FILE}.c api_test.c)

    TARGET_LINK_LIBRARIES(test_wbxml_${SRC_FILE} wbxml2)
    TARGET_LINK_LIBRARIES(test_wbxml_${SRC_FILE} ${CHECK_LIBRARIES})

    ADD_TEST(api_private_wbxml_${SRC_FILE} ${CMAKE_CURRENT_BINARY_DIR}/test_wbxml_${SRC_FILE})

ENDFOREACH( SRC_FILE lists  )
