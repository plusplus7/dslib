#ifndef DSLIB_DS_NUMBER_H_
#define DSLIB_DS_NUMBER_H_

#include <stdlib.h>
#include <string.h>

int* ds_basic_prime_number_sieve(size_t count, int* target);

int* ds_basic_prime_number_sieve(size_t count, int* target)
{
    if (!target) {
        target = (int *)malloc(count*sizeof(int));
    }

    memset(target, 0, count*sizeof(int));

    size_t i, j, k;
    for (i=2; i*i<=count; i++) {
        if (!target[i]) {
            for (j=2, k=2*i; k<=count; ++j, k=i*j) {
                target[k] = 1;
            }
        } else {
            continue;
        }
    }
    return target;
}

#endif /* end of DSLIB_DS_NUMBER_H_ */
