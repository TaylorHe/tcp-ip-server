#include "list.h"
/*
 Prints all the elems as strings separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL)
 */
void debug_string(struct s_node* head){
    if(head == NULL){
        my_char('\n');
        return;
    }
    struct s_node* iter = head;
    while(iter != NULL){
        my_char('(');
        print_string(iter->prev);
        my_str(" <- ");
        print_string(iter);
        my_str(" -> ");
        print_string(iter->next);
        my_str(")");
        iter = iter->next;
        if(iter != NULL){
            my_str(", ");
        }
    }
}
