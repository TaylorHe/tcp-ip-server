#include "my.h"
/*
Takes a vector (array of string ended by a NULL)
 Allocates a new string and copies each string from the array into new string separated by a single space, until NULL pointer to string is found
 Returns new string
 {"hello","world",NULL} -> "hello world";
 */
char* my_vect2str(char **x){
	int counter = 0;
	int posChangeCounter = 0;
	char* newString = NULL;
	if(x != NULL){
	    /* get length of needed string */
		while(*x !=NULL){
			counter+= my_strlen(*x);
			counter++; /*leave space for null/ space*/
			x++;
			posChangeCounter++;
		}
		x-=posChangeCounter;
	    if(!counter){counter++;}
		newString = (char*)malloc(sizeof(char)*counter);
		
		while(*x !=NULL){
			while(**x!='\0'){
				*newString++ = **x;		
				*x = *x +1;
			}
			if(x+1 != NULL){
				/*don't add space if not last string*/
				*newString++ = ' ';
			}
			x++;
		}
		*newString = '\0';
	}
	return newString-counter;
}

