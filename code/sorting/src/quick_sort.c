#include "quick_sort.h"

#include "swap.h"

#include <time.h>

// A shorthand
#define ADDR_OF_ELEM(A, e, s) (A + (e) * (s))


//**************//
// PARTITIONING //
//**************//

unsigned int partition(void* A, unsigned int l, unsigned int r, unsigned int p, const size_t elem_size, total_order leq)
{
    swap(ADDR_OF_ELEM(A, p, elem_size), ADDR_OF_ELEM(A, l, elem_size), elem_size);
    p = l;
    l++;

    while (l <= r)
    {
        if (leq(ADDR_OF_ELEM(A, p, elem_size), ADDR_OF_ELEM(A, l, elem_size)))
        {
            swap(ADDR_OF_ELEM(A, l, elem_size), ADDR_OF_ELEM(A, r, elem_size), elem_size);
            r--;
        }
        else
        {
            l++;
        }
    }

    swap(ADDR_OF_ELEM(A, p, elem_size), ADDR_OF_ELEM(A, r, elem_size), elem_size);
    return r;
}


//*************//
// AUXILIARIES //
//*************//

void quick_sort_aux(void* A, unsigned int l, const unsigned int r, const size_t elem_size, total_order leq)
{
    unsigned int p;

    while (l < r)
    {
        p = partition(A, l, r, l, elem_size, leq);

        // Here some heuristics can be applied to select p, e.g.:
        //srand(time(NULL));  // Random pivot
        //p = partition(A, l, r, (l + rand() % (r - l)), elem_size, leq);

        quick_sort_aux(A, l, p, elem_size, leq);
        l = p + 1;
    }
}


//***********//
// QUICKSORT //
//***********//

void quick_sort(void* A, const unsigned int n, const size_t elem_size, total_order leq)
{
    quick_sort_aux(A, 0, n, elem_size, leq);
}
