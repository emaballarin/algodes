#include "bubble_sort.h"

#include "swap.h"

// A shorthand
#define ADDR_OF_ELEM(elem_idx) ((A) + ((elem_idx) * (elem_size)))


void bubble_sort(void* A, const unsigned int n, const size_t elem_size, total_order leq)
{
    for (unsigned int outer = n; outer > 0; outer--)
    {
        for (unsigned int inner = 0; inner < outer - 1; inner++)  // Useless to check with itself!
        {
            if (leq(ADDR_OF_ELEM(inner + 1), ADDR_OF_ELEM((inner))))
            {
                swap(ADDR_OF_ELEM(inner + 1), ADDR_OF_ELEM(inner), elem_size);
            }
        }
    }
}
