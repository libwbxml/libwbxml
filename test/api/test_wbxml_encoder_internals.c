#include "api_test.h"

#include "../../src/wbxml_encoder.c"

START_TEST (security_test_xml_build_result_null_params)
{
    WBXMLEncoder *enc = NULL;
    WB_UTINY *xml = NULL;
    WB_ULONG len = 0;

    enc = wbxml_encoder_create();

    /* Check: xml_len == NULL */
    /* There is no default XML doctype. */
    ck_assert(xml_build_result(enc, &xml, (WB_ULONG *) NULL) == WBXML_ERROR_LANG_TABLE_UNDEFINED);

    /* Check: xml == NULL */
    ck_assert(xml_build_result(enc, NULL, NULL) == WBXML_ERROR_BAD_PARAMETER);

    wbxml_encoder_destroy(enc);
}
END_TEST

BEGIN_TESTS(wbxml_encoder_internals)

    ADD_TEST(security_test_xml_build_result_null_params);

END_TESTS

