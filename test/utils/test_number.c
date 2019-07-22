#include <assert.h>

#include "utils/number.h"
#include "test_number.h"

void test_get_int_from_str()
{
    assert(get_int_from_str("10") == 10);
    assert(get_int_from_str("0") == 0);
    assert(get_int_from_str("-10") == -10);
    assert(get_int_from_str("NaN") == -1);
}
