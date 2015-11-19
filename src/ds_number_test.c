#include "ds_number.h"
#define DS_LOG_DEBUG_ON
#include "ds_debug.h"

int test_ds_fast_power()
{
    long long a = 0ll;
    a = ds_fast_power(2, 32);
    if (!DS_EQUAL(a, 4294967296ll)) {
        DS_LOG_DEBUG("ds_fast_power got wrong: %lld", a);
        return 1;
    }
    a = ds_fast_power(777, 5);
    if (!DS_EQUAL(a, 283207724127657ll)) {
        DS_LOG_DEBUG("ds_fast_power got wrong: %lld", a);
        return 1;
    }
    for (int i=700; i<720; i++) {
        for (int j=0; j<5; j++) {
            double c = pow(i, j);
            long long cc = ds_fast_power(i, j);
            if (!DS_EQUAL(cc, c)) {
                DS_LOG_DEBUG("ds_fast_power got wrong: %lld pow(%d %d)", cc, i, j);
                return 1;
            }
        }
    }
    return 0;
}

int run_tests()
{
    DS_UNITTEST_START(ds_number_test);
    DS_UNITTEST_ADD(test_ds_fast_power);
    DS_UNITTEST_END(ds_number_test);
}

int main()
{
    return run_tests();
}
