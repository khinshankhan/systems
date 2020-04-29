#include "pipe_networking.h"  

#ifndef FAMOUSPIPE
#define FAMOUSPIPE "imfamous"
#endif

/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int c2serv; // FIFO FD

  char buf[HANDSHAKE_BUFFER_SIZE];
  mkfifo(FAMOUSPIPE, 0644); // Create FIFO
  printf("The most famous pipe has arrived in town. \n");

  c2serv = open(FAMOUSPIPE, O_RDONLY); // Open the pipe
  read(c2serv, buf, sizeof(buf)); // Read FIFO info sent by client.c
  printf("Received a interesting message: %s\n", buf);
  remove(FAMOUSPIPE); // Turns the FIFO into an unnamed pipe

  *to_client = open(buf, O_WRONLY); // Open client file
  strcpy(buf, ACK); // Copies message over from 'ACK'
  write(*to_client, buf, sizeof(buf)); // Send message back to client

  read(c2serv, buf, sizeof(buf));
  printf("Received another interesting confirmation message: %s\n", buf);
  if (!strcmp(buf, ACK)) {
    printf("Good news everyone! You've made a new acquaintance!\n");
  }

  return c2serv;
}


/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int s2clie;
                                                                                
  char buf[HANDSHAKE_BUFFER_SIZE];
  char p_name[HANDSHAKE_BUFFER_SIZE];

  sprintf(p_name, "%d", getpid());
  strcpy(buf, p_name);
  mkfifo(p_name, 0644);
  printf("Announcing the arrival of a famous pipe: Pipe %s\n", p_name);

  *to_server = open(FAMOUSPIPE, O_WRONLY);
  if(*to_server == -1){
    printf("Server is already engaged with a client.\nPlease try again later.\nlogout\n");
    remove(p_name);
    exit(1);
  }
  printf("Reached out to the famous pipe\n");
  write(*to_server, buf, sizeof(buf));

  s2clie = open(p_name, O_RDONLY);
  read(s2clie, buf, sizeof(buf));
  printf("Received a message from the famous pipe: %s\n", buf);

  if (!strcmp(buf, ACK)) {
    printf("Hands shook!\n");
  }
  
  remove(p_name);

  write(*to_server, buf, sizeof(buf));

  return s2clie;
}
