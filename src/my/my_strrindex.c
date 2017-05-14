#include "my.h"

int my_strrindex(char* s, char c){
    int i;
    if(s == NULL){
        return -1;
    }
    i = my_strlen(s) - 1;
    while(i >= 0){
        if(s[i] == c){
            return i;
        }
        --i;
    }
    return -1;
}
