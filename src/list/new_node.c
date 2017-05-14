#include "list.h"

/*
    @desc       Allocates a new s_node. NULL nodes can be created.
    @returns    pointer to new s_node
 */
struct s_node* new_node(void* elem){
    struct s_node* n = (struct s_node*)malloc(sizeof(struct s_node));
    n->elem = elem;
    n->next = NULL;
    n->prev = NULL;
    return n;
}
