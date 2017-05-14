#include <stdlib.h>
#include "my.h"

char* my_strconcat(char* a, char* b){
    int len_a;
    int len_b;
    char* ret;
    int len_total;
    int i;
    if(a == NULL && b == NULL) return NULL;
    len_a = my_strlen(a);
    len_b = my_strlen(b);
    if (len_a < 0) len_a = 0;
    if (len_b < 0) len_b = 0;

    len_total = len_a + len_b + 1;
    ret = malloc(len_total);
    if(ret == NULL)
        return (NULL);
    i = 0;
    while(i < len_a){
        ret[i] = a[i];
        ++i;
    }
    while(i < len_total - 1){
        ret[i] = b[i - len_a];
        ++i;
    }
    ret[len_total - 1] = '\0';
    return ret;
}
