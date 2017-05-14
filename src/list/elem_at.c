#include "list.h"
/*
 Returns a pointer to the elem at index n or the last node.
 Parse once.
 */
void* elem_at(struct s_node* head, int n){
    if(head == NULL){
        return NULL;
    }
    if(n < 0) n = 0;
    struct s_node* iter = head;
    int count = 0;
    while(iter->next != NULL && count < n){
        count++;
        iter = iter->next;
    }
    return iter->elem;
}
