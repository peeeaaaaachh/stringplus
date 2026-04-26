#include "s21_string.h"
// функция для определения первого вхождения какого то элемента в буфер
void* s21_memchr(const void* str, int c, s21_size n) {
  const unsigned char* s = (const unsigned char*)str;
  char* p = s21_NULL;
  int flag = 0;
  for (s21_size i = 0; i < n; i++) {
    if (s[i] == c && flag == 0) {
      p = ((char*)&s[i]);
      flag = 1;
    }
  }
  return p;
}