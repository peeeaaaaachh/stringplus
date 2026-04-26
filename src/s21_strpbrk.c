#include "s21_string.h"
// функция для поиска символовов из одного массива в другом в строке str поиск
char* s21_strpbrk(const char* str1, const char* str2) {
  char* s = s21_NULL;
  int flag = 0;
  for (s21_size i = 0; str1[i] != '\0' && flag == 0; i++) {
    for (s21_size j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        s = ((char*)&str1[i]);
        flag = 1;
      }
    }
  }
  return s;
}
