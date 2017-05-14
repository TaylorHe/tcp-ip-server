#include "list.h"
/*
 Prints all the elems as chars separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL)
 */
void debug_char(struct s_node* head){
    if(head == NULL){
        my_char('\n');
        return;
    }
    struct s_node* iter = head;
    while(iter != NULL){
        my_char('(');
        print_char(iter->prev);
        my_str(" <- ");
        print_char(iter);
        my_str(" -> ");
        print_char(iter->next);
        my_char(')');
        iter = iter->next;
        if(iter != NULL){
            my_str(", ");
        }
    }
}
