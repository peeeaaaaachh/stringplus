#include "s21_string.h"

char* s21_strerror(int errnum) {
  char* result = s21_NULL;

  if (errnum >= 0 && errnum < errors_array_size && errors_array[errnum]) {
    result = (char*)errors_array[errnum];
  } else {
    static char buffer[STRERROR_BUF_SIZE];
#ifdef __linux__
    snprintf(buffer, sizeof(buffer), "Unknown error %d", errnum);
#endif
#if defined(__APPLE__) && defined(__MACH__)
    snprintf(buffer, sizeof(buffer), "Unknown error: %d", errnum);
#endif
    result = buffer;
  }

  return result;
}
