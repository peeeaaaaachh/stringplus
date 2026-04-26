#ifndef SRC_S21_SPRINTF_H
#define SRC_S21_SPRINTF_H
#define BUFFER_SIZE 1024
#define MAX_DOUBLE_PRECISION 15
#define MAX_LONG_DOUBLE_PRECISION 20

// #include "s21_string.h"

typedef enum {
  LENGTH_NONE = 0,
  LENGTH_H,
  LENGTH_HH,
  LENGTH_L,
  LENGTH_LL,
  LENGTH_LD,
  LENGTH_Z,
  LENGTH_L_UPPER
} length_mod;

typedef struct {
  int minus;
  int plus;
  int space;
  int zero;
  int hash;

  int width;
  int precision;
  int precision_set;
  char specifier;
  length_mod length;
} s21_flags;

int s21_sprintf(char* str, char const* format, ...);

void parse_flags(const char** format, s21_flags* flags);
void parse_width(const char** format, s21_flags* flags, va_list* args);
void parse_precision(const char** format, s21_flags* flags, va_list* args);
void parse_length(const char** format, s21_flags* flags);

long long get_signed_int(s21_flags* flags, va_list* args);

void uint_to_str(unsigned long long value, char* buffer, int base,
                 int uppercase);
void int_to_str(long long value, char* buffer, int base);
void long_double_to_str(long double value, char* buffer, s21_flags* flags);
void double_to_str(double value, char* buffer, s21_flags* flags);
void long_double_to_scientific(long double value, char* buffer,
                               s21_flags* flags, int uppercase);
void double_to_scientific(double value, char* buffer, s21_flags* flags,
                          int uppercase);
void long_double_to_adaptive(long double value, char* buffer, s21_flags* flags,
                             int uppercase);
void double_to_adaptive(double value, char* buffer, s21_flags* flags,
                        int uppercase);

void apply_int_format(char* buffer, s21_flags* flags);
void apply_width_general(char* buffer, s21_flags* flags, int content_len);
void precision_number(char* buffer, s21_flags* flags);

void handle_string(s21_flags* flags, char* buffer, va_list* args);
void handle_char(s21_flags* flags, char* buffer, va_list* args);
void handle_decimal(s21_flags* flags, char* buffer, va_list* args);
void handle_unsigned(s21_flags* flags, char* buffer, va_list* args);
void handle_hex(s21_flags* flags, char* buffer, va_list* args, int uppercase);
void handle_octal(s21_flags* flags, char* buffer, va_list* args);
void handle_n(s21_flags* flags, va_list* args, int written_count);
void handle_pointer(s21_flags* flags, char* buffer, va_list* args);
void handle_percent(s21_flags* flags, char* buffer);
void handle_float(s21_flags* flags, char* buffer, va_list* args);
void handle_scientific(s21_flags* flags, char* buffer, va_list* args,
                       int uppercase);
void handle_adaptive(s21_flags* flags, char* buffer, va_list* args,
                     int uppercase);

int num_specifier(char specifier);
char get_fill_char(s21_flags* flags, int is_numeric);
void handle_num_with_sign(char const* buffer, char* temp, int len, int padding,
                          s21_flags* flags);
void int_to_str_zeropad(unsigned int value, char* out, int min_digits);
void trim_trailing_zeros(char* buffer, int hash_flags);

#endif