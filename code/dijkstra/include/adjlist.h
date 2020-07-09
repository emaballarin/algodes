/*
 * A no-frills Adjacency List implementation based on Linked Lists
 * (actually: an Adjacency List should be an array of such Linked Lists)
 *
 * NOTE:
 * The implementation is centered around the trick that nodes in the graph have
 * a size_t "key" denoting their position inside a data structure (array mostly)
 * thus requiring just it to be identified.
 */

#ifndef __ADJLIST__
#define __ADJLIST__

#include <stdio.h>
#include <stdlib.h>

// Useful to print node keys
void sizet_printer(const void* value);


// The "block" which will contain a Node/Weight pair representing an edge
typedef struct ListBlock
{
    size_t nodekey;
    unsigned int weight;
    struct ListBlock* next;
} listblock_type;


// A list linked of blocks: actually just the pointer to the first node and length
typedef struct List
{
    listblock_type* head;
    size_t len;
} linkedlist_type;

linkedlist_type* create_empty_adjlist();
listblock_type* create_new_adjlist_node(const size_t nodekey, const unsigned int weight);
void insert_block_in_adjlist(linkedlist_type* adjlist, const size_t nodekey, const unsigned int weight);
void remove_block_from_adjlist(linkedlist_type* adjlist, const size_t nodekey);
//void destroy_listblock(listblock_type* listblock);
void destroy_adjlist(linkedlist_type* adjlist);
void print_adjlist(linkedlist_type* adjlist, void (*key_printer)(const void* value));

#endif  // __ADJLIST__
