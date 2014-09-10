#include "api_test.h"

#include "../../src/wbxml_errors.h"

START_TEST (security_test_errors_datetime_without_percent)
{
    ck_assert(strchr(wbxml_errors_string(WBXML_ERROR_BAD_DATETIME), '%') == NULL);
}
END_TEST

START_TEST (test_errors_ok)
{
    ck_assert(wbxml_errors_string(WBXML_OK) != NULL);
    ck_assert(strcmp(wbxml_errors_string(WBXML_OK), "Unknown Error Code") != 0);
}
END_TEST

START_TEST (test_errors_last_item)
{
    ck_assert(wbxml_errors_string(WBXML_ERROR_XMLPARSER_OUTPUT_UTF16) != NULL);
    ck_assert(strcmp(wbxml_errors_string(WBXML_ERROR_XMLPARSER_OUTPUT_UTF16), "Unknown Error Code") != 0);

    ck_assert(wbxml_errors_string(WBXML_ERROR_CHARSET_NOT_FOUND) != NULL);
    ck_assert(strcmp(wbxml_errors_string(WBXML_ERROR_CHARSET_NOT_FOUND), "Unknown Error Code") != 0);
}
END_TEST

START_TEST (test_errors_unknown_error_code)
{
    ck_assert(wbxml_errors_string(127) != NULL);
    ck_assert(strcmp(wbxml_errors_string(127), "Unknown Error Code") == 0);
}
END_TEST

BEGIN_TESTS(wbxml_encoder_internals)

    ADD_TEST(security_test_errors_datetime_without_percent);
    ADD_TEST(test_errors_ok);
    ADD_TEST(test_errors_last_item);
    ADD_TEST(test_errors_unknown_error_code);

END_TESTS

