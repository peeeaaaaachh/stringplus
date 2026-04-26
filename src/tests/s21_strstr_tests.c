#include "tests.h"

START_TEST(hello_world) {
  char haystack[] = "hello world";
  char needle[] = "world";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(empty_string) {
  char haystack[] = "";
  char needle[] = "hello world";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(empty_string2) {
  char haystack[] = "hello world";
  char needle[] = "";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(no_word) {
  char haystack[] = "hello world";
  char needle[] = "project";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_with_register) {
  char haystack[] = "HELLO hello HELLO";
  char needle[] = "hello";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_with_pattern) {
  char haystack[] = "hi hello hello HELLO hello";
  char needle[] = "hello";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_with_num) {
  char haystack[] = "12348437892 3278 9939";
  char needle[] = "3278";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(one_symbol) {
  char haystack[] = "1";
  char needle[] = "1";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(test_with_no_num) {
  char haystack[] = "167";
  char needle[] = "59";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

START_TEST(diff_string) {
  char haystack[] = "abXabY";
  char needle[] = "abc";

  ck_assert_pstr_eq(s21_strstr(haystack, needle), strstr(haystack, needle));
}
END_TEST

Suite* s21_strstr_suite(void) {
  Suite* s = suite_create("s21_strstr");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, hello_world);
  tcase_add_test(tc, empty_string);
  tcase_add_test(tc, empty_string2);
  tcase_add_test(tc, no_word);
  tcase_add_test(tc, test_with_register);
  tcase_add_test(tc, test_with_pattern);
  tcase_add_test(tc, test_with_num);
  tcase_add_test(tc, one_symbol);
  tcase_add_test(tc, test_with_no_num);
  tcase_add_test(tc, diff_string);

  suite_add_tcase(s, tc);
  return s;
}