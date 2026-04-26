#include "s21_string.h"
// функция для преобразования строки в верхний регистр
void* s21_to_upper(const char* str) {
  char* str_copy = s21_NULL;

  if (str != s21_NULL) {
    s21_size len = s21_strlen(str);
    str_copy = (char*)malloc((len + 1));

    if (str_copy != s21_NULL) {
      s21_size i = 0;

      for (; str[i] != '\0'; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
          str_copy[i] = str[i] - 32;
        } else
          str_copy[i] = str[i];
      }
      str_copy[i] = '\0';
    }
  }
  return str_copy;
}