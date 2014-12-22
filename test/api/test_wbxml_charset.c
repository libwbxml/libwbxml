#include "api_test.h"

#include "../../src/wbxml_charset.h"

START_TEST (test_charset_existence)
{
    const WB_TINY *name [4] = { "UTF-8", "UTF-16", "ISO-8859-1", "US-ASCII"};
    WBXMLCharsetMIBEnum mib = 0;
    const WB_TINY *charset = NULL;
    int i;

    for (i=0; i < 4; i++)
    {
        ck_assert(wbxml_charset_get_mib(name[i], &mib) == TRUE);
        ck_assert(wbxml_charset_get_name(mib, &charset) == TRUE);
        ck_assert(strcmp(name[i], charset) == 0);
    }
}
END_TEST

BEGIN_TESTS(wbxml_charset)

    ADD_TEST(test_charset_existence);

END_TESTS

