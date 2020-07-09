#include "select.h"

#include "insertion_sort.h"  // For base-case sorting (I.S. because it's cool!)
#include "swap.h"


#define ADDR_OF_ELEM(A, e, s) (A + (e) * (s))

int are_equal(const void* a, const void* b, total_order to)
{
    return to(a, b) && to(b, a);
}

// A partition to deal with duplicates (leq_than_pivot | eq_to_pivot | gt_than_pivot)
pair tripartition(void* A, unsigned int l, unsigned int r, unsigned int p, const size_t elem_size, total_order leq)
{
    swap(ADDR_OF_ELEM(A, l, elem_size), ADDR_OF_ELEM(A, p, elem_size), elem_size);
    p = l;
    l++;

    // Central partition sizer
    unsigned int reps = 0;

    // Iteration
    while (l <= r)
    {
        if (!are_equal(ADDR_OF_ELEM(A, l, elem_size), ADDR_OF_ELEM(A, p, elem_size), leq))
        {
            if (leq(ADDR_OF_ELEM(A, l, elem_size), ADDR_OF_ELEM(A, p, elem_size)))
            {
                // l < p
                swap(ADDR_OF_ELEM(A, l, elem_size), ADDR_OF_ELEM(A, (p - reps), elem_size), elem_size);
                p = l;
                l++;
            }
            else
            {
                // l > p
                swap(ADDR_OF_ELEM(A, l, elem_size), ADDR_OF_ELEM(A, r, elem_size), elem_size);
                r--;
            }
        }
        else
        {
            // l == p
            p = l;
            l++;
            reps++;
        }
    }

    // Final swap
    swap(ADDR_OF_ELEM(A, p, elem_size), ADDR_OF_ELEM(A, r, elem_size), elem_size);

    // Prepare what needs to be returned

    pair to_be_ret;
    to_be_ret.top = r - reps;  // END OF "smaller than"
    to_be_ret.bottom = r;      // END OF "equal to"

    return to_be_ret;
}

unsigned int select_pivot(void* A, const unsigned int n, const size_t elem_size, total_order leq)
{
    unsigned int l = 0;
    unsigned int r = n - 1;

    if (n <= 10)
    {
        // Base case -> Sort via I.S.
        insertion_sort(A, n, elem_size, leq);
        return n / 2;
    }

    // Compute the median of the 5 chunks
    unsigned int chunks_nr = n / 5;

    // For each chunk
    for (unsigned int i = 0; i < chunks_nr; i++)
    {
        unsigned int arr_start = l + 5 * i;
        unsigned int arr_stop = (arr_start + 4 < r) ? arr_start + 4 : r;  // The smallest of the two
        unsigned int arr_len = arr_stop - arr_start + 1;

        // Sort with I.S. and a sparkle of ptr arithmetic
        insertion_sort(A + arr_start * elem_size, arr_len, elem_size, leq);

        // Get median
        unsigned int mdn = (arr_start + 2 < r) ? arr_start + 2 : r;

        // Median swap
        swap(ADDR_OF_ELEM(A, l + i, elem_size), ADDR_OF_ELEM(A, mdn, elem_size), elem_size);
    }

    return select_index(A, chunks_nr, chunks_nr / 2, elem_size, leq);
}


unsigned int select_index(void* A, const unsigned int n, const unsigned int i, const size_t elem_size, total_order leq)
{
    if (n <= 10)
    {
        // Base case -> Sort via I.S.
        insertion_sort(A, n, elem_size, leq);
        return i;
    }

    unsigned int j = select_pivot(A, n, elem_size, leq);

    // Partitioning
    pair pivots = tripartition(A, 0, n - 1, j, elem_size, leq);


    // Dealing with all this partitions can be messy...

    if (i < pivots.bottom)
    {
        if (pivots.bottom > 0)
        {
            return select_index(A, pivots.bottom - 1, i, elem_size, leq);
        }
        else
        {
            return pivots.bottom;
        }
    }

    if (i > pivots.top)
    {
        if (pivots.top < n)
        {
            return select_index(A + elem_size * pivots.top, n - pivots.top - 1, i, elem_size, leq);
        }
        else
        {
            return pivots.top;
        }
    }

    return i;
}


void quick_sort_select_aux(void* A, size_t l, size_t r, const size_t elem_size, total_order leq)
{
    // Define what needs to be recursed...
    while (l < r)
    {
        unsigned int j = (unsigned int)(l + select_pivot(A + l * elem_size, (unsigned int)(r - l), elem_size, leq));

        pair pivots = tripartition(A, (unsigned int)l, (unsigned int)(r - 1), j, elem_size, leq);

        quick_sort_select_aux(A, l, pivots.bottom, elem_size, leq);
        l = pivots.top + 1;
    }
}


void quick_sort_select(void* A, const unsigned int n, const size_t elem_size, total_order leq)
{
    quick_sort_select_aux(A, 0, n, elem_size, leq);
}
