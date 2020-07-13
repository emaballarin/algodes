#include "util.h"

size_t getmin(const size_t a, const size_t b)
{
    return a < b ? a : b;
}

size_t getmax(const size_t a, const size_t b)
{
    return a > b ? a : b;
}
