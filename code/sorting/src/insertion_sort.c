#include "insertion_sort.h"

#include "swap.h"

// A shorthand
#define ADDR_OF_ELEM(elem_idx) ((A) + ((elem_idx) * (elem_size)))

void insertion_sort(void* A, const unsigned int n, const size_t elem_size, total_order leq)
{
    unsigned int cursor;

    for (unsigned int outer = 1; outer < n; outer++)
    {
        cursor = outer;

        while ((cursor > 0) && (leq(ADDR_OF_ELEM(cursor), ADDR_OF_ELEM(cursor - 1))))
        {
            swap(ADDR_OF_ELEM(cursor), ADDR_OF_ELEM(cursor - 1), elem_size);
            cursor--;
        }
    }
}
