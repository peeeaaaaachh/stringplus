#include "s21_string.h"

int s21_isdigit(int c) { return (c >= '0' && c <= '9'); }

int s21_isspace(int c) {
  return (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
          c == '\r');
}

void skip_space(char** str) {
  while (s21_isspace(**str)) {
    (*str)++;
  }
}

int let_to_digit(char c) {
  int result = -1;
  if (c >= '0' && c <= '9') result = c - '0';
  if (c >= 'a' && c <= 'f') result = c - 'a' + 10;
  if (c >= 'A' && c <= 'F') result = c - 'A' + 10;
  return result;
}

char tolower_char(char c) {
  if (c >= 'A' && c <= 'Z') return c + 32;
  return c;
}

int s21_strncasecmp(const char* a, const char* b, size_t n) {
  for (size_t i = 0; i < n; i++) {
    if (tolower_char(a[i]) != tolower_char(b[i])) return 1;

    if (a[i] == '\0') break;
  }
  return 0;
}

int s21_sscanf(const char* str, const char* fstr, ...) {
  if (!str || !fstr) return EOF;
  va_list args;
  va_start(args, fstr);
  char *s = (char*)str, *f = (char*)fstr;
  int match_count = 0, eof = 0;

  while (*f) {
    if (s21_isspace(*f)) {
      while (s21_isspace(*f)) f++;
      while (s21_isspace(*s)) s++;
      continue;
    }
    // литералы
    if (*f != '%') {
      if (*s != *f) break;
      s++;
      f++;
      continue;
    }
    // парсинг спецификаторов
    format_t spec = {0};
    if (!format_parser(&f, &spec)) break;
    // %% + проверка на конец строки
    if (spec.type == type_percent) {
      if (*s != '%') {
        if (*s == '\0') eof = -1;
        break;
      }
      s++;
      continue;
    }
    // спецификаторы
    int result = distributor(str, &s, &spec, &args);
    if (result == -1) {
      eof = -1;
      break;
    }
    if (result == 0) break;
    if ((!spec.suppress) && (spec.type != type_counter)) match_count++;
  }
  va_end(args);
  return match_count ? match_count : eof;
}

int format_parser(char** fstr, format_t* out_spec) {
  // skip %
  (*fstr)++;
  // обнуляем структуру
  out_spec->is_spec = 1;
  out_spec->width = 0;
  out_spec->length = none_len;
  out_spec->suppress = 0;
  // %%
  if (**fstr == '%') {
    out_spec->type = type_percent;
    (*fstr)++;
    return 1;
  }
  if (**fstr == '*') {
    out_spec->suppress = 1;
    (*fstr)++;
  }
  width_parse(fstr, out_spec);
  length_parse(fstr, out_spec);
  parse_specifier(fstr, out_spec);

  if (out_spec->type == invalid_type) return 0;

  return 1;
}

void width_parse(char** fstr, format_t* out_spec) {
  if (s21_isdigit((unsigned char)**fstr)) {
    int w = 0;
    while (s21_isdigit(**fstr)) {
      w = w * 10 + (**fstr - '0');
      (*fstr)++;
    }
    out_spec->width = w;
  }
}

void length_parse(char** fstr, format_t* out_spec) {
  if (**fstr == 'h') {
    out_spec->length = len_h;
    (*fstr)++;
  } else if (**fstr == 'l' && *(*fstr + 1) == 'l') {
    out_spec->length = len_ll;
    (*fstr) += 2;
  } else if (**fstr == 'l') {
    out_spec->length = len_l;
    (*fstr)++;
  } else if (**fstr == 'L') {
    out_spec->length = len_L;
    (*fstr)++;
  } else {
    out_spec->length = none_len;
  }
}

void parse_specifier(char** fstr, format_t* out_spec) {
  switch (**fstr) {
    case 'c':
      out_spec->type = type_char;
      break;
    case 'd':
      out_spec->type = type_int_dec;
      break;
    case 'i':
      out_spec->type = type_int_octhex;
      break;
    case 'e':
    case 'E':
    case 'f':
    case 'g':
    case 'G':
      out_spec->type = type_float;
      break;
    case 'o':
      out_spec->type = type_unsigned_oct;
      break;
    case 's':
      out_spec->type = type_string;
      break;
    case 'u':
      out_spec->type = type_unsigned_dec;
      break;
    case 'x':
    case 'X':
      out_spec->type = type_unsigned_hex;
      break;
    case 'p':
      out_spec->type = type_pointer;
      break;
    case 'n':
      out_spec->type = type_counter;
      break;
    default:
      out_spec->type = invalid_type;
      break;
  }
  if (out_spec->type != invalid_type) (*fstr)++;
}

int distributor(const char* start_str, char** str, format_t* spec,
                va_list* args) {
  int result = 0;
  switch (spec->type) {
    case type_char:
      result = interpretate_char(str, spec, args);
      break;
    case type_int_dec:
      result = interpretate_integer(str, spec, args, 10, 0, 1);
      break;
    case type_int_octhex:
      result = interpretate_integer(str, spec, args, 0, 1, 1);
      break;
    case type_unsigned_dec:
      result = interpretate_integer(str, spec, args, 10, 0, 0);
      break;
    case type_unsigned_oct:
      result = interpretate_integer(str, spec, args, 8, 0, 0);
      break;
    case type_unsigned_hex:
      result = interpretate_integer(str, spec, args, 16, 0, 0);
      break;
    case type_string:
      result = interpretate_string(str, spec, args);
      break;
    case type_counter:
      result = interpretate_counter(start_str, (const char**)str, spec,
                                    args);  // add const
      break;
    case type_pointer:
      result = interpretate_pointer(str, spec, args);
      break;
    case type_float:
      result = interpretate_float(str, spec, args);
      break;
    default:
      break;
  }
  return result;
}

int interpretate_char(char** str, format_t* spec, va_list* args) {
  if (!**str) return EOF;
  int width = spec->width ? spec->width : 1;
  if (spec->suppress) {
    while (width-- && **str) {
      (*str)++;
    }
  } else {
    char* dest = va_arg(*args, char*);
    while (width-- && **str) {
      *dest++ = **str;
      (*str)++;
    }
  }
  return 1;
}

int interpretate_integer(char** str, format_t* spec, va_list* args, int base,
                         int auto_base, int is_signed) {
  skip_space(str);

  if (**str == '\0') return EOF;

  int sign = 1;
  int width = spec->width ? spec->width : INT_MAX;
  int digits = 0;
  long long value = 0;
  char* s = *str;

  if (width > 0 && (*s == '+' || *s == '-')) {
    if (*s == '-') sign = -1;
    s++;
    width--;
  }

  if (width <= 0) return 0;

  // auto base для %i
  if (auto_base) {
    if (*s == '0') {
      if (width > 2 && (s[1] == 'x' || s[1] == 'X') &&
          (let_to_digit(s[2])) >= 0) {
        base = 16;
        s += 2;
        width -= 2;
      } else {
        base = 8;
        width--;
      }
    } else {
      base = 10;
    }
  }
  if (base == 16) {
    if (width > 2 && s[0] == '0' && (s[1] == 'x' || s[1] == 'X') &&
        let_to_digit(s[2]) >= 0) {
      s += 2;
      width -= 2;
    }
  }

  while (*s && width > 0) {
    int d = let_to_digit(*s);
    if (d < 0 || d >= base) break;
    value = value * base + d;
    s++;
    width--;
    digits++;
  }

  if (digits == 0) return 0;
  *str = s;

  value *= sign;

  if (!spec->suppress) {
    if (is_signed)
      int_record(spec, args, value);
    else
      un_int_record(spec, args, value);
  }
  return 1;
}

int interpretate_pointer(char** str, format_t* spec, va_list* args) {
  skip_space(str);
  if (**str == '\0') {
    return EOF;
  }
  char* start = *str;
  void** dest = NULL;
  if (!spec->suppress) {
    dest = va_arg(*args, void**);
  }

  unsigned long long width = spec->width ? spec->width : 0xFFFFFFFF;
  unsigned long long hex_val = 0;

  if (**str == '0' && (*(*str + 1) == 'x' || *(*str + 1) == 'X')) {
    (*str) += 2;
    width -= 2;
  }

  while (width > 0 && **str != '\0') {
    int current_digit = let_to_digit(**str);
    if (current_digit == -1) break;

    hex_val = hex_val * 16 + current_digit;
    (*str)++;
    width--;
  }

  if (*str == start) return 0;

  if (!spec->suppress && dest != NULL) {
    *dest = (void*)hex_val;
  }

  return 1;
}

// add const
int interpretate_counter(const char* start_str, const char** str,
                         format_t* spec, va_list* args) {
  if (!spec->suppress) {
    long long processed = (long long)(*str - start_str);
    int_record(spec, args, processed);
  }
  return 1;
}

int interpretate_string(char** str, format_t* spec, va_list* args) {
  skip_space(str);

  if (**str == '\0') return EOF;

  char* dest = NULL;
  if (!spec->suppress) {
    dest = va_arg(*args, char*);
  }

  unsigned int width = spec->width ? spec->width : 0xFFFFFFFF;

  while (**str != '\0' && !s21_isspace(**str) && width > 0) {
    if (!spec->suppress) {
      *dest = **str;
      dest++;
    }
    (*str)++;
    width--;
  }

  if (!spec->suppress) {
    *dest = '\0';
  }

  return 1;
}

int interpretate_float(char** str, format_t* spec, va_list* args) {
  skip_space(str);
  if (**str == '\0') return EOF;

  char* s = *str;
  int width = spec->width ? spec->width : INT_MAX;

  int sign = 1;
  if (width > 0 && (*s == '+' || *s == '-')) {
    if (*s == '-') sign = -1;
    s++;
    width--;
  }

  long double value;

  if (parse_special(&s, &width, &value)) {
    value *= sign;
    *str = s;

    if (!spec->suppress) float_record(spec, args, value);

    return 1;
  }

  // мантисса
  if (!parse_mantissa(&s, &width, &value)) return 0;

  // экспонента
  parse_exponent(&s, &width, &value);

  value *= sign;
  *str = s;

  if (!spec->suppress) float_record(spec, args, value);

  return 1;
}

int parse_special(char** s, int* width, long double* value) {
  if (*width < 3) return 0;

  if (s21_strncasecmp(*s, "inf", 3) == 0) {
    *s += 3;
    *width -= 3;

    if (*width >= 5 && s21_strncasecmp(*s, "inity", 5) == 0) {
      *s += 5;
      *width -= 5;
    }

    *value = INFINITY;
    return 1;
  }

  if (s21_strncasecmp(*s, "nan", 3) == 0) {
    *s += 3;
    *width -= 3;

    *value = NAN;
    return 1;
  }

  return 0;
}

int parse_mantissa(char** s, int* width, long double* value) {
  long double val = 0.0L;
  int digits = 0;

  // целая часть
  while (*width > 0 && s21_isdigit(**s)) {
    val = val * 10.0L + (**s - '0');
    (*s)++;
    (*width)--;
    digits++;
  }

  // дробная часть
  if (*width > 0 && **s == '.') {
    (*s)++;
    (*width)--;

    long double frac = 0.0L;
    long double div = 1.0L;

    while (*width > 0 && s21_isdigit(**s)) {
      frac = frac * 10.0L + (**s - '0');
      div *= 10.0L;
      (*s)++;
      (*width)--;
      digits++;
    }

    val += frac / div;
  }

  if (digits == 0) return 0;

  *value = val;
  return 1;
}

void parse_exponent(char** s, int* width, long double* value) {
  if (*width <= 0 || (**s != 'e' && **s != 'E')) return;

  char* exp_start = *s;
  int saved_width = *width;

  (*s)++;
  (*width)--;

  int exp_sign = 1;
  if (*width > 0 && (**s == '+' || **s == '-')) {
    if (**s == '-') exp_sign = -1;

    (*s)++;
    (*width)--;
  }

  int exp = 0;
  int digits = 0;

  while (*width > 0 && s21_isdigit(**s)) {
    exp = exp * 10 + (**s - '0');
    (*s)++;
    (*width)--;
    digits++;
  }

  if (digits == 0) {
    *s = exp_start;
    *width = saved_width;
  } else {
    *value *= powl(10.0L, exp * exp_sign);
  }
}

void int_record(format_t* spec, va_list* args, long long int value) {
  switch (spec->length) {
    case none_len:
      *(va_arg(*args, int*)) = (int)value;
      break;
    case len_h:
      *(va_arg(*args, short*)) = (short)value;
      break;
    case len_l:
      *(va_arg(*args, long*)) = (long)value;
      break;
    case len_ll:
      *(va_arg(*args, long long*)) = (long long)value;
      break;
    default:
      break;
  }
}

void un_int_record(format_t* spec, va_list* args, unsigned long long value) {
  switch (spec->length) {
    case none_len:
      *(va_arg(*args, unsigned int*)) = (unsigned int)value;
      break;
    case len_h:
      *(va_arg(*args, unsigned short*)) = (unsigned short)value;
      break;
    case len_l:
      *(va_arg(*args, unsigned long*)) = (unsigned long)value;
      break;
    case len_ll:
      *(va_arg(*args, unsigned long long*)) = (unsigned long long)value;
      break;
    default:
      break;
  }
}

void float_record(format_t* spec, va_list* args, long double value) {
  switch (spec->length) {
    case none_len:
      *(va_arg(*args, float*)) = (float)value;
      break;
    case len_l:
      *(va_arg(*args, double*)) = (double)value;
      break;
    case len_L:
      *(va_arg(*args, long double*)) = (long double)value;
      break;
    default:
      break;
  }
}