#include "my.h"

char* my_strcpy(char *dst, char *src){
    int i = 0;
    if(dst == NULL) return NULL;
    if(src == NULL) return dst;
    while(src[i]){
        dst[i] = src[i];
        ++i;
    }
    dst[i] = '\0';
    return dst;
}
