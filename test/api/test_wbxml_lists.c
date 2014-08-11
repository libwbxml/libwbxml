#include "api_test.h"

#include "../../src/wbxml_lists.h"

START_TEST (test_init_and_destroy)
{
    WBXMLList *list;

    list = wbxml_list_create();
    ck_assert(list != NULL);
    ck_assert(wbxml_list_len(list) == 0);
    wbxml_list_destroy(list, NULL);
}
END_TEST

START_TEST (test_append_not_null)
{
    WBXMLList *list;

    list = wbxml_list_create();
    ck_assert(wbxml_list_append(list, NULL) == FALSE);
    ck_assert(wbxml_list_len(list) == 0);
    wbxml_list_destroy(list, NULL);
}
END_TEST

START_TEST (test_insert_not_null)
{
    WBXMLList *list;

    list = wbxml_list_create();
    ck_assert(wbxml_list_insert(list, NULL, 0) == FALSE);
    ck_assert(wbxml_list_len(list) == 0);
    wbxml_list_destroy(list, NULL);
}
END_TEST

START_TEST (test_insert_wrong_pos)
{
    WBXMLList *list;

    list = wbxml_list_create();
    ck_assert(wbxml_list_insert(list, NULL, 4) == FALSE);
    ck_assert(wbxml_list_len(list) == 0);
    wbxml_list_destroy(list, NULL);
}
END_TEST

START_TEST (test_append)
{
    WBXMLList *list;
    const char *t1 = "test 1";
    const char *t2 = "test 2";
    const char *t3 = "test 3";

    list = wbxml_list_create();
    ck_assert(wbxml_list_get(list, 0) == NULL);
    ck_assert(wbxml_list_append(list, (void *) t1) == TRUE);
    ck_assert(wbxml_list_len(list) == 1);
    ck_assert(wbxml_list_append(list, (void *) t2) == TRUE);
    ck_assert(wbxml_list_len(list) == 2);
    ck_assert(wbxml_list_append(list, (void *) t3) == TRUE);
    ck_assert(wbxml_list_len(list) == 3);
    ck_assert(strcmp(wbxml_list_get(list, 0), t1) == 0);
    ck_assert(strcmp(wbxml_list_get(list, 1), t2) == 0);
    ck_assert(strcmp(wbxml_list_get(list, 2), t3) == 0);
    ck_assert(wbxml_list_len(list) == 3);
    wbxml_list_destroy(list, NULL);
}
END_TEST

START_TEST (test_insert)
{
    WBXMLList *list;
    const char *t1 = "test 1";
    const char *t2 = "test 2";
    const char *t3 = "test 3";
    const char *t4 = "test 4";
    const char *t5 = "test 5";

    list = wbxml_list_create();
    ck_assert(wbxml_list_get(list, 0) == NULL);
    ck_assert(wbxml_list_insert(list, (void *) t1, 0) == TRUE);
    ck_assert(wbxml_list_len(list) == 1);
    ck_assert(wbxml_list_insert(list, (void *) t2, 1) == TRUE);
    ck_assert(wbxml_list_len(list) == 2);
    ck_assert(wbxml_list_insert(list, (void *) t3, 1) == TRUE);
    ck_assert(wbxml_list_len(list) == 3);
    ck_assert(wbxml_list_insert(list, (void *) t4, 0) == TRUE);
    ck_assert(wbxml_list_len(list) == 4);
    ck_assert(wbxml_list_insert(list, (void *) t5, 4) == TRUE);
    ck_assert(wbxml_list_len(list) == 5);
    ck_assert(strcmp(wbxml_list_get(list, 0), t4) == 0);
    ck_assert(strcmp(wbxml_list_get(list, 1), t1) == 0);
    ck_assert(strcmp(wbxml_list_get(list, 2), t3) == 0);
    ck_assert(strcmp(wbxml_list_get(list, 3), t2) == 0);
    ck_assert(strcmp(wbxml_list_get(list, 4), t5) == 0);
    ck_assert(wbxml_list_len(list) == 5);
    wbxml_list_destroy(list, NULL);
}
END_TEST

START_TEST (test_extract_first)
{
    WBXMLList *list;
    const char *t1 = "test 1";
    const char *t2 = "test 2";

    list = wbxml_list_create();
    ck_assert(wbxml_list_get(list, 0) == NULL);
    ck_assert(wbxml_list_insert(list, (void *) t1, 0) == TRUE);
    ck_assert(wbxml_list_len(list) == 1);
    ck_assert(wbxml_list_insert(list, (void *) t2, 1) == TRUE);
    ck_assert(wbxml_list_len(list) == 2);
    ck_assert(strcmp(wbxml_list_extract_first(list), t1) == 0);
    ck_assert(wbxml_list_len(list) == 1);
    ck_assert(strcmp(wbxml_list_extract_first(list), t2) == 0);
    ck_assert(wbxml_list_len(list) == 0);
    ck_assert(wbxml_list_extract_first(list) == NULL);
    ck_assert(wbxml_list_len(list) == 0);
    wbxml_list_destroy(list, NULL);
}
END_TEST

void list_element_destructor(int *element)
{
    *element = 0;
}

START_TEST (test_destructor)
{
    WBXMLList *list;
    int i = 1;

    list = wbxml_list_create();
    ck_assert(wbxml_list_append(list, &i) == TRUE);
    ck_assert(wbxml_list_len(list) == 1);
    ck_assert(i == 1);
    wbxml_list_destroy(list, (void *)(void *) &list_element_destructor);
    ck_assert(i == 0);
}
END_TEST

BEGIN_TESTS(wbxml_lists)

    ADD_TEST(test_init_and_destroy);
    ADD_TEST(test_append_not_null);
    ADD_TEST(test_insert_not_null);
    ADD_TEST(test_insert_wrong_pos);
    ADD_TEST(test_append);
    ADD_TEST(test_insert);
    ADD_TEST(test_extract_first);
    ADD_TEST(test_destructor);

END_TESTS

