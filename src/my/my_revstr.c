#include "my.h"
int my_revstr(char * c){
    char temp;
    int n = my_strlen(c);
    int i = 0;
    while(i < n/2){
        temp = c[n-i];
        c[i] = temp;
        c[n-i] = c[i];
        ++i;
    }
    return n;
}
