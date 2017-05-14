OBJS=add_node.o new_node.o add_elem.o append.o add_node_at.o remove_node.o remove_last.o remove_node_at.o count_s_nodes.o empty_list.o node_at.o elem_at.o print_int.o print_char.o print_string.o debug_int.o debug_char.o debug_string.o
CFLAGS=-I../../include -g -Wall -Werror --pedantic -std=c99 
CC=gcc
LIB=liblist.a
RL=ranlib liblist.a
LPATH=../../lib

all: $(OBJS)
	ar -rc $(LIB) $(OBJS)
	ranlib $(LIB)
	mv $(LIB) $(LPATH)
	
	
clean:
	rm -f $(OBJS)

fclean: clean
	rm $(LPATH)/$(LIB)

re:
	make fclean all

