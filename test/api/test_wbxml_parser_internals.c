#include "api_test.h"

#include "../../src/wbxml_parser.c"

#if ( defined( WBXML_SUPPORT_SI ) || defined( WBXML_SUPPORT_EMN ) )

/* This test case verifies the standard compliance.
   The used timestamp is exactly the example from the OMA specification.
   2002-04-16T06:40:00Z
   0010 0000 0000 0010 => 2 0 0 2
   0000 0100           => 0 4
   0001 0110           => 1 6
   0000 0110           => 0 6
   0100 0000           => 4 0
   0000 0000           => 0 0 (not encoded - ommitted)
 */
START_TEST (test_parser_decode_datetime)
{
    const char opaque[7] = { 0x20, 0x02, 0x04, 0x16, 0x06, 0x40, 0x12 };
    WBXMLBuffer *buf = NULL;

    /* test timestamp including minutes */
    buf = wbxml_buffer_create(opaque, 7, 7);
    ck_assert(buf != NULL);
    ck_assert(decode_datetime(buf) == WBXML_OK);
    ck_assert(wbxml_buffer_compare_cstr(buf, "2002-04-16T06:40:12Z") == 0);
    wbxml_buffer_destroy(buf);
    buf = NULL;

    /* test timestamp including minutes - OMA example*/
    buf = wbxml_buffer_create(opaque, 6, 6);
    ck_assert(buf != NULL);
    ck_assert(decode_datetime(buf) == WBXML_OK);
    ck_assert(wbxml_buffer_compare_cstr(buf, "2002-04-16T06:40:00Z") == 0);
    wbxml_buffer_destroy(buf);
    buf = NULL;

    /* test timestamp including hours */
    buf = wbxml_buffer_create(opaque, 5, 5);
    ck_assert(buf != NULL);
    ck_assert(decode_datetime(buf) == WBXML_OK);
    ck_assert(wbxml_buffer_compare_cstr(buf, "2002-04-16T06:00:00Z") == 0);
    wbxml_buffer_destroy(buf);
    buf = NULL;

    /* test timestamp including date */
    buf = wbxml_buffer_create(opaque, 4, 4);
    ck_assert(buf != NULL);
    ck_assert(decode_datetime(buf) == WBXML_OK);
    ck_assert(wbxml_buffer_compare_cstr(buf, "2002-04-16T00:00:00Z") == 0);
    wbxml_buffer_destroy(buf);
    buf = NULL;

    /* test incomplete timestamp => ERROR */
    buf = wbxml_buffer_create(opaque, 3, 3);
    ck_assert(buf != NULL);
    ck_assert(decode_datetime(buf) == WBXML_ERROR_BAD_DATETIME);
    wbxml_buffer_destroy(buf);
    buf = NULL;

    /* test NULL timestamp => ERROR */
    ck_assert(decode_datetime(NULL) == WBXML_ERROR_INTERNAL);
}
END_TEST

#endif /* WBXML_SUPPORT_SI || WBXML_SUPPORT_EMN */

BEGIN_TESTS(wbxml_parser_internals)

#if ( defined( WBXML_SUPPORT_SI ) || defined( WBXML_SUPPORT_EMN ) )
    ADD_TEST(test_parser_decode_datetime);
#endif /* WBXML_SUPPORT_SI || WBXML_SUPPORT_EMN */

END_TESTS

