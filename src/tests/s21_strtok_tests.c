
#include "tests.h"

// ==================== BASIC TESTS ====================

START_TEST(test_s21_strtok_basic_single_delim) {
  char str1[] = "Hello,Strtok,Test";
  char str2[] = "Hello,Strtok,Test";
  char delim[] = ",";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  // Первый токен
  ck_assert_ptr_nonnull(token1);
  ck_assert_str_eq(token1, "Hello");
  ck_assert_str_eq(token1, token2);

  // Второй токен
  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_ptr_nonnull(token1);
  ck_assert_str_eq(token1, "Strtok");
  ck_assert_str_eq(token1, token2);

  // Третий токен
  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_ptr_nonnull(token1);
  ck_assert_str_eq(token1, "Test");
  ck_assert_str_eq(token1, token2);

  // Больше нет токенов
  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_ptr_eq(token1, s21_NULL);
  ck_assert_ptr_eq(token2, s21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_basic_multiple_delims) {
  char str1[] = "Hello, Strtok; Test";
  char str2[] = "Hello, Strtok; Test";
  char delim[] = ",; ";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  ck_assert_str_eq(token1, "Hello");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Strtok");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Test");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_ptr_eq(token1, s21_NULL);
  ck_assert_ptr_eq(token2, s21_NULL);
}
END_TEST

// ==================== EDGE CASES ====================

START_TEST(test_s21_strtok_consecutive_delimiters) {
  char str1[] = "Hello,,Strtok,,Test";
  char str2[] = "Hello,,Strtok,,Test";
  char delim[] = ",";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  // Должны пропускать пустые токены
  ck_assert_str_eq(token1, "Hello");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Strtok");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Test");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_ptr_eq(token1, s21_NULL);
  ck_assert_ptr_eq(token2, s21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_multiple_consecutive_delims) {
  char str1[] = "Hello,,,,Strtok,,,Test";
  char str2[] = "Hello,,,,Strtok,,,Test";
  char delim[] = ",";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  ck_assert_str_eq(token1, "Hello");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Strtok");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Test");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_s21_strtok_delimiters_at_start) {
  char str1[] = ",,,Hello,Strtok";
  char str2[] = ",,,Hello,Strtok";
  char delim[] = ",";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  // Должен пропустить начальные разделители
  ck_assert_str_eq(token1, "Hello");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Strtok");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_ptr_eq(token1, s21_NULL);
  ck_assert_ptr_eq(token2, s21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_delimiters_at_end) {
  char str1[] = "Hello,Strtok,,,";
  char str2[] = "Hello,Strtok,,,";
  char delim[] = ",";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  ck_assert_str_eq(token1, "Hello");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Strtok");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_ptr_eq(token1, s21_NULL);
  ck_assert_ptr_eq(token2, s21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_all_delimiters) {
  char str1[] = ",,,,";
  char str2[] = ",,,,";
  char delim[] = ",";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  // Строка из одних разделителей должна вернуть s21_NULL
  ck_assert_ptr_eq(token1, s21_NULL);
  ck_assert_ptr_eq(token2, s21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_empty_string) {
  char str1[] = "";
  char str2[] = "";
  char delim[] = ",";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  ck_assert_ptr_eq(token1, s21_NULL);
  ck_assert_ptr_eq(token2, s21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_empty_delim) {
  char str1[] = "Hello,Strtok";
  char str2[] = "Hello,Strtok";
  char delim[] = "";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  // С пустым разделителем должна вернуться вся строка
  ck_assert_str_eq(token1, "Hello,Strtok");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_ptr_eq(token1, s21_NULL);
  ck_assert_ptr_eq(token2, s21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_single_char_string) {
  char str1[] = "a";
  char str2[] = "a";
  char delim[] = ",";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  ck_assert_str_eq(token1, "a");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_ptr_eq(token1, s21_NULL);
  ck_assert_ptr_eq(token2, s21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_single_char_is_delim) {
  char str1[] = "a";
  char str2[] = "a";
  char delim[] = "a";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  ck_assert_ptr_eq(token1, s21_NULL);
  ck_assert_ptr_eq(token2, s21_NULL);
}
END_TEST

// ==================== STATE PRESERVATION TESTS ====================

START_TEST(test_s21_strtok_multiple_calls_different_delims) {
  char str1[] = "Hello,Strtok:Test";
  char str2[] = "Hello,Strtok:Test";
  char delim1[] = ",";
  char delim2[] = ":";

  char* token1 = s21_strtok(str1, delim1);
  char* token2 = strtok(str2, delim1);

  ck_assert_str_eq(token1, "Hello");
  ck_assert_str_eq(token1, token2);

  // Меняем разделитель - должно работать с новым
  token1 = s21_strtok(s21_NULL, delim2);
  token2 = strtok(s21_NULL, delim2);
  ck_assert_str_eq(token1, "Strtok");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim2);
  token2 = strtok(s21_NULL, delim2);
  ck_assert_str_eq(token1, "Test");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_s21_strtok_reset_with_new_string) {
  char str1_first[] = "Hello,Strtok";
  char str2_first[] = "Hello,Strtok";
  char str1_second[] = "Test,Example";
  char str2_second[] = "Test,Example";
  char delim[] = ",";

  // Первая строка
  char* token1 = s21_strtok(str1_first, delim);
  char* token2 = strtok(str2_first, delim);
  ck_assert_str_eq(token1, "Hello");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Strtok");
  ck_assert_str_eq(token1, token2);

  // Начинаем новую строку - состояние должно сброситься
  token1 = s21_strtok(str1_second, delim);
  token2 = strtok(str2_second, delim);
  ck_assert_str_eq(token1, "Test");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Example");
  ck_assert_str_eq(token1, token2);
}
END_TEST

// ==================== STRING MODIFICATION TESTS ====================

START_TEST(test_s21_strtok_original_string_modified) {
  char str[] = "Hello,Strtok,Test";
  char delim[] = ",";

  // Копируем для сравнения
  char original[20];
  strcpy(original, str);
  s21_strtok(str, delim);

  // Проверяем, что исходная строка изменилась
  // После первого токена запятая должна быть заменена на '\0'
  ck_assert_int_eq(str[5], '\0');  // позиция запятой
  ck_assert_str_eq(str,
                   "Hello");  // строка теперь заканчивается на первом токене

  // Сравниваем с оригиналом
  ck_assert_mem_eq(str, original, 5);  // первые 5 символов те же
  ck_assert_int_eq(str[5], '\0');      // 6-й символ стал нулем
  ck_assert_int_eq(original[5], ',');  // в оригинале там запятая
}
END_TEST

// ==================== s21_NULL TESTS ====================

START_TEST(test_s21_strtok_null_str_without_previous) {
  // Вызов с s21_NULL без предыдущего вызова
  char* token = s21_strtok(s21_NULL, ",");
  ck_assert_ptr_eq(token, s21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_null_delim) {
  char str[] = "Hello,Strtok";
  char* token = s21_strtok(str, s21_NULL);

  // Поведение с s21_NULL разделителем может быть разным
  // Обычно это приводит к неопределенному поведению
  // Проверяем, что не падает
  if (token != s21_NULL) {
    // Если не s21_NULL, то должна вернуть всю строку
    ck_assert_str_eq(token, "Hello,Strtok");
  }
}
END_TEST

START_TEST(test_s21_strtok_both_null) {
  char* token = s21_strtok(s21_NULL, s21_NULL);
  ck_assert_ptr_eq(token, s21_NULL);
}
END_TEST

// ==================== COMPLEX TESTS ====================

START_TEST(test_s21_strtok_multiple_delimiters_complex) {
  char str1[] = "  Hello,  Strtok;  Test  ";
  char str2[] = "  Hello,  Strtok;  Test  ";
  char delim[] = " ,;";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  ck_assert_str_eq(token1, "Hello");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Strtok");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Test");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_ptr_eq(token1, s21_NULL);
  ck_assert_ptr_eq(token2, s21_NULL);
}
END_TEST

START_TEST(test_s21_strtok_mixed_delimiters) {
  char str1[] = "Hello, Strtok; Test:Example";
  char str2[] = "Hello, Strtok; Test:Example";
  char delim[] = " ,;:";

  char* token1 = s21_strtok(str1, delim);
  char* token2 = strtok(str2, delim);

  ck_assert_str_eq(token1, "Hello");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Strtok");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Test");
  ck_assert_str_eq(token1, token2);

  token1 = s21_strtok(s21_NULL, delim);
  token2 = strtok(s21_NULL, delim);
  ck_assert_str_eq(token1, "Example");
  ck_assert_str_eq(token1, token2);
}
END_TEST

START_TEST(test_s21_strtok_delimiter_change_midway) {
  char str[] = "Hello,Strtok:Test";
  char delim1[] = ",";
  char delim2[] = ":";

  char* token = s21_strtok(str, delim1);
  ck_assert_str_eq(token, "Hello");

  // Меняем разделитель - должно работать с оставшейся строкой
  token = s21_strtok(s21_NULL, delim2);
  ck_assert_str_eq(token, "Strtok");

  token = s21_strtok(s21_NULL, delim2);
  ck_assert_str_eq(token, "Test");

  token = s21_strtok(s21_NULL, delim2);
  ck_assert_ptr_eq(token, s21_NULL);
}
END_TEST

// ==================== ADD TESTS TO SUITE ====================

Suite* s21_strtok_suite() {
  Suite* s = suite_create("s21_strtok");

  // Группа базовых тестов
  TCase* tc_basic = tcase_create("strtok_basic");
  tcase_add_test(tc_basic, test_s21_strtok_basic_single_delim);
  tcase_add_test(tc_basic, test_s21_strtok_basic_multiple_delims);
  suite_add_tcase(s, tc_basic);

  // Группа граничных случаев
  TCase* tc_edge = tcase_create("strtok_edge");
  tcase_add_test(tc_edge, test_s21_strtok_consecutive_delimiters);
  tcase_add_test(tc_edge, test_s21_strtok_multiple_consecutive_delims);
  tcase_add_test(tc_edge, test_s21_strtok_delimiters_at_start);
  tcase_add_test(tc_edge, test_s21_strtok_delimiters_at_end);
  tcase_add_test(tc_edge, test_s21_strtok_all_delimiters);
  tcase_add_test(tc_edge, test_s21_strtok_empty_string);
  tcase_add_test(tc_edge, test_s21_strtok_empty_delim);
  tcase_add_test(tc_edge, test_s21_strtok_single_char_string);
  tcase_add_test(tc_edge, test_s21_strtok_single_char_is_delim);
  suite_add_tcase(s, tc_edge);

  // Группа тестов состояния
  TCase* tc_state = tcase_create("strtok_state");
  tcase_add_test(tc_state, test_s21_strtok_multiple_calls_different_delims);
  tcase_add_test(tc_state, test_s21_strtok_reset_with_new_string);
  tcase_add_test(tc_state, test_s21_strtok_delimiter_change_midway);
  suite_add_tcase(s, tc_state);

  // Группа тестов модификации строки
  TCase* tc_modify = tcase_create("strtok_modify");
  tcase_add_test(tc_modify, test_s21_strtok_original_string_modified);
  suite_add_tcase(s, tc_modify);

  // Группа тестов с s21_NULL
  TCase* tc_null = tcase_create("strtok_null");
  tcase_add_test(tc_null, test_s21_strtok_null_str_without_previous);
  tcase_add_test(tc_null, test_s21_strtok_null_delim);
  tcase_add_test(tc_null, test_s21_strtok_both_null);
  suite_add_tcase(s, tc_null);

  // Группа сложных тестов
  TCase* tc_complex = tcase_create("strtok_complex");
  tcase_add_test(tc_complex, test_s21_strtok_multiple_delimiters_complex);
  tcase_add_test(tc_complex, test_s21_strtok_mixed_delimiters);
  suite_add_tcase(s, tc_complex);

  return s;
}
