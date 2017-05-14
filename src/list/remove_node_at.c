#include "list.h"
/*
 Removes the node at index n or the last node.
 Parse once
 */
void* remove_node_at(struct s_node** head, int n){
    if(head == NULL || *head == NULL){
        return NULL;
    }
    int count = 0;
    struct s_node* iter = *head;
    void* ret = iter->elem;
    /* if 0th item or negative */
    if(n <= 0) {
        return remove_node(head);
    }
    /* if last item or greater than size*/
    if(n > count_s_nodes(*head)){
        remove_last(head);
        return ret;
    }
    /* else */
    while(iter){
        ret = iter->elem;
        if(n == count-1){
            my_int(count);
            my_str("\n");
            iter->next->prev = iter->prev;
            iter->prev->next = iter->next;
            free(iter);
            return ret;
        }
        iter = iter->next;
        count ++;
    }
    return ret;
}
