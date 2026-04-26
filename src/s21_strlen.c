#include "s21_string.h"
// функция определения длины строки
s21_size s21_strlen(const char* str) {
  const char* s1 = str;
  s21_size length = 0;
  while (*s1++) {
    length++;
  }
  return length;
}