Hello!

This is my implementation of a TCP/IP chat client and server using the curses library.

There are some bugs currently. Read bugs.txt to see the problems and my miserable attempts at fixing them.


HOW TO RUN:
make re
./server [portno]
./client [host] [portno]

Type on the client to send messages through the server to other clients. Messages received from the server are displayed in COLOR_YELLOW, and your sent messages are displayed in COLOR_WHITE. Errors from the server are displayed as COLOR_RED.


If you don’t want to deal with my utter failure with curses, the working original version is in the sockettalk_old folder.