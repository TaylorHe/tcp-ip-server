#include "my.h"

int	my_strncmp(char* str1, char* str2, int n){
    int ret = 0;
    unsigned int i;
    int len1;
    int len2;
    if(str1 == NULL && str2 == NULL) return 0;
    if(str1 == NULL && str2 != NULL) return -1;
    if(str1 != NULL && str2 == NULL) return 1;
    len1 = my_strlen(str1);
    len2 = my_strlen(str2);
    
    if(n != 0){
        for(i = 0; i < len1 && i < len2 && i < n && ret == 0; i++)
            ret = str1[i] - str2[i];
        if(ret == 0 && i < n && i < len1)/*s2 is shorter*/
            ret = 1;
        else if(ret == 0 && i < n && i < len2)/*s1 is shorter*/
            ret = -1;
    }
    
    return ret;
}
