#include "s21_string.h"
// функция для сравнения буферов
int s21_memcmp(const void* str1, const void* str2, s21_size n) {
  const unsigned char* p = (const unsigned char*)str1;
  const unsigned char* s = (const unsigned char*)str2;
  int flag = 0;
  int res = 0;
  for (s21_size i = 0; i < n && flag == 0; i++) {
    if (s[i] != p[i]) {
      res = p[i] - s[i];
      flag = 1;
    }
  }
  return res;
}
