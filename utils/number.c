#include <limits.h>
#include <stdlib.h>

#include "number.h"

int get_int_from_str(char *str) {
  long val;
  char *p;

  val = strtol(str, &p, 10);

  if (*p != '\0' || val > INT_MAX) {
    return -1;
  }

  return (int) val;
}
