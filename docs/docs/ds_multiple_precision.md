# ds_multiple_precision.h

The multiple precision module
=============

#### DMP_ABS(x)

Returns |x|

#### DMP_MAX(a, b)

Returns max(a, b)

#### DMP_MIN(a, b)

Returns min(a, b)

#### dmp_t* dmp_new(dmp_t *r, int n)

Try to create a dmp_t instance to r with n digits limits

Memory blocks are allocated from heap, so dmp_free is supposed to call after jobs finished

```c
	dmp_t *r;
	dmp_new(r, 10); // memory from heap
	dmp_free(r)
```

#### void dmp_init(dmp_t *r, int n, int *s)

Simply initialize a dmp_t instance, no memory allocates

For those who want to rock with heap memory

```c
	dmp_t r;
	int s[10];
	dmp_init(&r, 10, s);
```
	
#### void dmp_load_str(dmp_t *r, const char *s)

Initialize a dmp_t instance from a char string

```c
	dmp_t r;
	int s[100];
	dmp_init(&r, 100, s);
	char sn[100] = "2333333333333333333333333";
	dmp_load_str(&r, sn);
```
	
#### int dmp_add_s(dmp_t *r, const dmp_t *a, const dmp_t *b)

Do r = a+b

```c
	dmp_t r;
	dmp_t a, b;
	...
	dmp_add_s(&r, &a, &b);
```

#### int dmp_sub_s(dmp_t *r, const dmp_t *a, const dmp_t *b)

Do r = a-b
	
```c
	dmp_t r;
	dmp_t a, b;
	...
	dmp_sub_s(&r, &a, &b);
```

#### int dmp_mul_s(dmp_t *r, const dmp_t *a, const dmp_t *b)

Do r = a*b
	
```c
	dmp_t r;
	dmp_t a, b;
	...
	dmp_mul_s(&r, &a, &b);
```

#### char*   dmp_get_str(dmp_t *r, char *s)

Returns dmp_t as a char string

Allocate memory from heap, if s == NULL

```c
	dmp_t r;
	dmp_t a, b;
	...
	dmp_mul_s(&r, &a, &b);
	char s[100];
	printf("%s\n", dmp_get_str(&r, s));
```

#### void    dmp_free(dmp_t *r)

Free memory

Rock with dmp_new, or boom

```c
	dmp_t *r;
	dmp_new(r, 10); // memory from heap
	dmp_free(r)
```
	
#### int     dmp_cmp_abs(dmp_t *a, dmp_t *b)

Compare |a| and |b|

```c
	dmp_t r;
	dmp_t a, b;
	...
	if (dmp_cmp_abs(&a, &b) < 0) {
		printf("a < b");
	}
```
