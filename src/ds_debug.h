#ifndef DSLIB_DS_DEBUG_H_
#define DSLIB_DS_DEBUG_H_

#include <math.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#ifdef DS_LOG_DEBUG_ON
    #define DS_LOG_DEBUG(fmt, args...) ds_basic_log(__FILE__, __LINE__, fmt, ## args)
#else
    #define DS_LOG_DEBUG(fmt, args...)
#endif

#define DS_EQUAL(a, b)          ( (a) == (b) )
#define DS_EQUAL_FLOAT(a, b)    ( fabs((a)-(b)) < 1e-8 )
#define DS_EQUAL_STR(a, b)      ( strcmp((a), (b)) == 0)

void ds_basic_log(const char *filename, int line, const char *fmt, ...)
{
    int len;
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "[BASIC] %s:%d ", filename, line);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
}

#endif /* end of DSLIB_DS_DEBUG_H_ */
