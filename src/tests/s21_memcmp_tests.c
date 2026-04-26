#include "tests.h"

START_TEST(zero_byte) {
  char str1[] = "hello";
  char str2[] = "hello";
  int n = 5;
  int s21 = s21_memcmp(str1, str2, n);
  int string = memcmp(str1, str2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(first_byte) {
  char str1[] = "hello";
  char str2[] = "hello";
  int n = 1;
  int s21 = s21_memcmp(str1, str2, n);
  int string = memcmp(str1, str2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(first_byte_in_num) {
  char str1[] = "123456";
  char str2[] = "1";

  s21_size len1 = s21_strlen(str1);
  s21_size len2 = s21_strlen(str2);
  s21_size n = (len1 < len2) ? len1 : len2;

  ck_assert_int_eq(s21_memcmp(str1, str2, n), memcmp(str1, str2, n));
}
END_TEST

START_TEST(byte_in_num) {
  char str1[] = "123456";
  char str2[] = "4";

  s21_size len1 = s21_strlen(str1);
  s21_size len2 = s21_strlen(str2);
  s21_size n = (len1 < len2) ? len1 : len2;

  int s21 = s21_memcmp(str1, str2, n);
  int string = memcmp(str1, str2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(two_byte_long_two_num) {
  char str1[] = "13";
  char str2[] = "1234";
  int n = 2;

  int s21 = s21_memcmp(str1, str2, n);
  int string = memcmp(str1, str2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(two_byte_long_first_num) {
  char str1[] = "134567";
  char str2[] = "1234";
  int n = 2;

  int s21 = s21_memcmp(str1, str2, n);
  int string = memcmp(str1, str2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(n_zero) {
  char str1[] = "abc";
  char str2[] = "xyz";
  int n = 0;

  int s21 = s21_memcmp(str1, str2, n);
  int string = memcmp(str1, str2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(diff_last_byte) {
  char str1[] = "abcde";
  char str2[] = "abcdx";
  int n = 5;

  int s21 = s21_memcmp(str1, str2, n);
  int string = memcmp(str1, str2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

START_TEST(high_bytes) {
  unsigned char str1[] = {200, 201, 202};
  unsigned char str2[] = {200, 200, 202};
  int n = 3;

  int s21 = s21_memcmp(str1, str2, n);
  int string = memcmp(str1, str2, n);

  ck_assert_int_eq(s21, string);
}
END_TEST

Suite* s21_memcmp_suite(void) {
  Suite* s = suite_create("s21_memcmp");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, zero_byte);
  tcase_add_test(tc, first_byte);
  tcase_add_test(tc, first_byte_in_num);
  tcase_add_test(tc, byte_in_num);
  tcase_add_test(tc, two_byte_long_two_num);
  tcase_add_test(tc, two_byte_long_first_num);
  tcase_add_test(tc, n_zero);
  tcase_add_test(tc, diff_last_byte);
  tcase_add_test(tc, high_bytes);

  suite_add_tcase(s, tc);
  return s;
}
