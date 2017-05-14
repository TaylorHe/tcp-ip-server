#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>
#include <curses.h>
#include "my.h"
#define BUFSIZE 1024
#define h_addr h_addr_list[0]
int run;

WINDOW *input, *display;
int maxY = 0, maxX = 0;
char charsafe[1000];
int size = 0;
char str[1024];
int maxycheck = 0, maxxcheck = 0;

void initialize_curses(){
    for(int i = 0; i < 1000; i++){
        charsafe[i] = 0;
    }
    for(int i = 32; i <= 126; i++){
        charsafe[i] = 1;
    }
    memset(str, 0, 1024);
    initscr();
    erase();
    getmaxyx(stdscr, maxY, maxX);
    display = newwin(maxY-1,maxX,0,0);
    input = newwin(1, maxX, maxY - 1, 0);
    start_color();
    //init_pair(0, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_WHITE);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    cbreak();
    scrollok(display, true);
    idlok(display, true);

    wbkgd(input, COLOR_PAIR(5));

    keypad(input, true);
    keypad(display,true);
    //wbkgd(display, COLOR_PAIR(3));
    //wbkgdset(display, COLOR_PAIR(3));
    refresh();
    wrefresh(display);
    wrefresh(input);
    wmove(input, 0,0);
}
void print_curse_color(char* poop, int pair){
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_WHITE);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    wattron(display, COLOR_PAIR(pair));
    scroll(display);
    mvwprintw(display, maxY - 2, 0, "%s", poop);
    wmove(input, 0, 0);
    refresh();
    wrefresh(display);
    wrefresh(input);

}
void print_curse(char* poop, int pair){
  start_color();
  init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_WHITE);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
    wattron(display, COLOR_PAIR(pair));
    //attron(COLOR_PAIR(0));
    scroll(display);
    mvwprintw(display, maxY - 2, 0, "%s", poop);
    wmove(input, 0,0);
    refresh();
    wrefresh(display);
    wrefresh(input);
}

void writemsg(int fd, char * buffer){
  int n = write(fd, buffer, my_strlen(buffer));
  print_curse(buffer, 3);
  fsync(fd);
  if (n < 0){
    run = 0; 
    print_curse("Error writing message to socket\n", 2);
  }
}
void writemsg_color(int fd, char* buffer, int pair){
  int n = write(fd, buffer, my_strlen(buffer));
  print_curse(buffer,pair);
  fsync(fd);
  if (n < 0){
    run = 0; 
    print_curse("Error writing message to socket\n", 2);
  }

}
void do_iteration(){
    wmove(input, 0, 0);
    getmaxyx(stdscr, maxycheck, maxxcheck);
    if(maxxcheck != maxX || maxycheck != maxY){
       // If the new window is taller then the old one, scroll the messages down
        if(maxY < maxycheck){
            wresize(display, maxycheck - 1, maxxcheck);
            wscrl(display, (maxY - maxycheck));
            wrefresh(display);
            wrefresh(input);
        } else if(maxY > maxycheck){
            // else, scroll the messages up
            wscrl(display, (maxycheck - maxY + 4));
            wresize(display, maxycheck - 1, maxxcheck);
            wrefresh(display);
            wrefresh(input);
        }
        wresize(input, 1, maxxcheck);
        maxY = maxycheck;
        maxX = maxxcheck;
        delwin(input);
        //wclear(inputWin);
        input = newwin(1, maxX, maxY - 1, 0);
        wbkgd(input, COLOR_PAIR(5));
        keypad(input, true);
        refresh();
        wrefresh(display);
        wrefresh(input);
        wmove(input, 0,0);
        int reloadchar = 0;
        while(str[reloadchar] < size){
            mvwprintw(input, 0, reloadchar, &str[reloadchar]);
            reloadchar++;
        }
        refresh();
        wrefresh(display);
        wrefresh(input);
    } else {

        //attron(COLOR_PAIR(2));
        int buf = 0;
        int getchar = 0;
        int resized = 0;
        noecho();
        while((getchar = wgetch(input)) && buf < 1023){
            //handle left, right, and delete
          if(getchar == KEY_RESIZE || getchar == 410){
            resized = 1;
            refresh();
            wrefresh(input);
            wrefresh(display);
          }
            if(getchar == '\n'){
                str[size] = '\0';
                break;
            } else if(getchar == 127 || getchar == KEY_BACKSPACE){
                if(buf > 0){
                    buf--;
                    wmove(input, 0, buf);
                    wdelch(input);
                    int temp = buf;
                    while(temp <= size){
                        str[temp] = str[temp+1];
                        temp++;
                    }
                    size--;
                }
               
            } else if(getchar == KEY_LEFT){
                if(buf > 0){
                    buf--;
                    wmove(input, 0, buf);
                }
            } else if(getchar == KEY_RIGHT){
                if(buf < size){
                    buf++;
                    wmove(input, 0, buf);
                }

            }else if(charsafe[getchar] == 0){
                // do nothing                 
            }else if(charsafe[getchar] == 1){
                if(buf == size){
                    mvwprintw(input, 0, buf, "%c", getchar);     
                } else {
                    winsch(input, getchar);
                    int temp = size;
                    while(temp >= buf){
                        str[temp+1] = str[temp];
                        temp--;

                    }
                }
                str[buf] = getchar;
                size++;
                buf++;
                wmove(input, 0, buf);
                
                
            }
            wmove(input, 0, buf);
            
        }
        
        if(resized == 0){
          wclear(input);
    
        wattron(display, COLOR_PAIR(1));
        scroll(display);
        mvwprintw(display, maxY - 2, 0, "%s",str);
        wmove(input, 0,0);
        size = 0;
        buf = 0;
        //memset(str, 0, 1024);
        refresh();
        wrefresh(input);
        wrefresh(display);
        }
        
        
        
    }
}



void s_addr_cpy(char *a, char *b, int len){
  int i = 0;
  for(i = 0; i < len; ++i){
    b[i] = a[i];
  }
}

int main(int argc, char **argv){
  int sockfd, portno, n, w_ok;
  int run = 1;
  fd_set fds;
  int maxfd;
  struct sockaddr_in serv_addr;
  struct hostent *server;
  char i_buf[BUFSIZE];
  char o_buf[BUFSIZE];


  if (argc != 3) {
    my_str("Usage: ./client [host] [port]\n");
    exit(0);
  }
  portno = my_atoi(argv[2]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0){
    my_str("Socket error\n");
    run = 0;
    return -1;
  } 
   
  server = gethostbyname(argv[1]);
  if (server == NULL) {
    my_str("Server not found\n");
    run = 0;
    return -1;
  }

  for(int i = 0; i < sizeof(serv_addr); i++){
    ((char*) &serv_addr)[i] = 0;
  }


  // Connect to server
  serv_addr.sin_family = AF_INET;
  s_addr_cpy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0){
    my_str("Connection error\n");
    run = 0;
    return -1;
  }

  //Get the nickname
  my_str("Enter nickname: ");
  for(int i = 0; i < BUFSIZE; i++){
    i_buf[i] = 0;
  }
  fgets(i_buf, BUFSIZE - 1, stdin);

  //give server the username
  writemsg(sockfd, i_buf);
  if(sockfd > 0){
    maxfd = sockfd;
  } else {
    maxfd = 0;
  }

  initialize_curses();
   start_color();
    //init_pair(0, COLOR_RED, COLOR_BLACK);
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    init_pair(4, COLOR_BLUE, COLOR_WHITE);
    init_pair(5, COLOR_BLACK, COLOR_WHITE);
  // While loop
  while(run){
    i_buf[0] = 0;
    o_buf[0] = 0;
    memset(str, 0, 1024);    
    FD_ZERO(&fds);
    FD_SET(sockfd, &fds);
    FD_SET(0, &fds);
    select(maxfd+1, &fds, NULL, NULL, NULL);
    w_ok = 0;
    if (FD_ISSET(0, &fds)){
      // Put one iteration of loop in here
      do_iteration();
      my_strcpy(i_buf, str);
      send(sockfd, i_buf, strlen(i_buf), 0);
      // for(int i = 0; i < BUFSIZE; i++){
      //   i_buf[i] = 0;
      // }
      // n = read(0, i_buf, BUFSIZE - 1);
      // i_buf[n] = 0;
      // if (n < 0){ 
      //   run = 0;
      //   my_str("stdin error\n");
      //   delwin(input);
      //   delwin(display);
      //   endwin();
	     //  return -1;
      // }
      // w_ok = 1;
    }
   
    
  if (FD_ISSET(sockfd, &fds)){
      for(int i = 0; i < BUFSIZE; i++){
        o_buf[i] = 0;
      }
      n = read(sockfd, o_buf, BUFSIZE - 1);
      o_buf[n] = 0;
      if (n < 0) {
         print_curse("Error reading from server\n", 2);
	       delwin(input);
         delwin(display);
         endwin();
         return -1;
      }else if(n == 0){
	       run = 0;
	       print_curse("Server terminated unexpectedly\n", 2);
         print_curse("Exiting Client...\n", 2);
         delwin(input);
         delwin(display);
         endwin();
         return -1;
      }
      if(!(o_buf[0] == '/' && my_strcmp("/exit", o_buf) == 0)){
        print_curse(o_buf, 3);
        //print_curse("\n");
        wmove(input,0,0);
        refresh();
        wrefresh(input);
        wrefresh(display);
	      // my_str(o_buf), my_str("\n");
      }
    }
    // Three way handshake
    if(run && i_buf[0] == '/'){
      if(my_strcmp("/exit", i_buf) == 0){
	      w_ok = 0;

  	    writemsg(sockfd, i_buf);
  	    i_buf[0] = 0;
        delwin(input);
        delwin(display);
        endwin();
        return -1;
      }
    }
    
    if(run && o_buf[0] == '/'){
      if(my_strcmp("/exit", o_buf) == 0){
	       print_curse("Session was terminated by the server\n", 3);
	       run = 0;
         delwin(input);
         delwin(display);
         endwin();
      }
    }
    
    if(run && w_ok){
      writemsg_color(sockfd, i_buf, 3);

    }    
    wmove(input, 0, 0);
    refresh();
    wrefresh(input);
    wrefresh(display);
  }
          delwin(input);
         delwin(display);
         endwin();
  return 0;
}
