#include "ds_multiple_precision.h"

#define DS_LOG_DEBUG_ON
#include "ds_debug.h"

#include <stdio.h>
#include <string.h>

int test_dmp_new()
{
    {
        dmp_t *a = dmp_new(a, 100);
        if (DS_EQUAL(a, NULL)) {
            DS_LOG_DEBUG("dmp_init get NULL: %d", a);
            return 1;
        }
        if (!DS_EQUAL(a->n, 100)) {
            DS_LOG_DEBUG("dmp_init get not 100 a->n: %d", a->n);
            return 1;
        }
        dmp_free(a);
    }
    return 0;
}

int test_dmp_init()
{
    {
        dmp_t a;
        int s[100] = {1, 2, 3, 4};
        dmp_init(&a, 100, s);
        if (!DS_EQUAL(a.n, 100)) {
            DS_LOG_DEBUG("dmp_init get not 100 a->n: %d", a.n);
            return 1;
        }
        int i;
        for (i=0; i<4; i++) {
            if (!DS_EQUAL(a.s[i], i+1)) {
                DS_LOG_DEBUG("dmp_init get not %d a->s[%d]: %d", s[i], i, a.s[i]);
            }
        }
    }

    return 0;
}

int test_dmp_load_str()
{
    {
        char s[30] = "110120130401010404050007070";
        dmp_t a;
        int sn[100];
        dmp_init(&a, 100, sn);
        dmp_load_str(&a, s);
        if (!DS_EQUAL(a.n, strlen(s))) {
            DS_LOG_DEBUG("dmp_init get not %d a->n: %d", strlen(s), a.n);
            return 1;
        }
        int i;
        for (i=0; i<a.n; i++) {
            if (!DS_EQUAL(a.s[i]+'0', s[strlen(s)-i-1])) {
                DS_LOG_DEBUG("dmp_init get not %c a->s[%d]: %c", s[strlen(s)-i-1], i, a.s[i]+'0');
                return 1;
            }
        }
    }
    return 0;
}

int test_dmp_get_str()
{
    {
        char s[30] = "110120130401010404050007070";
        dmp_t a;
        int sn[100];
        dmp_init(&a, 100, sn);
        dmp_load_str(&a, s);
        if (!DS_EQUAL(a.n, strlen(s))) {
            DS_LOG_DEBUG("dmp_init get not %d a->n: %d", strlen(s), a.n);
            return 1;
        }
        int i;
        for (i=0; i<a.n; i++) {
            if (!DS_EQUAL(a.s[i]+'0', s[strlen(s)-i-1])) {
                DS_LOG_DEBUG("dmp_init get not %c a->s[%d]: %c", s[strlen(s)-i-1], i, a.s[i]+'0');
                return 1;
            }
        }
        char res[100];
        if (!DS_EQUAL_STR(dmp_get_str(&a, res), s)) {
            DS_LOG_DEBUG("dmp_get_str get not %s: %s", s, res);
            return 1;
        }
        return 0;
    }
}

int test_dmp_add_s()
{
    {
        char s[5][3][100] = {
            {"99999999999999999999999999", "99999999999999999999999999999999", "100000099999999999999999999999998"},
            {"999999999999999999999999999", "1", "1000000000000000000000000000"},
            {"999999999999999999999999999", "8888888888888888888888888888888888", "8888889888888888888888888888888887"},
            {"00222", "0011", "233"},
            {"0", "0", "0"},
        };
        int i;
        for (i=0; i<5; i++) {
            dmp_t a, b, c;
            int an[100], bn[100], cn[100];
            dmp_init(&a, 100, an);
            dmp_init(&b, 100, bn);
            dmp_init(&c, 100, cn);
            dmp_load_str(&a, s[i][0]);
            dmp_load_str(&b, s[i][1]);
            dmp_add_s(&c, &a, &b);
            char res[100];
            if (!DS_EQUAL_STR(dmp_get_str(&c, res), s[i][2])) {
                DS_LOG_DEBUG("dmp_add_s no good, case %d: c: %s expected: %s", i, dmp_get_str(&c, res), s[i][2]);
                return 1;
            }
        }
    }
    return 0;
}

int test_dmp_sub_s()
{
    {
        char s[6][3][100] = {
            {"9", "9", "0"},
            {"010010", "1", "10009"},
            {"990", "90", "900"},
            {"1900", "900", "1000"},
            {"1900", "1000", "900"},
            {"999999999999999999999999999","1", "999999999999999999999999998"},
        };
        int i;
        for (i=0; i<5; i++) {
            dmp_t a, b, c;
            int an[100], bn[100], cn[100];
            dmp_init(&a, 100, an);
            dmp_init(&b, 100, bn);
            dmp_init(&c, 100, cn);
            dmp_load_str(&a, s[i][0]);
            dmp_load_str(&b, s[i][1]);
            dmp_sub_s(&c, &a, &b);
            char res[100];
            if (!DS_EQUAL_STR(dmp_get_str(&c, res), s[i][2])) {
                DS_LOG_DEBUG("dmp_add_s no good, case %d: c: %s expected: %s", i, dmp_get_str(&c, res), s[i][2]);
                return 1;
            }
        }
    }
    return 0;
}

int test_dmp_mul_s()
{
    {
        char s[4][3][100] = {
            {"10000000000", "10", "100000000000"},
            {"1", "100000000000000", "100000000000000"},
            {"99", "99", "9801"},
            {"123456789", "987654321", "121932631112635269"},
        };
        int i;
        for (i=0; i<4; i++) {
            dmp_t a, b, c;
            int an[100], bn[100], cn[100];
            dmp_init(&a, 100, an);
            dmp_init(&b, 100, bn);
            dmp_init(&c, 100, cn);
            dmp_load_str(&a, s[i][0]);
            dmp_load_str(&b, s[i][1]);
            dmp_mul_s(&c, &a, &b);
            char res[100];
            if (!DS_EQUAL_STR(dmp_get_str(&c, res), s[i][2])) {
                DS_LOG_DEBUG("dmp_add_s no good, case %d: c: %s expected: %s", i, dmp_get_str(&c, res), s[i][2]);
                return 1;
            }
        }
    }
    return 0;
}

int run_tests()
{
    int res = 1;
    int overall = 0;

    printf("* Running test_dmp_init\n");
    res = test_dmp_init();
    overall = overall + res;
    printf("* test_dmp_init: %s\n\n", !res?"PASS":"FAILED");

    printf("* Running test_dmp_new\n");
    res = test_dmp_new();
    overall = overall + res;
    printf("* test_dmp_new: %s\n\n", !res?"PASS":"FAILED");

    printf("* Running test_dmp_load_str\n");
    res = test_dmp_load_str();
    overall = overall + res;
    printf("* test_dmp_load_str: %s\n\n", !res?"PASS":"FAILED");

    printf("* Running test_dmp_get_str\n");
    res = test_dmp_get_str();
    overall = overall + res;
    printf("* test_dmp_get_str: %s\n\n", !res?"PASS":"FAILED");

    printf("* Running test_dmp_add_s\n");
    res = test_dmp_add_s();
    overall = overall + res;
    printf("* test_dmp_add_s: %s\n\n", !res?"PASS":"FAILED");

    printf("* Running test_dmp_sub_s\n");
    res = test_dmp_sub_s();
    overall = overall + res;
    printf("* test_dmp_sub_s: %s\n\n", !res?"PASS":"FAILED");

    printf("* Running test_dmp_mul_s\n");
    res = test_dmp_mul_s();
    overall = overall + res;
    printf("* test_dmp_mul_s: %s\n\n", !res?"PASS":"FAILED");
    return overall;
}

int main()
{
    return run_tests();
}
