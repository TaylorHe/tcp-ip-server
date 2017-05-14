#include "my.h"

void my_int(int i)
{
    unsigned int a = 1;
    unsigned int b;
    if( i < 0)
    {
        b = i * (-1);
        my_char('-');
    } else {
        b = i;
    }
    
    while(a<= b/10)
    {
        a = a * 10;
    }
    
    while( a > 0)
    {
        my_char('0' +(b / a));
        b = b % a;
        a = a / 10;
    }
}
