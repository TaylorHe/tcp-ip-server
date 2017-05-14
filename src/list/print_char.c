#include "list.h"

/*
 Prints the elem of node as a char
 */
void print_char(struct s_node* node){
    if(node == NULL){
        my_str("NULL");
        return;
    }
    if(node->elem == NULL){
        my_str("NULL");
        return;
    }
    char i = *(char*)node->elem;
    my_char(i);
}
