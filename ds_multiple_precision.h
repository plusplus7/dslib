#ifndef DSLIB_DS_MULTIPLE_PRECISION_H_
#define DSLIB_DS_MULTIPLE_PRECISION_H_

#include <stdlib.h>
#include <string.h>

#define DMP_ABS(x)   ((x) >= 0 ? (x) : -(x))
#define DMP_MAX(a, b) ((a) > (b) ? (a) : (b))
#define DMP_MIN(a, b) ((a) < (b) ? (a) : (b))

typedef struct {
    int *s;
    int n;
} dmp_t;

dmp_t*  dmp_new(dmp_t *r, int n);
void    dmp_init(dmp_t *r, int n, int *s);
void    dmp_load_str(dmp_t *r, const char *s);
int     dmp_add_s(dmp_t *r, const dmp_t *a, const dmp_t *b);
char*   dmp_get_str(dmp_t *r, char *s);
void    dmp_free(dmp_t *r);
int     _dmp_abs_add(dmp_t *r, const dmp_t *a, const dmp_t *b);

dmp_t* dmp_new(dmp_t *r, int n)
{
    r    = (dmp_t *) malloc(sizeof(dmp_t));
    r->s = (int *) malloc(DMP_ABS(n)*sizeof(int));
    r->n = n;
    return r;
}

void dmp_free(dmp_t *r)
{
    if (!r) {
        return ;
    }
    if (r->s) {
        free((void *) r->s);
    }
    free((void *) r);
}

void dmp_init(dmp_t *r, int n, int *s)
{
    r->s = s;
    r->n = n;
}

void dmp_load_str(dmp_t *r, const char *s)
{
    int i = 0, j, ls = strlen(s);
    while (s[i] == '0' && i < ls-1) i++;
    r->n = ls-i;
    for (j=0; i < ls; i++, j++) {
        r->s[j] = s[ls-1-j] - '0';
    }
}

char* dmp_get_str(dmp_t *r, char *s)
{
    int ln = DMP_ABS(r->n);
    int ls = ln + (r->n < 0) + 1;
    if (!s) {
        s = (char *) malloc(ls * sizeof(char));
    }
    int i, j;
    s[ls-1] = '\0';
    for (i=0, j=ls-2; i<ln; i++, j--) {
        s[j] = r->s[i] + '0';
    }
    if (!j) {
        s[j] = '-';
    }
    return s;
}

int _dmp_abs_add(dmp_t *r, const dmp_t *a, const dmp_t *b)
{
    int la = DMP_ABS(a->n);
    int lb = DMP_ABS(b->n);
    int limit = DMP_MAX(la, lb);
    int i, g = 0;

    for (i=0; g || i < limit; i++) {
        int s = g;
        if (i < la) {
            s = s+a->s[i];
        }
        if (i < lb) {
            s = s+b->s[i];
        }
        r->s[i] = s%10;    // FIXME: Inelegant hardcode 10
        g = s/10;
    }
    r->n = i;
    return r->n;
}

int dmp_add_s(dmp_t *r, const dmp_t *a, const dmp_t *b)
{
    if (!a || !b) {
        return 1;
    }
    int rn;
    if ((a->n^b->n) >= 0) {
        rn = _dmp_abs_add(r, a, b);
    } else {
        // rn = _dmp_abs_sub(r, a, b);
    }
    r->n = (a->n >= 0) ? rn : -rn;
    return r->n;
}

#endif /* end of DSLIB_DS_MULTIPLE_PRECISION_H_ */
