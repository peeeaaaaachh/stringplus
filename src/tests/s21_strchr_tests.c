#include "tests.h"

START_TEST(find_a) {
  char src[] = "fjdskkfaehweqjd";
  char find = 'a';
  ck_assert_ptr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(find_A) {
  char src[] = "dmkasmdDFGwhAdnp";
  char find = 'A';
  ck_assert_ptr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(find_1) {
  char src[] = "Hell1o";
  char find = '1';
  ck_assert_ptr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(find_2) {
  char src[] = "Hell1o";
  char find = '2';
  ck_assert_ptr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(find_P) {
  char src[] = "World";
  char find = 'P';
  ck_assert_ptr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(find_first_symbol) {
  char src[] = "hello";
  char find = 'h';
  ck_assert_ptr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(empty) {
  char src[] = "";
  char find = 'A';
  ck_assert_ptr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(find_zero) {
  char src[] = "hello";
  char find = '\0';
  ck_assert_ptr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(one_symbol) {
  char src[] = "a";
  char find = 'a';
  ck_assert_ptr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

START_TEST(no_one_symbol) {
  char src[] = "a";
  char find = 'b';
  ck_assert_ptr_eq(s21_strchr(src, find), strchr(src, find));
}
END_TEST

Suite* s21_strchr_suite(void) {
  Suite* s = suite_create("s21_strchr");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, find_a);
  tcase_add_test(tc, find_A);
  tcase_add_test(tc, find_1);
  tcase_add_test(tc, find_2);
  tcase_add_test(tc, find_P);
  tcase_add_test(tc, find_first_symbol);
  tcase_add_test(tc, empty);
  tcase_add_test(tc, find_zero);
  tcase_add_test(tc, one_symbol);
  tcase_add_test(tc, no_one_symbol);

  suite_add_tcase(s, tc);
  return s;
}
