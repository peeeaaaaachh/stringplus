#include "tests.h"

START_TEST(empty) {
  char s1[] = "";
  char s2[] = "";
  s21_size n = 0;
  int s21 = s21_strncmp(s1, s2, n);
  int string = strncmp(s1, s2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(hello_no_byte) {
  char s1[] = "hello";
  char s2[] = "";
  s21_size n = 0;
  int s21 = s21_strncmp(s1, s2, n);
  int string = strncmp(s1, s2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(hello_with_no_word) {
  char s1[] = "hello";
  char s2[] = "";

  s21_size len1 = s21_strlen(s1);
  s21_size len2 = s21_strlen(s2);
  s21_size n = (len1 < len2) ? len1 : len2;

  int s21 = s21_strncmp(s1, s2, n);
  int string = strncmp(s1, s2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(hello) {
  char s1[] = "hello";
  char s2[] = "hello";
  s21_size n = 5;
  int s21 = s21_strncmp(s1, s2, n);
  int string = strncmp(s1, s2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(hello_one_byte) {
  char s1[] = "hello";
  char s2[] = "hello";
  s21_size n = 1;
  int s21 = s21_strncmp(s1, s2, n);
  int string = strncmp(s1, s2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(first_word) {
  char s1[] = "dwlkdwldkfo";
  char s2[] = "dwlkd";
  s21_size n = 5;
  int s21 = s21_strncmp(s1, s2, n);
  int string = strncmp(s1, s2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(diffrent_word) {
  char s1[] = "hello";
  char s2[] = "hezlo";
  s21_size n = 5;
  int s21 = s21_strncmp(s1, s2, n);
  int string = strncmp(s1, s2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(second_word) {
  char s1[] = "dwlkd";
  char s2[] = "dwlkdwldkfo";
  s21_size n = 5;
  int s21 = s21_strncmp(s1, s2, n);
  int string = strncmp(s1, s2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(one_symbol) {
  char s1[] = "a";
  char s2[] = "a";
  s21_size n = 1;
  ck_assert_int_eq(s21_strncmp(s1, s2, n), strncmp(s1, s2, n));
}
END_TEST

START_TEST(one_symbol_diff) {
  char s1[] = "a";
  char s2[] = "b";
  s21_size n = 1;
  ck_assert_int_eq(s21_strncmp(s1, s2, n), strncmp(s1, s2, n));
}
END_TEST

Suite* s21_strncmp_suite(void) {
  Suite* s = suite_create("s21_strncmp");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, hello_no_byte);
  tcase_add_test(tc, hello_with_no_word);
  tcase_add_test(tc, hello);
  tcase_add_test(tc, hello_one_byte);
  tcase_add_test(tc, first_word);
  tcase_add_test(tc, diffrent_word);
  tcase_add_test(tc, second_word);
  tcase_add_test(tc, one_symbol);
  tcase_add_test(tc, one_symbol_diff);

  suite_add_tcase(s, tc);
  return s;
}
