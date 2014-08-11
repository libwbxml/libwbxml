#include <check.h>

#define BEGIN_TESTS(name) \
  Suite* wbxml_suite (void) {\
    Suite *suite = suite_create("name");\
    TCase *tcase;

#define ADD_TEST(name) \
  tcase = tcase_create("name"); \
  tcase_add_test(tcase, name); \
  suite_add_tcase(suite, tcase);

#define END_TESTS \
    return suite; \
  }

