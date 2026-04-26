#include "s21_string.h"
// функция выводит кол во символов до первого такого же элемента
s21_size s21_strcspn(const char* str1, const char* str2) {
  int flag = 0;
  int found = 0;
  s21_size length = 0;
  for (s21_size i = 0; str1[i] != '\0' && flag == 0; i++) {
    for (s21_size j = 0; str2[j] != '\0'; j++) {
      if (str1[i] == str2[j]) {
        found = 1;
      }
    }
    if (found) {
      flag = 1;
    } else
      length++;
  }

  return length;
}
