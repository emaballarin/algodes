#ifndef __UTILITIES__

    #include "total_order.h"

    #include <stdlib.h>

int* get_random_int_array(const unsigned int n);

int is_sorted(const void* A, const unsigned int n, const size_t elem_size, total_order leq);

double test(void (*sort)(void* A, const unsigned int n, const size_t elem_size, total_order leq), const void* A,
            const unsigned int n, const size_t elem_size, total_order leq, const unsigned int rep, int* sorted);

#endif  // __UTILITIES__