#include "my.h"

char* my_strcat(char *dst, char *src){
    int lend;
    int i = 0;
    if(dst == NULL) return NULL;
    if(src == NULL) return dst;
    if(*dst == '\0') return dst;
    lend = my_strlen(dst);
    while(src[i]) {
        dst[lend + i] = src[i];
        i = i + 1;
    }
    dst[lend + i] = '\0';
    return (dst);
}
