#include "heap_sort.h"

#include "binheap.h"
#include "swap.h"
#include "total_order.h"

#define ADDR_OF_ELEM(elem_idx) ((A) + ((elem_idx) * (elem_size)))

void heap_sort(void* A, const unsigned int n, const size_t elem_size, total_order leq)
{
    // Build the heap
    binheap_type* heap = build_heap(A, n, n, elem_size, leq);

    for (unsigned int i = n - 1; i > 0; i--)
    {
        extract_min(heap);  // Swapping heap: already sorted array!
        // But this is a min-heap :(
    }

    // Invert array with minimal # of swaps
    for (unsigned int i = 0; i < (n / 2); i++)  // Already floor of division!
    {
        swap(ADDR_OF_ELEM(i), ADDR_OF_ELEM(n - 1 - i), elem_size);
    }
}
