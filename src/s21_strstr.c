#include "s21_string.h"
// функция для поиска слева направо фрагмента другой строки
char* s21_strstr(const char* haystack, const char* needle) {
  char* s = s21_NULL;
  if (*needle == '\0') {
    s = (char*)haystack;
  } else {
    s21_size i = 0;
    s21_size j = 0;
    while (haystack[i] && s == s21_NULL) {
      while (needle[j] && haystack[i + j] == needle[j]) {
        j++;
      }
      if (needle[j] == '\0') {
        s = (char*)&haystack[i];
      }
      i++;
    }
  }

  return s;
}
