#include "tests.h"

START_TEST(empty) {
  char src[] = "";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(Hello_world) {
  char src[] = "Hello world";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(num) {
  char src[] = "1234567890";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(num_word) {
  char src[] = "1234Hello56789";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

START_TEST(Program_) {
  char src[] = "Program_";
  ck_assert_int_eq(s21_strlen(src), strlen(src));
}
END_TEST

Suite* s21_strlen_suite(void) {
  Suite* s = suite_create("s21_strlen");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, Hello_world);
  tcase_add_test(tc, num);
  tcase_add_test(tc, num_word);
  tcase_add_test(tc, Program_);

  suite_add_tcase(s, tc);
  return s;
}
