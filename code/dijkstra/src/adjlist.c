#include "adjlist.h"

void sizet_printer(const void* value)
{
    printf("%u", *((const unsigned int*)value));
}

linkedlist_type* create_empty_adjlist()
{
    linkedlist_type* new_adjlist = (linkedlist_type*)malloc(sizeof(linkedlist_type));
    new_adjlist->head = NULL;
    new_adjlist->len = 0;
    return new_adjlist;
}


// Mostly auxiliary
listblock_type* create_new_adjlist_node(const size_t nodekey, const unsigned int weight)
{
    listblock_type* new_listblock = (listblock_type*)malloc(sizeof(listblock_type));
    new_listblock->nodekey = nodekey;
    new_listblock->weight = weight;
    new_listblock->next = NULL;
    return new_listblock;
}


void insert_block_in_adjlist(linkedlist_type* adjlist, const size_t nodekey, const unsigned int weight)
{
    listblock_type* new_listblock = create_new_adjlist_node(nodekey, weight);

    // Break-insert on head (to be faster; i.e. order is not important in the LL)
    new_listblock->next = adjlist->head;    // Works even if NULL! ;)
    adjlist->head = new_listblock;
    adjlist->len++;
}


void remove_block_from_adjlist(linkedlist_type* adjlist, const size_t nodekey)    // nodekey is unique!
{
    listblock_type* cursor = adjlist->head;

    // Save time/space if removee in linked to head!
    if (cursor->nodekey == nodekey)
    {
        adjlist->head = cursor->next;
        adjlist->len--;
        free(cursor);
        return;
    }
    else    // Skip the check on head
    {
        cursor = cursor->next;
        listblock_type* previously_touched = NULL;

        while ((cursor->nodekey != nodekey) && cursor)
        {
            previously_touched = cursor;
            cursor = cursor->next;
        }

        // If found the node...
        if (cursor)
        {
            previously_touched->next = cursor->next;
            adjlist->len--;
            free(cursor);
            return;
        }
    }
}

void destroy_adjlist(linkedlist_type* adjlist)
{
    listblock_type* cursor = adjlist->head;
    listblock_type* next_up = NULL;

    // Iterate the list and wipe everything found along the path :P

    while(cursor)
    {
        next_up = cursor->next;
        free(cursor);
        cursor = next_up;
    }

    // Then remove the empty LL
    //free(adjlist);
}


// Try to print the list, too
void print_adjlist(linkedlist_type* adjlist, void (*key_printer)(const void* value))
{
    listblock_type* cursor = adjlist->head;

    while(cursor)
    {
        printf("->(key: ");
        key_printer(&(cursor->nodekey));
        printf(", wgt: %u)", cursor->weight);
        cursor = cursor->next;
    }
    // At the end, point to NULL
    printf("->(NULL)");
}
