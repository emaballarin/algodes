/*
 * TOOLS FOR SOLVING SSSPP WITH EDSGER W. DIJKSTRA'S SPA ALGORITHM
 */

#ifndef __EDSGER__
#define __EDSGER__

#include "adjlist.h"
#include "graphops.h"

// What a solution will look like
typedef struct SolvedSSSP
{
    size_t* predecessors;
    unsigned int* distances;
    size_t num_of_elem;
} solvedsssp_type;

solvedsssp_type* deploy_solvedsssp(size_t num_of_nodes);
void destroy_solvedsssp(solvedsssp_type* solvedsssp);

void relax_array_queue(size_t min_node_idx, listblock_type* adj_cursor, unsigned int* distances, size_t* predecessors);

solvedsssp_type* dijkstra_solve_array(linkedlist_type* graph, size_t num_of_elem, size_t source);
solvedsssp_type* dijkstra_solve_heap(linkedlist_type* graph, size_t num_of_elem, size_t source);

#endif // __EDSGER__
