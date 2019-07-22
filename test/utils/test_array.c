#include <assert.h>

#include "utils/array.h"
#include "test_array.h"

void test_array_has_value()
{
    int a1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int a2[] = {};
    int len_a1 = sizeof(a1) / sizeof(int);
    int len_a2 = sizeof(a2) / sizeof(int);

    assert(array_has_value(a1, len_a1, 1) == 1);
    assert(array_has_value(a1, len_a1, 7) == 1);
    assert(array_has_value(a1, len_a1, 10) == 1);
    assert(array_has_value(a1, len_a1, 0) == 0);
    assert(array_has_value(a1, len_a1, -1) == 0);

    assert(array_has_value(a2, len_a2, -1) == 0);
    assert(array_has_value(a2, len_a2, 1) == 0);
    assert(array_has_value(a2, len_a2, 0) == 0);
}
