
#include "tests.h"

// ==================== POSITIVE TESTS ====================

START_TEST(test_s21_trim_basic_spaces) {
  const char* src = "  Hello, Strtok!  ";
  const char* trim_chars = " ";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello, Strtok!");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_basic_tabs) {
  const char* src = "\t\tHello, Strtok!\t\t";
  const char* trim_chars = "\t";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello, Strtok!");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_basic_mixed_whitespace) {
  const char* src = " \t \n Hello, Strtok! \n\t ";
  const char* trim_chars = " \t\n";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello, Strtok!");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_multiple_chars) {
  const char* src = "xxyyHello, Strtok!yyxx";
  const char* trim_chars = "xy";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello, Strtok!");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_numbers) {
  const char* src = "123Hello456";
  const char* trim_chars = "0123456789";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_special_chars) {
  const char* src = "!@#Hello$%^";
  const char* trim_chars = "!@#$%^";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_mixed_alnum) {
  const char* src = "abcHello123";
  const char* trim_chars = "abc123";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello");

  free(result);
}
END_TEST

// ==================== EDGE CASES ====================

START_TEST(test_s21_trim_empty_src) {
  const char* src = "";
  const char* trim_chars = " ";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_empty_trim_chars) {
  const char* src = "  Hello  ";
  const char* trim_chars = "";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "  Hello  ");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_both_empty) {
  const char* src = "";
  const char* trim_chars = "";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_nothing_to_trim) {
  const char* src = "Hello";
  const char* trim_chars = " ";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_all_chars_trimmed) {
  const char* src = "aaaaa";
  const char* trim_chars = "a";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_all_chars_trimmed_multiple) {
  const char* src = "abcabc";
  const char* trim_chars = "abc";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_trim_chars_longer) {
  const char* src = "abcHelloabc";
  const char* trim_chars = "abcdefghijklmnopqrstuvwxyz";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "H");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_trim_chars_subset) {
  const char* src = "xyzHellozyx";
  const char* trim_chars = "xyz";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello");

  free(result);
}
END_TEST

// ==================== CORNER CASES ====================

START_TEST(test_s21_trim_only_start) {
  const char* src = "xxxHello";
  const char* trim_chars = "x";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_only_end) {
  const char* src = "Helloxxx";
  const char* trim_chars = "x";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_middle_untouched) {
  const char* src = "xHxexlxloxox";
  const char* trim_chars = "x";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hxexlxloxo");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_complex_middle) {
  const char* src = "aaabbbHelloaaabbb";
  const char* trim_chars = "ab";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_one_char_string) {
  const char* src = "a";
  const char* trim_chars = "a";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_one_char_not_in_trim) {
  const char* src = "a";
  const char* trim_chars = "b";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "a");

  free(result);
}
END_TEST

START_TEST(test_s21_trim_trim_chars_with_duplicates) {
  const char* src = "aaabbbHelloaaabbb";
  const char* trim_chars = "aabb";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_nonnull(result);
  ck_assert_str_eq(result, "Hello");

  free(result);
}
END_TEST

// ==================== s21_NULL TESTS ====================

START_TEST(test_s21_trim_null_src) {
  const char* src = s21_NULL;
  const char* trim_chars = " ";
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_eq(result, s21_NULL);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_null_trim_chars) {
  const char* src = "  Hello  ";
  const char* trim_chars = s21_NULL;
  char* result = s21_trim(src, trim_chars);
  free(result);
}
END_TEST

START_TEST(test_s21_trim_both_null) {
  const char* src = s21_NULL;
  const char* trim_chars = s21_NULL;
  char* result = s21_trim(src, trim_chars);

  ck_assert_ptr_eq(result, s21_NULL);
  free(result);
}
END_TEST

// ==================== ADD TESTS TO SUITE ====================

Suite* s21_trim_suite() {
  Suite* s = suite_create("s21_trim");

  // Группа базовых тестов
  TCase* tc_basic = tcase_create("trim_basic");
  tcase_add_test(tc_basic, test_s21_trim_basic_spaces);
  tcase_add_test(tc_basic, test_s21_trim_basic_tabs);
  tcase_add_test(tc_basic, test_s21_trim_basic_mixed_whitespace);
  tcase_add_test(tc_basic, test_s21_trim_multiple_chars);
  tcase_add_test(tc_basic, test_s21_trim_numbers);
  tcase_add_test(tc_basic, test_s21_trim_special_chars);
  tcase_add_test(tc_basic, test_s21_trim_mixed_alnum);
  suite_add_tcase(s, tc_basic);

  // Группа граничных случаев
  TCase* tc_edge = tcase_create("trim_edge");
  tcase_add_test(tc_edge, test_s21_trim_empty_src);
  tcase_add_test(tc_edge, test_s21_trim_empty_trim_chars);
  tcase_add_test(tc_edge, test_s21_trim_both_empty);
  tcase_add_test(tc_edge, test_s21_trim_nothing_to_trim);
  tcase_add_test(tc_edge, test_s21_trim_all_chars_trimmed);
  tcase_add_test(tc_edge, test_s21_trim_all_chars_trimmed_multiple);
  tcase_add_test(tc_edge, test_s21_trim_trim_chars_longer);
  tcase_add_test(tc_edge, test_s21_trim_trim_chars_subset);
  suite_add_tcase(s, tc_edge);

  // Группа особых случаев
  TCase* tc_corner = tcase_create("trim_corner");
  tcase_add_test(tc_corner, test_s21_trim_only_start);
  tcase_add_test(tc_corner, test_s21_trim_only_end);
  tcase_add_test(tc_corner, test_s21_trim_middle_untouched);
  tcase_add_test(tc_corner, test_s21_trim_complex_middle);
  tcase_add_test(tc_corner, test_s21_trim_one_char_string);
  tcase_add_test(tc_corner, test_s21_trim_one_char_not_in_trim);
  tcase_add_test(tc_corner, test_s21_trim_trim_chars_with_duplicates);
  suite_add_tcase(s, tc_corner);

  // Группа тестов с s21_NULL
  TCase* tc_null = tcase_create("trim_null");
  tcase_add_test(tc_null, test_s21_trim_null_src);
  tcase_add_test(tc_null, test_s21_trim_null_trim_chars);
  tcase_add_test(tc_null, test_s21_trim_both_null);
  suite_add_tcase(s, tc_null);

  return s;
}
