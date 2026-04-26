#include <errno.h>

#include "tests.h"

// ==================== STANDARD ERROR TESTS ====================

START_TEST(test_s21_strerror_eperm) {
  // Operation not permitted
  const char* expected = strerror(EPERM);
  char* actual = s21_strerror(EPERM);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_enofile) {
  // No such file or directory
  const char* expected = strerror(ENOENT);
  char* actual = s21_strerror(ENOENT);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_esrch) {
  // No such process
  const char* expected = strerror(ESRCH);
  char* actual = s21_strerror(ESRCH);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_eintr) {
  // Interrupted system call
  const char* expected = strerror(EINTR);
  char* actual = s21_strerror(EINTR);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_eio) {
  // I/O error
  const char* expected = strerror(EIO);
  char* actual = s21_strerror(EIO);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_enxio) {
  // No such device or address
  const char* expected = strerror(ENXIO);
  char* actual = s21_strerror(ENXIO);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_e2big) {
  // Argument list too long
  const char* expected = strerror(E2BIG);
  char* actual = s21_strerror(E2BIG);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_enomem) {
  // Out of memory
  const char* expected = strerror(ENOMEM);
  char* actual = s21_strerror(ENOMEM);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_eacces) {
  // Permission denied
  const char* expected = strerror(EACCES);
  char* actual = s21_strerror(EACCES);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_efault) {
  // Bad address
  const char* expected = strerror(EFAULT);
  char* actual = s21_strerror(EFAULT);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_ebusy) {
  // Device or resource busy
  const char* expected = strerror(EBUSY);
  char* actual = s21_strerror(EBUSY);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_eexist) {
  // File exists
  const char* expected = strerror(EEXIST);
  char* actual = s21_strerror(EEXIST);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_enotdir) {
  // Not a directory
  const char* expected = strerror(ENOTDIR);
  char* actual = s21_strerror(ENOTDIR);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_eisdir) {
  // Is a directory
  const char* expected = strerror(EISDIR);
  char* actual = s21_strerror(EISDIR);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_einval) {
  // Invalid argument
  const char* expected = strerror(EINVAL);
  char* actual = s21_strerror(EINVAL);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_emfile) {
  // Too many open files
  const char* expected = strerror(EMFILE);
  char* actual = s21_strerror(EMFILE);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_efbig) {
  // File too large
  const char* expected = strerror(EFBIG);
  char* actual = s21_strerror(EFBIG);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_enospc) {
  // No space left on device
  const char* expected = strerror(ENOSPC);
  char* actual = s21_strerror(ENOSPC);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_espipe) {
  // Broken pipe
  const char* expected = strerror(ESPIPE);
  char* actual = s21_strerror(ESPIPE);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_erofs) {
  // Read-only file system
  const char* expected = strerror(EROFS);
  char* actual = s21_strerror(EROFS);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_epipe) {
  // Broken pipe
  const char* expected = strerror(EPIPE);
  char* actual = s21_strerror(EPIPE);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

// ==================== BOUNDARY TESTS ====================

START_TEST(test_s21_strerror_zero) {
  // Error 0 обычно "Success" или "Undefined error"
  const char* expected = strerror(0);
  char* actual = s21_strerror(0);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

// ==================== UNKNOWN ERROR TESTS ====================

START_TEST(test_s21_strerror_unknown_positive) {
  // Неизвестный положительный номер ошибки
  int unknown_err = 9999;

  const char* expected = strerror(unknown_err);
  char* actual = s21_strerror(unknown_err);

  // Обе функции должны вернуть одинаковое сообщение об ошибке
  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_unknown_negative) {
  // Отрицательный номер ошибки
  int unknown_err = -1;

  const char* expected = strerror(unknown_err);
  char* actual = s21_strerror(unknown_err);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

START_TEST(test_s21_strerror_unknown_large) {
  // Очень большой номер ошибки
  int unknown_err = 999999;

  const char* expected = strerror(unknown_err);
  char* actual = s21_strerror(unknown_err);

  ck_assert_ptr_nonnull(actual);
  ck_assert_str_eq(actual, expected);
}
END_TEST

// ==================== RANGE TESTS ====================

START_TEST(test_s21_strerror_range_0_10) {
  // Тестируем первые 10 кодов ошибок
  for (int i = 0; i < 10; i++) {
    const char* expected = strerror(i);
    char* actual = s21_strerror(i);

    ck_assert_ptr_nonnull(actual);
    ck_assert_str_eq(actual, expected);
  }
}
END_TEST

START_TEST(test_s21_strerror_range_100_110) {
  // Тестируем диапазон 100-110
  for (int i = 100; i <= 110; i++) {
    const char* expected = strerror(i);
    char* actual = s21_strerror(i);

    ck_assert_ptr_nonnull(actual);
    ck_assert_str_eq(actual, expected);
  }
}
END_TEST

START_TEST(test_s21_strerror_range_1000_1010) {
  // Тестируем диапазон 1000-1010
  for (int i = 1000; i <= 1010; i++) {
    const char* expected = strerror(i);
    char* actual = s21_strerror(i);

    ck_assert_ptr_nonnull(actual);
    ck_assert_str_eq(actual, expected);
  }
}
END_TEST

// ==================== CONSISTENCY TESTS ====================

START_TEST(test_s21_strerror_same_pointer_for_same_error) {
  // Проверяем, что для одного номера возвращается тот же указатель
  char* first = s21_strerror(EINVAL);
  char* second = s21_strerror(EINVAL);

  ck_assert_ptr_eq(first, second);
}
END_TEST

START_TEST(test_s21_strerror_different_pointers_for_different_errors) {
  // Проверяем, что для разных номеров возвращаются разные указатели
  char* error1 = s21_strerror(EINVAL);
  char* error2 = s21_strerror(ENOENT);

  ck_assert_ptr_ne(error1, error2);
}
END_TEST

// ==================== PLATFORM SPECIFIC TESTS ====================

#ifdef __linux__
// Дополнительные коды ошибок Linux
START_TEST(test_s21_strerror_linux_specific) {
  // Linux имеет дополнительные коды ошибок
  const int linux_errors[] = {ECANCELED, EOWNERDEAD, ENOTRECOVERABLE, ERFKILL,
                              EHWPOISON,  // Некоторые версии
                              0};

  for (int i = 0; linux_errors[i] != 0; i++) {
    int err = linux_errors[i];
    const char* expected = strerror(err);
    char* actual = s21_strerror(err);

    ck_assert_ptr_nonnull(actual);
    ck_assert_str_eq(actual, expected);
  }
}
END_TEST
#endif

#if defined(__APPLE__) && defined(__MACH__)
// Дополнительные коды ошибок macOS
START_TEST(test_s21_strerror_macos_specific) {
  // macOS имеет свои специфичные коды
  const int macos_errors[] = {EPROCLIM,     EUSERS,       EBADRPC,
                              ERPCMISMATCH, EPROGUNAVAIL, 0};

  for (int i = 0; macos_errors[i] != 0; i++) {
    int err = macos_errors[i];
    const char* expected = strerror(err);
    char* actual = s21_strerror(err);

    ck_assert_ptr_nonnull(actual);
    ck_assert_str_eq(actual, expected);
  }
}
END_TEST
#endif

// ==================== ADD TESTS TO SUITE ====================

Suite* s21_strerror_suite() {
  Suite* s = suite_create("s21_strerror");

  // Группа стандартных ошибок
  TCase* tc_standard = tcase_create("strerror_standard");
  tcase_add_test(tc_standard, test_s21_strerror_eperm);
  tcase_add_test(tc_standard, test_s21_strerror_enofile);
  tcase_add_test(tc_standard, test_s21_strerror_esrch);
  tcase_add_test(tc_standard, test_s21_strerror_eintr);
  tcase_add_test(tc_standard, test_s21_strerror_eio);
  tcase_add_test(tc_standard, test_s21_strerror_enxio);
  tcase_add_test(tc_standard, test_s21_strerror_e2big);
  tcase_add_test(tc_standard, test_s21_strerror_enomem);
  tcase_add_test(tc_standard, test_s21_strerror_eacces);
  tcase_add_test(tc_standard, test_s21_strerror_efault);
  tcase_add_test(tc_standard, test_s21_strerror_ebusy);
  tcase_add_test(tc_standard, test_s21_strerror_eexist);
  tcase_add_test(tc_standard, test_s21_strerror_enotdir);
  tcase_add_test(tc_standard, test_s21_strerror_eisdir);
  tcase_add_test(tc_standard, test_s21_strerror_einval);
  tcase_add_test(tc_standard, test_s21_strerror_emfile);
  tcase_add_test(tc_standard, test_s21_strerror_efbig);
  tcase_add_test(tc_standard, test_s21_strerror_enospc);
  tcase_add_test(tc_standard, test_s21_strerror_espipe);
  tcase_add_test(tc_standard, test_s21_strerror_erofs);
  tcase_add_test(tc_standard, test_s21_strerror_epipe);
  suite_add_tcase(s, tc_standard);

  // Группа граничных значений
  TCase* tc_boundary = tcase_create("strerror_boundary");
  tcase_add_test(tc_boundary, test_s21_strerror_zero);
  suite_add_tcase(s, tc_boundary);

  // Группа неизвестных ошибок
  TCase* tc_unknown = tcase_create("strerror_unknown");
  tcase_add_test(tc_unknown, test_s21_strerror_unknown_positive);
  tcase_add_test(tc_unknown, test_s21_strerror_unknown_negative);
  tcase_add_test(tc_unknown, test_s21_strerror_unknown_large);
  suite_add_tcase(s, tc_unknown);

  // Группа диапазонов
  TCase* tc_range = tcase_create("strerror_range");
  tcase_add_test(tc_range, test_s21_strerror_range_0_10);
  tcase_add_test(tc_range, test_s21_strerror_range_100_110);
  tcase_add_test(tc_range, test_s21_strerror_range_1000_1010);
  suite_add_tcase(s, tc_range);

  // Группа консистентности
  TCase* tc_consistency = tcase_create("strerror_consistency");
  tcase_add_test(tc_consistency, test_s21_strerror_same_pointer_for_same_error);
  tcase_add_test(tc_consistency,
                 test_s21_strerror_different_pointers_for_different_errors);
  suite_add_tcase(s, tc_consistency);

// Группа платформозависимых тестов
#ifdef __linux__
  TCase* tc_linux = tcase_create("strerror_linux");
  tcase_add_test(tc_linux, test_s21_strerror_linux_specific);
  suite_add_tcase(s, tc_linux);
#endif

#if defined(__APPLE__) && defined(__MACH__)
  TCase* tc_macos = tcase_create("strerror_macos");
  tcase_add_test(tc_macos, test_s21_strerror_macos_specific);
  suite_add_tcase(s, tc_macos);
#endif

  return s;
}
