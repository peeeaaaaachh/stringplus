#include <check.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../s21_string.h"

int main(void) {
  Suite* s = suite_create("s21_string");
  Suite* s1 = s21_strlen_suite();
  Suite* s2 = s21_strchr_suite();
  Suite* s3 = s21_strcspn_suite();
  Suite* s4 = s21_strpbrk_suite();
  Suite* s5 = s21_strrchr_suite();
  Suite* s6 = s21_strncat_suite();
  Suite* s7 = s21_strncpy_suite();
  Suite* s8 = s21_strncmp_suite();
  Suite* s9 = s21_memchr_suite();
  Suite* s10 = s21_memcmp_suite();
  Suite* s11 = s21_memcpy_suite();
  Suite* s12 = s21_memset_suite();
  Suite* s13 = s21_to_upper_suite();
  Suite* s14 = s21_to_lower_suite();
  Suite* s15 = s21_insert_suite();
  Suite* s16 = s21_strerror_suite();
  Suite* s17 = s21_strtok_suite();
  Suite* s18 = s21_trim_suite();
  Suite* s19 = s21_strstr_suite();
  Suite* s20 = s21_sscanf_suite();
  Suite* s21 = s21_sprintf_suite();

  SRunner* sr = srunner_create(s);
  srunner_add_suite(sr, s1);
  srunner_add_suite(sr, s2);
  srunner_add_suite(sr, s3);
  srunner_add_suite(sr, s4);
  srunner_add_suite(sr, s5);
  srunner_add_suite(sr, s6);
  srunner_add_suite(sr, s7);
  srunner_add_suite(sr, s8);
  srunner_add_suite(sr, s9);
  srunner_add_suite(sr, s10);
  srunner_add_suite(sr, s11);
  srunner_add_suite(sr, s12);
  srunner_add_suite(sr, s13);
  srunner_add_suite(sr, s14);
  srunner_add_suite(sr, s15);
  srunner_add_suite(sr, s16);
  srunner_add_suite(sr, s17);
  srunner_add_suite(sr, s18);
  srunner_add_suite(sr, s19);
  srunner_add_suite(sr, s20);
  srunner_add_suite(sr, s21);

  srunner_run_all(sr, CK_NORMAL);
  int failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return failed;
}