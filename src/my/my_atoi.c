#include "my.h"
#include <stdlib.h>
int my_atoi(char* s) {
    if(s == NULL) return 0;
    unsigned int ret = 0;
    int preceding = 1;
    int pos = 1;
    while (*s) {
        /* if negative signs, reverse signs */
        if(preceding && *s == '-') pos = !pos;
        /* If it is a digit, add to ret val
         preceding = false;*/
        if (*s >= '0' && *s <= '9'){
            ret *= 10;
            ret += *s - '0';
            preceding = 0;
        } else if(!preceding){
            if(!pos) return ret * -1;
            return ret;
        }
        s++;
    }
    if(!pos) return ret * -1;
    return ret;
}
