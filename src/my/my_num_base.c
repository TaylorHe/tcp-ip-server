#include "my.h"

void my_num_base(int num, char* s){
    int base, r, i, j;
    long int n = num, temp;
    
    if((base = my_strlen(s)) > 0){
        if(n < 0){
            my_char('-');
            n *= -1;
        }
        temp = n;
        if(base != 0 && base != 1){
            for(i = 0 ; temp > 0 ; i++, temp /= base);
            for(temp = n ; i != 0 ; temp = n, i--){
                for(j = 0 ; j < i ; r = temp % base, temp /= base, j++);
                my_char(s[r]);
            }
        }else if(base == 1){
            for(i = 0; i < temp; i++)
                my_char(s[0]);
        }else
            my_str("You can't even base.");
    }else if(n == 0){
        my_int(0);
    }else{
        my_str("Your base is no good.");
    }
}
