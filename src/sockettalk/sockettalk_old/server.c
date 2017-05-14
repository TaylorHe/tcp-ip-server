#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include "list.h"
#include "my.h"


// define all the things!
#define BUFSIZE 1024
char valid_char_set[256];
typedef struct s_node Node;
Node *dummy = NULL;
Node ** client_list = &dummy;
struct sockaddr_in serv_addr;
typedef struct client_obj{
  int fd, name_len;
  char * name;
} Client;

int portno;
int sockfd;
Client *client;

void send_to_all(char * message, int ignore);

int my_error(char *msg){
  my_str(msg);
  my_char('\n');
  return -1;
}


Client * make_client(){
  Client * c = (Client *)malloc(sizeof(Client));
  c->name = NULL;
  return c;
}

void remove_client(Client * client){
  close(client->fd);
  if(client->name != NULL)
    free(client->name);
  free(client);
}


int write_to_client(Client *client, char *message){
  int n, len;
  len = my_strlen(message);
  if(len <= 0){
    return 1;
  }
  n = write(client->fd,message,len);
  my_str(message);
  my_str(" sent to ");
  my_str(client->name);
  my_str("\n");
  fsync(client->fd);
  return n;
}


int remove_client_from_list(Node ** head, Node * toRemove){
  if(toRemove == *head){
    remove_client(remove_node(head));
  }else{
    remove_client(remove_node(&toRemove));
  }
  return -1;
}

void client_leaving(char * outbuffer, Client * client){
  if(client->name == NULL) return;
  my_strcpy(outbuffer, "SERVER SAYS: ");
  my_strcpy(outbuffer + 13, client->name);
  my_strcpy(outbuffer + 13 + client->name_len, " has left the chat");
  send_to_all(outbuffer, client->fd);
}


int rm_unexpected_client_error(Node ** head, Node * temp){
  my_str("client ");
  my_str(client->name);
  my_str(" unexpectedly terminated.\n");
  return remove_client_from_list(head, temp);
}

void make_valid_buff(char * str){
  if(my_strlen(str) > 0 && str[my_strlen(str) - 1] == '\n')
    str[my_strlen(str) - 1] = 0;
  unsigned char toCheck;
  while((toCheck=(unsigned char) *(str++))){
    if(valid_char_set[(int) toCheck] == 0){
      my_str("Invalid character with ascii code ");
      my_int((int) toCheck);
      my_str(". Stopping valid check.\n");
      *(str - 1) = 0;
      break;
    }
  }
}

void send_to_all(char * message, int ignore){
  Node * temp = NULL;
  for(temp = *client_list; temp != NULL; temp = temp->next){
    client = (Client *)temp->elem;
    /*if(ignore != client->fd)*/
    write_to_client(client, message);
  }
}

int readFromClient(int fd){
  char *nick;
  Node *temp = NULL;
  int n, oldlen;
  char outbuffer[BUFSIZE];
  char buffer[BUFSIZE];
  for(int i = 0; i < BUFSIZE; i++){
    buffer[i] = 0;
    outbuffer[i] = 0;
  }
  temp = *client_list;
  client = NULL;
  while(temp != NULL){
    client = (Client *)temp->elem;
    if(client->fd == fd)
      break;
    /*move on*/
    temp = temp->next;
  }
  
  if(temp == NULL || client == NULL)
    return 0;
  
  n = read(client->fd,buffer,255);
  
  if (n <= 0){
    client_leaving(outbuffer, client);
    return rm_unexpected_client_error(client_list, temp);
  }

  // Make sure the message is valid
  make_valid_buff(buffer);

  if(client->name == NULL){
    if(buffer[0] == '/' || buffer[0] == 0){
      write_to_client(client, "Error setting username, try again\n");
      return 0;
    }
    my_str("New user: "), my_str(buffer), my_str("\n");
    client->name = my_strdup(buffer);
    client->name_len = my_strlen(client->name);
    
    if (write_to_client(client, "Welcome to Taylor's Chatroom\n") < 0){
      return rm_unexpected_client_error(client_list, temp);
    }

    //If someone joined
    char *jmsg = " has joined the chat";
    char *smsg = "SERVER SAYS: ";
    int len = my_strlen(smsg) + client->name_len + my_strlen(jmsg);
    char * message = malloc(sizeof(char) * (len + 1));
    my_strcpy(message, smsg);
    my_strcpy(message + my_strlen(smsg), client->name);
    my_strcpy(message + (my_strlen(smsg) + client->name_len), jmsg);
    message[len] = 0;
    send_to_all(message, client->fd);

  
  }else if(buffer[0] == '/'){
    if(my_strcmp(buffer, "/exit") == 0){
      write_to_client(client, "/exit");
      client_leaving(outbuffer, client);
      return remove_client_from_list(client_list, temp);
    }else if(my_strncmp("/me ",buffer, 4) == 0){
      my_strcpy(outbuffer, client->name);
      my_strcpy(outbuffer + client->name_len, " ");
      my_strcpy(outbuffer + client->name_len + 1, buffer + 4);
      
      send_to_all(outbuffer, client->fd);
    }else if(my_strncmp("/nick ",buffer, 6) == 0){
      nick = buffer + 6;
      if(nick[0] == '/' || nick[0] == 0){
	       write_to_client(client, "SERVER SAYS: invalid nickname.");
	     return 0;
      }
      oldlen = client->name_len + 13;
      my_strcpy(outbuffer, "SERVER SAYS: ");
      my_strcpy(outbuffer + 13, client->name);
      free(client->name);
      client->name = my_strdup(nick);
      client->name_len = my_strlen(nick);
      my_strcpy(outbuffer + oldlen, " changed name to ");
      oldlen += 17;
      my_strcpy(outbuffer + oldlen, client->name);
      oldlen += client->name_len;
      
      send_to_all(outbuffer, client->fd);
    }else{
      write_to_client(client, "SERVER SAYS: Invalid command!");
    }
  }else{
    
    my_strcpy(outbuffer, client->name);
    my_strcpy(outbuffer + client->name_len, ": ");
    my_strcpy(outbuffer + client->name_len + 2, buffer);
    
    send_to_all(outbuffer, client->fd);
  }
  return 0;
}


int main(int argc, char *argv[]){
  if(argc != 2){
    my_str("Usage is: ./server [port]");
    return 1;
  }
  portno = my_atoi(argv[1]);
  if(portno < 1){
    my_str("Invalid port number\n");
    return 1;
  }

  // Build a valid char set
  for(int i = 0; i < 256; ++i){
    if(i >= 32 && i <=126){
      valid_char_set[i] = 1;
    } else if(i == 0 || i == 7 || i == 9){
      valid_char_set[i] = 1;
    } else{
      valid_char_set[i] = 0;
    }
  }
  valid_char_set[58] = 0;

  fd_set active_fd_set, read_fd_set;
  int i, times = 10;
  struct sockaddr_in clientname;
  socklen_t size;
  int enable = 1;
  // Start the socket
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) 
    return my_error("Error opening socket\n");
  if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) < 0)
    return my_error("setsockopt(SO_REUSEADDR) error\n");
  for(int i = 0; i < sizeof(serv_addr); i++){
    ((char*) &serv_addr)[i] = 0;
  }
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    return my_error("Binding error\n");
  

  FD_ZERO (&active_fd_set);
  FD_SET (sockfd, &active_fd_set);
  listen(sockfd, SOMAXCONN);
  while (times){
    read_fd_set = active_fd_set;
    if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0){
      return my_error("select error \n");
    }

  
    for (i = 0; i < FD_SETSIZE; ++i){
      if (FD_ISSET (i, &read_fd_set)){
        if (i == sockfd){
          int new;
          size = sizeof (clientname);
          new = accept(sockfd, (struct sockaddr *) &(clientname), &(size));
        if (new >= 0){
          FD_SET(new, &active_fd_set);
          Client * client = make_client();
          client->fd = new;
          add_elem((void *)client, client_list);
        }
      }else{
        // Read from existing client
          if (readFromClient(i) < 0){
            FD_CLR(i, &active_fd_set);
          }
        }
      }
    }
  }
  return 0;
  
  send_to_all("/exit", -1);
  client = (Client *)remove_node(client_list);
  while(client != NULL){
    remove_client(client);
    client = (Client *)remove_node(client_list);
  }
  close(sockfd);
  
  return 0; 
}
