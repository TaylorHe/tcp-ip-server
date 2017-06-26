# tcp-ip-server
A TCP/IP chat client and server with custom implementations of my own string and linked list library.
Written in good ol' fashioned C.
-------------
Hello!

This is my implementation of a TCP/IP chat client and server using the curses library.

I've also built my own custom doubly linked list library and custom string library with [a stupid amount of] error handling and null checks. 
Give any function any parameter you want, and most likely it won't break. NULL checks for days.

There are some bugs currently, as all applications with curses have. 

Read bugs.txt to see the problems and my (miserable) attempts at fixing them and some hacky fixes I've found through much trial and error.

This compiles on Mac and Linux afaik. I have no idea if it runs on Cygwin.

HOW TO RUN:
cd src/sockettalk
make re
./server [portno]
./client [host] [portno]

Type on the client to send messages through the server to other clients. Messages received from the server are displayed in COLOR_YELLOW, and your sent messages are displayed in COLOR_WHITE. Errors from the server are displayed as COLOR_RED.

You can have unlmited clients, if you wish. I used select() instead of multithreading so it doesn't die with more clients.

The server displays its recieved messages and what it send to other clients. 

If you don’t want to deal with curses, a working original version that uses the terminal is in the src/sockettalk/sockettalk_old folder.
