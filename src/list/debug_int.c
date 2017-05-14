#include "list.h"
/*
 Prints all the elems as ints separated by a space in the format
 (NULL <- Elem -> Next elem), ..., (Previous elem <- Elem -> NULL)
 */
void debug_int(struct s_node* head){
    if(head == NULL){
        my_char('\n');
        return;
    }
    struct s_node* iter = head;
    while(iter != NULL && iter->elem != NULL){
        my_char('(');
        print_int(iter->prev);
        my_str(" <- ");
        print_int(iter);
        my_str(" -> ");
        print_int(iter->next);
        my_char(')');
        iter = iter->next;
        if(iter != NULL){
            my_str(", ");
        }
    }
}
