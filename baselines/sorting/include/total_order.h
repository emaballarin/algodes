#ifndef __TOTAL_ORDER__

typedef int (*total_order)(const void *a, const void *b);

int leq_float(const void *a, const void *b);
int leq_int(const void *a, const void *b);
int geq_int(const void *a, const void *b);

#endif // __TOTAL_ORDER__