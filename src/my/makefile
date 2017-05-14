OBJS=my_alpha.o my_char.o my_revstr.o my_str.o my_strlen.o my_int.o my_num_base.o my_strindex.o my_strrindex.o my_strfind.o my_strrfind.o my_strcmp.o my_strncmp.o my_strcpy.o my_strncpy.o my_strcat.o my_strdup.o my_strconcat.o my_strnconcat.o my_atoi.o my_vect2str.o
CFLAGS=-I../../include -Wall -Werror --pedantic -std=c99 
CC=gcc
LIB=libmy.a
RL=ranlib libmy.a
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
