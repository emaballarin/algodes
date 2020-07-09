#include <binheap.h>
#include <stdio.h>
#include <string.h>

/* MACROS */

#define PARENT(node) (((node)-1) / 2)
#define LEFT_CHILD(node) (2 * (node) + 1)
#define RIGHT_CHILD(node) (2 * ((node) + 1))

#define VALID_NODE(H, node) ((H)->num_of_elem > (node))

#define ADDR(H, node) ((H)->A + (node) * (H)->key_size)
#define INDEX_OF(H, addr) (((addr) - ((H)->A)) / (H)->key_size)

#define POS_FROM_KEY(H, key) (H->key_pos[key])
#define KEY_FROM_POS(H, pos) (H->rev_pos[pos])


int is_heap_empty(const binheap_type* H)
{
    return (H->num_of_elem == 0);
}

const void* min_value(const binheap_type* H)
{
    if (is_heap_empty(H))
    {
        return NULL;
    }

    // The minimum is stored in the root, a.k.a. A[0]
    return ADDR(H, 0);
}

void swap_keys(binheap_type* H, unsigned int n_a, unsigned int n_b)
{
    unsigned int a_pos = POS_FROM_KEY(H, n_a);
    unsigned int b_pos = POS_FROM_KEY(H, n_b);
    unsigned int tmpswp = POS_FROM_KEY(H, n_a);

    POS_FROM_KEY(H, n_a) = POS_FROM_KEY(H, n_b);
    POS_FROM_KEY(H, n_b) = tmpswp;

    KEY_FROM_POS(H, a_pos) = n_b;
    KEY_FROM_POS(H, b_pos) = n_a;
}

void heapify(binheap_type* H, unsigned int node)
{
    unsigned int dst_node = node, child, node_pos, child_pos;

    do
    {
        // Find the minimum among node and its children

        dst_node = node;
        node_pos = POS_FROM_KEY(H, node);

        // Right
        child_pos = RIGHT_CHILD(node_pos);

        // Do the 1st check here, since we need to pass through positions
        if (VALID_NODE(H, child_pos))
        {
            child = KEY_FROM_POS(H, child_pos);

            // The other part of the check...
            if (H->leq(ADDR(H, child), ADDR(H, dst_node)))
            {
                dst_node = child;
            }
        }

        // Left
        child_pos = LEFT_CHILD(node_pos);

        // Do the 1st check here, since we need to pass through positions
        if (VALID_NODE(H, child_pos))
        {
            child = KEY_FROM_POS(H, child_pos);

            // The other part of the check...
            if (H->leq(ADDR(H, child), ADDR(H, dst_node)))
            {
                dst_node = child;
            }
        }

        // NOW BUSINESS AS USUAL:
        // If the minimum is not in node, swap the keys
        if (dst_node != node)
        {
            swap_keys(H, dst_node, node);
        }
    } while (dst_node != node);
}

const void* extract_min(binheap_type* H)
{
    if (is_heap_empty(H))
    {
        return NULL;
    }

    // Swapping the keys among the root A[0] and the rightmost key of the last level A[num_of_elem-1]
    swap_keys(H, KEY_FROM_POS(H, 0), KEY_FROM_POS(H,H->num_of_elem - 1));

    // Deleting the rightmost leaf of the last level A[num_of_elem-1]
    H->num_of_elem--;

    heapify(H, KEY_FROM_POS(H,0));

    return ADDR(H, KEY_FROM_POS(H,H->num_of_elem));
}

const void* find_the_max(void* A, const unsigned int num_of_elem, const size_t key_size, total_order_type leq)
{
    if (num_of_elem == 0)
    {
        return NULL;
    }

    const void* max_value = A;

    // for all the values in A
    for (const void* addr = A + key_size; addr != A + (num_of_elem-1) * key_size; addr += key_size)
    {
        // if addr > max_value
        if (!leq(addr, max_value))
        {
            max_value = addr;
        }
    }

    return max_value;
}

binheap_type* build_heap(void* A, const unsigned int num_of_elem, const unsigned int max_size, const size_t key_size,
                         total_order_type leq)
{
    binheap_type* H = (binheap_type*)malloc(sizeof(binheap_type));

    H->A = A;
    H->num_of_elem = num_of_elem;
    H->max_size = max_size;
    H->key_size = key_size;
    H->leq = leq;
    H->max_order_value = malloc(key_size);

    H->key_pos = (unsigned int*)malloc(max_size * sizeof(unsigned int));
    H->rev_pos = (unsigned int*)malloc(max_size * sizeof(unsigned int));

    for (unsigned int i = 0; i < max_size; i++)
    {
        H->key_pos[i] = i;
        H->rev_pos[i] = i;
    }

    if (num_of_elem == 0)
    {
        return H;
    }

    // Get the maximum among A[:num_of_elem-1] and store it in max_value_order
    const void* value = find_the_max(A, num_of_elem, key_size, leq);
    memcpy(H->max_order_value, value, key_size);

    // Fix the heap property from the second-last level up to the root
    for (unsigned int i = num_of_elem / 2; i > 0; i--)
    {
        heapify(H, KEY_FROM_POS(H, i));
    }
    heapify(H, KEY_FROM_POS(H,0));

    return H;
}

void delete_heap(binheap_type* H)
{
    free(H->max_order_value);
    free(H->key_pos);
    free(H->rev_pos);
    free(H);
}

const void* decrease_key(binheap_type* H, void* node, const void* value)
{
    if (H->num_of_elem == 1)
    {
        return NULL;
    }

    unsigned int node_idx = INDEX_OF(H, node);
    unsigned int node_pos = POS_FROM_KEY(H, node_idx);

    // If node does not belong to H, or *value > *node, return NULL.
    if (!(H->leq(value, node)))
    {
        return NULL;
    }

    memcpy(node, value, H->key_size);

    unsigned int parent_idx = KEY_FROM_POS(H, PARENT(node_idx));
    void* parent = ADDR(H, parent_idx);

    // while node != root and *parent > *node
    while ((node_idx != 0) && (!H->leq(parent, node)))
    {
        // swap parent and node keys
        swap_keys(H, parent_idx, node_idx);

        // focus on the node's parent
        node_pos = POS_FROM_KEY(H, node_idx);
        unsigned int parent_pos = PARENT(node_pos);

        // Other part of the check
        if (VALID_NODE(H, parent_pos))
        {
            parent_idx = KEY_FROM_POS(H, parent_pos);
            parent = ADDR(H, parent_idx);
        }
        else
        {
            break;
        }
    }
    return node;
}

const void* insert_value(binheap_type* H, const void* value)
{
    // if the heap is already full
    if (H->max_size == H->num_of_elem)
    {
        return NULL;
    }

    // if the new value > *max_order_value
    if ((H->num_of_elem == 0) || (!H->leq(value, H->max_order_value)))
    {
        memcpy(H->max_order_value, value, H->key_size);
    }

    // get the position of the new node
    unsigned int node_idx = KEY_FROM_POS(H, H->num_of_elem);
    void* new_node_address = ADDR(H, node_idx);
    memcpy(new_node_address, H->max_order_value, H->key_size);

    // increase the size of the heap
    H->num_of_elem++;

    // decrease the key of the new node
    return decrease_key(H, new_node_address, value);
}

void print_heap(const binheap_type* H, void (*key_printer)(const void* value))
{
    unsigned int next_level_node = 1;  // store the index of the
    // leftmost node of the next level
    for (unsigned int node = 0; node < H->num_of_elem; node++)
    {
        if (node == next_level_node)
        {
            printf("\n");
            next_level_node = LEFT_CHILD(node);
        }
        else
        {
            printf("\t");
        }

        key_printer(ADDR(H, KEY_FROM_POS(H, node)));
    }

    printf("\n\n");
    for (unsigned int i = 0; i < H->max_size; i++)
    {
        printf(" ");
        key_printer(ADDR(H, i));
    }
}
