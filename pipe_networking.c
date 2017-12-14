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
  char buf[HANDSHAKE_BUFFER_SIZE];
  mkfifo(FAMOUSPIPE, 0644);
  printf("The most famous pipe has arrived in town. \n");

  int c2serv = open(FAMOUSPIPE, O_RDONLY);
  read(c2serv, buf, sizeof(buf));
  printf("Received a interesting message: %s\n", buf);
  remove(FAMOUSPIPE);

  *to_client = open(buf, O_WRONLY);
  strncpy(buf, ACK, strlen(ACK));
  write(*to_client, buf, sizeof(buf));

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
  char buf[HANDSHAKE_BUFFER_SIZE];
  char p_name[HANDSHAKE_BUFFER_SIZE];

  sprintf(p_name, "%d", getpid());
  strncpy(buf, p_name, sizeof(p_name));
  mkfifo(p_name, 0644);
  printf("Announcing the arrival of a famous pipe: Pipe %s\n", p_name);

  *to_server = open(FAMOUSPIPE, O_WRONLY);
  printf("Reached out to the famous pipe\n");
  write(*to_server, buf, sizeof(buf));

  int s2clie = open(p_name, O_RDONLY);
  read(s2clie, buf, sizeof(buf));
  printf("Received a message from the famous pipe: %s\n", buf);

  if (!strcmp(buf, ACK)) {
    printf("Hands shook!\n");
  }
  
  remove(p_name);

  return s2clie;
}
