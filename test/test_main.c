#include <stdio.h>

#include "utils/test_array.h"
#include "utils/test_number.h"

int main()
{
    test_get_int_from_str();
    test_array_has_value();

    printf("ALL TESTS PASSED!\n");

    return 0;
}
