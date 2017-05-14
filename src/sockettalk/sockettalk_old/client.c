#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h> 
#include "my.h"
#define BUFSIZE 1024
#define h_addr h_addr_list[0]
int run;

void writemsg(int fd, char * buffer){
  int n = write(fd, buffer, my_strlen(buffer));
  fsync(fd);
  if (n < 0){
    run = 0; 
    my_str("Error writing message to socket\n");
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

  // While loop
  while(run){
    i_buf[0] = 0;
    o_buf[0] = 0;    
    FD_ZERO(&fds);
    FD_SET(sockfd, &fds);
    FD_SET(0, &fds);
    select(maxfd+1, &fds, NULL, NULL, NULL);
    w_ok = 0;
    if (FD_ISSET(0, &fds)){
      for(int i = 0; i < BUFSIZE; i++){
        i_buf[i] = 0;
      }
      n = read(0, i_buf, BUFSIZE - 1);
      i_buf[n] = 0;
      if (n < 0){ 
        run = 0;
        my_str("Error reading from stdin\n");
	      return -1;
      }
      w_ok = 1;
    }
   
    
  if (FD_ISSET(sockfd, &fds)){
      for(int i = 0; i < BUFSIZE; i++){
        o_buf[i] = 0;
      }
      n = read(sockfd, o_buf, BUFSIZE - 1);
      o_buf[n] = 0;
      if (n < 0) {
         my_str("Error reading from server\n");
	       return -1;
      }else if(n == 0){
	       run = 0;
	       my_str("Server terminated unexpectedly\n");
         my_str("Exiting Client...\n");
         return -1;
      }
      if(!(o_buf[0] == '/' && my_strcmp("/exit", o_buf) == 0))
	       my_str(o_buf), my_str("\n");
    }
    // Three way handshake
    if(run && i_buf[0] == '/'){
      if(my_strcmp("/exit", i_buf) == 0){
	     w_ok = 0;
	     writemsg(sockfd, i_buf);
	     i_buf[0] = 0;
      }
    }
    
    if(run && o_buf[0] == '/'){
      if(my_strcmp("/exit", o_buf) == 0){
	       my_str("Session was terminated by the server\n");
	       run = 0;
      }
    }
    
    if(run && w_ok){
      writemsg(sockfd, i_buf);
    }    
    
  }
  return 0;
}
