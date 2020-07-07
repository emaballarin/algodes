#ifndef __SWAP__
#define __SWAP__

#include <stdlib.h>

/**********************************************************************
 * Swap the values referenced by two pointers.
 *
 * This function swaps <size>-bytes values referenced by two 
 * pointers. 
 *
 * @param a a pointer to the first value to be swapped.
 * @param b a pointer to the second value to be swapped.
 * @param size is the length in bytes of the values to be swapped.
 **********************************************************************/
void swap(void *a, void *b, const size_t size);

#endif // __SWAP__