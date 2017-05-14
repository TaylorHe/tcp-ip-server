#include "my.h"
char* my_strfind(char* s, char c){
    int i = my_strindex(s, c);
    char* ret;
    if(i < 0)
        return NULL;
    ret = &s[i];
    return ret;
}
