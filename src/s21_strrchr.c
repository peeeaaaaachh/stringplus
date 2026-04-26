#include "s21_string.h"
// функция поиска символа справа налево
char* s21_strrchr(const char* str, int c) {
  char* s = s21_NULL;
  int flag = 0;
  int i = s21_strlen(str);
  do {
    if (str[i] == c && flag == 0) {
      s = ((char*)&str[i]);
      flag = 1;
    }
    i--;
  } while (i >= 0);
  return s;
}