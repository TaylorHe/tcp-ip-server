
#include "my.h"
char* my_strnconcat(char *a, char *b, int n)
{
    char *res;
    int i;
    int lena = my_strlen(a);
    int lenb = my_strlen(b);
    int len_total;
    /* fix */
    if(n < 0) n = 0;
    if(lena + lenb == -2) return NULL;
    if(lena == -1) lena = 0;
    if(lenb == -1) lenb = 0;
    /* max out n */
    if(n > lenb) n = lenb;
    len_total = lena + n;
    res = (char*)malloc(len_total+1);
    i = 0;
    while(i < lena){
        res[i] = a[i];
        ++i;
    }
    while(i < len_total){
        res[i] = b[i - lena];
        ++i;
    }
    res[len_total] = '\0';
    return res;
}
