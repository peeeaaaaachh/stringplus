#include "s21_string.h"
// функция копирования из одного буфера(или структуры) в другую
void* s21_memcpy(void* dest, const void* src, s21_size n) {
  if (dest != s21_NULL && src != s21_NULL) {
    unsigned char* s = (unsigned char*)dest;
    const unsigned char* p = (const unsigned char*)src;
    for (s21_size i = 0; i < n; i++) {
      s[i] = p[i];
    }
  }
  return dest;
}
