#include "api_test.h"

#include "../../src/wbxml_buffers.h"

START_TEST (test_init_and_destroy)
{
    WBXMLBuffer *buf;
    const char *t1 = "test 1";

    buf = wbxml_buffer_create(t1, strlen(t1)-2, 4);
    ck_assert(buf != NULL);
    ck_assert(wbxml_buffer_len(buf) == 4);
    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_init_and_destroy_string)
{
    WBXMLBuffer *buf;
    const char *t1 = "test 1";

    buf = wbxml_buffer_create_from_cstr(t1);
    ck_assert(buf != NULL);
    ck_assert(wbxml_buffer_len(buf) == 6);
    wbxml_buffer_destroy(buf);
}
END_TEST

/*
  This test is only necessary because on Win32 systems
  WBXML_DECLARE and WBXML_DECLARE_NONSTD are different.
*/
START_TEST (test_init_and_destroy_win32)
{
    WBXMLBuffer *buf;
    const char *t1 = "test 1";

    buf = wbxml_buffer_create(t1, strlen(t1)-2, 4);
    ck_assert(buf != NULL);
    ck_assert(wbxml_buffer_len(buf) == 4);
    wbxml_buffer_destroy_item(buf);
}
END_TEST

START_TEST (test_init_and_destroy_static)
{
    WBXMLBuffer *buf, *buf2;
    const char *t1 = "  abcdef test 12  ";
    const char *t2 = "no";

    buf = wbxml_buffer_sta_create(t1, 4);
    buf2 = wbxml_buffer_create_from_cstr(t2);
    ck_assert(buf != NULL);
    ck_assert(wbxml_buffer_len(buf) == 4);

    /* check that all write functions are blocked */

    ck_assert( ! wbxml_buffer_set_char(buf, 3, 'c'));

    ck_assert( ! wbxml_buffer_insert(buf, buf2, 2));
    ck_assert( ! wbxml_buffer_insert_cstr(buf, (const WB_UTINY*) t2, 2));

    ck_assert( ! wbxml_buffer_append(buf, buf2));
    ck_assert( ! wbxml_buffer_append_data(buf, t2, 2));
    ck_assert( ! wbxml_buffer_append_cstr(buf, t2));
    ck_assert( ! wbxml_buffer_append_char(buf, 'c'));
    ck_assert( ! wbxml_buffer_append_mb_uint_32(buf, 12345)); 

    ck_assert( ! wbxml_buffer_delete(buf, 2, 1));
    ck_assert( ! wbxml_buffer_shrink_blanks(buf));
    ck_assert( ! wbxml_buffer_strip_blanks(buf));

    ck_assert( ! wbxml_buffer_hex_to_binary(buf));
    ck_assert( ! wbxml_buffer_binary_to_hex(buf, FALSE));

    ck_assert( wbxml_buffer_decode_base64(buf) == WBXML_ERROR_INTERNAL );
    ck_assert( wbxml_buffer_encode_base64(buf) == WBXML_ERROR_INTERNAL );

    ck_assert( ! wbxml_buffer_remove_trailing_zeros(buf));

    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_set_char)
{
    WBXMLBuffer *buf;
    const char *t1 = "test 1";
    char c;

    buf = wbxml_buffer_create_from_cstr(t1);
    ck_assert(buf != NULL);
    ck_assert(wbxml_buffer_len(buf) == 6);

    /* set first char */

    ck_assert(wbxml_buffer_set_char(buf, 0, 'T'));
    ck_assert(wbxml_buffer_get_char(buf, 0, (WB_UTINY *) &c));
    ck_assert(c == 'T');

    /* set middle char */

    ck_assert(wbxml_buffer_set_char(buf, 2, 'S'));
    ck_assert(wbxml_buffer_get_char(buf, 2, (WB_UTINY *) &c));
    ck_assert(c == 'S');

    /* set last char */

    ck_assert(wbxml_buffer_set_char(buf, 5, '2'));
    ck_assert(wbxml_buffer_get_char(buf, 5, (WB_UTINY *) &c));
    ck_assert(c == '2');

    /* set last+1 char */

    ck_assert(! wbxml_buffer_set_char(buf, 6, 'X'));

    /* set last+2 char */

    ck_assert(! wbxml_buffer_set_char(buf, 7, 'T'));

    /* check for correct result */

    ck_assert(wbxml_buffer_compare_cstr(buf, "TeSt 2") == 0);

    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_append)
{
    WBXMLBuffer *buf, *buf2;
    WB_UTINY c;

    /* create empty buffer */

    buf = wbxml_buffer_create_from_cstr("");
    ck_assert(buf != NULL);
    ck_assert(wbxml_buffer_len(buf) == 0);

    /* append to empty buffer */

    ck_assert(wbxml_buffer_append_cstr(buf, "test"));
    ck_assert(wbxml_buffer_len(buf) == 4);

    /* append buffer */

    buf2 = wbxml_buffer_create_from_cstr("1");
    ck_assert(wbxml_buffer_append(buf, buf2));
    wbxml_buffer_destroy(buf2);
    ck_assert(wbxml_buffer_compare_cstr(buf, "test1") == 0);

    /* append cstr */

    ck_assert(wbxml_buffer_append_cstr(buf, "12"));
    ck_assert(wbxml_buffer_compare_cstr(buf, "test112") == 0);

    /* append data */

    ck_assert(wbxml_buffer_append_data(buf, "1234", 3));
    ck_assert(wbxml_buffer_compare_cstr(buf, "test112123") == 0);

    /* append char */

    ck_assert(wbxml_buffer_append_char(buf, '5'));
    ck_assert(wbxml_buffer_compare_cstr(buf, "test1121235") == 0);

    /* append mb uint 32 */
    /* |00000000|00000000|00000000|00000000| => 0 => |00000000| => '0' */
    /* |00000000|00000001|00000000|00000001| => 0 => |10000100|10000000|00000001| => */

    ck_assert(wbxml_buffer_append_mb_uint_32(buf, (WB_ULONG) 0));
    ck_assert(wbxml_buffer_len(buf) == 12);
    ck_assert(wbxml_buffer_get_char(buf, 11, &c));
    ck_assert(c == 0);
    ck_assert((WB_ULONG) 0x010001 == (WB_ULONG) 65537);
    ck_assert(wbxml_buffer_append_mb_uint_32(buf, (WB_ULONG) 65537));
    ck_assert(wbxml_buffer_len(buf) == 15);
    ck_assert(wbxml_buffer_get_char(buf, 12, &c));
    ck_assert(c == (WB_UTINY) 0x84);
    ck_assert(wbxml_buffer_get_char(buf, 13, &c));
    ck_assert(c == (WB_UTINY) 0x80);
    ck_assert(wbxml_buffer_get_char(buf, 14, &c));
    ck_assert(c == (WB_UTINY) 0x01);

    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_insert)
{
    WBXMLBuffer *buf, *buf2;

    /* create empty buffer */

    buf = wbxml_buffer_create_from_cstr("");
    ck_assert(buf != NULL);
    ck_assert(wbxml_buffer_len(buf) == 0);

    /* insert to an empty buffer */

    ck_assert(wbxml_buffer_insert_cstr(buf, (const WB_UTINY *) "test", 0));
    ck_assert(wbxml_buffer_len(buf) == 4);

    /* insert to head */

    ck_assert(wbxml_buffer_insert_cstr(buf, (const WB_UTINY *) "1", 0));
    ck_assert(wbxml_buffer_len(buf) == 5);
    ck_assert(wbxml_buffer_compare_cstr(buf, "1test") == 0);

    /* insert into middle */

    ck_assert(wbxml_buffer_insert_cstr(buf, (const WB_UTINY *) "23", 1));
    ck_assert(wbxml_buffer_len(buf) == 7);
    ck_assert(wbxml_buffer_compare_cstr(buf, "123test") == 0);

    /* insert at end */

    ck_assert(wbxml_buffer_insert_cstr(buf, (const WB_UTINY *) "7", 6));
    ck_assert(wbxml_buffer_len(buf) == 8);
    ck_assert(wbxml_buffer_compare_cstr(buf, "123tes7t") == 0);

    /* insert after end */

    ck_assert(wbxml_buffer_insert_cstr(buf, (const WB_UTINY *) "9", 8));
    ck_assert(wbxml_buffer_len(buf) == 9);
    ck_assert(wbxml_buffer_compare_cstr(buf, "123tes7t9") == 0);

    /* insert far after end */

    ck_assert( ! wbxml_buffer_insert_cstr(buf, (const WB_UTINY *) "10", 10));
    ck_assert(wbxml_buffer_len(buf) == 9);
    ck_assert(wbxml_buffer_compare_cstr(buf, "123tes7t9") == 0);

    /* insert buffer */

    buf2 = wbxml_buffer_create_from_cstr("XYZ");
    ck_assert(wbxml_buffer_insert(buf, buf2, 3));
    ck_assert(wbxml_buffer_len(buf) == 12);
    ck_assert(wbxml_buffer_compare_cstr(buf, "123XYZtes7t9") == 0);

    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_delete)
{
    WBXMLBuffer *buf;

    /* create empty buffer */

    buf = wbxml_buffer_create_from_cstr("");
    ck_assert(buf != NULL);
    ck_assert(wbxml_buffer_len(buf) == 0);

    /* delete in an empty buffer */

    ck_assert( ! wbxml_buffer_delete(buf, 0, 0));
    ck_assert(wbxml_buffer_len(buf) == 0);
    ck_assert( ! wbxml_buffer_delete(buf, 0, 1));
    ck_assert(wbxml_buffer_len(buf) == 0);

    /* insert */

    ck_assert(wbxml_buffer_insert_cstr(buf, (const WB_UTINY *) "test", 0));
    ck_assert(wbxml_buffer_len(buf) == 4);

    /* delete head */

    ck_assert(wbxml_buffer_delete(buf, 0, 1));
    ck_assert(wbxml_buffer_len(buf) == 3);
    ck_assert(wbxml_buffer_compare_cstr(buf, "est") == 0);

    /* delete last */

    ck_assert(wbxml_buffer_delete(buf, 2, 1));
    ck_assert(wbxml_buffer_len(buf) == 2);
    ck_assert(wbxml_buffer_compare_cstr(buf, "es") == 0);

    /* delete last+1 */

    ck_assert( ! wbxml_buffer_delete(buf, 2, 1));
    ck_assert(wbxml_buffer_len(buf) == 2);
    ck_assert(wbxml_buffer_compare_cstr(buf, "es") == 0);

    /* delete all */

    ck_assert(wbxml_buffer_delete(buf, 0, 2));
    ck_assert(wbxml_buffer_len(buf) == 0);
    ck_assert(wbxml_buffer_compare_cstr(buf, "") == 0);

    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_compare)
{
    WBXMLBuffer *buf, *buf2;

    /* compare empty buffer */

    buf = wbxml_buffer_create_from_cstr("");
    buf2 = wbxml_buffer_create_from_cstr("");
    ck_assert(buf != NULL);
    ck_assert(wbxml_buffer_len(buf) == 0);
    ck_assert(buf2 != NULL);
    ck_assert(wbxml_buffer_len(buf2) == 0);
    ck_assert(wbxml_buffer_compare(buf, buf2) == 0);
    ck_assert(wbxml_buffer_compare_cstr(buf, "") == 0);

    /* compare empty and filled buffer */

    wbxml_buffer_destroy(buf2);
    buf2 = wbxml_buffer_create_from_cstr("test");
    ck_assert(buf2 != NULL);
    ck_assert(wbxml_buffer_len(buf2) == 4);
    ck_assert(wbxml_buffer_compare(buf, buf2) != 0);
    ck_assert(wbxml_buffer_compare_cstr(buf, "test") != 0);

    /* compare empty and filled buffer */

    wbxml_buffer_destroy(buf);
    buf = wbxml_buffer_create_from_cstr("test");
    ck_assert(buf != NULL);
    ck_assert(wbxml_buffer_len(buf) == 4);
    ck_assert(wbxml_buffer_compare(buf, buf2) == 0);
    ck_assert(wbxml_buffer_compare_cstr(buf, "test") == 0);

    wbxml_buffer_destroy(buf);
    buf = wbxml_buffer_create_from_cstr("TEST");
    ck_assert(buf != NULL);
    ck_assert(wbxml_buffer_len(buf) == 4);
    ck_assert(wbxml_buffer_compare(buf, buf2) != 0);
    ck_assert(wbxml_buffer_compare_cstr(buf, "test") != 0);

    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_search)
{
    WBXMLBuffer *buf, *buf2;
    WB_ULONG l;

    buf2 = wbxml_buffer_create_from_cstr("123");

    /* test with null/empty buffer */

    buf = wbxml_buffer_create_from_cstr("");

    ck_assert(! wbxml_buffer_search_char(NULL, '3', 0, &l));

    ck_assert(! wbxml_buffer_search(NULL, buf2, 0, &l));
    ck_assert(! wbxml_buffer_search(buf, NULL, 0, &l));
    ck_assert(! wbxml_buffer_search(buf, buf2, 0, &l));
    ck_assert(! wbxml_buffer_search(buf, NULL, 0, &l));

    ck_assert(! wbxml_buffer_search_cstr(NULL, (const WB_UTINY *) "123", 0, &l));
    ck_assert(! wbxml_buffer_search_cstr(NULL, (const WB_UTINY *) "", 0, &l));
    ck_assert(! wbxml_buffer_search_cstr(NULL, NULL, 0, &l));
    ck_assert(! wbxml_buffer_search_cstr(buf, (const WB_UTINY *) "123", 0, &l));
    l = 1;
    ck_assert(wbxml_buffer_search_cstr(buf, (const WB_UTINY *) "", 0, &l));
    ck_assert(l == 0);
    ck_assert(! wbxml_buffer_search_cstr(buf, NULL, 0, &l));

    wbxml_buffer_destroy(buf);

    /* test with filled buffer */

    buf = wbxml_buffer_create_from_cstr("test123ABCD");

    ck_assert(wbxml_buffer_search_char(buf, '3', 0, &l));
    ck_assert(l == 6);
    ck_assert(wbxml_buffer_search_char(buf, '3', 0, NULL));
    ck_assert(! wbxml_buffer_search_char(buf, '3', 7, &l));
    ck_assert(! wbxml_buffer_search_char(buf, '3', 7, NULL));

    ck_assert(wbxml_buffer_search(buf, buf2, 4, &l));
    ck_assert(l == 4);
    ck_assert(wbxml_buffer_search(buf, buf2, 4, NULL));
    ck_assert(! wbxml_buffer_search(buf, buf2, 5, &l));
    ck_assert(! wbxml_buffer_search(buf, buf2, 5, NULL));

    l = 1;
    ck_assert(wbxml_buffer_search_cstr(buf, (const WB_UTINY *) "123", 0, &l));
    ck_assert(l == 4);
    ck_assert(wbxml_buffer_search_cstr(buf, (const WB_UTINY *) "123", 0, NULL));
    ck_assert(wbxml_buffer_search_cstr(buf, (const WB_UTINY *) "", 0, &l));
    ck_assert(l == 0);
    ck_assert(! wbxml_buffer_search_cstr(buf, NULL, 0, &l));

    /* search after end */

    ck_assert(! wbxml_buffer_search_char(buf, '3', wbxml_buffer_len(buf), &l));
    ck_assert(! wbxml_buffer_search(buf, buf2, wbxml_buffer_len(buf), &l));
    ck_assert(! wbxml_buffer_search_cstr(buf, (const WB_UTINY *) "3", wbxml_buffer_len(buf), &l));

    wbxml_buffer_destroy(buf);
    wbxml_buffer_destroy(buf2);
}
END_TEST

START_TEST (test_split_words)
{
    WBXMLBuffer *buf, *item;
    WBXMLList *list;
    int i;

    /* test with null/empty buffer */

    ck_assert(wbxml_buffer_split_words(NULL) == NULL);

    buf = wbxml_buffer_create_from_cstr("");
    list = wbxml_buffer_split_words(buf);
    ck_assert(list != NULL);
    ck_assert(wbxml_list_len(list) == 0);
    wbxml_list_destroy(list, NULL);
    wbxml_buffer_destroy(buf);

    buf = wbxml_buffer_create_from_cstr(" \n\r\v\f\t");
    list = wbxml_buffer_split_words(buf);
    ck_assert(list != NULL);
    ck_assert(wbxml_list_len(list) == 0);
    wbxml_list_destroy(list, NULL);
    wbxml_buffer_destroy(buf);

    /* split several words an verify it */

    buf = wbxml_buffer_create_from_cstr(" 1\n2\r3\v4\f5\t");
    list = wbxml_buffer_split_words(buf);
    ck_assert(list != NULL);
    ck_assert(wbxml_list_len(list) == 5);
    for (i=0; i<5; i++) {
        item = wbxml_list_extract_first(list);
        ck_assert(item != NULL);
        switch(i) {
            case 0: ck_assert(wbxml_buffer_compare_cstr(item, "1") == 0); break;
            case 1: ck_assert(wbxml_buffer_compare_cstr(item, "2") == 0); break;
            case 2: ck_assert(wbxml_buffer_compare_cstr(item, "3") == 0); break;
            case 3: ck_assert(wbxml_buffer_compare_cstr(item, "4") == 0); break;
            case 4: ck_assert(wbxml_buffer_compare_cstr(item, "5") == 0); break;
            default: ck_abort();
        }
        wbxml_buffer_destroy(item);
    }
    wbxml_list_destroy(list, NULL);
    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_duplicate)
{
    WBXMLBuffer *buf, *dup;

    /* test with null/empty/filled buffer */

    ck_assert(wbxml_buffer_duplicate(NULL) == NULL);

    buf = wbxml_buffer_create_from_cstr("");
    dup = wbxml_buffer_duplicate(buf);
    ck_assert(dup != NULL);
    ck_assert(wbxml_buffer_compare(buf, dup) == 0);
    ck_assert(wbxml_buffer_compare_cstr(dup, "") == 0);
    wbxml_buffer_destroy(dup);
    wbxml_buffer_destroy(buf);

    buf = wbxml_buffer_create_from_cstr("test");
    dup = wbxml_buffer_duplicate(buf);
    ck_assert(dup != NULL);
    ck_assert(wbxml_buffer_compare(buf, dup) == 0);
    ck_assert(wbxml_buffer_compare_cstr(dup, "test") == 0);
    wbxml_buffer_destroy(dup);
    wbxml_buffer_destroy(buf);

    /* test with static */

    buf = wbxml_buffer_sta_create_from_cstr("test");
    dup = wbxml_buffer_duplicate(buf);
    ck_assert(dup != NULL);
    ck_assert(wbxml_buffer_compare(buf, dup) == 0);
    ck_assert(wbxml_buffer_compare_cstr(dup, "test") == 0);
    wbxml_buffer_destroy(dup);
    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_conversion_hex)
{
    WBXMLBuffer *buf;
    const char *bin = "test image";
    const char *hex = "7465737420696D616765";

    /* test convert to base64 */

    buf = wbxml_buffer_create_from_cstr(bin);
    ck_assert(wbxml_buffer_binary_to_hex(buf, TRUE));
    ck_assert(wbxml_buffer_compare_cstr(buf, hex) == 0);
    wbxml_buffer_destroy(buf);

    /* test convert to binary */

    buf = wbxml_buffer_create_from_cstr(hex);
    ck_assert(wbxml_buffer_hex_to_binary(buf));
    ck_assert(wbxml_buffer_compare_cstr(buf, bin) == 0);
    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_conversion_base64)
{
    WBXMLBuffer *buf;
    const char *bin = "test image\n";
    const char *b64 = "dGVzdCBpbWFnZQo=";

    /* test convert to base64 */

    buf = wbxml_buffer_create_from_cstr(bin);
    ck_assert(wbxml_buffer_encode_base64(buf) == WBXML_OK);
    ck_assert(wbxml_buffer_compare_cstr(buf, b64) == 0);
    wbxml_buffer_destroy(buf);

    /* test convert to binary */

    buf = wbxml_buffer_create_from_cstr(b64);
    ck_assert(wbxml_buffer_decode_base64(buf) == WBXML_OK);
    ck_assert(wbxml_buffer_compare_cstr(buf, bin) == 0);
    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_shrink_blanks)
{
    WBXMLBuffer *buf;
    const char *raw = " \n\t\rtest\n\f\t image\t\v \n";
    const char *fix = " test image ";

    /* init buffers */

    buf = wbxml_buffer_create_from_cstr(raw);
    ck_assert(buf != NULL);

    /* shrink and test */

    ck_assert(wbxml_buffer_shrink_blanks(buf));
    ck_assert(wbxml_buffer_compare_cstr(buf, fix) == 0);

    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_strip_blanks)
{
    WBXMLBuffer *buf;
    const char *raw = " \n\t\f\rtest image\t\v \n";
    const char *fix = "test image";

    /* init buffers */

    buf = wbxml_buffer_create_from_cstr(raw);
    ck_assert(buf != NULL);

    /* shrink and test */

    ck_assert(wbxml_buffer_strip_blanks(buf));
    ck_assert(wbxml_buffer_compare_cstr(buf, fix) == 0);

    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_remove_trailing_zeros)
{
    WBXMLBuffer *buf;
    const char *raw = "test image\0\0\0";
    const char *fix = "test image";

    /* init buffers */

    buf = wbxml_buffer_create(raw, 13, 13);
    ck_assert(buf != NULL);

    /* shrink and test */

    ck_assert(wbxml_buffer_remove_trailing_zeros(buf));
    ck_assert(wbxml_buffer_compare_cstr(buf, fix) == 0);

    wbxml_buffer_destroy(buf);
}
END_TEST

START_TEST (test_buffer_get_char_wrong_params)
{
    WBXMLBuffer *buf;
    WB_UTINY result;

    /* init buffer */

    buf = wbxml_buffer_create("test", 4, 4);
    ck_assert(buf != NULL);

    /* test */

    ck_assert(wbxml_buffer_get_char(NULL, 0, &result) == FALSE);
    ck_assert(wbxml_buffer_get_char(buf, 0, &result) == TRUE);
    ck_assert(wbxml_buffer_get_char(buf, 3, &result) == TRUE);
    ck_assert(wbxml_buffer_get_char(buf, 4, &result) == FALSE);
    ck_assert(wbxml_buffer_get_char(buf, 0, NULL) == FALSE);

    /* cleanup buffer */

    wbxml_buffer_destroy(buf);
}
END_TEST

BEGIN_TESTS(wbxml_buffers)

    /* initialization */
    ADD_TEST(test_init_and_destroy);
    ADD_TEST(test_init_and_destroy_string);
    ADD_TEST(test_init_and_destroy_win32);
    ADD_TEST(test_init_and_destroy_static);

    /* write operations */
    ADD_TEST(test_set_char);
    ADD_TEST(test_append);
    ADD_TEST(test_insert);
    ADD_TEST(test_delete);

    /* read operations */
    ADD_TEST(test_compare);
    ADD_TEST(test_search);

    /* buffer level write functions */
    ADD_TEST(test_split_words);
    ADD_TEST(test_duplicate);

    /* conversion */
    ADD_TEST(test_conversion_hex);
    ADD_TEST(test_conversion_base64);

    /* handle whitespaces */
    ADD_TEST(test_shrink_blanks);
    ADD_TEST(test_strip_blanks);
    ADD_TEST(test_remove_trailing_zeros);

    /* found bugs - test driven development */
    ADD_TEST(test_buffer_get_char_wrong_params);

END_TESTS

