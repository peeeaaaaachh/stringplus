#include "s21_string.h"
// функция для конкатенации строк и копирует только n элементы
char* s21_strncat(char* dest, const char* src, s21_size n) {
  s21_size i = 0;
  s21_size dest_length = s21_strlen(dest);
  for (; i < n && src[i] != '\0'; i++) {
    dest[dest_length + i] = src[i];
  }
  dest[dest_length + i] = '\0';
  return dest;
}