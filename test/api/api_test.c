#include <stdio.h>
#include <check.h>

Suite* wbxml_suite (void);

int main (int argc, char *argv[]) {
        int number_failed;
        Suite *suite = wbxml_suite();
        SRunner *runner = srunner_create(suite);
        srunner_run_all(runner, CK_NORMAL);
        number_failed = srunner_ntests_failed(runner);
        srunner_free(runner);
        return number_failed;
}
