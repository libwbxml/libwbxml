
ENABLE_TESTING()

# Please note, the provided test files originally caused system level crashs.
SET( FUZZ_FILES
    SIGABRT.PC.fffff7db0a10.STACK.0.CODE.-6.ADDR.0.INSTR.cmn_w0_0x1_lsl_12.2024-03-07.035819.705486.fuzz
    SIGSEGV.PC.aaaaaaae3998.STACK.0.CODE.1.ADDR.8.INSTR.ldrb_w8_x8_8.2024-03-07.035825.707512.fuzz
    SIGSEGV.PC.aaaaaaae39ac.STACK.0.CODE.1.ADDR.8.INSTR.ldrb_w20_x21_8.2024-03-11.003303.27182.fuzz
   )
SET( WBXML2XML "${CMAKE_CURRENT_BINARY_DIR}/../../tools/wbxml2xml" )

FOREACH( FUZZ_FILE IN LISTS FUZZ_FILES )
    SET( TEST_NAME "Fuzz_file_${FUZZ_FILE}" )
    ADD_TEST( NAME ${TEST_NAME} COMMAND ${WBXML2XML} "${CMAKE_CURRENT_SOURCE_DIR}/${FUZZ_FILE}" )
    # Please note, a system level crash like SIGABRT or SIGSEGV would cause this test to fail.
    # The regular expression ensures that the library returned a proper error.
    SET_PROPERTY( TEST ${TEST_NAME} PROPERTY WILL_FAIL TRUE)
    SET_PROPERTY( TEST ${TEST_NAME} PROPERTY FAIL_REGULAR_EXPRESSION "wbxml2xml failed: ")
ENDFOREACH()
