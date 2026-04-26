#include "tests.h"

START_TEST(find_a) {
  char src[] = "fjdskkfaehweqjd";
  char find = 'a';
  ck_assert_ptr_eq(s21_strrchr(src, find), strrchr(src, find));
}
END_TEST

START_TEST(find_A) {
  char src[] = "dmkasmdDFGwhAdnp";
  char find = 'A';
  ck_assert_ptr_eq(s21_strrchr(src, find), strrchr(src, find));
}
END_TEST

START_TEST(find_1) {
  char src[] = "Hell1o";
  char find = '1';
  ck_assert_ptr_eq(s21_strrchr(src, find), strrchr(src, find));
}
END_TEST

START_TEST(find_2) {
  char src[] = "Hell1o";
  char find = '2';
  ck_assert_ptr_eq(s21_strrchr(src, find), strrchr(src, find));
}
END_TEST

START_TEST(find_P) {
  char src[] = "World";
  char find = 'P';
  ck_assert_ptr_eq(s21_strrchr(src, find), strrchr(src, find));
}
END_TEST

START_TEST(empty) {
  char src[] = "";
  char find = 'A';
  ck_assert_ptr_eq(s21_strrchr(src, find), strrchr(src, find));
}
END_TEST

START_TEST(empty1) {
  char str1[] = "";
  char str2 = '\0';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(house_) {
  char str1[] = "house";
  char str2 = '\0';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

START_TEST(_house) {
  char str1[] = "";
  char str2 = 'h';

  ck_assert_pstr_eq(s21_strrchr(str1, str2), strrchr(str1, str2));
}
END_TEST

Suite* s21_strrchr_suite(void) {
  Suite* s = suite_create("s21_strrchr");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, find_a);
  tcase_add_test(tc, find_A);
  tcase_add_test(tc, find_1);
  tcase_add_test(tc, find_2);
  tcase_add_test(tc, find_P);
  tcase_add_test(tc, empty);
  tcase_add_test(tc, empty1);
  tcase_add_test(tc, house_);
  tcase_add_test(tc, house_);
  tcase_add_test(tc, _house);

  suite_add_tcase(s, tc);
  return s;
}
