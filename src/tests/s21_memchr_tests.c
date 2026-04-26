#include "tests.h"

START_TEST(empty) {
  char str[10] = "";
  int c = '\0';
  int n = 6;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(hello_zero_byte) {
  char str[10] = "hello";
  int c = '\0';
  int n = 6;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(first_symbol) {
  char str[10] = "hello";
  int c = 'h';
  int n = 6;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(end_symbol) {
  char str[10] = "hello";
  int c = 'o';
  int n = 6;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(repeat_symbol) {
  char str[] = "hello";
  int c = 'l';
  int n = 6;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(num) {
  char str[10] = "1234567";
  int c = '4';
  int n = 6;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(num1_with_string) {
  char str[30] = "123456gello7890";
  int c = '5';
  int n = 15;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(num2_with_string) {
  char str[30] = "123456gello7890";
  int c = 'l';
  int n = 15;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(no_find) {
  char str[10] = "hello";
  int c = 'k';
  int n = 6;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(n_zero) {
  char str[] = "hello";
  int c = 'h';
  int n = 0;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

START_TEST(high_byte) {
  unsigned char str[] = {200, 201, 202, 0};
  int c = 201;
  int n = 3;
  ck_assert_ptr_eq(s21_memchr(str, c, n), memchr(str, c, n));
}
END_TEST

Suite* s21_memchr_suite(void) {
  Suite* s = suite_create("s21_memchr");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, hello_zero_byte);
  tcase_add_test(tc, first_symbol);
  tcase_add_test(tc, end_symbol);
  tcase_add_test(tc, repeat_symbol);
  tcase_add_test(tc, num);
  tcase_add_test(tc, num1_with_string);
  tcase_add_test(tc, num2_with_string);
  tcase_add_test(tc, no_find);
  tcase_add_test(tc, n_zero);
  tcase_add_test(tc, high_byte);

  suite_add_tcase(s, tc);
  return s;
}
