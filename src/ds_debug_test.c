#define DS_LOG_DEBUG_ON
#include "ds_debug.h"

int asdf()
{
    return 0;
}

int run_tests()
{
    DS_UNITTEST_START(asdf);
    DS_UNITTEST_ADD(asdf);
    DS_UNITTEST_END(asdf);
}
int main()
{
    DS_LOG_DEBUG("%s", "2333");
    DS_LOG_DEBUG("I have %c big apple, %d blue %s and %x bad pears", 'a', 2, "bananas", 300);
    return run_tests();
}
