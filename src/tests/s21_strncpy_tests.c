#include "tests.h"

START_TEST(empty) {
  char dest1[] = "";
  char dest2[] = "";
  char src[] = "";
  s21_size n = 0;
  s21_strncpy(dest1, src, n);
  strncpy(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(zero_byte) {
  char dest1[10] = "123";
  char dest2[10] = "123";
  char src[] = "4";
  s21_size n = 0;
  s21_strncpy(dest1, src, n);
  strncpy(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(n_equal_src_len) {
  char dest1[10] = "abcdef";
  char dest2[10] = "abcdef";

  char src[] = "hi";
  s21_size n = 2;

  s21_strncpy(dest1, src, n);
  strncpy(dest2, src, n);
  ck_assert_mem_eq(dest1, dest2, n);
}
END_TEST

START_TEST(src_shorter) {
  char dest1[10] = "123";
  char dest2[10] = "123";

  char src[] = "hi";
  s21_size n = 6;

  s21_strncpy(dest1, src, n);
  strncpy(dest2, src, n);

  ck_assert_mem_eq(dest1, dest2, 10);
}
END_TEST

START_TEST(one_byte) {
  char dest1[10] = "123";
  char dest2[10] = "123";
  char src[] = "abc";
  s21_size n = 1;
  s21_strncpy(dest1, src, n);
  strncpy(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(two_byte) {
  char dest1[10] = "123";
  char dest2[10] = "123";
  char src[] = "abc";
  s21_size n = 2;
  s21_strncpy(dest1, src, n);
  strncpy(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(string) {
  char dest1[15] = "world";
  char dest2[15] = "world";
  char src[] = "hello";
  s21_size n = 3;
  s21_strncpy(dest1, src, n);
  strncpy(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(string2) {
  char dest1[20] = "he1lo";
  char dest2[20] = "he1lo";
  char src[] = "lalalalalalalalala";
  s21_size n = 10;
  s21_strncpy(dest1, src, n);
  strncpy(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

Suite* s21_strncpy_suite(void) {
  Suite* s = suite_create("s21_strncpy");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, zero_byte);
  tcase_add_test(tc, n_equal_src_len);
  tcase_add_test(tc, src_shorter);
  tcase_add_test(tc, two_byte);
  tcase_add_test(tc, one_byte);
  tcase_add_test(tc, string);
  tcase_add_test(tc, string2);

  suite_add_tcase(s, tc);
  return s;
}