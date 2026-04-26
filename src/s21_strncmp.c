#include "s21_string.h"
// функция сравнения строк только уже до n-го элемента
int s21_strncmp(const char* s1, const char* s2, s21_size n) {
  s21_size i = 0;
  int res = 0;
  int flag = 0;
  while (s1[i] != '\0' && s2[i] != '\0' && flag == 0 && i < n) {
    if (s1[i] != s2[i]) {
      flag = 1;
      res = s1[i] - s2[i];
    }
    i++;
  }
  if (res == 0 && i < n && flag == 0) {
    res = s1[i] - s2[i];
  }
  return res;
}
