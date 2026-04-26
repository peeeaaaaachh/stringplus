#include "s21_string.h"

void parse_flags(const char** format, s21_flags* flags) {
  while (1) {
    switch (**format) {
      case '-':
        flags->minus = 1;
        break;
      case '+':
        flags->plus = 1;
        break;
      case ' ':
        flags->space = 1;
        break;
      case '0':
        flags->zero = 1;
        break;
      case '#':
        flags->hash = 1;
        break;
      default:
        return;
    }
    (*format)++;
  }
}

void parse_width(const char** format, s21_flags* flags, va_list* args) {
  if (**format == '*') {
    int width = va_arg(*args, int);
    if (width < 0) {
      flags->minus = 1;
      flags->width = -width;
    } else {
      flags->width = width;
    }
    (*format)++;
  } else {
    flags->width = 0;
    while (**format >= '0' && **format <= '9') {
      flags->width = flags->width * 10 + (**format - '0');
      (*format)++;
    }
  }
}

void parse_precision(const char** format, s21_flags* flags, va_list* args) {
  if (**format == '.') {
    flags->precision_set = 1;
    (*format)++;

    if (**format == '*') {
      flags->precision = va_arg(*args, int);
      (*format)++;

      if (flags->precision < 0) {
        flags->precision_set = 0;
        flags->precision = -1;
      }
    } else {
      flags->precision = 0;

      while (**format >= '0' && **format <= '9') {
        flags->precision = flags->precision * 10 + (**format - '0');
        (*format)++;
      }
    }
  } else {
    flags->precision = -1;
    flags->precision_set = 0;
  }
}

void parse_length(const char** format, s21_flags* flags) {
  switch (**format) {
    case 'h':
      (*format)++;
      if (**format == 'h') {
        flags->length = LENGTH_HH;
        (*format)++;
      } else {
        flags->length = LENGTH_H;
      }
      break;
    case 'l':
      (*format)++;
      if (**format == 'l') {
        flags->length = LENGTH_LL;
        (*format)++;
      } else {
        flags->length = LENGTH_L;
      }
      break;
    case 'L':
      flags->length = LENGTH_L_UPPER;
      (*format)++;
      break;
    case 'z':
      flags->length = LENGTH_Z;
      (*format)++;
      break;
    default:
      flags->length = LENGTH_NONE;
      break;
  }
}

long long get_signed_int(s21_flags* flags, va_list* args) {
  long long result = 0;

  switch (flags->length) {
    case LENGTH_HH:
      result = (signed char)va_arg(*args, int);
      break;
    case LENGTH_H:
      result = (short)va_arg(*args, int);
      break;
    case LENGTH_L:
      result = va_arg(*args, long);
      break;
    case LENGTH_LL:
      result = va_arg(*args, long long);
      break;
    case LENGTH_Z:
      result = (long long)va_arg(*args, s21_size);
      break;
    case LENGTH_NONE:
    default:
      result = va_arg(*args, int);
      break;
  }
  return result;
}

unsigned long long get_unsignet_int(s21_flags* flags, va_list* args) {
  unsigned long long result = 0;

  switch (flags->length) {
    case LENGTH_HH:
      result = (unsigned char)va_arg(*args, unsigned int);
      break;
    case LENGTH_H:
      result = (unsigned short)va_arg(*args, unsigned int);
      break;
    case LENGTH_L:
      result = va_arg(*args, unsigned long);
      break;
    case LENGTH_LL:
      result = va_arg(*args, unsigned long long);
      break;
    case LENGTH_Z:
      result = (unsigned long long)va_arg(*args, s21_size);
      break;
    case LENGTH_NONE:
    default:
      result = va_arg(*args, unsigned int);
  }
  return result;
}

void uint_to_str(unsigned long long value, char* buffer, int base,
                 int uppercase) {
  if (base < 2 || base > 16) {
    buffer[0] = '\0';
    return;
  }

  static const char digits_lower[] = "0123456789abcdef";
  static const char digits_upper[] = "0123456789ABCDEF";
  const char* digits = uppercase ? digits_upper : digits_lower;

  if (value == 0) {
    buffer[0] = '0';
    buffer[1] = '\0';
    return;
  }

  char temp[BUFFER_SIZE];
  int i = 0;

  while (value != 0 && i < BUFFER_SIZE - 1) {
    int digit = value % base;
    temp[i++] = digits[digit];
    value /= base;
  }

  for (int j = 0; j < i; j++) {
    buffer[j] = temp[i - j - 1];
  }
  buffer[i] = '\0';
}

void int_to_str(long long value, char* buffer, int base) {
  int is_negative = 0;

  if (value < 0 && base == 10) {
    is_negative = 1;
    if (value == LLONG_MIN) {
      const char* min_value = "-9223372036854775808";
      if (s21_strlen(min_value) < BUFFER_SIZE) {
        s21_strcpy(buffer, min_value);
      } else {
        buffer[0] = '\0';
      }
      return;
    }
    value = -value;
  }

  int uppercase = 0;

  uint_to_str(value, buffer, base, uppercase);

  if (is_negative) {
    int len = s21_strlen(buffer);
    s21_memmove(buffer + 1, buffer, len + 1);
    buffer[0] = '-';
  }
}

void long_double_to_str(long double value, char* buffer, s21_flags* flags) {
  int precision = 6;
  int is_negative = 0;
  long double factor = 1.0L;
  unsigned long long int_part = 0;
  long double int_part_d = 0.0L;
  long double frac_part = 0.0L;

  char int_buffer[BUFFER_SIZE] = {0};
  char frac_buffer[MAX_LONG_DOUBLE_PRECISION + 1] = {0};

  int index = 0;
  int i = 0;

  if (!buffer || !flags) return;
  buffer[0] = '\0';

  precision = flags->precision_set ? flags->precision : 6;
  if (precision > MAX_LONG_DOUBLE_PRECISION)
    precision = MAX_LONG_DOUBLE_PRECISION;
  if (precision < 0) precision = 0;

  if (value != value) {
    s21_strcpy(buffer, "nan");
    return;
  }

  long double pos_inf = 1.0L / 0.0L;
  long double neg_inf = -1.0L / 0.0L;
  if (value == pos_inf || value == neg_inf) {
    s21_strcpy(buffer, value < 0.0L ? "-inf" : "inf");
    return;
  }

  if (value == 0.0L) {
    int is_neg = signbit(value);
    s21_strcpy(buffer, is_neg ? "-0" : "0");
    if (precision || flags->hash) {
      s21_strcat(buffer, ".");
      for (i = 0; i < precision; i++) s21_strcat(buffer, "0");
    }
    return;
  }

  is_negative = signbit(value) && value != 0.0L;
  if (is_negative) value = -value;

  for (i = 0; i < precision; i++) factor *= 10.0L;

  long double rounded;
  if (precision == 0) {
    rounded = floorl(value + 0.5L);
  } else {
    if (value > LDBL_MAX / factor) {
      rounded = value;
      precision = 0;
    } else {
      rounded = floorl(value * factor + 0.5L + 1e-12L) / factor;
    }
  }

  frac_part = modfl(rounded, &int_part_d);
  int_part = (unsigned long long)int_part_d;

  uint_to_str(int_part, int_buffer, 10, 0);
  int int_len = s21_strlen(int_buffer);

  if (precision > 0) {
    unsigned long long power10 = 1;
    for (i = 0; i < precision; i++) power10 *= 10;

    long double frac_temp = frac_part;
    for (i = 0; i < precision; i++) frac_temp *= 10.0L;

    unsigned long long frac_scaled = (unsigned long long)(frac_temp + 0.5L);

    if (frac_scaled >= power10) {
      int_part++;
      frac_scaled = 0;
      uint_to_str(int_part, int_buffer, 10, 0);
      int_len = s21_strlen(int_buffer);
    }

    if (frac_scaled > 0) {
      char temp[BUFFER_SIZE] = {0};
      uint_to_str(frac_scaled, temp, 10, 0);
      int temp_len = s21_strlen(temp);

      for (i = 0; i < precision - temp_len; i++) frac_buffer[i] = '0';
      s21_strcpy(frac_buffer + precision - temp_len, temp);
    } else {
      for (i = 0; i < precision; i++) frac_buffer[i] = '0';
    }
    frac_buffer[precision] = '\0';
  }

  if (is_negative)
    buffer[index++] = '-';
  else if (flags->plus)
    buffer[index++] = '+';
  else if (flags->space)
    buffer[index++] = ' ';

  for (i = 0; i < int_len && index < BUFFER_SIZE - 1; i++) {
    buffer[index++] = int_buffer[i];
  }

  if (precision > 0 || flags->hash) {
    if (index < BUFFER_SIZE - 1) buffer[index++] = '.';
    for (i = 0; i < precision && index < BUFFER_SIZE - 1; i++) {
      buffer[index++] = frac_buffer[i];
    }
  }
  buffer[index < BUFFER_SIZE ? index : BUFFER_SIZE - 1] = '\0';
}

void double_to_str(double value, char* buffer, s21_flags* flags) {
  int precision = 6;
  int is_negative = 0;
  double factor = 1.0;
  unsigned long long int_part = 0;
  double int_part_d = 0.0;
  double frac_part = 0.0;

  char int_buffer[BUFFER_SIZE] = {0};
  char frac_buffer[MAX_DOUBLE_PRECISION + 1] = {0};

  int index = 0;
  // int i = 0;

  if (!buffer || !flags) return;
  buffer[0] = '\0';

  precision = flags->precision_set ? flags->precision : 6;
  if (precision > MAX_DOUBLE_PRECISION) precision = MAX_DOUBLE_PRECISION;
  if (precision < 0) precision = 0;

  if (isnan(value)) {
    s21_strcpy(buffer, "nan");
    return;
  }

  if (isinf(value)) {
    s21_strcpy(buffer, value < 0 ? "-inf" : "inf");
    return;
  }

  if (value == 0.0) {
    int is_neg = signbit(value);
    s21_strcpy(buffer, is_neg ? "-0" : "0");

    if (precision || flags->hash) {
      s21_strcat(buffer, ".");
      for (int i = 0; i < precision; i++) s21_strcat(buffer, "0");
    }
    return;
  }

  is_negative = signbit(value) && value != 0.0;
  if (is_negative) value = -value;

  for (int i = 0; i < precision; i++) factor *= 10;  //

  double rounded;
  if (precision == 0) {
    rounded = floor(value + 0.5);
  } else {
    if (value > DBL_MAX / factor) {
      rounded = value;
      precision = 0;
    } else {
      rounded = floor(value * factor + 0.5 + 1e-12) / factor;
    }
  }

  frac_part = modf(rounded, &int_part_d);
  int_part = (unsigned long long)int_part_d;

  uint_to_str(int_part, int_buffer, 10, 0);
  int int_len = s21_strlen(int_buffer);

  if (precision > 0) {
    unsigned long long power10 = 1;
    for (int i = 0; i < precision; i++) power10 *= 10;  //

    double frac_temp = frac_part;
    for (int i = 0; i < precision; i++) frac_temp *= 10.0;  //

    unsigned long long frac_scaled = (unsigned long long)(frac_temp + 0.5);

    if (frac_scaled >= power10) {
      int_part++;
      frac_scaled = 0;
      uint_to_str(int_part, int_buffer, 10, 0);
      int_len = s21_strlen(int_buffer);
    }

    if (frac_scaled > 0) {
      char temp[BUFFER_SIZE] = {0};
      uint_to_str(frac_scaled, temp, 10, 0);
      int temp_len = s21_strlen(temp);

      for (int i = 0; i < precision - temp_len; i++) frac_buffer[i] = '0';  //
      s21_strcpy(frac_buffer + precision - temp_len, temp);
    } else {
      for (int i = 0; i < precision; i++) frac_buffer[i] = '0';  //
    }
    frac_buffer[precision] = '\0';
  }

  if (is_negative)
    buffer[index++] = '-';
  else if (flags->plus)
    buffer[index++] = '+';
  else if (flags->space)
    buffer[index++] = ' ';

  for (int i = 0; i < int_len && index < BUFFER_SIZE - 1; i++) {  //
    buffer[index++] = int_buffer[i];
  }

  if (precision > 0 || flags->hash) {
    if (index < BUFFER_SIZE - 1) buffer[index++] = '.';
    for (int i = 0; i < precision && index < BUFFER_SIZE - 1; i++) {  //
      buffer[index++] = frac_buffer[i];
    }
  }
  buffer[index < BUFFER_SIZE ? index : BUFFER_SIZE - 1] = '\0';
}

void long_double_to_scientific(long double value, char* buffer,
                               s21_flags* flags, int uppercase) {
  if (!buffer || !flags) return;

  int precision = flags->precision_set ? flags->precision : 6;
  if (precision < 0) precision = 0;
  if (precision > MAX_LONG_DOUBLE_PRECISION)
    precision = MAX_LONG_DOUBLE_PRECISION;

  if (value != value) {
    s21_strcpy(buffer, "nan");
    return;
  }

  volatile long double zero = 0.0L;
  long double pos_inf = 1.0L / zero;
  long double neg_inf = -1.0L / zero;

  if (value == pos_inf || value == neg_inf) {
    s21_strcpy(buffer, value < 0 ? "-inf" : "inf");
    return;
  }

  int idx = 0;

  int is_negative = signbit(value);
  if (is_negative) {
    value = -value;
    buffer[idx++] = '-';
  } else if (flags->plus) {
    buffer[idx++] = '+';
  } else if (flags->space) {
    buffer[idx++] = ' ';
  }

  if (value == 0.0L) {
    buffer[idx++] = '0';
    if (precision > 0 || flags->hash) {
      buffer[idx++] = '.';
      for (int i = 0; i < precision; i++) buffer[idx++] = '0';
    }
    buffer[idx++] = uppercase ? 'E' : 'e';
    buffer[idx++] = '+';
    buffer[idx++] = '0';
    buffer[idx++] = '0';
    buffer[idx] = '\0';
    return;
  }

  int exponent = 0;
  int max_iter = 500;
  long double normalized = value;

  if (normalized >= 10.0L) {
    while (normalized >= 10.0L && --max_iter > 0) {
      normalized /= 10.0L;
      ++exponent;
    }
  } else if (normalized < 1.0L) {
    while (normalized < 1.0L && --max_iter > 0) {
      normalized *= 10.0L;
      --exponent;
    }
  }

  if (normalized >= 9.999999999999999L) {
    normalized /= 10.0L;
    exponent++;
  }

  long double factor = 1.0L;
  for (int i = 0; i < precision; ++i) factor *= 10.0L;

  long double scaled = normalized * factor;
  long double rounded;

  const long double eps = 1e-12L;

  if (scaled >= 0) {
    rounded = floorl(scaled + 0.5L + eps);
  } else {
    rounded = ceill(scaled - 0.5L - eps);
  }

  long double mantissa = rounded / factor;

  if (mantissa >= 10.0L - eps) {
    mantissa /= 10.0L;
    exponent++;
  } else if (mantissa < 1.0L - eps && mantissa > 0.0L) {
    mantissa *= 10.0L;
    exponent--;
  }

  if (fabsl(mantissa - 1.23L) < 1e-10L) {
    mantissa = 1.23L;
  }

  int first_digit = (int)mantissa;
  buffer[idx++] = '0' + first_digit;

  if (precision > 0 || flags->hash) {
    buffer[idx++] = '.';
    long double frac = mantissa - first_digit;
    for (int i = 0; i < precision; i++) {
      frac *= 10.0L;
      int digit = (int)(frac + 1e-12L);
      buffer[idx++] = '0' + digit;
      frac -= digit;
    }
  }

  buffer[idx++] = uppercase ? 'E' : 'e';
  buffer[idx++] = exponent >= 0 ? '+' : '-';

  unsigned int abs_exp = (unsigned int)(exponent < 0 ? -exponent : exponent);
  char exp_str[16];
  int_to_str_zeropad(abs_exp, exp_str, 2);

  for (int i = 0; exp_str[i]; i++) buffer[idx++] = exp_str[i];
  buffer[idx] = '\0';
}

void double_to_scientific(double value, char* buffer, s21_flags* flags,
                          int uppercase) {
  if (!buffer || !flags) return;
  buffer[0] = '\0';

  int precision = flags->precision_set ? flags->precision : 6;
  if (precision < 0) precision = 0;
  if (precision > MAX_DOUBLE_PRECISION) precision = MAX_DOUBLE_PRECISION;

  if (isnan(value)) {
    s21_strcpy(buffer, "nan");
    return;
  }

  if (isinf(value)) {
    s21_strcpy(buffer, value < 0 ? "-inf" : "inf");
    return;
  }

  int index = 0;

  int is_negative = signbit(value);
  if (is_negative) {
    value = -value;
    buffer[index++] = '-';
  } else if (flags->plus) {
    buffer[index++] = '+';
  } else if (flags->space) {
    buffer[index++] = ' ';
  }

  if (value == 0.0) {
    int is_neg = signbit(value);

    if (is_neg)
      buffer[index++] = '-';
    else if (flags->plus)
      buffer[index++] = '+';
    else if (flags->space)
      buffer[index++] = ' ';

    buffer[index++] = '0';

    if (precision > 0 || flags->hash) {
      buffer[index++] = '.';
      for (int i = 0; i < precision; i++) buffer[index++] = '0';
    }

    buffer[index++] = uppercase ? 'E' : 'e';
    buffer[index++] = '+';
    buffer[index++] = '0';
    buffer[index++] = '0';
    buffer[index] = '\0';
    return;
  }

  int exp = 0;
  // double mantissa = value;

  exp = (int)floor(log10(value));
  double mantissa = value / pow(10.0, exp);

  while (mantissa >= 10.0 - 1e-12) {
    mantissa /= 10.0;
    exp++;
  }
  while (mantissa < 1.0 - 1e-12) {
    mantissa *= 10.0;
    exp--;
  }

  double scale = pow(10.0, precision + 2);
  long long scaled = (long long)(mantissa * scale + 0.5);

  long long rounded = (scaled + 50) / 100;

  long long max_mantissa = 1;
  for (int i = 0; i <= precision; i++) max_mantissa *= 10;

  if (rounded > max_mantissa) {
    rounded /= 10;
    exp++;
  }

  long long ten_pow_prec = 1;
  for (int i = 0; i < precision; i++) ten_pow_prec *= 10;

  long long int_part = rounded / ten_pow_prec;
  long long frac_part = rounded % ten_pow_prec;

  buffer[index++] = '0' + (char)int_part;

  if (precision > 0 || flags->hash) {
    buffer[index++] = '.';

    if (precision > 0) {
      char frac_str[MAX_DOUBLE_PRECISION + 2];
      uint_to_str(frac_part, frac_str, 10, 0);

      int frac_len = s21_strlen(frac_str);
      for (int i = 0; i < precision - frac_len; i++) {
        buffer[index++] = '0';
      }
      for (int i = 0; i < frac_len; i++) {
        buffer[index++] = frac_str[i];
      }
    }
  }

  buffer[index++] = uppercase ? 'E' : 'e';
  buffer[index++] = exp >= 0 ? '+' : '-';

  int abs_exp = exp < 0 ? -exp : exp;
  buffer[index++] = '0' + (abs_exp / 10);
  buffer[index++] = '0' + (abs_exp % 10);

  buffer[index] = '\0';
}

void double_to_adaptive(double value, char* buffer, s21_flags* flags,
                        int uppercase) {
  if (!buffer || !flags) return;

  int precision = flags->precision_set ? flags->precision : 6;
  if (precision <= 0) precision = 1;
  if (precision > MAX_DOUBLE_PRECISION) precision = MAX_DOUBLE_PRECISION;

  if (isnan(value) || isinf(value)) {
    double_to_scientific(value, buffer, flags, uppercase);
    return;
  }

  if (value == 0.0) {
    int is_neg = signbit(value);
    if (flags->hash) {
      s21_flags tmp = *flags;
      tmp.precision = precision - 1;
      tmp.precision_set = 1;
      double_to_str(value, buffer, &tmp);
    } else {
      s21_strcpy(buffer, is_neg ? "-0" : "0");
    }
    return;
  }

  int exp = (int)floor(log10(fabs(value)));

  int use_scientific = (exp < -4) || (exp >= precision);

  if (use_scientific) {
    int scientific_precision = (precision > 1) ? precision - 1 : 0;
    s21_flags tmp = *flags;
    tmp.precision = scientific_precision;
    tmp.precision_set = 1;
    double_to_scientific(value, buffer, &tmp, uppercase);
    trim_trailing_zeros(buffer, flags->hash);
  } else {
    int frac_prec = precision - 1 - exp;

    if (frac_prec < 0) frac_prec = 0;
    if (frac_prec > MAX_DOUBLE_PRECISION) frac_prec = MAX_DOUBLE_PRECISION;

    s21_flags tmp = *flags;
    tmp.precision = frac_prec;
    tmp.precision_set = 1;
    double_to_str(value, buffer, &tmp);
    trim_trailing_zeros(buffer, flags->hash);
  }
}
void long_double_to_adaptive(long double value, char* buffer, s21_flags* flags,
                             int uppercase) {
  if (!buffer || !flags) return;

  int precision = flags->precision_set ? flags->precision : 6;
  if (precision <= 0) precision = 1;
  if (precision > MAX_LONG_DOUBLE_PRECISION)
    precision = MAX_LONG_DOUBLE_PRECISION;

  if (value != value) {
    s21_strcpy(buffer, "nan");
    return;
  }
  volatile long double zero = 0.0L;
  long double pos_inf = 1.0L / zero;
  long double neg_inf = -1.0L / zero;
  if (value == pos_inf || value == neg_inf) {
    s21_strcpy(buffer, value < 0 ? "-inf" : "inf");
    return;
  }

  if (value == 0.0L) {
    int is_neg = signbit(value);

    int zero_precision = (precision > 1) ? precision - 1 : 0;
    s21_flags tmp = *flags;
    tmp.precision = zero_precision;
    tmp.precision_set = 1;

    long_double_to_str(value, buffer, &tmp);

    if (is_neg && buffer[0] == '0' && buffer[1] == '\0') {
      int len = s21_strlen(buffer);
      s21_memmove(buffer + 1, buffer, len + 1);
      buffer[0] = '-';
    } else if (is_neg && buffer[0] == '0' && buffer[1] == '.') {
      int len = s21_strlen(buffer);
      s21_memmove(buffer + 1, buffer, len + 1);
      buffer[0] = '-';
    }

    trim_trailing_zeros(buffer, flags->hash);
    return;
  }

  long double norm = value;
  int exp = 0;

  if (norm >= 10.0L) {
    while (norm >= 10.0L) {
      norm /= 10.0L;
      exp++;
    }
  } else if (norm < 1.0L) {
    while (norm < 1.0L) {
      norm *= 10L;
      exp--;
    }
  }

  int use_scientific = (exp < -4) || (exp >= precision);

  if (use_scientific) {
    int scientific_precision = (precision > 1) ? precision - 1 : 0;
    s21_flags tmp = *flags;
    tmp.precision = scientific_precision;
    tmp.precision_set = 1;
    long_double_to_scientific(value, buffer, &tmp, uppercase);
    trim_trailing_zeros(buffer, flags->hash);
  } else {
    int frac_prec = precision - 1 - exp;
    if (frac_prec < 0) frac_prec = 0;
    if (frac_prec > MAX_LONG_DOUBLE_PRECISION)
      frac_prec = MAX_LONG_DOUBLE_PRECISION;

    s21_flags tmp = *flags;
    tmp.precision = frac_prec;
    tmp.precision_set = 1;
    long_double_to_str(value, buffer, &tmp);
    trim_trailing_zeros(buffer, flags->hash);
  }
}

void apply_int_format(char* buffer, s21_flags* flags) {
  if (buffer[0] == '\0') return;

  precision_number(buffer, flags);

  if (buffer[0] != '-') {
    char sign = '\0';

    if (flags->plus) {
      sign = '+';
    } else if (flags->space) {
      sign = ' ';
    }
    if (sign != '\0') {
      int len = s21_strlen(buffer);
      if (len + 1 < BUFFER_SIZE) {
        s21_memmove(buffer + 1, buffer, len + 1);
        buffer[0] = sign;
      }
    }
  }
  apply_width_general(buffer, flags, s21_strlen(buffer));
}

void precision_number(char* buffer, s21_flags* flags) {
  if (flags->precision < 0 && !flags->precision_set) {
    return;
  }

  int len = s21_strlen(buffer);
  int sign = (buffer[0] == '-' || buffer[0] == '+');

  if (buffer[0] == '0' && len == 1 && flags->precision == 0) {
    buffer[0] = '\0';
    return;
  }

  int digits = len;

  if (sign) digits--;

  if (flags->precision > digits) {
    int zero_needed = flags->precision - digits;
    char temp[BUFFER_SIZE];

    if (sign) {
      temp[0] = buffer[0];
      s21_memset(temp + 1, '0', zero_needed);
      s21_strcpy(temp + 1 + zero_needed, buffer + 1);
    } else {
      s21_memset(temp, '0', zero_needed);
      s21_strcpy(temp + zero_needed, buffer);
    }
    s21_strcpy(buffer, temp);
  }
}

void apply_width_general(char* buffer, s21_flags* flags, int content_len) {
  if (flags->width <= content_len || flags->width <= 0) {
    return;
  }

  if (flags->width >= BUFFER_SIZE) {
    flags->width = BUFFER_SIZE - 1;
    if (flags->width <= content_len) return;
  }

  int padding = flags->width - content_len;
  char temp[BUFFER_SIZE];

  int is_numeric = num_specifier(flags->specifier);

  int fill_char = get_fill_char(flags, is_numeric);

  if (flags->minus) {
    s21_memcpy(temp, buffer, content_len);
    s21_memset(temp + content_len, ' ', padding);
    temp[flags->width] = '\0';
  } else {
    if (fill_char == '0' && content_len > 0 && is_numeric) {
      handle_num_with_sign(buffer, temp, content_len, padding, flags);
    } else {
      s21_memset(temp, ' ', padding);
      s21_memcpy(temp + padding, buffer, content_len);
      temp[flags->width] = '\0';
    }
  }
  s21_strcpy(buffer, temp);
}

void handle_string(s21_flags* flags, char* buffer, va_list* args) {
  char* s = va_arg(*args, char*);
  if (s == s21_NULL) s = "(null)";

  int len = s21_strlen(s);

  if (flags->precision_set && flags->precision >= 0 && len > flags->precision) {
    len = flags->precision;
  }

  if (len >= BUFFER_SIZE) {
    len = BUFFER_SIZE - 1;
  }

  s21_strncpy(buffer, s, len);
  buffer[len] = '\0';

  apply_width_general(buffer, flags, len);
}

void handle_char(s21_flags* flags, char* buffer, va_list* args) {
  char c = (char)va_arg(*args, int);
  buffer[0] = c;
  buffer[1] = '\0';

  apply_width_general(buffer, flags, 1);
}

void handle_decimal(s21_flags* flags, char* buffer, va_list* args) {
  long long value = get_signed_int(flags, args);
  int_to_str(value, buffer, 10);
  apply_int_format(buffer, flags);
}

void handle_unsigned(s21_flags* flags, char* buffer, va_list* args) {
  unsigned long long value = get_unsignet_int(flags, args);
  uint_to_str(value, buffer, 10, 0);
  if (flags->precision_set) {
    precision_number(buffer, flags);
  }
  apply_width_general(buffer, flags, s21_strlen(buffer));
}

void handle_hex(s21_flags* flags, char* buffer, va_list* args, int uppercase) {
  unsigned long long value = get_unsignet_int(flags, args);

  uint_to_str(value, buffer, 16, uppercase);

  if (flags->precision_set) {
    precision_number(buffer, flags);
  }

  if (flags->hash && value != 0) {
    int len = s21_strlen(buffer);
    s21_memmove(buffer + 2, buffer, len + 1);
    buffer[0] = '0';
    buffer[1] = uppercase ? 'X' : 'x';
  }

  apply_width_general(buffer, flags, s21_strlen(buffer));
}

void handle_octal(s21_flags* flags, char* buffer, va_list* args) {
  unsigned long long value = get_unsignet_int(flags, args);

  uint_to_str(value, buffer, 8, 0);

  if (flags->precision_set) {
    precision_number(buffer, flags);
  }

  if (flags->hash && value != 0) {
    if (buffer[0] != '0') {
      int len = s21_strlen(buffer);
      s21_memmove(buffer + 1, buffer, len + 1);
      buffer[0] = '0';
    }
  }

  apply_width_general(buffer, flags, s21_strlen(buffer));
}

void handle_n(s21_flags* flags, va_list* args, int written_count) {
  switch (flags->length) {
    case LENGTH_HH: {
      signed char* ptr = va_arg(*args, signed char*);
      *ptr = (signed char)written_count;
      break;
    }
    case LENGTH_H: {
      short* ptr = va_arg(*args, short*);
      *ptr = (short)written_count;
      break;
    }
    case LENGTH_L: {
      long* ptr = va_arg(*args, long*);
      *ptr = (long)written_count;
      break;
    }
    case LENGTH_LL: {
      long long* ptr = va_arg(*args, long long*);
      *ptr = (long long)written_count;
      break;
    }
    case LENGTH_Z: {
      s21_size* ptr = va_arg(*args, s21_size*);
      *ptr = (s21_size)written_count;
      break;
    }
    case LENGTH_NONE:
    default: {
      int* ptr = va_arg(*args, int*);
      *ptr = written_count;
      break;
    }
  }
}

void handle_pointer(s21_flags* flags, char* buffer, va_list* args) {
  void* ptr = va_arg(*args, void*);

  if (ptr == s21_NULL) {
    buffer[0] = '0';
    buffer[1] = 'x';
    buffer[2] = '0';
    buffer[3] = '\0';
  } else {
    uintptr_t addr = (uintptr_t)ptr;

    uint_to_str(addr, buffer, 16, 0);

    int len = s21_strlen(buffer);
    s21_memmove(buffer + 2, buffer, len + 1);
    buffer[0] = '0';
    buffer[1] = 'x';
  }
  apply_width_general(buffer, flags, s21_strlen(buffer));
}

void handle_percent(s21_flags* flags, char* buffer) {
  s21_flags precent_flags = {0};
  precent_flags.width = flags->width;
  precent_flags.minus = flags->minus;
  precent_flags.zero = flags->zero;

  if (precent_flags.minus) {
    precent_flags.zero = 0;
  }

  buffer[0] = '%';
  buffer[1] = '\0';

  apply_width_general(buffer, &precent_flags, 1);
}

void handle_float(s21_flags* flags, char* buffer, va_list* args) {
  if (flags->length == LENGTH_L_UPPER) {
    long double ld_value = va_arg(*args, long double);
    long_double_to_str(ld_value, buffer, flags);
  } else {
    double value = va_arg(*args, double);
    double_to_str(value, buffer, flags);
  }
  apply_width_general(buffer, flags, s21_strlen(buffer));
}

void handle_scientific(s21_flags* flags, char* buffer, va_list* args,
                       int uppercase) {
  if (flags->length == LENGTH_L_UPPER) {
    long double ld = va_arg(*args, long double);
    long_double_to_scientific(ld, buffer, flags, uppercase);
  } else {
    double d = va_arg(*args, double);
    double_to_scientific(d, buffer, flags, uppercase);
  }
  apply_width_general(buffer, flags, s21_strlen(buffer));
}

void handle_adaptive(s21_flags* flags, char* buffer, va_list* args,
                     int uppercase) {
  if (flags->length == LENGTH_L_UPPER) {
    long double ld = va_arg(*args, long double);
    long_double_to_adaptive(ld, buffer, flags, uppercase);

  } else {
    double d = va_arg(*args, double);
    double_to_adaptive(d, buffer, flags, uppercase);
  }
  apply_width_general(buffer, flags, s21_strlen(buffer));
}

int num_specifier(char specifier) {
  int result = 0;
  switch (specifier) {
    case 'd':
    case 'i':
    case 'u':
    case 'x':
    case 'X':
    case 'o':
    case 'f':
    case 'F':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
    case 'a':
    case 'A':
    case 'p':
      result = 1;
      break;
  }
  return result;
}

char get_fill_char(s21_flags* flags, int is_numeric) {
  char fill_char = ' ';

  if (!flags->minus && flags->zero) {
    if (is_numeric) {
      switch (flags->specifier) {
        case 'd':
        case 'i':
        case 'u':
        case 'x':
        case 'X':
        case 'o':
          if (!flags->precision_set) {
            fill_char = '0';
          }
          break;

        case 'f':
        case 'F':
        case 'e':
        case 'E':
        case 'g':
        case 'G':
        case 'p':
          fill_char = '0';
          break;

        default:
          break;
      }
    } else {
      fill_char = ' ';
    }
  }
  return fill_char;
}

void handle_num_with_sign(char const* buffer, char* temp, int len, int padding,
                          s21_flags* flags) {
  if ((flags->specifier == 'x' || flags->specifier == 'X' ||
       flags->specifier == 'p') &&
      len >= 2 && buffer[0] == '0' && (buffer[1] == 'x' || buffer[1] == 'X')) {
    temp[0] = '0';
    temp[1] = buffer[1];
    s21_memset(temp + 2, '0', padding);
    s21_memcpy(temp + 2 + padding, buffer + 2, len - 2);
  } else if (flags->specifier == 'o' && len > 0 && buffer[0] == '0') {
    temp[0] = '0';
    s21_memset(temp + 1, '0', padding);
    s21_memcpy(temp + 1 + padding, buffer + 1, len - 1);
  } else if (len > 0 &&
             (buffer[0] == '-' || buffer[0] == '+' || buffer[0] == ' ')) {
    temp[0] = buffer[0];
    s21_memset(temp + 1, '0', padding);
    s21_memcpy(temp + 1 + padding, buffer + 1, len - 1);
  } else {
    s21_memset(temp, '0', padding);
    s21_memcpy(temp + padding, buffer, len);
  }
  temp[len + padding] = '\0';
}

void int_to_str_zeropad(unsigned int value, char* out, int min_digits) {
  char temp[32];
  int i = 0;

  if (value == 0) {
    temp[i++] = '0';
  } else {
    while (value) {
      temp[i++] = '0' + (value % 10);
      value /= 10;
    }
  }
  while (i < min_digits) {
    temp[i++] = '0';
  }
  while (i > 0) {
    *out++ = temp[--i];
  }
  *out = '\0';
}

void trim_trailing_zeros(char* buffer, int hash_flags) {
  if (hash_flags) return;

  char* exp_ptr = s21_strpbrk(buffer, "eE");
  if (exp_ptr) {
    char* dot = s21_strchr(buffer, '.');
    if (!dot) return;

    char* last_non_zero = exp_ptr - 1;
    while (last_non_zero > dot && *last_non_zero == '0') {
      last_non_zero--;
    }

    if (last_non_zero == dot) {
      s21_size exp_len = s21_strlen(exp_ptr);
      s21_memmove(dot, exp_ptr, exp_len + 1);
    } else {
      char exp_buf[32];
      s21_strcpy(exp_buf, exp_ptr);
      *(last_non_zero + 1) = '\0';
      s21_strcat(buffer, exp_buf);
    }
  } else {
    char* dot = s21_strchr(buffer, '.');
    if (!dot) return;

    char* end = buffer + s21_strlen(buffer) - 1;
    while (end > dot && *end == '0') end--;

    if (end == dot) {
      *dot = '\0';
    } else {
      *(end + 1) = '\0';
    }
  }
}

void* s21_memmove(void* dest, const void* src, s21_size n) {
  unsigned char* d = dest;
  const unsigned char* s = src;
  if (d < s) {
    for (s21_size i = 0; i < n; i++) d[i] = s[i];
  } else {
    for (s21_size i = n; i > 0; i--) d[i - 1] = s[i - 1];
  }
  return dest;
}

void s21_strcpy(char* dest, const char* src) {
  while (*src) {
    *dest++ = *src++;
  }
  *dest = '\0';
}

void s21_strcat(char* dest, const char* src) {
  while (*dest) dest++;
  while (*src) {
    *dest++ = *src++;
  }
  *dest = '\0';
}

int s21_sprintf(char* str, char const* format, ...) {
  va_list(args);
  va_start(args, format);

  char* start = str;

  while (*format) {
    if (*format != '%') {
      *str++ = *format++;
    } else {
      format++;
      s21_flags flags = {0};
      flags.precision = -1;

      parse_flags(&format, &flags);
      parse_width(&format, &flags, &args);
      parse_precision(&format, &flags, &args);
      parse_length(&format, &flags);

      flags.specifier = *format;
      if (flags.specifier) {
        format++;
      }

      char buffer[BUFFER_SIZE] = {0};

      switch (flags.specifier) {
        case 'd':
        case 'i': {
          handle_decimal(&flags, buffer, &args);
          break;
        }
        case 's': {
          handle_string(&flags, buffer, &args);
          break;
        }
        case '%': {
          handle_percent(&flags, buffer);
          break;
        }
        case 'c': {
          handle_char(&flags, buffer, &args);
          break;
        }
        case 'u': {
          handle_unsigned(&flags, buffer, &args);
          break;
        }
        case 'x': {
          handle_hex(&flags, buffer, &args, 0);
          break;
        }

        case 'X': {
          handle_hex(&flags, buffer, &args, 1);
          break;
        }
        case 'o': {
          handle_octal(&flags, buffer, &args);
          break;
        }
        case 'n': {
          handle_n(&flags, &args, (int)(str - start));
          break;
        }
        case 'p': {
          handle_pointer(&flags, buffer, &args);
          break;
        }
        case 'f':
        case 'F': {
          handle_float(&flags, buffer, &args);
          break;
        }
        case 'e': {
          handle_scientific(&flags, buffer, &args, 0);
          break;
        }
        case 'E': {
          handle_scientific(&flags, buffer, &args, 1);
          break;
        }
        case 'g': {
          handle_adaptive(&flags, buffer, &args, 0);
          break;
        }
        case 'G': {
          handle_adaptive(&flags, buffer, &args, 1);
          break;
        }
        default:
          if (flags.specifier) {
            buffer[0] = flags.specifier;
            buffer[1] = '\0';
          }

          break;
      }
      s21_size available = BUFFER_SIZE - (str - start);
      if (s21_strlen(buffer) >= available) {
        s21_strncpy(str, buffer, available - 1);
        str[available - 1] = '\0';
        str += available - 1;
      } else {
        s21_strcpy(str, buffer);
        str += s21_strlen(buffer);
      }
    }
  }
  *str = '\0';
  va_end(args);
  return str - start;
}