#include "list.h"

/*
 Inserts a node at the start of the list You can assume that the provided pointer to
 head is the actual head of the list, and there are no elements before it.
 ****DO NOT add a node with a NULL elem or with a NULL head.****
 Make sure to check that head!= NULL, and that *head !=NULL
 DOES NOT PARSE THE LIST
*/
void add_node(struct s_node* node, struct s_node** head){
    if(node == NULL || node->elem == NULL || head == NULL)
        return;
    if(*head == NULL){
        *head = node;
        return;
    }
    
    //node->prev = NULL;
    (*head)->prev = node;
    node->next = *head;
    //node->prev = NULL;
    (*head) = node;
}
