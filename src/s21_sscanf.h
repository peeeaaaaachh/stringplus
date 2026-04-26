#ifndef SRC_S21_SSCANF_H
#define SRC_S21_SSCANF_H

// #include "s21_string.h"

typedef enum { none_len, len_h, len_l, len_ll, len_L } length_t;

typedef enum {
  invalid_type = 0,
  type_char,          // c
  type_int_dec,       // d
  type_int_octhex,    // i
  type_percent,       // %%
  type_unsigned_oct,  // o
  type_unsigned_dec,  // u
  type_unsigned_hex,  // x / X
  type_float,         // e / E / f / g / G
  type_counter,       // n
  type_string,        // s
  type_pointer,       // p
} conv_type_t;

typedef struct {
  int is_spec;       // specifiers
  int suppress;      // *
  size_t width;      // width
  length_t length;   // modificators
  conv_type_t type;  // type
} format_t;

// main function
int s21_sscanf(const char* str, const char* fstr, ...);
// parsers
int format_parser(char** fstr, format_t* out_spec);
void width_parse(char** fstr, format_t* out_spec);
void length_parse(char** fstr, format_t* out_spec);
void parse_specifier(char** fstr, format_t* out_spec);
// processing functions
int distributor(const char* start_str, char** str, format_t* spec,
                va_list* args);  //
int interpretate_char(char** str, format_t* spec, va_list* args);
int interpretate_integer(char** str, format_t* spec, va_list* args, int base,
                         int auto_base, int is_signed);
int interpretate_string(char** str, format_t* spec, va_list* args);
int interpretate_counter(const char* start_str, const char** str,
                         format_t* spec, va_list* args);
int interpretate_pointer(char** str, format_t* spec, va_list* args);
int interpretate_float(char** str, format_t* spec, va_list* args);

// functions type conversion
void int_record(format_t* spec, va_list* args, long long int value);
void un_int_record(format_t* spec, va_list* args, unsigned long long value);
void float_record(format_t* spec, va_list* args, long double value);
//   assistant functions
void skip_space(char** str);
int s21_isspace(int c);
int s21_isdigit(int c);
int let_to_digit(char c);
int s21_strncasecmp(const char* a, const char* b, size_t n);
char tolower_char(char c);

int parse_special(char** s, int* width, long double* value);
int parse_mantissa(char** s, int* width, long double* value);
void parse_exponent(char** s, int* width, long double* value);
#endif