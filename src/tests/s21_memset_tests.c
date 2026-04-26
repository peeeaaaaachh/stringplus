#include "tests.h"

START_TEST(empty) {
  char str1[] = "";
  char str2[] = "";
  char c = '\0';
  s21_size n = 0;

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(hello) {
  char str1[] = "hello";
  char str2[] = "hello";
  char c = 'g';
  s21_size n = 5;

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(hello_zero_byte) {
  char str1[] = "hello";
  char str2[] = "hello";
  char c = 'g';
  s21_size n = 0;

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(hello_word) {
  char str1[] = "hello";
  char str2[] = "hello";
  char c = 'A';
  s21_size n = 3;

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(num) {
  char str1[] = "12345";
  char str2[] = "12345";
  char c = '9';
  s21_size n = 1;

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_str_eq(str1, str2);
}
END_TEST

START_TEST(num_with_string) {
  char str1[] = "12hello345";
  char str2[] = "12hello345";
  char c = '3';
  s21_size n = 3;

  s21_memset(str1, c, n);
  memset(str2, c, n);

  ck_assert_str_eq(str1, str2);
}
END_TEST

Suite* s21_memset_suite(void) {
  Suite* s = suite_create("s21_memset");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, hello);
  tcase_add_test(tc, hello_zero_byte);
  tcase_add_test(tc, hello_word);
  tcase_add_test(tc, num);
  tcase_add_test(tc, num_with_string);

  suite_add_tcase(s, tc);
  return s;
}
