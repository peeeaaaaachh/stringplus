#include "s21_string.h"

// функця для вставки одной строки в другую
void* s21_insert(const char* src, const char* str, s21_size start_index) {
  char* result = s21_NULL;

  if (src != s21_NULL && str != s21_NULL) {
    s21_size src_len = s21_strlen(src);

    if (start_index <= src_len) {
      s21_size str_len = s21_strlen(str);
      s21_size total_len = src_len + str_len;

      result = (char*)malloc((total_len + 1));

      if (result != s21_NULL) {
        s21_size i = 0;
        s21_size j = 0;

        for (; i < start_index; i++) {
          result[i] = src[i];
        }
        for (; str[j] != '\0'; j++) {
          result[i + j] = str[j];
        }
        s21_size k = i + j;
        for (; src[i] != '\0'; i++, k++) {
          result[k] = src[i];
        }
        result[k] = '\0';
      }
    }
  }
  return result;
}