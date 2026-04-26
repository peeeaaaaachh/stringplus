#include "tests.h"

START_TEST(second_word) {
  char src[] = "Hello ";
  char str[] = "world";
  s21_size index = 6;
  char res[] = "Hello world";
  char* got = (char*)s21_insert(src, str, index);
  ck_assert_str_eq(got, res);
  free(got);
}
END_TEST

START_TEST(word) {
  char src[] = "world";
  char str[] = "Hello ";
  s21_size index = 0;
  char res[] = "Hello world";
  char* got = (char*)s21_insert(src, str, index);
  ck_assert_str_eq(got, res);
  free(got);
}
END_TEST

START_TEST(third_word) {
  char src[] = "Hello . It's my project!";
  char str[] = "world";
  s21_size index = 6;
  char res[] = "Hello world. It's my project!";
  char* got = (char*)s21_insert(src, str, index);
  ck_assert_str_eq(got, res);
  free(got);
}
END_TEST

START_TEST(emtpy) {
  char src[] = "";
  char str[] = "";
  s21_size index = 10;
  char* got = (char*)s21_insert(src, str, index);
  ck_assert_ptr_eq(got, s21_NULL);
  free(got);
}
END_TEST

START_TEST(no_index) {
  char src[] = "hello test";
  char str[] = "123";
  s21_size index = 100;
  char* got = (char*)s21_insert(src, str, index);
  ck_assert_ptr_eq(got, s21_NULL);
  free(got);
}
END_TEST

START_TEST(num) {
  char src[] = "1234";
  char str[] = "56789";
  s21_size index = 4;
  char res[] = "123456789";
  char* got = (char*)s21_insert(src, str, index);
  ck_assert_str_eq(got, res);
  free(got);
}
END_TEST

START_TEST(num_2) {
  char src[] = "1234";
  char str[] = "";
  s21_size index = 2;
  char res[] = "1234";
  char* got = (char*)s21_insert(src, str, index);
  ck_assert_str_eq(got, res);
  free(got);
}
END_TEST

START_TEST(null) {
  char* src = s21_NULL;
  char str[] = "";
  s21_size index = 10;
  char* got = (char*)s21_insert(src, str, index);
  ck_assert_ptr_eq(got, s21_NULL);
  free(got);
}
END_TEST

START_TEST(null_2) {
  char src[] = "hello";
  char* str = s21_NULL;
  s21_size index = 10;
  char* got = (char*)s21_insert(src, str, index);
  ck_assert_ptr_eq(got, s21_NULL);
  free(got);
}
END_TEST

START_TEST(null_full) {
  char* src = s21_NULL;
  char* str = s21_NULL;
  s21_size index = 10;
  char* got = (char*)s21_insert(src, str, index);
  ck_assert_ptr_eq(got, s21_NULL);
  free(got);
}
END_TEST

START_TEST(one_word) {
  char src[] = "";
  char str[] = "hello";
  s21_size index = 0;
  char res[] = "hello";
  char* got = (char*)s21_insert(src, str, index);
  ck_assert_str_eq(got, res);
  free(got);
}
END_TEST

START_TEST(no_index_2) {
  char src[] = "abc";
  char str[] = "d";
  s21_size index = 4;
  char* got = (char*)s21_insert(src, str, index);
  ck_assert_ptr_eq(got, s21_NULL);
  free(got);
}
END_TEST

Suite* s21_insert_suite(void) {
  Suite* s = suite_create("s21_insert");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, second_word);
  tcase_add_test(tc, word);
  tcase_add_test(tc, third_word);
  tcase_add_test(tc, emtpy);
  tcase_add_test(tc, no_index);
  tcase_add_test(tc, num);
  tcase_add_test(tc, num_2);
  tcase_add_test(tc, null);
  tcase_add_test(tc, null_2);
  tcase_add_test(tc, null_full);
  tcase_add_test(tc, one_word);
  tcase_add_test(tc, no_index_2);

  suite_add_tcase(s, tc);
  return s;
}