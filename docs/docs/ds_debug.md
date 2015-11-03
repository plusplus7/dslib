# ds_debug.h

The debugging and testing module
=============

#### DS_LOG_DEBUG(fmt, args)

Print a line of debug message

```c
    #define DS_LOG_DEBUG_ON
    #include "ds_debug.h"

    DS_LOG_DEBUG("%s %d", str, n)
```

#### DS_EQUAL*(a, b)

Tell whether variable a and b equal

Return bool

```c
    int a, b;
    double c, d;
    char e[7], f[7]
    DS_EQUAL(a, b)
    DS_EQUAL_FLOAT(c, d)
    DS_EQUAL_STR(e, f)
```
