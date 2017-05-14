#include "my.h"

int my_strindex(char* s, char c){
    int i = 0;
    if(s == NULL || !(my_strcmp(s,""))){
        return -1;
    }
    while(s[i] != '\0'){
        if(s[i] == c){
            return i;
        }
        ++i;
    }
    return -1;
}
