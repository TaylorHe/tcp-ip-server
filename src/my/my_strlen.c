#include "my.h"
int my_strlen(char* c){
    int i = 0;
    if(c == NULL){
        return -1;
    }
    while(c[i] != '\0'){
        i++;
    }
    return i;
}
