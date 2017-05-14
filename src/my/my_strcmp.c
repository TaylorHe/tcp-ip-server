#include "my.h"
int	my_strcmp(char* str1, char* str2)
{
    int	i = 0;
    int len1;
    int len2;
    /* handle NULL cases */
    if(str1 == NULL && str2 == NULL) return 0;
    if(str1 == NULL && str2 != NULL) return -1;
    if(str1 != NULL && str2 == NULL) return 1;

    /* while not null and equal */
    while (str1[i] != '\0'
           && str2[i] != '\0'
           && str1[i] == str2[i]){
        ++i;
    }
    len1 = my_strlen(str1);
    len2 = my_strlen(str2);
    if(i == len1 && i < len2) return -1;
    if(i == len2 && i < len1) return 1;
    if(i == len1 && i == len2) return 0;
    return (str1[i] - str2[i]);
}
