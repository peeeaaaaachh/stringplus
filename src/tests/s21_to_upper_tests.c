#include "tests.h"

START_TEST(hello_world_word) {
  char str1[] = "hello world";
  char res[] = "HELLO WORLD";
  char* res1 = (char*)s21_to_upper(str1);
  ck_assert_str_eq(res1, res);

  free(res1);
}
END_TEST

START_TEST(empty_word) {
  char str1[] = "empty";
  char res[] = "EMPTY";
  char* res1 = (char*)s21_to_upper(str1);
  ck_assert_str_eq(res1, res);

  free(res1);
}
END_TEST

START_TEST(null_input) {
  char* str1 = s21_NULL;
  char* res = (char*)s21_to_upper(str1);
  ck_assert_ptr_eq(res, s21_NULL);
}
END_TEST

START_TEST(num) {
  char str1[] = "111";
  char res[] = "111";
  char* res1 = (char*)s21_to_upper(str1);
  ck_assert_str_eq(res1, res);

  free(res1);
}
END_TEST

START_TEST(empty) {
  char str1[] = " ";
  char res[] = " ";
  char* res1 = (char*)s21_to_upper(str1);
  ck_assert_str_eq(res1, res);

  free(res1);
}
END_TEST

Suite* s21_to_upper_suite(void) {
  Suite* s = suite_create("s21_to_upper");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, hello_world_word);
  tcase_add_test(tc, null_input);
  tcase_add_test(tc, empty_word);
  tcase_add_test(tc, num);
  tcase_add_test(tc, empty);

  suite_add_tcase(s, tc);
  return s;
}
