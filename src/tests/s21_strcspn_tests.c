#include "tests.h"

START_TEST(empty) {
  char src[] = "";
  char res[] = "";
  ck_assert_int_eq(s21_strcspn(src, res), strcspn(src, res));
}
END_TEST

START_TEST(empty_2) {
  char src[] = "hello";
  char res[] = "";
  ck_assert_int_eq(s21_strcspn(src, res), strcspn(src, res));
}
END_TEST

START_TEST(first_symbol) {
  char src[] = "hello";
  char res[] = "h";
  ck_assert_int_eq(s21_strcspn(src, res), strcspn(src, res));
}
END_TEST

START_TEST(end_symbol) {
  char src[] = "hello";
  char res[] = "o";
  ck_assert_int_eq(s21_strcspn(src, res), strcspn(src, res));
}
END_TEST

START_TEST(find_world) {
  char src[] = "kjndfkwenfakworldjkdndsk";
  char res[] = "world";
  ck_assert_int_eq(s21_strcspn(src, res), strcspn(src, res));
}
END_TEST

START_TEST(find_no_world) {
  char src[] = "kjndfkwenfamsmks";
  char res[] = "world";
  ck_assert_int_eq(s21_strcspn(src, res), strcspn(src, res));
}
END_TEST

START_TEST(find_num) {
  char src[] = "123";
  char res[] = "123";
  ck_assert_int_eq(s21_strcspn(src, res), strcspn(src, res));
}
END_TEST

START_TEST(find_no_num) {
  char src[] = "567";
  char res[] = "123";
  ck_assert_int_eq(s21_strcspn(src, res), strcspn(src, res));
}
END_TEST

START_TEST(find_long_num) {
  char src[] = "905123";
  char res[] = "123";
  ck_assert_int_eq(s21_strcspn(src, res), strcspn(src, res));
}
END_TEST

START_TEST(find_no_long_num) {
  char src[] = "123";
  char res[] = "859657";
  ck_assert_int_eq(s21_strcspn(src, res), strcspn(src, res));
}
END_TEST

START_TEST(find_num_with_letter) {
  char src[] = "abc1284qw";
  char res[] = "84";
  ck_assert_int_eq(s21_strcspn(src, res), strcspn(src, res));
}
END_TEST

Suite* s21_strcspn_suite(void) {
  Suite* s = suite_create("s21_strcspn");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, empty_2);
  tcase_add_test(tc, first_symbol);
  tcase_add_test(tc, end_symbol);
  tcase_add_test(tc, find_world);
  tcase_add_test(tc, find_no_world);
  tcase_add_test(tc, find_num);
  tcase_add_test(tc, find_no_num);
  tcase_add_test(tc, find_long_num);
  tcase_add_test(tc, find_no_long_num);
  tcase_add_test(tc, find_num_with_letter);

  suite_add_tcase(s, tc);
  return s;
}
