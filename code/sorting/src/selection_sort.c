#include "selection_sort.h"

#include "swap.h"

// A shorthand
#define ADDR_OF_ELEM(elem_idx) ((A) + ((elem_idx) * (elem_size)))

void selection_sort(void* A, const unsigned int n, const size_t elem_size, total_order leq)
{
    unsigned int max_inner;

    for (unsigned int outer = n - 1; outer > 0; outer--)
    {
        max_inner = 0;

        for (unsigned int inner = 1; inner <= outer; inner++)
        {
            if (leq(ADDR_OF_ELEM(max_inner), ADDR_OF_ELEM(inner)))
            {
                max_inner = inner;
            }
            swap(ADDR_OF_ELEM(outer), ADDR_OF_ELEM(max_inner), elem_size);
        }
    }
}
