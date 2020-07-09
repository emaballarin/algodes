#ifndef __GRAPHOPS__
#define __GRAPHOPS__

#include "adjlist.h"

#include <time.h>  // A poor but useful source of randomness

// Create graphs (<- graph representations as Adjacency Lists) with ease
linkedlist_type* build_random_graph(size_t num_of_nodes, double density, unsigned int minwgt, unsigned int maxwgt);
void print_graph(linkedlist_type* graph, size_t num_of_nodes);
void destroy_graph(linkedlist_type* graph, size_t num_of_elem);

#endif  // __GRAPHOPS__
