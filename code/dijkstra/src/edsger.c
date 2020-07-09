#include "edsger.h"
#include "binheap.h"
#include <limits.h>

#define NIL (solution->num_of_elem + 2)
#define INDEX_OF(H, addr) (((addr) - ((H)->A)) / (H)->key_size)


solvedsssp_type* deploy_solvedsssp(size_t num_of_nodes)
{
    size_t* new_predecessors = (size_t*)malloc(sizeof(size_t) * num_of_nodes);
    unsigned int* new_distances = (unsigned int*)malloc(sizeof(unsigned int) * num_of_nodes);

    solvedsssp_type* new_solvedsssp = (solvedsssp_type*)malloc(sizeof(solvedsssp_type));
    new_solvedsssp->num_of_elem = num_of_nodes;

    new_solvedsssp->distances = new_distances;
    new_solvedsssp->predecessors = new_predecessors;

    return new_solvedsssp;
}

void destroy_solvedsssp(solvedsssp_type* solvedsssp)
{
    free(solvedsssp->predecessors);
    free(solvedsssp->distances);
    free(solvedsssp);
}


// Init SSSP
void init_sssp(solvedsssp_type* solution)
{

    for (size_t i=0; i<solution->num_of_elem; i++)
    {
        solution->distances[i] = UINT_MAX;
        solution->predecessors[i] = NIL;
    }
    return;
}

// Relax for array queues
void relax_array_queue(size_t min_node_idx, listblock_type* adj_cursor, unsigned int* distances, size_t* predecessors)
{
    if ((distances[min_node_idx] + adj_cursor->weight) < distances[adj_cursor->nodekey])
    {
        distances[adj_cursor->nodekey] = distances[min_node_idx] + adj_cursor->weight;
        predecessors[adj_cursor->nodekey] = min_node_idx;
    }
}


solvedsssp_type* dijkstra_solve_array(linkedlist_type* graph, size_t num_of_elem, size_t source)
{

    // The solution will be put here
    solvedsssp_type* solution = deploy_solvedsssp(num_of_elem);


    // ALGORITHM //

    // Initialization
    init_sssp(solution);
    solution->distances[source] = 0;

    // Queue building
    size_t* array_queue = (size_t*)malloc(sizeof(size_t)*num_of_elem);
    size_t queue_size = num_of_elem;

    // Start with the full queue
    for (size_t i=0; i<queue_size; i++)
    {
        array_queue[i] = i;
    }

    // Queue Iteration
    while (queue_size > 0)      // Queue is not empty
    {
        // Find the index in the queue corresponding to the smallest distance
        size_t min_queue_idx = 0;
        for (size_t i = 1; i < queue_size; i++)
        {
            if (solution->distances[array_queue[i]] < solution->distances[array_queue[min_queue_idx]])
            {
                min_queue_idx = i;
            }
        }

        // Get the corresponding node index
        size_t min_node_idx = array_queue[min_queue_idx];

        // Extract min from the queue
        array_queue[min_queue_idx] = array_queue[queue_size-1];
        queue_size--;

        // Relax Iteration

        listblock_type* adj_cursor = graph[min_node_idx].head;

        while (adj_cursor)  // As long as the cursor is inside the list
        {
            relax_array_queue(min_node_idx, adj_cursor, solution->distances, solution->predecessors);

            // Next, please!
            adj_cursor = adj_cursor->next;
        }
    }

    // Tidy memory
    free(array_queue);

    // Return the solution
    return solution;
}

solvedsssp_type* dijkstra_solve_heap(linkedlist_type* graph, size_t num_of_elem, size_t source)
{
    // The solution will be put here
    solvedsssp_type* solution = deploy_solvedsssp(num_of_elem);


    // ALGORITHM //

    // Initialization
    init_sssp(solution);
    solution->distances[source] = 0;

    // Queue building
    binheap_type* heap_queue = build_heap(solution->distances, num_of_elem, num_of_elem, sizeof(unsigned int), leq_usi);

    // Queue iteration
    while(heap_queue->num_of_elem > 0)
    {
        // Find the index in the queue corresponding to the smallest distance and get the corresponding node index
        //size_t min_node_idx = HEAP_POS_FROM_NODE(heap_queue, *(unsigned int*)extract_min(heap_queue));
        size_t min_node_idx = INDEX_OF(heap_queue, extract_min(heap_queue));

        // Relax Iteration

        listblock_type* adj_cursor = graph[min_node_idx].head;

        while (adj_cursor)  // As long as the cursor is inside the list
        {
            relax_array_queue(min_node_idx, adj_cursor, solution->distances, solution->predecessors);

            // Next, please!
            adj_cursor = adj_cursor->next;
        }
    }

    // Tidy memory
    delete_heap(heap_queue);

    return solution;
}
