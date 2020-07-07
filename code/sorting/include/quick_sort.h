#ifndef __QUICK_SORT__
#define __QUICK_SORT__

#include <stdlib.h>

#include "total_order.h"

/**********************************************************************
 * An implementation for the Quick Sort algorithm.
 *
 * This function implements the Quick Sort algorithm to sort an 
 * array of elements whose type is unknown with respect to the total 
 * order implemented by the function `leq`. The resulting permutation 
 * is stored in the input array.
 * If the fuction `leq` costs Theta(1), then the execution of this 
 * function takes time O(n^2)\cap Omega(n \log n) where n is the 
 * number of elements in the array.
 *
 * @param A is the array to be sorted. This array is also used to 
 *          store the output of the function.
 * @param n is the number of element of A.
 * @param elem_size is the type size in bytes of the elements in A.
 * @param leq is the total order to be satisfied by the sorting.
 **********************************************************************/
void quick_sort(void *A, const unsigned int n, 
                const size_t elem_size, 
                total_order leq);

#endif // __QUICK_SORT__