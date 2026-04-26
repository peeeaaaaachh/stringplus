#include "tests.h"

START_TEST(empty) {
  char src[] = "";
  char res[] = "";
  ck_assert_ptr_eq(s21_strpbrk(src, res), strpbrk(src, res));
}
END_TEST

START_TEST(_floppy) {
  char src[] = "";
  char res[] = "floppy";

  ck_assert_ptr_eq(s21_strpbrk(src, res), strpbrk(src, res));
}
END_TEST

START_TEST(find_world) {
  char src[] = "kjndfkwenfakworldjkdndsk";
  char res[] = "world";
  ck_assert_ptr_eq(s21_strpbrk(src, res), strpbrk(src, res));
}
END_TEST

START_TEST(find_no_world) {
  char src[] = "kjndfkwenfamsmks";
  char res[] = "world";
  ck_assert_ptr_eq(s21_strpbrk(src, res), strpbrk(src, res));
}
END_TEST

START_TEST(find_big_P) {
  char src[] = "ppppppppppppP";
  char res[] = "P";
  ck_assert_ptr_eq(s21_strpbrk(src, res), strpbrk(src, res));
}
END_TEST

START_TEST(find_num) {
  char src[] = "123";
  char res[] = "123";
  ck_assert_ptr_eq(s21_strpbrk(src, res), strpbrk(src, res));
}
END_TEST

START_TEST(find_no_num) {
  char src[] = "567";
  char res[] = "123";
  ck_assert_ptr_eq(s21_strpbrk(src, res), strpbrk(src, res));
}
END_TEST

START_TEST(find_long_num) {
  char src[] = "905123";
  char res[] = "123";
  ck_assert_ptr_eq(s21_strpbrk(src, res), strpbrk(src, res));
}
END_TEST

START_TEST(find_zero) {
  char src[] = "ppppppppppppP";
  char res[] = "\0";

  ck_assert_pstr_eq(s21_strpbrk(src, res), strpbrk(src, res));
}
END_TEST

START_TEST(find_num_with_letter) {
  char src[] = "abc1284qw";
  char res[] = "84";
  ck_assert_ptr_eq(s21_strpbrk(src, res), strpbrk(src, res));
}
END_TEST

Suite* s21_strpbrk_suite(void) {
  Suite* s = suite_create("s21_strpbrk");
  TCase* tc = tcase_create("core");

  tcase_add_test(tc, empty);
  tcase_add_test(tc, _floppy);
  tcase_add_test(tc, find_world);
  tcase_add_test(tc, find_no_world);
  tcase_add_test(tc, find_big_P);
  tcase_add_test(tc, find_num);
  tcase_add_test(tc, find_no_num);
  tcase_add_test(tc, find_long_num);
  tcase_add_test(tc, find_zero);
  tcase_add_test(tc, find_num_with_letter);

  suite_add_tcase(s, tc);
  return s;
}