#include "list.h"

/*
 Prints the elem of node as a int
 */
void print_int(struct s_node* node){
    if(node == NULL){
        my_str("NULL");
        return;
    }
    if(node != NULL && node->elem == NULL){
        my_str("NULL");
        return;
    }
    my_int(*(int*)(node->elem));
}
