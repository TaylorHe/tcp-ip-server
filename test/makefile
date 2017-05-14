all:
	gcc testlist.c -o testlist -g -Wall -Werror -std=c99 -pedantic -I../include -L../lib -lmy -llist

clean:
	rm -f *.o
fclean: clean
	rm -f ../lib/liblist.a
re:
	make fclean all
