SERVER = server
CLIENT = client
all:
	make re -C ../list -C ../my
	gcc $(SERVER).c -o ./$(SERVER) -Wall -Werror -D_POSIX_C_SOURCE=200809L -pedantic -std=c99 -I../../include -L../../lib -lmy -llist
	gcc $(CLIENT).c -o ./$(CLIENT) -Wall -Werror -pedantic -D_POSIX_C_SOURCE=200809L -std=c99 -lcurses -I../../include -L../../lib -lmy -llist
clean:
	rm -f $(SERVER).o $(CLIENT).o
fclean:
	rm -f ./$(SERVER) $(SERVER).o ./$(CLIENT) $(CLIENT).o
re:
	make fclean all
relib:
	make re -C ../list
	make re run
