#include "tests.h"

START_TEST(empty) {
  char dest1[10] = "";
  char dest2[10] = "";
  char src[] = "";
  s21_size n = 5;
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(empty_2) {
  char dest1[30] = "";
  char dest2[30] = "";
  char src[] = "Hello";
  s21_size n = 3;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(n_bigger) {
  char dest1[30] = "Hello";
  char dest2[30] = "Hello";
  char src[] = "Hi";
  s21_size n = 10;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(one_symbol) {
  char dest1[10] = "Hi";
  char dest2[10] = "Hi";
  char src[] = "A";
  s21_size n = 1;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(src_shorter) {
  char dest1[30] = "Test";
  char dest2[30] = "Test";
  char src[] = "OK";
  s21_size n = 5;

  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(zero_byte) {
  char dest1[10] = "";
  char dest2[10] = "";
  char src[] = "";
  s21_size n = 0;
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(Hello_world) {
  char dest1[30] = "Hello";
  char dest2[30] = "Hello";
  char src[] = "World";
  s21_size n = 5;
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(Hello) {
  char dest1[30] = "Hello";
  char dest2[30] = "Hello";
  char src[] = "World";
  s21_size n = 0;
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(HELLO) {
  char dest1[30] = "HELLO";
  char dest2[30] = "HELLO";
  char src[] = "WORLD";
  s21_size n = 5;
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(word) {
  char dest1[30] = "jkdfhwkejjds";
  char dest2[30] = "jkdfhwkejjds";
  char src[] = "lalalalalalala";
  s21_size n = 10;
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

START_TEST(word1) {
  char dest1[30] = "jkdfhwkejjds";
  char dest2[30] = "jkdfhwkejjds";
  char src[] = "lalalalalalala";
  s21_size n = 1;
  s21_strncat(dest1, src, n);
  strncat(dest2, src, n);

  ck_assert_str_eq(dest1, dest2);
}
END_TEST

Suite* s21_strncat_suite(void) {
  Suite* s = suite_create("s21_strncat");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, empty_2);
  tcase_add_test(tc, n_bigger);
  tcase_add_test(tc, one_symbol);
  tcase_add_test(tc, src_shorter);
  tcase_add_test(tc, zero_byte);
  tcase_add_test(tc, Hello_world);
  tcase_add_test(tc, Hello);
  tcase_add_test(tc, HELLO);
  tcase_add_test(tc, word);
  tcase_add_test(tc, word1);

  suite_add_tcase(s, tc);
  return s;
}
