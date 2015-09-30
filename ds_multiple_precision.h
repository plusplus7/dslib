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
int     dmp_sub_s(dmp_t *r, const dmp_t *a, const dmp_t *b);
int     dmp_mul_s(dmp_t *r, const dmp_t *a, const dmp_t *b);
char*   dmp_get_str(dmp_t *r, char *s);
void    dmp_free(dmp_t *r);
int     dmp_cmp_abs(dmp_t *a, dmp_t *b);
int     _dmp_check_zero(const dmp_t *r);
dmp_t*  _dmp_set_zero(dmp_t *r);
int     _dmp_abs_add(dmp_t *r, const dmp_t *a, const dmp_t *b);
int     _dmp_abs_sub(dmp_t *r, const dmp_t *a, const dmp_t *b);
int     _dmp_abs_mul(dmp_t *r, const dmp_t *a, const dmp_t *b);
int     _dmp_cmp(int *a, int *b, int n);
int     _dmp_cmp4(int *a, int an, int *b, int bn);

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

int _dmp_cmp(int *a, int *b, int n)
{
    while (--n >= 0)
    {
        if (a[n] != b[n])
            return a[n] > b[n] ? 1 : -1;
    }
    return 0;
}

int _dmp_cmp4(int *a, int an, int *b, int bn)
{
    if (an != bn) {
        return an < bn ? -1 : 1;
    } else {
        return _dmp_cmp(a, b, an);
    }
}

int dmp_cmp_abs(dmp_t *a, dmp_t *b)
{
    return _dmp_cmp4(a->s, DMP_ABS(a->n), b->s, DMP_ABS(b->n));
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

int _dmp_check_zero(const dmp_t *r)
{
    return (r->n == 1) && (r->s[0] == 0);
}

dmp_t* _dmp_set_zero(dmp_t *r)
{
    r->n = 1;
    r->s[0] = 0;
    return r;
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

int _dmp_abs_sub(dmp_t *r, const dmp_t *a, const dmp_t *b)
{
    int la = DMP_ABS(a->n);
    int lb = DMP_ABS(b->n);
    int i, g = 0;
    int cmp = _dmp_cmp4(a->s, la, b->s, lb);
    if (cmp == 0) {
        r->n = 1;
        r->s[0] = 0;
        return 1;
    }
    const dmp_t *ta, *tb;
    int tla, tlb;
    if (cmp > 0) {
        r->n = la;
        ta = a, tb = b;
        tla = la, tlb = lb;
    } else if (cmp < 0) {
        r->n = lb;
        ta = b, tb = a;
        tla = lb, tlb = la;
    }
    for (i=0; i<tla; i++) {
        int s = g+ta->s[i];
        if (i < tlb) {
            s = s-tb->s[i];
        }
        r->s[i] = s < 0 ? 10+s: s;
        g = -(s < 0);
    }
    for (; r->n > 0 && r->s[r->n-1] == 0; r->n--)
        ;
    return r->n;
}

int _dmp_abs_mul(dmp_t *r, const dmp_t *a, const dmp_t *b)
{
    if (_dmp_check_zero(a) || _dmp_check_zero(b)) {
        r = _dmp_set_zero(r);
        return r->n;
    }
    int la = DMP_ABS(a->n);
    int lb = DMP_ABS(b->n);
    int i, j;
    memset(r->s, 0, DMP_ABS(r->n)*sizeof(int));
    for (i=0; i<la; i++) {
        for (j=0; j<lb; j++) {
            int k = i+j;
            r->s[k] = r->s[k] + (a->s[i]*b->s[j]);
            if (r->s[k]) {
                r->s[k+1] = r->s[k+1]+r->s[k]/10;
                r->s[k] = r->s[k]%10;
            }
        }
    }
    if (!r->s[la+lb-1]) {
        r->n = la+lb-1;
    } else {
        r->n = la+lb;
    }
    return r->n;
}

int dmp_add_s(dmp_t *r, const dmp_t *a, const dmp_t *b)
{
    if (!a || !b || !r) {
        return 1;
    }
    int rn;
    if ((a->n^b->n) >= 0) {
        rn = _dmp_abs_add(r, a, b);
    } else {
        rn = _dmp_abs_sub(r, a, b);
    }
    r->n = (a->n >= 0) ? rn : -rn;
    return r->n;
}

int dmp_sub_s(dmp_t *r, const dmp_t *a, const dmp_t *b)
{
    if (!a || !b || !r) {
        return 1;
    }
    int rn;
    if ((a->n^b->n) >= 0) {
        rn = _dmp_abs_sub(r, a, b);
    } else {
        rn = _dmp_abs_add(r, a, b);
    }
    r->n = (a->n >= 0) ? rn : -rn;
    return r->n;
}

int dmp_mul_s(dmp_t *r, const dmp_t *a, const dmp_t *b)
{
    if (!a || !b || !r) {
        return 1;
    }
    if ((a->n^b->n) >= 0) {
        r->n = _dmp_abs_mul(r, a, b);
    } else {
        r->n = -_dmp_abs_mul(r, a, b);
    }
    return r->n;
}
#endif /* end of DSLIB_DS_MULTIPLE_PRECISION_H_ */
