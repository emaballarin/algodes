#include <string.h>
#include <stdlib.h>

#include "swap.h"

void swap(void *a, void *b, const size_t size)
{
    void *tmp = malloc(size);
    
    memcpy(tmp, a, size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);

    free(tmp);
}