#include "list.h"

/*
 Adds a node to the end of a list. DO NOT add a NULL node pointer or
 a node with a NULL elem.
 Parse the list once
 */
void append(struct s_node* node, struct s_node** head){
    if(node == NULL || node->elem == NULL || head == NULL)
        return;
    if(*head == NULL){
        *head = node;
        return;
    }
    
    /* Traverse the linked list */
    struct s_node* iter = *head;
    while(iter->next != NULL){
        iter = iter->next;
    }
    //for(iter = *head; iter->next != NULL; iter = iter->next);
    
    iter->next = node;
    node->prev = iter;
    //node->prev = iter;
}
