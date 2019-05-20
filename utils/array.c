#include "array.h"

int array_has_value(int *arr, int arr_size, int val) {
  int i;
  for (i = 0; i < arr_size; i++) {
    if (arr[i] == val) {
      return 1;
    }
  }

  return 0;
}

