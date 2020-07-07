#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "total_order.h"

int *get_random_int_array(const unsigned int n) 
{
  
  int *A=(int *)malloc(sizeof(int)*n);
  
  srand(10);
  for (unsigned int i = 0; i < n; i++) {
    A[i] = (rand() - RAND_MAX / 2) % n*n;
  }

  return A;
}

int is_sorted(const void *A, const unsigned int n, 
              const size_t elem_size, 
              total_order leq)
{
  for (const void *addr=A; addr!=A+(n-1)*elem_size; 
    addr+=elem_size) {
        
    if (!leq(addr, addr+elem_size)) {
      return 0;
    }
  }

  return 1;
}

double test(void (*sort)(void *A, const unsigned int n, 
                         const size_t elem_size, 
                         total_order leq), 
            const void *A, const unsigned int n, 
            const size_t elem_size, total_order leq, 
            const unsigned int rep,
            int *sorted)
{
  struct timespec requestStart, requestEnd;
  double accum, cpy_accum;
  const size_t total_size = n*elem_size;

  void *B=malloc(total_size);

  // Collecting time for copy A into B and sorting B
  clock_gettime(CLOCK_REALTIME, &requestStart);
  for (size_t i = 0; i < rep; i++) {
    memcpy(B,A+i*n,total_size);
    sort(B,n,elem_size,leq);
  }
  clock_gettime(CLOCK_REALTIME, &requestEnd);

  accum = (requestEnd.tv_sec - requestStart.tv_sec) +
          (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;


  if (sorted != NULL) {
    *sorted = is_sorted(B, n, elem_size, leq);
  }

  // Collecting time for copying A in B
  clock_gettime(CLOCK_REALTIME, &requestStart);
  for (size_t i = 0; i < rep; i++) {
    memcpy(B,A+i*n,total_size);
  }
  clock_gettime(CLOCK_REALTIME, &requestEnd);

  cpy_accum = (requestEnd.tv_sec - requestStart.tv_sec) +
             (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;

  free(B);

  double secs = (accum-cpy_accum) / rep;

  return (secs<0?0:secs);
}
