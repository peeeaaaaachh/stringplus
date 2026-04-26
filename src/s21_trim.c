#include "s21_string.h"

void* s21_trim(const char* src, const char* trim_chars) {
  /**
   * @note	ВНИМАНИЕ: Вызывающий должен освободить память через free()!
   */

  char* res = s21_NULL;

  if (src && trim_chars) {
    // Если src пустая строка
    if (*src == '\0') {
      res = malloc(1);
      if (res) res[0] = '\0';
    }
    // Если trim_chars пустая строка - возвращаем копию src
    else if (*trim_chars == '\0') {
      s21_size len = s21_strlen(src);
      res = malloc(len + 1);
      if (res) {
        s21_memcpy(res, src, len);
        res[len] = '\0';
      }
    } else {
      const char* start = src;
      while (*start && s21_strchr(trim_chars, *start)) {
        start++;
      }

      if (*start == '\0') {
        res = malloc(1);
        if (res) res[0] = '\0';
      } else {
        const char* end = src + s21_strlen(src) - 1;
        while (end > start && s21_strchr(trim_chars, *end)) {
          end--;
        }

        s21_size len = end - start + 1;
        res = malloc(len + 1);

        if (res) {
          s21_memcpy(res, start, len);
          res[len] = '\0';
        }
      }
    }
  }

  return res;
}
