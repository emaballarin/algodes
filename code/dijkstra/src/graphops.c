#include "graphops.h"

linkedlist_type* build_random_graph(size_t num_of_nodes, double density, unsigned int minwgt, unsigned int maxwgt)
{
    // Seed the PRNG
    srand(time(NULL));

    // Pre-allocate stuff
    linkedlist_type* new_graph_al = (linkedlist_type*)malloc(sizeof(linkedlist_type) * num_of_nodes);
    int include_this_node = 0;
    unsigned int a_weight = 0;

    // For each node in the graph...
    for (size_t node_idx = 0; node_idx < num_of_nodes; node_idx++)
    {
        // For every possible link...
        for (size_t destination_node = 0; destination_node < num_of_nodes; destination_node++)
        {
            // Flip a coin
            include_this_node = (int)(drand48() < density);

            // If "head"...
            if (include_this_node)
            {
                // Draw a weight
                a_weight = (unsigned int)(minwgt + (maxwgt - minwgt) * (drand48()));

                insert_block_in_adjlist(&new_graph_al[node_idx], destination_node, a_weight);
            }
        }
    }

    return new_graph_al;
}


void print_graph(linkedlist_type* graph, size_t num_of_nodes)
{
    for (size_t i = 0; i < num_of_nodes; i++)
    {
        print_adjlist(&graph[i], sizet_printer);
        printf("\n");
    }
}

void destroy_graph(linkedlist_type* graph, size_t num_of_elem)
{
    for (size_t i = num_of_elem - 1; i > 0; i--)
    {
        destroy_adjlist(&graph[i]);
    }
    destroy_adjlist(graph);
    free(graph);
    //destroy_adjlist(graph);
}
