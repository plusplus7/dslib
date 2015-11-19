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

#define DS_UNITTEST_START(testname)  { printf("\n[\033[32m  START  \033[00m]: Test %s start\n", #testname); int overall = 0; int res = 0; do {
#define DS_UNITTEST_ADD(casename) do {printf("[\033[32m  RUN    \033[00m]: Running %s\n", #casename); res = casename(); overall = overall + res; printf("%s: %s\n", !res?"[\033[32m  PASS   \033[00m]":"[\033[31m  FAILED \033[00m]", #casename);}while(0);
#define DS_UNITTEST_END(testname)     printf("\n* Test %s %s\n\n", #testname, !overall?"\033[32mPASS\033[00m":"\033[31mFAILED\033[00m");  } while(0); return overall; }

#endif /* end of DSLIB_DS_DEBUG_H_ */
