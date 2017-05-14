#include <stdlib.h>
#include "my.h"

char* my_strdup(char* str){
    int len;
    char* dup;
    if(str == NULL) return NULL;

    /* allocate memory, use my_strcpy */
    len = my_strlen(str);
    dup = malloc(len + 1);
    dup = my_strcpy(dup, str);
    dup[len] = '\0';
    return (dup);
}
