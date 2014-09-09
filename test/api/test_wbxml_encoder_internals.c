#include "api_test.h"

#include "../../src/wbxml_encoder.c"

START_TEST (security_test_xml_len_null_check)
{
    WBXMLEncoder *enc = NULL;
    WB_UTINY *xml = NULL;
    WB_ULONG len = 0;

    enc = wbxml_encoder_create();
    ck_assert(xml_build_result(enc, &xml, (WB_ULONG *) NULL) == WBXML_OK);
    ck_assert(xml != NULL);
    wbxml_free(xml);
}
END_TEST

BEGIN_TESTS(wbxml_encoder_internals)

    ADD_TEST(security_test_xml_len_null_check);

END_TESTS

