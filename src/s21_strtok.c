#include "s21_string.h"

char* s21_strtok(char* str, const char* delim) {
  static char* saved_ptr = s21_NULL;
  char* current_pos = str ? str : saved_ptr;
  char* result = s21_NULL;

  if (current_pos && delim) {
    // пропускаем разделители если они стоят в начале строки
    while (*current_pos && s21_strchr(delim, *current_pos)) {
      current_pos++;
    }
    // если токен существует, запоминаем его начало
    if (*current_pos) {
      result = current_pos;

      int delim_found = 0;
      // ищем конец токена
      while (*current_pos && !delim_found) {
        if (s21_strchr(delim, *current_pos)) {
          *current_pos = '\0';
          saved_ptr = current_pos + 1;

          // пропускаем разделители после найденного токена
          while (*saved_ptr && s21_strchr(delim, *saved_ptr)) {
            saved_ptr++;
          }
          delim_found = 1;
        }
        current_pos++;
      }

      if (!delim_found) {
        saved_ptr = s21_NULL;
      }
    } else {
      saved_ptr = s21_NULL;
    }
  } else {
    saved_ptr = s21_NULL;
  }

  return result;
}
