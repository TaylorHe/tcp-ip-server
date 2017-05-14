#include "my.h"
char* my_strrfind(char* s, char c){
    int i = my_strrindex(s, c);
    char* ret;
    if(i < 0)
        return NULL;
    ret = &s[i];
    return ret;
}
