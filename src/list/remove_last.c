#include "list.h"
/*
 Removes the last node from the list.
 Parse Once.
 */
void* remove_last(struct s_node** head){
    if(head == NULL || *head == NULL){
        return NULL;
    }
    struct s_node* iter = *head;
    for(iter = *head; iter->next != NULL; iter = iter->next);
    void* ret = iter->elem;
    if(iter->prev == NULL){
        free(iter);
        return ret;
    }
    iter->prev->next = NULL;
    free(iter);
    return ret;
}
