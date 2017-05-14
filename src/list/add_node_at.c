#include "list.h"

/*
 Adds a node at index n of a list or at the end of the list if n is
 too large.
 Parse the list once
 */
void add_node_at(struct s_node* node, struct s_node** head, int n){
    if(node == NULL || node->elem == NULL || head == NULL)
        return;
    if(*head == NULL){
        *head = node;
        return;
    }
    /* first element */
    if(n <= 0){
        add_node(node, head);
        return;
    }
    
    /* Traverse the linked list until we reach the nth element or the end*/
    int count = 0;
    struct s_node* iter = *head;
    while(count < n && iter->next != NULL){
        iter = iter->next;
        count ++;
    }
    
    /* if it's the end */
    if(iter->next == NULL && count < n){
        iter->next = node;
        node->prev = iter;
        return;
    }
    /* Add the item at index n
    iter->next->prev = node;
    node->next = iter->next;
    iter->next = node;
    node->prev = iter;*/
    
    iter->prev->next = node;
    node->prev = iter->prev;
    iter->prev = node;
    node->next = iter;
}
