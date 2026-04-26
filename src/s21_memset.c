#include "s21_string.h"
// функция для установления нужного значения в буфер
void* s21_memset(void* str, int c, s21_size n) {
  unsigned char* s = (unsigned char*)str;
  for (s21_size i = 0; i < n; i++) {
    s[i] = (unsigned char)c;
  }
  return str;
}
