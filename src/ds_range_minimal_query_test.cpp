#include "ds_range_minimal_query.hpp"
#define DS_LOG_DEBUG_ON
#include "ds_debug.h"

int test_ds_rmq_simple()
{
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    dslib::DsRmqInstance<int> ai;
    ai.init(a, 8);
    for (int i=0; i<8; i++) {
        int j = ai.query(i, 7);
        if (!DS_EQUAL(j, i+1)) {
            DS_LOG_DEBUG("test_ds_rmq_simple got wrong: ai.query(%d, 8)=%d expected: %d", i, j, i+1);
            return 1;
        }
        int j2 = ai.query(0, i);
        if (!DS_EQUAL(j2, 1)) {
            DS_LOG_DEBUG("test_ds_rmq_simple got wrong: ai.query(0, %d)=%d expected: %d", i, j2, 1);
            return 1;
        }
    }
    return 0;
}

int run_tests()
{
    DS_UNITTEST_START(ds_range_minimal_query_test);
    DS_UNITTEST_ADD(test_ds_rmq_simple);
    DS_UNITTEST_END(ds_range_minimal_query_test);
}

int main()
{
    return run_tests();
}
