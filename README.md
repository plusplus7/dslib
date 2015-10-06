dslib, codes for programming competitions and contests
=============

### ds_debug.h

For debug and test

* macro DS_LOG_DEBUG

Print a line of debug message

    #define DS_LOG_DEBUG_ON
    #include "ds_debug.h"

    DS_LOG_DEBUG("%s %d", str, n)

* macro DS_EQUAL*(a, b)

Tell whether variable a and b equal

    int a, b;
    double c, d;
    char e[7], f[7]
    DS_EQUAL(a, b)
    DS_EQUAL_FLOAT(c, d)
    DS_EQUAL_STR(e, f)

### ds_multiple_precision.h

* marco 
