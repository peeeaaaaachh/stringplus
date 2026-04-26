#include "tests.h"

#define TEST_SPRINTF(format, ...)           \
  do {                                      \
    char buf1[BUFFER_SIZE] = {0};           \
    char buf2[BUFFER_SIZE] = {0};           \
    s21_sprintf(buf1, format, __VA_ARGS__); \
    sprintf(buf2, format, __VA_ARGS__);     \
    ck_assert_str_eq(buf1, buf2);           \
  } while (0)

#define TEST_SPRINTF_NULL(format, arg)  \
  do {                                  \
    char buf1[BUFFER_SIZE] = {0};       \
    char buf2[BUFFER_SIZE] = {0};       \
    s21_sprintf(buf1, format, arg);     \
    sprintf(buf2, format, (char*)NULL); \
    ck_assert_str_eq(buf1, buf2);       \
  } while (0)

START_TEST(test_basic_string) {
  char buf1[100] = {0}, buf2[100] = {0};
  s21_sprintf(buf1, "Hello, World!");
  sprintf(buf2, "Hello, World!");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_basic_percent) {
  char buf1[100] = {0}, buf2[100] = {0};
  s21_sprintf(buf1, "100%%");
  sprintf(buf2, "100%%");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_integer_basic) {
  TEST_SPRINTF("%d", 42);
  TEST_SPRINTF("%d", -42);
  TEST_SPRINTF("%d", 0);
}
END_TEST

START_TEST(test_integer_limits) {
  TEST_SPRINTF("%d", INT_MAX);
  TEST_SPRINTF("%d", INT_MIN);
  TEST_SPRINTF("%lld", LLONG_MAX);
  TEST_SPRINTF("%lld", LLONG_MIN);
}
END_TEST

START_TEST(test_integer_flags) {
  TEST_SPRINTF("%+d", 42);
  TEST_SPRINTF("% d", 42);
  TEST_SPRINTF("%-10d", 42);
  TEST_SPRINTF("%010d", 42);

  TEST_SPRINTF("%+d", -42);
  TEST_SPRINTF("% d", -42);
  TEST_SPRINTF("%-10d", -42);
  TEST_SPRINTF("%010d", -42);

  TEST_SPRINTF("%+-10d", 42);
  TEST_SPRINTF("%+010d", 42);
}
END_TEST

START_TEST(test_integer_precision) {
  TEST_SPRINTF("%.5d", 42);
  TEST_SPRINTF("%.5d", -42);
  TEST_SPRINTF("%.0d", 0);
  TEST_SPRINTF("%.0d", 42);
  TEST_SPRINTF("%10.5d", 42);
#ifndef __linux__
  TEST_SPRINTF("%010.5d", 42);
#endif
}
END_TEST

START_TEST(test_unsigned_basic) {
  TEST_SPRINTF("%u", 42u);
  TEST_SPRINTF("%u", 0u);
  TEST_SPRINTF("%u", UINT_MAX);
}
END_TEST

START_TEST(test_unsigned_flags) {
  TEST_SPRINTF("%10u", 42u);
  TEST_SPRINTF("%-10u", 42u);
  TEST_SPRINTF("%010u", 42u);
  TEST_SPRINTF("%.5u", 42u);
  TEST_SPRINTF("%.0u", 0u);
}
END_TEST

START_TEST(test_hex_basic) {
  TEST_SPRINTF("%x", 255);
  TEST_SPRINTF("%X", 255);
  TEST_SPRINTF("%x", 0);
  TEST_SPRINTF("%X", 0);
}
END_TEST

START_TEST(test_hex_hash) {
  TEST_SPRINTF("%#x", 255);
  TEST_SPRINTF("%#X", 255);
  TEST_SPRINTF("%#x", 0);
  TEST_SPRINTF("%#08x", 255);
  TEST_SPRINTF("%#010x", 0xABC);
}
END_TEST

START_TEST(test_hex_precision) {
  TEST_SPRINTF("%.4x", 255);
  TEST_SPRINTF("%8.4x", 255);
  TEST_SPRINTF("%#8.4x", 255);
  TEST_SPRINTF("%.0x", 0);
}
END_TEST

START_TEST(test_octal_basic) {
  TEST_SPRINTF("%o", 64);
  TEST_SPRINTF("%o", 0);
  TEST_SPRINTF("%o", UINT_MAX);
}
END_TEST

START_TEST(test_octal_hash) {
  TEST_SPRINTF("%#o", 64);
  TEST_SPRINTF("%#o", 0);
  TEST_SPRINTF("%#08o", 63);
  TEST_SPRINTF("%#010o", 0777);
}
END_TEST

#ifndef __linux__
START_TEST(test_string_basic) {
  TEST_SPRINTF("%s", "Hello");
  TEST_SPRINTF("%s", "");

  char buf1[BUFFER_SIZE] = {0}, buf2[BUFFER_SIZE] = {0};

  // Тестируем с пустой строкой
  s21_memset(buf1, 0, BUFFER_SIZE);
  s21_memset(buf2, 0, BUFFER_SIZE);
  s21_sprintf(buf1, "%s", "");
  sprintf(buf2, "%s", "");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST
#endif

START_TEST(test_string_width) {
  TEST_SPRINTF("%10s", "test");
  TEST_SPRINTF("%-10s", "test");
  TEST_SPRINTF("%.3s", "abcdef");
  TEST_SPRINTF("%10.3s", "abcdef");
  TEST_SPRINTF("%-10.3s", "abcdef");
}
END_TEST

START_TEST(test_char_basic) {
  TEST_SPRINTF("%c", 'A');
  TEST_SPRINTF("%c", '\0');
  TEST_SPRINTF("%c", '\n');
  TEST_SPRINTF("%c", 0xFF);
}
END_TEST

START_TEST(test_char_width) {
  TEST_SPRINTF("%5c", 'A');
  TEST_SPRINTF("%-5c", 'A');
  TEST_SPRINTF("%*c", 5, 'A');
  TEST_SPRINTF("%*c", -5, 'A');
}
END_TEST

START_TEST(test_length_h) {
  short s_pos = 32767;
  short s_neg = -32768;
  unsigned short us = 65535;

  TEST_SPRINTF("%hd", s_pos);
  TEST_SPRINTF("%hd", s_neg);
  TEST_SPRINTF("%hu", us);
  TEST_SPRINTF("%hx", us);
  TEST_SPRINTF("%ho", us);
}
END_TEST

START_TEST(test_length_hh) {
  signed char sc_pos = 127;
  signed char sc_neg = -128;
  unsigned char uc = 255;

  TEST_SPRINTF("%hhd", sc_pos);
  TEST_SPRINTF("%hhd", sc_neg);
  TEST_SPRINTF("%hhu", uc);
  TEST_SPRINTF("%hhx", uc);
  TEST_SPRINTF("%hho", uc);
}
END_TEST

START_TEST(test_length_l) {
  long l_pos = 2147483647L;
  long l_neg = -2147483648L;
  unsigned long ul = 4294967295UL;

  TEST_SPRINTF("%ld", l_pos);
  TEST_SPRINTF("%ld", l_neg);
  TEST_SPRINTF("%lu", ul);
  TEST_SPRINTF("%lx", ul);
  TEST_SPRINTF("%lo", ul);
}
END_TEST

START_TEST(test_length_ll) {
  long long ll_pos = 9223372036854775807LL;
  long long ll_neg = -9223372036854775807LL - 1;
  unsigned long long ull = 18446744073709551615ULL;

  TEST_SPRINTF("%lld", ll_pos);
  TEST_SPRINTF("%lld", ll_neg);
  TEST_SPRINTF("%llu", ull);
  TEST_SPRINTF("%llx", ull);
  TEST_SPRINTF("%llo", ull);
}
END_TEST

START_TEST(test_pointer) {
  int x = 42;
  int* ptr = &x;

  char buf1[100] = {0}, buf2[100] = {0};
  s21_sprintf(buf1, "%p", ptr);
  sprintf(buf2, "%p", ptr);

  ck_assert_int_eq(buf1[0], '0');
  ck_assert_int_eq(buf1[1], 'x');
  ck_assert_int_eq(buf2[0], '0');
  ck_assert_int_eq(buf2[1], 'x');
}
END_TEST

START_TEST(test_n_specifier) {
  char buf[100];
  int n1 = 0, n2 = 0;

  s21_sprintf(buf, "Hello%n", &n1);
  sprintf(buf, "Hello%n", &n2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(n1, 5);

  long ln1 = 0, ln2 = 0;
  s21_sprintf(buf, "Test%ln", &ln1);
  sprintf(buf, "Test%ln", &ln2);
  ck_assert_int_eq(ln1, ln2);
}
END_TEST

START_TEST(test_float_basic) {
  TEST_SPRINTF("%f", 123.456);
  TEST_SPRINTF("%f", -123.456);
  TEST_SPRINTF("%f", 0.0);
}
END_TEST

START_TEST(test_float_precision) {
  TEST_SPRINTF("%.2f", 123.456);
  TEST_SPRINTF("%.0f", 123.456);
  TEST_SPRINTF("%.10f", 123.456);
  TEST_SPRINTF("%.0f", 0.0);
  TEST_SPRINTF("%#.0f", 123.456);
}
END_TEST

START_TEST(test_float_width) {
  TEST_SPRINTF("%10.2f", 123.456);
  TEST_SPRINTF("%-10.2f", 123.456);
  TEST_SPRINTF("%010.2f", 123.456);
  TEST_SPRINTF("%+10.2f", 123.456);
  TEST_SPRINTF("% 10.2f", 123.456);
}
END_TEST

START_TEST(test_scientific_basic) {
  TEST_SPRINTF("%e", 123.456);
  TEST_SPRINTF("%E", 123.456);
  TEST_SPRINTF("%e", -123.456);
  TEST_SPRINTF("%e", 0.0);
}
END_TEST

START_TEST(test_scientific_precision) {
  TEST_SPRINTF("%.2e", 123.456);
  TEST_SPRINTF("%.0e", 123.456);
  TEST_SPRINTF("%.10e", 123.456);
}
END_TEST

START_TEST(test_adaptive_basic) {
  TEST_SPRINTF("%g", 123.456);
  TEST_SPRINTF("%G", 123.456);
  TEST_SPRINTF("%g", 0.000123);
  TEST_SPRINTF("%g", 1234567.0);
}
END_TEST

START_TEST(test_adaptive_precision) {
  TEST_SPRINTF("%.2g", 123.456);
  TEST_SPRINTF("%.10g", 0.000123);
  TEST_SPRINTF("%#.2g", 123.0);
}
END_TEST

START_TEST(test_star_width) {
  TEST_SPRINTF("%*d", 10, 42);
  TEST_SPRINTF("%*d", -10, 42);
  TEST_SPRINTF("%*.*d", 10, 5, 42);
  TEST_SPRINTF("%*.*f", 15, 3, 123.456);
}
END_TEST

START_TEST(test_edge_cases) {
  TEST_SPRINTF("%.0d", 0);
  TEST_SPRINTF("%.0u", 0U);
  TEST_SPRINTF("%.0x", 0);
  TEST_SPRINTF("%.0o", 0);

  TEST_SPRINTF("%1000d", 42);

  TEST_SPRINTF("%+-10d", 42);
  TEST_SPRINTF("%+d", 42);
}
END_TEST

START_TEST(test_length_z) {
  size_t st = 12345;
  ssize_t sst = -12345;

  TEST_SPRINTF("%zu", st);
  TEST_SPRINTF("%zx", st);
  TEST_SPRINTF("%zo", st);
  TEST_SPRINTF("%zd", sst);

  TEST_SPRINTF("%10zu", st);
  TEST_SPRINTF("%-10zu", st);
  TEST_SPRINTF("%010zu", st);
  TEST_SPRINTF("%+.10zd", sst);

  char buf[100];
  size_t n1 = 0, n2 = 0;
  s21_sprintf(buf, "test%zn", &n1);
  sprintf(buf, "test%zn", &n2);
  ck_assert_int_eq(n1, n2);
}
END_TEST

START_TEST(test_n_all_lengths) {
  char buf[100];

  signed char c1 = 0, c2 = 0;
  s21_sprintf(buf, "test%hhn", &c1);
  sprintf(buf, "test%hhn", &c2);
  ck_assert_int_eq(c1, c2);

  short s1 = 0, s2 = 0;
  s21_sprintf(buf, "test%hn", &s1);
  sprintf(buf, "test%hn", &s2);
  ck_assert_int_eq(s1, s2);

  long long ll1 = 0, ll2 = 0;
  s21_sprintf(buf, "test%lln", &ll1);
  sprintf(buf, "test%lln", &ll2);
  ck_assert_int_eq(ll1, ll2);
}
END_TEST

START_TEST(test_precision_negative_star) {
  char buf1[100], buf2[100];

  s21_sprintf(buf1, "%.*d", -5, 42);
  sprintf(buf2, "%.*d", -5, 42);
  ck_assert_str_eq(buf1, buf2);

  s21_sprintf(buf1, "%.*s", -3, "hello");
  sprintf(buf2, "%.*s", -3, "hello");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(test_float_special_all) {
  TEST_SPRINTF("%f", INFINITY);
  TEST_SPRINTF("%f", -INFINITY);
  TEST_SPRINTF("%f", NAN);
#ifndef __linux__
  TEST_SPRINTF("%f", -NAN);
#endif

  TEST_SPRINTF("%e", INFINITY);
  TEST_SPRINTF("%e", -INFINITY);
  TEST_SPRINTF("%e", NAN);

  TEST_SPRINTF("%g", INFINITY);
  TEST_SPRINTF("%g", -INFINITY);
  TEST_SPRINTF("%g", NAN);

  TEST_SPRINTF("%f", -0.0);
  TEST_SPRINTF("%+f", -0.0);
  TEST_SPRINTF("%.0f", -0.0);
  TEST_SPRINTF("%#.0f", -0.0);
  TEST_SPRINTF("%e", -0.0);
  TEST_SPRINTF("%g", -0.0);
}
END_TEST

START_TEST(test_float_overflow_rounding) {
  TEST_SPRINTF("%.3f", 999.9995);
  TEST_SPRINTF("%.3f", 1.0004);
}
END_TEST

START_TEST(test_adaptive_zero) {
  TEST_SPRINTF("%#g", 0.0);
  TEST_SPRINTF("%#.2g", 0.0);
  TEST_SPRINTF("%.0g", 0.0);
}
END_TEST

START_TEST(test_width_overflow) {
  char buf1[BUFFER_SIZE], buf2[BUFFER_SIZE];
  s21_sprintf(buf1, "%500d", 42);
  sprintf(buf2, "%500d", 42);
  ck_assert_str_eq(buf1, buf2);

  s21_sprintf(buf1, "%500s", "test");
  sprintf(buf2, "%500s", "test");
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

#ifndef __linux__
START_TEST(test_percent_flag_minus) {
  char buf1[100] = {0}, buf2[100] = {0};
  s21_sprintf(buf1, "%-10%");
  sprintf(buf2, "%-10%");
  ck_assert_str_eq(buf1, buf2);

  char buf3[100] = {0}, buf4[100] = {0};
  s21_sprintf(buf3, "%-5%");
  sprintf(buf4, "%-5%");
  ck_assert_str_eq(buf3, buf4);
}
END_TEST
#endif

START_TEST(test_adaptive_trim_scientific) {
  TEST_SPRINTF("%g", 1.200e-5);
  TEST_SPRINTF("%#g", 1.200e-5);
}
END_TEST

START_TEST(test_long_double_high_precision) {
  TEST_SPRINTF("%.10Lf", 123.456L);
  TEST_SPRINTF("%.10Le", 123.456L);
}
END_TEST

START_TEST(test_long_double_precision_zero) {
  TEST_SPRINTF("%.0Lf", 123.456L);
  TEST_SPRINTF("%.0Le", 123.456L);
}
END_TEST

START_TEST(test_long_double_rounding_carry) {
#ifndef __linux__
  TEST_SPRINTF("%.3Lf", 999.9995L);
#endif
  TEST_SPRINTF("%.3Lf", 1.0004L);
}
END_TEST

START_TEST(test_long_double_flags) {
  TEST_SPRINTF("%+Lf", 123.456L);
  TEST_SPRINTF("% Lf", 123.456L);
  TEST_SPRINTF("%+Le", 123.456L);
  TEST_SPRINTF("% Le", 123.456L);
  TEST_SPRINTF("%+Lf", -123.456L);
}
END_TEST

START_TEST(test_long_double_scientific_edge) {
  TEST_SPRINTF("%Le", 0.0L);
  TEST_SPRINTF("%Le", -0.0L);
  TEST_SPRINTF("%Le", -123.456L);
  TEST_SPRINTF("%Le", 0.000123L);
}
END_TEST

START_TEST(test_long_double_adaptive_edge) {
  TEST_SPRINTF("%Lg", 1.0L / 0.0L);
  TEST_SPRINTF("%Lg", -1.0L / 0.0L);
  TEST_SPRINTF("%Lg", 0.0L);
  TEST_SPRINTF("%Lg", -0.0L);
  TEST_SPRINTF("%Lg", 0.0000123L);
  TEST_SPRINTF("%Lg", 1e10L);
}
END_TEST

START_TEST(test_double_scientific_flags) {
  TEST_SPRINTF("%+e", 123.456);
  TEST_SPRINTF("% e", 123.456);
  TEST_SPRINTF("%.10e", 123.456);
  TEST_SPRINTF("%.5e", 1.23);
}
END_TEST

START_TEST(test_trim_trailing_zeros_edge) {
  TEST_SPRINTF("%g", 1.000e-5);
  TEST_SPRINTF("%g", 123.0);
}
END_TEST

START_TEST(test_double_overflow_rounding) {
  TEST_SPRINTF("%.3f", 999.9995);
  TEST_SPRINTF("%.3f", 1.0004);
}
END_TEST

Suite* s21_sprintf_suite(void) {
  Suite* s = suite_create("s21_sprintf");

  TCase* tc_basic = tcase_create("Basic");
  TCase* tc_integer = tcase_create("Integer");
  TCase* tc_unsigned = tcase_create("Unsigned");
  TCase* tc_hex = tcase_create("Hexadecimal");
  TCase* tc_octal = tcase_create("Octal");
  TCase* tc_string = tcase_create("String");
  TCase* tc_char = tcase_create("Char");
  TCase* tc_length = tcase_create("Length Modifiers");
  TCase* tc_pointer = tcase_create("Pointer");
  TCase* tc_n = tcase_create("N specifier");
  TCase* tc_float = tcase_create("Float");
  TCase* tc_scientific = tcase_create("Scientific");
  TCase* tc_adaptive = tcase_create("Adaptive");
  TCase* tc_star = tcase_create("Star");
  TCase* tc_edge = tcase_create("Edge Cases");

  tcase_add_test(tc_basic, test_basic_string);
  tcase_add_test(tc_basic, test_basic_percent);

  tcase_add_test(tc_integer, test_integer_basic);
  tcase_add_test(tc_integer, test_integer_limits);
  tcase_add_test(tc_integer, test_integer_flags);
  tcase_add_test(tc_integer, test_integer_precision);

  tcase_add_test(tc_unsigned, test_unsigned_basic);
  tcase_add_test(tc_unsigned, test_unsigned_flags);

  tcase_add_test(tc_hex, test_hex_basic);
  tcase_add_test(tc_hex, test_hex_hash);
  tcase_add_test(tc_hex, test_hex_precision);

  tcase_add_test(tc_octal, test_octal_basic);
  tcase_add_test(tc_octal, test_octal_hash);

#ifndef __linux__
  tcase_add_test(tc_string, test_string_basic);
#endif

  tcase_add_test(tc_string, test_string_width);

  tcase_add_test(tc_char, test_char_basic);
  tcase_add_test(tc_char, test_char_width);

  tcase_add_test(tc_length, test_length_h);
  tcase_add_test(tc_length, test_length_hh);
  tcase_add_test(tc_length, test_length_l);
  tcase_add_test(tc_length, test_length_ll);
  tcase_add_test(tc_length, test_length_z);
  tcase_add_test(tc_length, test_n_all_lengths);

  tcase_add_test(tc_pointer, test_pointer);
  tcase_add_test(tc_n, test_n_specifier);

  tcase_add_test(tc_float, test_float_basic);
  tcase_add_test(tc_float, test_float_precision);
  tcase_add_test(tc_float, test_float_width);
  tcase_add_test(tc_float, test_float_special_all);
  tcase_add_test(tc_float, test_float_overflow_rounding);
  tcase_add_test(tc_float, test_adaptive_zero);
  tcase_add_test(tc_float, test_adaptive_trim_scientific);
  tcase_add_test(tc_float, test_long_double_high_precision);
  tcase_add_test(tc_float, test_long_double_precision_zero);
  tcase_add_test(tc_float, test_long_double_rounding_carry);
  tcase_add_test(tc_float, test_long_double_flags);
  tcase_add_test(tc_float, test_long_double_scientific_edge);
  tcase_add_test(tc_float, test_long_double_adaptive_edge);
  tcase_add_test(tc_float, test_double_scientific_flags);
  tcase_add_test(tc_float, test_trim_trailing_zeros_edge);
  tcase_add_test(tc_float, test_double_overflow_rounding);

  tcase_add_test(tc_scientific, test_scientific_basic);
  tcase_add_test(tc_scientific, test_scientific_precision);

  tcase_add_test(tc_adaptive, test_adaptive_basic);
  tcase_add_test(tc_adaptive, test_adaptive_precision);

  tcase_add_test(tc_star, test_star_width);

  tcase_add_test(tc_edge, test_edge_cases);
  tcase_add_test(tc_edge, test_precision_negative_star);
  tcase_add_test(tc_edge, test_width_overflow);

#ifndef __linux__
  tcase_add_test(tc_edge, test_percent_flag_minus);
#endif

  suite_add_tcase(s, tc_basic);
  suite_add_tcase(s, tc_integer);
  suite_add_tcase(s, tc_unsigned);
  suite_add_tcase(s, tc_hex);
  suite_add_tcase(s, tc_octal);
  suite_add_tcase(s, tc_string);
  suite_add_tcase(s, tc_char);
  suite_add_tcase(s, tc_length);
  suite_add_tcase(s, tc_pointer);
  suite_add_tcase(s, tc_n);
  suite_add_tcase(s, tc_float);
  suite_add_tcase(s, tc_scientific);
  suite_add_tcase(s, tc_adaptive);
  suite_add_tcase(s, tc_star);
  suite_add_tcase(s, tc_edge);

  return s;
}