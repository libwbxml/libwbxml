#include "api_test.h"

#include "../../src/wbxml_base64.h"

START_TEST (test_encode)
{
    WB_UTINY *result;

    /* verify empty strings */

    ck_assert(wbxml_base64_encode(NULL, 0) == NULL);
    ck_assert(wbxml_base64_encode(NULL, 1) == NULL);

    ck_assert(wbxml_base64_encode("", 0) == NULL);
    ck_assert(wbxml_base64_encode("test", 0) == NULL);

    /* encode a string */

    result = wbxml_base64_encode("test", 4);
    ck_assert(result != NULL);
    ck_assert(strlen(result) == 8);
    ck_assert(strncmp(result, "dGVzdA==", 8) == 0);
    wbxml_free(result);
}
END_TEST

START_TEST (test_decode)
{
    WB_UTINY *result;

    /* verify empty strings */

    ck_assert(wbxml_base64_decode(NULL, 0, &result) <= 0);
    ck_assert(wbxml_base64_decode(NULL, 1, &result) <= 0);
    ck_assert(wbxml_base64_decode("", 0, &result) <= 0);
    ck_assert(wbxml_base64_decode("test", 0, &result) <= 0);

    /* decode a string */

    ck_assert(wbxml_base64_decode("dGVzdA==", 8, &result) == 4);
    ck_assert(strncmp(result, "test", 4) == 0);
    wbxml_free(result);
}
END_TEST

START_TEST (test_encode_and_decode)
{
    WB_UTINY *enc;
    WB_UTINY *dec;

    /* encode */

    enc = wbxml_base64_encode("test", 4);
    ck_assert(wbxml_base64_decode(enc, strlen(enc), &dec) == 4);
    ck_assert(strncmp(dec, "test", 4) == 0);
    wbxml_free(enc);
    wbxml_free(dec);
}
END_TEST

BEGIN_TESTS(wbxml_base64)

    ADD_TEST(test_encode);
    ADD_TEST(test_decode);
    ADD_TEST(test_encode_and_decode);

END_TESTS

