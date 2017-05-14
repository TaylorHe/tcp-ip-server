#include "list.h"
/*
 Creates a new node with elem and adds it to head (again, assume head is actually the head). DO NOT add a NULL elem to the list
 DOES NOT PARSE THE LIST
 */
void add_elem(void* elem, struct s_node** head){
    if(elem == NULL || head == NULL){
        return;
    }
    struct s_node* node = (struct s_node*)malloc(sizeof(struct s_node));
    if(*head == NULL){
        node->elem = elem;
        node->next = NULL;
        node->prev = NULL;
        *head = node;
        return;
    }
    
    
    node->elem = elem;
    node->next = *head;
    node->prev = NULL;
    (*head)->prev = node;
    *head = node;
    
}
