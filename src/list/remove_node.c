#include "list.h"

/*
 Removes the given node from the list. Returns elem and frees the
 node from memory.
 DOES NOT PARSE THE LIST!!!!!!!!!!!!!!!
 */
void* remove_node(struct s_node** node){
    
    //my_str("my node is *null\n");
    if(node == NULL){
        //my_str("my node is null\n");
        return NULL;
    }
    if(*node == NULL || (*node)->elem == NULL){
        //my_str("my node is *null\n");
        //free(**node);
        
        free(*node);
        *node = NULL;
        //free(node);
        return NULL;
    }
    void* ret = NULL;
    /* it is in the middle of the list */
    if((*node)->next != NULL && (*node)->prev != NULL){
        //my_str("my node is 1null\n");
        ret = (*node)->elem;
        (*node)->prev->next = (*node)->next;
        (*node)->next->prev = (*node)->prev;
        free(*node);
        *node = NULL;
    } else
    /* it is the head of the list */
    if((*node)->next != NULL && (*node)->prev == NULL){
        //my_str("my node is 2null\n");
        ret = (*node)->elem;
        (*node)->next->prev = NULL;
        struct s_node* t = *node;
        *node = (*node)->next;
        free(t);
        t = NULL;
    } else
    /* it is the tail of the list */
    if((*node)->next == NULL && (*node)->prev != NULL){
        //my_str("my node is 3null\n");
        ret = (*node)->elem;
        (*node)->prev->next = NULL;
        free(*node);
        *node = NULL;
    } else {
        //my_str("my node is *4null\n");
        ret = (*node)->elem;
        free(*node);
        *node = NULL;
    }
    
    return ret;
}
