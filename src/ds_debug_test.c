#define DS_LOG_DEBUG_ON
#include "ds_debug.h"

int main()
{
    DS_LOG_DEBUG("%s", "2333");
    DS_LOG_DEBUG("I have %c big apple, %d blue %s and %x bad pears", 'a', 2, "bananas", 300);
    return 0;
}
