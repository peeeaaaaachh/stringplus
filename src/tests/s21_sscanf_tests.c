#include "tests.h"
/*

MAIN TESTS

*/
START_TEST(no_lines) {
  int res1 = s21_sscanf("NULL", "NULL");
  int res2 = sscanf("NULL", "NULL");
  int res3 = s21_sscanf("123", "NULL");
  int res4 = sscanf("123", "NULL");

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(res3, res4);
}
END_TEST

#ifndef __linux__
START_TEST(invalid_spec) {
  int a1 = 0, a2 = 0;

  int res1 = s21_sscanf("123", "%m", &a1);
  int res2 = sscanf("123", "%b", &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST
#endif

START_TEST(no_percent_fstr) {
  int res1 = s21_sscanf("123", "hello");
  int res2 = sscanf("123", "hello");

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(EOF1) {
  char fstr[] = "%d";
  char str[] = "        ";

  int16_t res1 = s21_sscanf(str, fstr, 0);
  int16_t res2 = sscanf(str, fstr, 100);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(EOF2) {
  char fstr[] = "%d ";
  char str[] = "               ";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1);
  int16_t res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(EOF3) {
  char fstr[] = "%d ";
  char str[] = "  ";
  int16_t a1 = 0, a2 = 0;

  int16_t res1 = s21_sscanf(str, fstr, &a1);
  int16_t res2 = sscanf(str, fstr, &a2);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(EOF4) {
  int a1 = 0, b1 = 0;
  int a2 = 0, b2 = 0;

  int ret = s21_sscanf("123", "%d %d", &a1, &b1);
  int std_ret = sscanf("123", "%d %d", &a2, &b2);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
}
END_TEST

START_TEST(perc_too_much) {
  const char str[] = "%%";
  const char fstr[] = "%%";

  int32_t res1 = s21_sscanf(str, fstr);
  int32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(perc_not_enough) {
  const char str[] = "%";
  const char fstr[] = "%%%%";

  int32_t res1 = s21_sscanf(str, fstr);
  int32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(perc2) {
  int32_t a1 = 0, a2 = 0;

  const char str[] = "%%16";
  const char fstr[] = "%%%%%d";
  int32_t res1 = s21_sscanf(str, fstr, &a1);
  int32_t res2 = sscanf(str, fstr, &a2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
}
END_TEST

START_TEST(perc3) {
  const char str[] = "%%%";
  const char fstr[] = "%%%%%%";
  int32_t res1 = s21_sscanf(str, fstr);
  int32_t res2 = sscanf(str, fstr);

  ck_assert_int_eq(res1, res2);
}
END_TEST
/*

%c TESTS

*/
START_TEST(c_basic) {
  char buf = 'X';
  char std_buf = 'X';

  int ret = s21_sscanf("A", "%c", &buf);
  int std_ret = sscanf("A", "%c", &std_buf);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(buf, std_buf);
}
END_TEST

START_TEST(c_whitespace) {
  char buf = 'X';
  int ret = s21_sscanf(" A", "%c", &buf);

  ck_assert_int_eq(ret, 1);
  ck_assert_int_eq(buf, ' ');
}
END_TEST

START_TEST(c_whitespace_n) {
  char buf = 'X';
  char std_buf = 'X';

  int ret = s21_sscanf("\nA", "%c", &buf);
  int std_ret = sscanf("\nA", "%c", &std_buf);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(buf, std_buf);
}
END_TEST

START_TEST(c_suppress_basic) {
  char buf = 'X';
  char std_buf = 'X';

  int ret = s21_sscanf("A123", "%*c%c", &buf);
  int std_ret = sscanf("A123", "%*c%c", &std_buf);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(buf, std_buf);
}
END_TEST

START_TEST(c_suppress_width) {
  char buf = 'X';
  char std_buf = 'X';

  int ret = s21_sscanf("AB123", "%*2c%c", &buf);
  int std_ret = sscanf("AB123", "%*2c%c", &std_buf);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(buf, std_buf);
}
END_TEST

START_TEST(c_suppress_fail) {
  int ret = s21_sscanf("123", "%*c");
  int std_ret = sscanf("123", "%*c");

  ck_assert_int_eq(ret, std_ret);
}
END_TEST

START_TEST(c_width_exact) {
  char buf[3] = {'X', 'Y', 'Z'};
  char std_buf[3] = {'X', 'Y', 'Z'};

  int ret = s21_sscanf("AB", "%2c", buf);
  int std_ret = sscanf("AB", "%2c", std_buf);

  ck_assert_int_eq(buf[0], 'A');
  ck_assert_int_eq(buf[1], 'B');
  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(buf[0], std_buf[0]);
  ck_assert_int_eq(buf[1], std_buf[1]);
}
END_TEST

START_TEST(c_biggest_width) {
  char my_buf[3] = {'X', 'Y', 'Z'};
  char std_buf[3] = {'X', 'Y', 'Z'};

  int my_ret = s21_sscanf("A", "%2c", my_buf);
  int std_ret = sscanf("A", "%2c", std_buf);

  ck_assert_int_eq(my_ret, std_ret);
  ck_assert_int_eq(my_buf[0], std_buf[0]);
  ck_assert_int_eq(my_buf[1], std_buf[1]);
  ck_assert_int_eq(my_buf[2], std_buf[2]);
}
END_TEST

START_TEST(c_empty_input) {
  char ch = 'X';
  int ret = s21_sscanf("", "%c", &ch);

  char std_ch = 'X';
  int std_ret = sscanf("", "%c", &std_ch);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(ch, std_ch);
}
END_TEST

START_TEST(c_literal_match) {
  char ch = 'X';
  char std_ch = 'X';

  int ret = s21_sscanf("AX", "%cX", &ch);
  int std_ret = sscanf("AX", "%cX", &std_ch);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(ch, std_ch);
}
END_TEST

START_TEST(c_literal_mismatch) {
  char ch = 'X';
  char std_ch = 'X';

  int ret = s21_sscanf("AY", "%cX", &ch);
  int std_ret = sscanf("AY", "%cX", &std_ch);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(ch, std_ch);
}
END_TEST

START_TEST(c_skipspaces) {
  char a1 = 'x', b1 = 'x', c1 = 'x', a2 = 'x', b2 = 'x', c2 = 'x';

  int ret = s21_sscanf("a b c", "%c%c%c", &a1, &b1, &c1);
  int std_ret = sscanf("a b c", "%c%c%c", &a2, &b2, &c2);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
}
END_TEST
/*

%d TESTS

*/
START_TEST(dec_basic) {
  int val = 0;
  int std_val = 0;

  int ret = s21_sscanf("123", "%d", &val);
  int std_ret = sscanf("123", "%d", &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}
END_TEST

START_TEST(dec_signs) {
  int val = 0;
  int std_val = 0;

  int ret = s21_sscanf("+123", "%d", &val);
  int std_ret = sscanf("+123", "%d", &std_val);
  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);

  ret = s21_sscanf("-123", "%d", &val);
  std_ret = sscanf("-123", "%d", &std_val);
  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}
END_TEST

START_TEST(dec_width1) {
  int val = 0;
  int std_val = 0;

  int ret = s21_sscanf("12345", "%3d", &val);
  int std_ret = sscanf("12345", "%3d", &std_val);
  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}
END_TEST

START_TEST(dec_width2) {
  int val = 0;
  int std_val = 0;

  int ret = s21_sscanf("12345", "%5d", &val);
  int std_ret = sscanf("12345", "%5d", &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}
END_TEST

START_TEST(dec_whitespace) {
  int val = 0;
  int std_val = 0;

  int ret = s21_sscanf(" 123", "%d", &val);
  int std_ret = sscanf(" 123", "%d", &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}
END_TEST

START_TEST(dec_invalid_input1) {
  int val = 0;
  int std_val = 0;

  int ret = s21_sscanf("abc", "%d", &val);
  int std_ret = sscanf("abc", "%d", &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}
END_TEST

START_TEST(dec_invalid_input2) {
  int val = 0;
  int std_val = 0;

  int ret = s21_sscanf("", "%d", &val);
  int std_ret = sscanf("", "%d", &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}
END_TEST

START_TEST(dec_invalid_input3) {
  int val = 0;
  int std_val = 0;

  int ret = s21_sscanf("12ab", "%d", &val);
  int std_ret = sscanf("12ab", "%d", &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}
END_TEST

START_TEST(dec_overflow1) {
  int val = 0;
  int std_val = 0;

  int ret = s21_sscanf("2147483647", "%d", &val);
  int std_ret = sscanf("2147483647", "%d", &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}
END_TEST

START_TEST(dec_overflow2) {
  int val = 0;
  int std_val = 0;

  int ret = s21_sscanf("2147483648", "%d", &val);
  int std_ret = sscanf("2147483648", "%d", &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}
END_TEST

START_TEST(dec_overflow3) {
  int val = 0;
  int std_val = 0;

  int ret = s21_sscanf("-2147483648", "%d", &val);
  int std_ret = sscanf("-2147483648", "%d", &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}
END_TEST

START_TEST(dec_overflow4) {
  int val = 0;
  int std_val = 0;

  int ret = s21_sscanf("+2147483648", "%d", &val);
  int std_ret = sscanf("+2147483648", "%d", &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}
END_TEST

START_TEST(dec_short_int) {
  int16_t a1 = 0, b1 = 0, c1 = 0, d1 = 0;
  int16_t a2 = 0, b2 = 0, c2 = 0, d2 = 0;
  const char str[] = "1337 21 5008 32768";
  const char fstr[] = "%hd %hd %hd %hd";

  int16_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int16_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(dec_long_int) {
  long a1 = 0, b1 = 0, c1 = 0, d1 = 0;
  long a2 = 0, b2 = 0, c2 = 0, d2 = 0;

  const char fstr[] = "%ld %ld %ld %ld";
  const char str[] = "555 666 123 21474836478";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(dec_longlong_int) {
  long long a1 = 0, b1 = 0, c1 = 0, d1 = 0;
  long long a2 = 0, b2 = 0, c2 = 0, d2 = 0;

  const char fstr[] = "%lld %lld %lld %lld";
  const char str[] = "555 666 123 21474836478";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(a1, a2);
  ck_assert_int_eq(b1, b2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(d1, d2);
}
END_TEST
/*

%i TESTS

*/
typedef struct {
  const char* str;
  const char* fmt;
} i_case;

static i_case i_cases[] = {
    {"0", "%i"},   {"123", "%i"}, {"+42", "%i"},    {"-42", "%i"},
    {"075", "%i"}, {"08", "%i"},  {"0x1A", "%i"},   {"-0x10", "%i"},
    {"+", "%i"},   {"-", "%i"},   {"123abc", "%i"}, {"   77", "%i"},
    {"", "%i"},    {"0X", "%i"},  {"0x1f", "%i"},
};

static void run_i_test(const char* str, const char* fmt) {
  int val = 777;
  int std_val = 777;

  int ret = s21_sscanf(str, fmt, &val);
  int std_ret = sscanf(str, fmt, &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_int_eq(val, std_val);
}

START_TEST(test_i_parametrized) {
  run_i_test(i_cases[_i].str, i_cases[_i].fmt);
}
END_TEST
/*


%o TESTS

*/
typedef struct {
  const char* str;
  const char* fmt;
} o_case;

static o_case o_cases[] = {
    {"0", "%o"},      {"7", "%o"},     {"10", "%o"},     {"077", "%o"},
    {"+17", "%o"},    {"-17", "%o"},   {"78", "%o"},     {"01239", "%o"},
    {"123abc", "%o"}, {"   77", "%o"}, {"77   ", "%o"},  {"", "%o"},
    {"0x", "%o"},     {"-0xFF", "%o"}, {"0xABCE", "%o"}, {"0xfAB", "%o"},
};

static void run_o_test(const char* str, const char* fmt) {
  unsigned int val = 777;
  unsigned int std_val = 777;

  int ret = s21_sscanf(str, fmt, &val);
  int std_ret = sscanf(str, fmt, &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_uint_eq(val, std_val);
}

START_TEST(test_o_parametrized) {
  run_o_test(o_cases[_i].str, o_cases[_i].fmt);
}
END_TEST

START_TEST(oct_longlong) {
  unsigned long long a1 = 0, b1 = 0, c1 = 0, d1 = 0, e1 = 0, f1 = 0;
  unsigned long long a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0;
  const char str[] = "0555 022 0000 0123 0 18446744073709551615";
  const char fstr[] = "%llo %llo %llo %llo %llo %llo";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1, &f1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2, &f2);

  ck_assert_uint_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(e1, e2);
  ck_assert_uint_eq(f1, f2);
}
END_TEST

START_TEST(oct_long) {
  unsigned long a1 = 0, b1 = 0, c1 = 0, d1 = 0, e1 = 0, f1 = 0;
  unsigned long a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0;

  const char fstr[] = "%lo %lo %lo %lo %lo %lo";
  const char str[] = "0555 022 000 0123 0 18446744073709551615";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1, &f1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2, &f2);

  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(e1, e2);
  ck_assert_uint_eq(f1, f2);
}
END_TEST

START_TEST(oct_short) {
  unsigned short a1 = 0, b1 = 0, c1 = 0, d1 = 0, e1 = 0, f1 = 0;
  unsigned short a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0;

  const char fstr[] = "%ho %ho %ho %ho %ho %ho";
  const char str[] = "0555 022 033 0123 0 32767";

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1, &f1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2, &f2);

  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(e1, e2);
  ck_assert_uint_eq(f1, f2);
}
END_TEST
/*

%s TESTS

*/
START_TEST(sscanf_spec_s_basic) {
  char b1[100] = {0}, b2[100] = {0};
  const char* input = "Hello world";
  const char* fmt = "%s %s";

  int res = sscanf(input, fmt, b1, b2);
  int s21_res = s21_sscanf(input, fmt, b1, b2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_str_eq(b1, "Hello");
  ck_assert_str_eq(b2, "world");
}
END_TEST

START_TEST(sscanf_spec_s_width) {
  char b1[5] = {0};
  const char* input = "Longword";
  const char* fmt = "%4s";

  int res = sscanf(input, fmt, b1);
  int s21_res = s21_sscanf(input, fmt, b1);

  ck_assert_int_eq(res, s21_res);
  ck_assert_str_eq(b1, "Long");  // Должно считать только 4 символа
}
END_TEST

START_TEST(sscanf_spec_s_suppress) {
  char b1[100] = {0};
  const char* input = "Skip me please";
  const char* fmt = "%*s %*s %s";

  int res = sscanf(input, fmt, b1);
  int s21_res = s21_sscanf(input, fmt, b1);

  ck_assert_int_eq(res, s21_res);
  ck_assert_str_eq(b1, "please");
}
END_TEST

START_TEST(sscanf_spec_s_empty) {
  char b1[100] = {0};
  const char* input = "    ";
  const char* fmt = "%s";

  int res = sscanf(input, fmt, b1);
  int s21_res = s21_sscanf(input, fmt, b1);

  ck_assert_int_eq(res, s21_res);  // Должны оба вернуть -1 (EOF)
}
END_TEST

START_TEST(sscanf_spec_s_space) {
  char b1[100] = {0};
  const char* input = "   Hello";
  const char* fmt = "%s";

  int res = sscanf(input, fmt, b1);
  int s21_res = s21_sscanf(input, fmt, b1);

  ck_assert_int_eq(res, s21_res);
  ck_assert_str_eq(b1, "Hello");
}
END_TEST

START_TEST(sscanf_spec_s_space_2) {
  char b1[100] = {0};
  char b2[100] = {0};
  const char* input = "    Hello   world";
  const char* fmt = "%s %s";

  int res = sscanf(input, fmt, b1, b2);
  int s21_res = s21_sscanf(input, fmt, b1, b2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_str_eq(b1, "Hello");
  ck_assert_str_eq(b2, "world");
}
END_TEST

START_TEST(sscanf_spec_n_basic) {
  char buf1[100] = {0}, buf2[100] = {0};
  int n1 = 0, n2 = 0, n3 = 0, n4 = 0;
  int d1 = 0, d2 = 0;

  int res1 = sscanf("Hi 123", "%99s %n %d %n", buf1, &n1, &d1, &n2);
  int res2 = s21_sscanf("Hi 123", "%99s %n %d %n", buf2, &n3, &d2, &n4);

  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(n1, n3);
  ck_assert_int_eq(n2, n4);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(buf1, buf2);
}
END_TEST

START_TEST(sscanf_spec_n_width) {
  int n = 0, s21_n = 0;
  char b1[5] = {0}, b2[5] = {0};
  const char* input = "LongWordTest";
  const char* fmt = "%4s %n";

  int res = sscanf(input, fmt, b1, &n);
  int s21_res = s21_sscanf(input, fmt, b2, &s21_n);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(n, s21_n);
}
END_TEST

START_TEST(sscanf_spec_n_failure) {
  int n = -1, s21_n = -1;
  int d1 = 0, s21_d1 = 0;
  const char* input = "123 Error";
  const char* fmt = "%d %d %n";  // Должно упасть на втором %d

  int res = sscanf(input, fmt, &d1, &d1, &n);
  int s21_res = s21_sscanf(input, fmt, &s21_d1, &s21_d1, &s21_n);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(n, s21_n);  // Должно остаться -1 в обоих случаях
}
END_TEST

START_TEST(sscanf_spec_n_start_pos) {
  int n = 0, s21_n = 0;
  char b1[100] = {0}, b2[100] = {0};
  const char* input = "Hello";
  const char* fmt = "%n %s";

  int res = sscanf(input, fmt, &n, b1);
  int s21_res = s21_sscanf(input, fmt, &s21_n, b2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(n, s21_n);
}
END_TEST

START_TEST(sscanf_spec_n_repeat) {
  int n = 0, s21_n = 0;
  char b1[100] = {0}, b2[100] = {0};
  int d1 = 0, s21_d1 = 0;
  const char* input = "Hello 123";
  const char* fmt = " %s %n%n %d";

  int res = sscanf(input, fmt, b1, &n, &n, &d1);
  int s21_res = s21_sscanf(input, fmt, b2, &s21_n, &s21_n, &s21_d1);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(n, s21_n);
}
END_TEST

START_TEST(sscanf_spec_n_repeat_2) {
  int n = 0, s21_n = 0;
  char b1[100] = {0}, b2[100] = {0};
  int d1 = 0, s21_d1 = 0;
  const char* input = "Hello 123";
  const char* fmt = " %s %n %d %n";

  int res = sscanf(input, fmt, b1, &n, &d1, &n);
  int s21_res = s21_sscanf(input, fmt, b2, &s21_n, &s21_d1, &s21_n);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(n, s21_n);
}
END_TEST

START_TEST(sscanf_spec_n_space) {
  int n = 0, s21_n = 0;
  int d1 = 0, s21_d1 = 0;
  const char* input = "     123";
  const char* fmt = "%n %d";

  int res = sscanf(input, fmt, &n, &d1);
  int s21_res = s21_sscanf(input, fmt, &s21_n, &s21_d1);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(n, s21_n);
}
END_TEST

START_TEST(sscanf_spec_n_empty) {
  int n = 0, s21_n = 0;
  const char* input = "  ";
  const char* fmt = "%n";

  int res = sscanf(input, fmt, &n);
  int s21_res = s21_sscanf(input, fmt, &s21_n);

  ck_assert_int_eq(res, s21_res);
  ck_assert_int_eq(n, s21_n);
}
END_TEST

START_TEST(sscanf_spec_p_basic) {
  void *p1 = NULL, *p2 = NULL;
  const char* input = "0x12345678";
  const char* fmt = "%p";

  int res = sscanf(input, fmt, &p1);
  int s21_res = s21_sscanf(input, fmt, &p2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_no_prefix) {
  void *p1 = NULL, *p2 = NULL;
  const char* input = "abcde";
  const char* fmt = "%p";

  int res = sscanf(input, fmt, &p1);
  int s21_res = s21_sscanf(input, fmt, &p2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_mixed) {
  void *p1 = NULL, *p2 = NULL;
  int d1 = 0, d2 = 0;
  const char* input = "0x55aa 100";
  const char* fmt = "%p %d";

  int res = sscanf(input, fmt, &p1, &d1);
  int s21_res = s21_sscanf(input, fmt, &p2, &d2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(d1, d2);
}
END_TEST

START_TEST(sscanf_spec_p_null) {
  void *p1 = (void*)0x1, *p2 = (void*)0x1;
  const char* input = "0x0";
  const char* fmt = "%p";

  int res = sscanf(input, fmt, &p1);
  int s21_res = s21_sscanf(input, fmt, &p2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_64_bit) {
  void *p1 = NULL, *p2 = NULL;
  const char* input = "0xFFFFFFFFFFFFFFFF";
  const char* fmt = "%p";

  int res = sscanf(input, fmt, &p1);
  int s21_res = s21_sscanf(input, fmt, &p2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_space) {
  void *p1 = NULL, *p2 = NULL;
  const char* input = "    0x12345678   ";
  const char* fmt = "%p";

  int res = sscanf(input, fmt, &p1);
  int s21_res = s21_sscanf(input, fmt, &p2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_invalid_char) {
  void *p1 = NULL, *p2 = NULL;
  const char* input = "0x1235G678";
  const char* fmt = "%p";

  int res = sscanf(input, fmt, &p1);
  int s21_res = s21_sscanf(input, fmt, &p2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_char) {
  void *p1 = NULL, *p2 = NULL;
  char b1[100] = {0}, b2[100] = {0};
  const char* input = "Hello 0x1235678";
  const char* fmt = "%s %p";

  int res = sscanf(input, fmt, b1, &p1);
  int s21_res = s21_sscanf(input, fmt, b2, &p2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_str_eq(b1, b2);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_empty) {
  void *p1 = NULL, *p2 = NULL;
  const char* input = "";
  const char* fmt = "%p";

  int res = sscanf(input, fmt, &p1);
  int s21_res = s21_sscanf(input, fmt, &p2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_diff_register) {
  void *p1 = NULL, *p2 = NULL;
  const char* input = "0xAaBbCcDd";
  const char* fmt = "%p";

  int res = sscanf(input, fmt, &p1);
  int s21_res = s21_sscanf(input, fmt, &p2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_width) {
  void *p1 = NULL, *p2 = NULL;
  const char* input = "0x1235678";
  const char* fmt = "%4p";

  int res = sscanf(input, fmt, &p1);
  int s21_res = s21_sscanf(input, fmt, &p2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_repeat) {
  void *p1 = NULL, *p2 = NULL;
  void *p3 = NULL, *p4 = NULL;
  const char* input = "0x1234 0x5678";
  const char* fmt = "%p %p";

  int res = sscanf(input, fmt, &p1, &p2);
  int s21_res = s21_sscanf(input, fmt, &p3, &p4);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p3);
  ck_assert_ptr_eq(p2, p4);
}
END_TEST

START_TEST(sscanf_spec_p_only_prefix) {
  void *p1 = NULL, *p2 = NULL;
  const char* input = "0x";
  const char* fmt = "%p";

  int res = sscanf(input, fmt, &p1);
  int s21_res = s21_sscanf(input, fmt, &p2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST

START_TEST(sscanf_spec_p_upper_prefix) {
  void *p1 = NULL, *p2 = NULL;
  const char* input = "0XABCD";
  const char* fmt = "%p";

  int res = sscanf(input, fmt, &p1);
  int s21_res = s21_sscanf(input, fmt, &p2);

  ck_assert_int_eq(res, s21_res);
  ck_assert_ptr_eq(p1, p2);
}
END_TEST
/*

%u TESTS

*/
typedef struct {
  const char* str;
  const char* fmt;
} u_case;

static u_case u_cases[] = {
    {"0", "%u"},     {"1", "%u"},          {"0123", "%u"},   {"-23", "%u"},
    {"0003", "%u"},  {"4294967295", "%u"}, {"", "%u"},       {"  ", "%u"},
    {"0x1A", "%u"},  {"abc123", "%u"},     {"123abc", "%u"}, {"  123abc", "%u"},
    {"   77", "%u"}, {"0x", "%u"},         {"0x1f", "%u"},
};

static void run_u_test(const char* str, const char* fmt) {
  unsigned int val = 777;
  unsigned int std_val = 777;

  int ret = s21_sscanf(str, fmt, &val);
  int std_ret = sscanf(str, fmt, &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_uint_eq(val, std_val);
}

START_TEST(test_u_parametrized) {
  run_u_test(u_cases[_i].str, u_cases[_i].fmt);
}
END_TEST

START_TEST(u_longlong) {
  unsigned long long a1 = 0, b1 = 0, c1 = 0, d1 = 0, e1 = 0, f1 = 0;
  unsigned long long a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0;
  const char str[] = "0555 022 0000 0123 0 18446744073709551615";

  const char fstr[] = "%llu %llu %llu %llu %llu %llu";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1, &f1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2, &f2);

  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(e1, e2);
  ck_assert_uint_eq(f1, f2);
}
END_TEST

START_TEST(u_long_test) {
  unsigned long a1 = 0, b1 = 0, c1 = 0, d1 = 0, e1 = 0, f1 = 0;
  unsigned long a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0;

  const char fstr[] = "%lu %lu %lu %lu %lu %lu";
  const char str[] =
      "0555 022 000 0123 0 18446744073709551615";  // краевые случаи

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1, &f1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2, &f2);

  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(e1, e2);
  ck_assert_uint_eq(f1, f2);
}
END_TEST

START_TEST(u_short_test) {
  unsigned short a1 = 0, b1 = 0, c1 = 0, d1 = 0, e1 = 0, f1 = 0;
  unsigned short a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0;

  const char fstr[] = "%hu %hu %hu %hu %hu %hu";
  const char str[] =
      "0555 022 033 0123 0 32767";  // краевое значение для short - 32767

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1, &f1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2, &f2);

  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(e1, e2);
  ck_assert_uint_eq(f1, f2);
}

END_TEST
/*

%x TESTS

*/
typedef struct {
  const char* str;
  const char* fmt;
} x_case;

static x_case x_cases[] = {
    {"0", "%x"},    {"1", "%x"},    {"a", "%x"},     {"A", "%x"},
    {"f", "%x"},    {"F", "%x"},    {"10", "%x"},    {"ff", "%x"},
    {"FF", "%x"},   {"0x0", "%x"},  {"0x1A", "%x"},  {"0XFF", "%x"},
    {"0xff", "%x"}, {"0000", "%x"}, {"000ff", "%x"}, {"FFxyz", "%x"},
    {"", "%x"},     {"   ", "%x"},  {"   FF", "%x"}, {"GHI", "%x"},
    {"1G", "%x"},   {"xyz", "%x"},  {"0x", "%x"},    {"-0xFF", "%x"},
};

static void run_x_test(const char* str, const char* fmt) {
  unsigned int val = 777;
  unsigned int std_val = 777;

  int ret = s21_sscanf(str, fmt, &val);
  int std_ret = sscanf(str, fmt, &std_val);

  ck_assert_int_eq(ret, std_ret);
  ck_assert_uint_eq(val, std_val);
}

START_TEST(test_x_parametrized) {
  run_x_test(x_cases[_i].str, x_cases[_i].fmt);
}
END_TEST

START_TEST(x_longlong) {
  unsigned long long a1 = 0, b1 = 0, c1 = 0, d1 = 0, e1 = 0, f1 = 0;
  unsigned long long a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0;
  const char str[] = "0555 022 0000 0123 0 FFFFFFFFFFFFFFFF";  // краевые
                                                               // значения
  const char fstr[] = "%llx %llx %llx %llx %llx %llx";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1, &f1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2, &f2);

  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(e1, e2);
  ck_assert_uint_eq(f1, f2);
}
END_TEST

START_TEST(x_long_test) {
  unsigned long a1 = 0, b1 = 0, c1 = 0, d1 = 0, e1 = 0, f1 = 0;
  unsigned long a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0;
  const char str[] = "0555 022 0000 0123 0 FFFFFFFFFFFFFFFF";  // краевые
                                                               // значения
  const char fstr[] = "%lx %lx %lx %lx %lx %lx";

  int res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1, &f1);
  int res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2, &f2);

  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(e1, e2);
  ck_assert_uint_eq(f1, f2);
}
END_TEST

START_TEST(x_short_test) {
  unsigned short a1 = 0, b1 = 0, c1 = 0, d1 = 0, e1 = 0, f1 = 0;
  unsigned short a2 = 0, b2 = 0, c2 = 0, d2 = 0, e2 = 0, f2 = 0;

  const char fstr[] = "%hx %hx %hx %hx %hx %hx";
  const char str[] = "0555 022 033 0123 0 FFFF";  // краевые значения

  int32_t res1 = s21_sscanf(str, fstr, &a1, &b1, &c1, &d1, &e1, &f1);
  int32_t res2 = sscanf(str, fstr, &a2, &b2, &c2, &d2, &e2, &f2);

  ck_assert_int_eq(res1, res2);
  ck_assert_uint_eq(a1, a2);
  ck_assert_uint_eq(b1, b2);
  ck_assert_uint_eq(c1, c2);
  ck_assert_uint_eq(d1, d2);
  ck_assert_uint_eq(e1, e2);
  ck_assert_uint_eq(f1, f2);
}
END_TEST
/*

%f TESTS

*/
typedef struct {
  const char* str;
  const char* fmt;
} f_case;

static f_case feg_cases[] = {
    {"0", "%f"},          {"1.0", "%f"},      {"-1.5", "%f"},  // [0-2]
    {"+3.14", "%f"},      {"0.0", "%f"},      {"123.456", "%f"},
    {"1e10", "%f"},       {"1E10", "%f"},     {"-1e-5", "%f"},
    {"3.14e+2", "%f"},    {"   42.5", "%f"},  {"42.5   ", "%f"},
    {"1.2abc", "%f"},     {"inf", "%f"},      {"-inf", "%f"},  // [12-14]
    {"nan", "%f"},        {"NAN", "%f"},      {"", "%f"},
    {"   ", "%f"},        {"abc", "%f"},      {"1e10", "%e"},
    {"1E10", "%E"},       {"-3.5e-2", "%e"},  {"4.2E+3", "%E"},
    {"0e0", "%e"},        {"1.2e3abc", "%e"}, {"123.456", "%g"},
    {"1234567", "%g"},    {"1.23e5", "%g"},   {"1.23E5", "%G"},  // [27-29]
    {"0.00000123", "%g"}, {"1.23000", "%g"},  {"inf", "%g"},
    {"nan", "%G"},        {"-.5", "%f"},      {".5", "%f"},
    {"5.", "%f"},         {"-0", "%f"},       {"+0.0", "%f"},
    {"1e", "%f"},         {"1e+", "%f"},      {"1e-", "%f"},
    {"e10", "%f"},        {"--1.0", "%f"},  // [42-43]
};

static void run_f_test(const char* str, const char* fmt) {
  float val = 777.0f;
  float std_val = 777.0f;

  int ret = s21_sscanf(str, fmt, &val);
  int std_ret = sscanf(str, fmt, &std_val);

  ck_assert_int_eq(ret, std_ret);

  if (ret == 1) {
    if (isnan(std_val))
      ck_assert(isnan(val));
    else if (isinf(std_val))
      ck_assert(isinf(val));
    else
      ck_assert_float_eq_tol(val, std_val, 1e-6);
  }
}

START_TEST(test_f_parametrized) {
  run_f_test(feg_cases[_i].str, feg_cases[_i].fmt);
}
END_TEST

START_TEST(f_double_test) {
  double a1 = 0, b1 = 0, c1 = 0;
  double a2 = 0, b2 = 0, c2 = 0;

  const char str[] = "1.23 -4.56 7.89e10";
  const char fmt[] = "%lf %lf %lf";

  int r1 = s21_sscanf(str, fmt, &a1, &b1, &c1);
  int r2 = sscanf(str, fmt, &a2, &b2, &c2);

  ck_assert_int_eq(r1, r2);
  ck_assert_double_eq_tol(a1, a2, 1e-12);
  ck_assert_double_eq_tol(b1, b2, 1e-12);
  ck_assert_double_eq_tol(c1, c2, 1e-6);
}
END_TEST

START_TEST(f_long_double_test) {
  long double a1 = 0, b1 = 0;
  long double a2 = 0, b2 = 0;

  const char str[] = "1.23456789012345e10 -0.0000001";
  const char fmt[] = "%Lf %Lf";

  int r1 = s21_sscanf(str, fmt, &a1, &b1);
  int r2 = sscanf(str, fmt, &a2, &b2);

  ck_assert_int_eq(r1, r2);
  ck_assert_ldouble_eq_tol(a1, a2, 1e-9);
  ck_assert_ldouble_eq_tol(b1, b2, 1e-12);
}
END_TEST

START_TEST(f_extreme_values) {
  double a1 = 0, b1 = 0;
  double a2 = 0, b2 = 0;

  const char str[] = "1e308 1e-308";
  const char fmt[] = "%lf %lf";

  int r1 = s21_sscanf(str, fmt, &a1, &b1);
  int r2 = sscanf(str, fmt, &a2, &b2);

  ck_assert_int_eq(r1, r2);
  ck_assert_double_eq_tol(a1, a2, 1e292);
  ck_assert_double_eq_tol(b1, b2, 1e-320);
}
END_TEST

Suite* s21_sscanf_suite(void) {
  Suite* s;
  s = suite_create("s21_sscanf");
  TCase* tc;
  tc = tcase_create("core");
  /*
  main tests
  */
  tcase_add_test(tc, no_lines);
#ifndef __linux__
  tcase_add_test(tc, invalid_spec);
#endif
  tcase_add_test(tc, no_percent_fstr);
  tcase_add_test(tc, EOF1);
  tcase_add_test(tc, EOF2);
  tcase_add_test(tc, EOF3);
  tcase_add_test(tc, EOF4);
  tcase_add_test(tc, perc_too_much);
  tcase_add_test(tc, perc_not_enough);
  tcase_add_test(tc, perc2);
  tcase_add_test(tc, perc3);
  /*
  %c tests
  */
  tcase_add_test(tc, c_basic);
  tcase_add_test(tc, c_whitespace);
  tcase_add_test(tc, c_whitespace_n);
  tcase_add_test(tc, c_suppress_basic);
  tcase_add_test(tc, c_suppress_width);
  tcase_add_test(tc, c_suppress_fail);
  tcase_add_test(tc, c_width_exact);
  tcase_add_test(tc, c_biggest_width);
  tcase_add_test(tc, c_empty_input);
  tcase_add_test(tc, c_literal_match);
  tcase_add_test(tc, c_literal_mismatch);
  tcase_add_test(tc, c_skipspaces);
  /*
  %d tests
  */
  tcase_add_test(tc, dec_basic);
  tcase_add_test(tc, dec_signs);
  tcase_add_test(tc, dec_width1);
  tcase_add_test(tc, dec_width2);
  tcase_add_test(tc, dec_whitespace);
  tcase_add_test(tc, dec_invalid_input1);
  tcase_add_test(tc, dec_invalid_input2);
  tcase_add_test(tc, dec_invalid_input3);
  tcase_add_test(tc, dec_overflow1);
  tcase_add_test(tc, dec_overflow2);
  tcase_add_test(tc, dec_overflow3);
  tcase_add_test(tc, dec_overflow4);
  tcase_add_test(tc, dec_short_int);
  tcase_add_test(tc, dec_long_int);
  tcase_add_test(tc, dec_longlong_int);
  /*
  %i tests
  */
  tcase_add_loop_test(tc, test_i_parametrized, 0,
                      sizeof(i_cases) / sizeof(i_cases[0]));
  /*
  %o tests
  */
  tcase_add_loop_test(tc, test_o_parametrized, 0,
                      sizeof(o_cases) / sizeof(o_cases[0]));

  tcase_add_test(tc, oct_longlong);
  tcase_add_test(tc, oct_long);
  tcase_add_test(tc, oct_short);
  /*
  %s tests
  */
  tcase_add_test(tc, sscanf_spec_s_basic);
  tcase_add_test(tc, sscanf_spec_s_width);
  tcase_add_test(tc, sscanf_spec_s_suppress);
  tcase_add_test(tc, sscanf_spec_s_empty);
  tcase_add_test(tc, sscanf_spec_s_space);
  tcase_add_test(tc, sscanf_spec_s_space_2);
  /*
  %n tests
  */
  tcase_add_test(tc, sscanf_spec_n_basic);
  tcase_add_test(tc, sscanf_spec_n_width);
  tcase_add_test(tc, sscanf_spec_n_failure);
  tcase_add_test(tc, sscanf_spec_n_start_pos);
  tcase_add_test(tc, sscanf_spec_n_repeat);
  tcase_add_test(tc, sscanf_spec_n_repeat_2);
  tcase_add_test(tc, sscanf_spec_n_space);
  tcase_add_test(tc, sscanf_spec_n_empty);
  /*
  %p tests
  */
  tcase_add_test(tc, sscanf_spec_p_basic);
  tcase_add_test(tc, sscanf_spec_p_no_prefix);
  tcase_add_test(tc, sscanf_spec_p_mixed);
  tcase_add_test(tc, sscanf_spec_p_null);
  tcase_add_test(tc, sscanf_spec_p_64_bit);
  tcase_add_test(tc, sscanf_spec_p_space);
  tcase_add_test(tc, sscanf_spec_p_invalid_char);
  tcase_add_test(tc, sscanf_spec_p_char);
  tcase_add_test(tc, sscanf_spec_p_empty);
  tcase_add_test(tc, sscanf_spec_p_diff_register);
  tcase_add_test(tc, sscanf_spec_p_width);
  tcase_add_test(tc, sscanf_spec_p_repeat);
  tcase_add_test(tc, sscanf_spec_p_only_prefix);
  tcase_add_test(tc, sscanf_spec_p_upper_prefix);
  /*
  %u tests
  */
  tcase_add_loop_test(tc, test_u_parametrized, 0,
                      sizeof(u_cases) / sizeof(u_cases[0]));
  tcase_add_test(tc, u_longlong);
  tcase_add_test(tc, u_long_test);
  tcase_add_test(tc, u_short_test);
  /*
  %x tests
  */
  tcase_add_loop_test(tc, test_x_parametrized, 0,
                      sizeof(x_cases) / sizeof(x_cases[0]));
  tcase_add_test(tc, x_longlong);
  tcase_add_test(tc, x_long_test);
  tcase_add_test(tc, x_short_test);
  /*
  %float tests
  */
  tcase_add_loop_test(tc, test_f_parametrized, 0,
                      sizeof(feg_cases) / sizeof(feg_cases[0]));

  tcase_add_test(tc, f_double_test);
  tcase_add_test(tc, f_long_double_test);
  tcase_add_test(tc, f_extreme_values);

  suite_add_tcase(s, tc);
  return s;
}