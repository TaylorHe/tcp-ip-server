#include "list.h"

/*
 Returns the value the length of the list
 Parse Once.
 */
int count_s_nodes(struct s_node* head){
    struct s_node* iter = head;
    int size = 0;
    while(iter != NULL){
        size++;
        iter = iter->next;
    }
    return size;
}
