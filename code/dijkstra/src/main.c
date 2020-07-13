#include "edsger.h"
#include "graphops.h"
#include "total_orders.h"

#include <time.h>

double sssp_timed_solve_array(linkedlist_type* graph, size_t reps, size_t graphsize)
{
    solvedsssp_type* dummy;

    struct timespec requestStart, requestEnd;
    double accum = (double)0;

    clock_gettime(CLOCK_REALTIME, &requestStart);
    for (size_t i = 0; i < reps; i++)
    {
        dummy = dijkstra_solve_array(graph, graphsize, 0);
        destroy_solvedsssp(dummy);
    }
    clock_gettime(CLOCK_REALTIME, &requestEnd);

    accum = accum + (requestEnd.tv_sec - requestStart.tv_sec) + (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;

    return accum / reps;
}


double sssp_timed_solve_heap(linkedlist_type* graph, size_t reps, size_t graphsize)
{
    solvedsssp_type* dummy;

    struct timespec requestStart, requestEnd;
    double accum = (double)0;

    clock_gettime(CLOCK_REALTIME, &requestStart);
    for (size_t i = 0; i < reps; i++)
    {
        dummy = dijkstra_solve_heap(graph, graphsize, 0);
        destroy_solvedsssp(dummy);
    }
    clock_gettime(CLOCK_REALTIME, &requestEnd);


    accum = accum + (requestEnd.tv_sec - requestStart.tv_sec) + (requestEnd.tv_nsec - requestStart.tv_nsec) / 1E9;
    return accum / reps;
}


int main()
{
    printf("SIZE\t\tARRAY\t\tHEAP\n");

    int nrnr = 20000;

    for (size_t graphsize = nrnr; graphsize < nrnr+1; graphsize += 2)
    {
        linkedlist_type* mygraph = build_random_graph(graphsize, 0.5, 1, 500);

        // Array
        double arr_time = sssp_timed_solve_array(mygraph, 1, graphsize);

        // Heap
        double hea_time = sssp_timed_solve_heap(mygraph, 1, graphsize);

        // PRINT
        printf("%lu", graphsize);
        printf("\t\t");
        printf("%f", arr_time);
        printf("\t\t");
        printf("%f", hea_time);
        printf("\n");

        destroy_graph(mygraph, graphsize);
    }
    return 0;
}
