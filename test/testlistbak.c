#include <stdio.h>
#include "list.h"
int main(){
    struct s_node* int_node4 = new_node("4");
    struct s_node* int_node3 = new_node("3");
    struct s_node* int_node2 = new_node("2");
    struct s_node* int_node1 = new_node("1");
    
    // TESTING ADD_NODE
    printf("TESTING ADD_NODE ------------------\n");
    add_node(int_node4, &int_node3);
    debug_int(int_node4);
    printf("\nShould be (NULL 4 NULL)\n\n");
    
    add_node(int_node4, NULL);
    debug_int(int_node4);
    printf("\nShould be (NULL 4 NULL)\n\n");
    
    add_node(int_node2, &int_node3);
    debug_int(int_node2);
    printf("\nShould be (NULL <- 2 -> 3), (2 <- 3 -> NULL)\n\n");
    add_node(int_node1, &int_node2);
    
    // TESTING ADD_ELEM
    printf("TESTING ADD_ELEM ------------------\n");
    add_elem(NULL, &int_node2);
    debug_int(int_node1);
    printf("\nShould be (NULL 1 2), (1 2 3), (2 3 NULL)\n\n");
    //add_elem("1", &int_node2);
    //debug_int(int_node2);
    //printf("\nShould be (1 <- 2 -> 3), (2 <- 3 -> NULL)\n\n");
    
    //TESTING APPEND
    printf("TESTING APPEND ------------------\n");
    struct s_node* int_nodeA = new_node("A");
    append(int_nodeA, &int_node1);
    debug_int(int_node1);
    printf("\nShould be (NULL 1 2), (1 2 3), (2 3 A), (3 A NULL)\n\n");
    
    //TESTING ADD_NODE_AT
    printf("TESTING ADD_NODE_AT ------------------\n");
    struct s_node* int_nodeB = new_node("B");
    add_node_at(int_nodeB,&int_node1, 100);
    debug_char(int_node1);
    printf("\nShould be (NULL 1 2), (1 2 3), (2 3 A), (3 A B), (A B NULL)\n\n");
    
    struct s_node* int_nodeNULL = new_node(NULL);
    add_node_at(int_nodeNULL, &int_node1, 100);
    debug_char(int_node1);
    printf("\nShould be (NULL 1 2), (1 2 3), (2 3 A), (3 A B), (A B NULL), (B NULL NULL)\n\n");

    
    //TESTING REMOVE_NODE
    printf("TESTING REMOVE_NODE ------------------\n");
    remove_node(&int_nodeA);
    debug_string(int_node2);
    printf("\nShould be (NULL 1 2) (1 2 3), (2 3 B), (3 B NULL), (B NULL NULL)\n\n");
    
    // TESTING REMOVE_LAST
    printf("TESTING REMOVE_LAST ------------------\n");
    remove_last(&int_node1);
    debug_string(int_node1);
    printf("\nShould be (NULL 1 2) (1 2 3), (2 3 B), (3 B NULL)\n\n");
    
    // TESTING REMOVE_NODE_AT
    printf("TESTING REMOVE_NODE_AT ------------------\n");
    debug_string(int_node1);
    printf("\n");
    remove_node_at(&int_node1, -13);
    debug_string(int_node1);
    printf("\nShould be (NULL 2 3), (2 3 B), (3 B NULL)\n\n");
    
    int_node1 = new_node("1");
    add_node(int_node1, &int_node2);
    debug_string(int_node1);
    printf("\n");
    remove_node_at(&int_node1, 0);
    debug_string(int_node1);
    printf("\nShould be (NULL 2 3), (2 3 B), (3 B NULL)\n\n");
    
    int_node1 = new_node("1");
    add_node(int_node1, &int_node2);
    debug_string(int_node1);
    printf("\n");
    remove_node_at(&int_node1, 5);
    debug_string(int_node1);
    printf("\nShould be (NULL 1 2), (1 2 3), (2 3 NULL)\n\n");
    
    
    int_node1 = new_node("1");
    add_node(int_node1, &int_node2);
    debug_string(int_node1);
    printf("\n");
    remove_node_at(&int_node1, 1);
    debug_string(int_node1);
    printf("\nShould be (NULL 1 3), (1 3 NULL)\n\n");
    
    
    
    //TESTING COUNT_S_NODES
    printf("TESTING COUNT_S_NODES ------------------\n");
    printf("%i, %i, %i\n", count_s_nodes(int_node1), count_s_nodes(NULL), count_s_nodes(new_node("8")));
    printf("Should be 3, 0, 1\n\n");
    
    //TESTING EMPTY_LIST
    printf("TESTING EMPTY_LIST ------------------\n");
    debug_string(int_node1);
    printf("\n");
    empty_list(&int_node1);
    debug_string(int_node1);
    printf("\nShould print nothing\n\n");
    // Build list again
    int_node1 = new_node("1");
    int_node2 = new_node("2");
    int_node3 = new_node("3");
    append(int_node2, &int_node1);
    append(int_node3, &int_node1);
    
    // TESTING NODE_AT
    printf("TESTING NODE_AT ------------------\n");
    
    debug_string(int_node1);
    printf("\n");
    print_int(node_at(int_node1, 8));
    printf("\nShould be 3\n");
    print_int(node_at(int_node1, 2));
    printf("\nShould be 3\n");
    print_int(node_at(int_node1, 0));
    printf("\nShould be 1\n");
    print_int(node_at(int_node1, 1));
    printf("\nShould be 2\n");
    print_int(node_at(int_node1, -8));
    printf("\nShould be 1\n\n");
    
    // TESTING ELEM_AT
    printf("TESTING ELEM_AT ------------------\n");
    //too lazy

    



    
    
    
    
    
    
    
    
    
    
}
