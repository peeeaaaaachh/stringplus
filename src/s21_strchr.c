#include "s21_string.h"
// функция поиска символа слева направо
char* s21_strchr(const char* str, int c) {
  char* s = s21_NULL;
  int flag = 0;
  for (s21_size i = 0; i <= s21_strlen(str); i++) {
    if (str[i] == c && flag == 0) {
      s = ((char*)&str[i]);
      flag = 1;
    }
  }
  return s;
}