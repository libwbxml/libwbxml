#include "api_test.h"

#include "../../src/wbxml_conv.h"

START_TEST (security_test_conv_init_null_reference)
{
    /* use undefined converter address reference */
    ck_assert(wbxml_conv_wbxml2xml_create(NULL) == WBXML_ERROR_BAD_PARAMETER);
    ck_assert(wbxml_conv_xml2wbxml_create(NULL) == WBXML_ERROR_BAD_PARAMETER);
}
END_TEST

BEGIN_TESTS(wbxml_conv)

    ADD_TEST(security_test_conv_init_null_reference);

END_TESTS

