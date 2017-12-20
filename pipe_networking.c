#include "pipe_networking.h"

/*=========================
  server_setup
  args:

  creates the WKP (upstream) and opens it, waiting for a
  connection.

  removes the WKP once a connection has been made

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_setup() {
  int up_pipe;
  char buffer[HANDSHAKE_BUFFER_SIZE];

  printf(WKP);

  int make_status = mkfifo(WKP, 0600);
  //in case pipe couldnt be made
  if(make_status == -1){
    printf("Error: WKP Creation has failed. Billy Mays is not liable.\n");
    exit(1);
  }

  //block on open, recieve mesage
  printf("[server] handshake: making wkp\n");
  up_pipe = open(WKP, O_RDONLY, 0);
  //in case pipe couldnt be accessed
  if(up_pipe == -1) {
    printf("Error: WKP Access has failed. Billy Mays is not reliable.\n");
    remove(WKP);
    exit(1);
  }
  read(up_pipe, buffer, sizeof(buffer));
  printf("[server] handshake: received [%s]\n", buffer);

  remove(WKP);
  printf("[server] handshake: removed wkp\n");
  return up_pipe;
}


/*=========================
  server_connect
  args: int from_client

  handles the subserver portion of the 3 way handshake

  returns the file descriptor for the downstream pipe.
  =========================*/
int server_connect(int from_client) {
  int dwn_pipe;
  char buffer[HANDSHAKE_BUFFER_SIZE];

  //send pp name to server
  printf("[client] handshake: connecting to wkp\n");
  dwn_pipe = open(WKP, O_WRONLY, 0);
  if(dwn_pipe == -1 ){
    printf("Error: Billy Mays isn't finding his paparazzi\n");
    //remove(from_client);
    exit(1);
  }

  //make private pipe
  sprintf(buffer, "%d", getpid() );
  int make_status = mkfifo(buffer, 0600);
  //in case pipe couldnt be made
  if(make_status == -1){
    printf("Error: Local Pipe Creation has failed. This is not part of Billy Mays' job.\n");
    exit(1);
  }

  make_status = write(dwn_pipe, buffer, sizeof(buffer));
  if(make_status == -1){
    printf("Error: Local Pipe Writing has failed. This is not part of Billy Mays' job.\n");
    exit(1);
  }

  //open and wait for connection
  dwn_pipe = open(buffer, O_RDONLY, 0);
  make_status = read(dwn_pipe, buffer, sizeof(buffer));
  if(make_status == -1){
    printf("Error: Local Pipe Reading has failed. This is not part of Billy Mays' job.\n");
    exit(1);
  }
  /*validate buffer code goes here */
  if(strncmp(buffer, ACK, sizeof(buffer)) == 0) {
    printf("[client] handshake: received [%s]\n", buffer);
  }
  else{
    printf("Error: received message \"%s\" instead of confirmation message \"%s\".\nBilly Mays' instructions were not listened to\n", buffer, ACK);
  }

  //remove pp
  remove(buffer);
  printf("[client] handshake: removed pp\n");

  //send ACK to server
  //write(*to_server, ACK, sizeof(buffer));

  return dwn_pipe;
}

/*=========================
  server_handshake
  args: int * to_client

  Performs the server side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {

  int from_client;

  char buffer[HANDSHAKE_BUFFER_SIZE];

  int make_status = mkfifo(WKP, 0600);
  //in case pipe couldnt be made
  if(make_status == -1){
    printf("Error: WKP Creation has failed. Billy Mays is not liable.\n");
    exit(1);
  }

  //block on open, recieve mesage
  printf("[server] handshake: making wkp\n");
  from_client = open(WKP, O_RDONLY, 0);
  if(from_client == -1){
    printf("Error: Local Pipe opening has failed. Billy Mays' client doesn't exist. He didn't fail at anything.\n");
    //remove(WKP);
    exit(1);
  }

  make_status = read(from_client, buffer, sizeof(buffer));
  if(make_status == -1){
    printf("Error: Local Pipe reading has failed. Billy Mays' eyesight may be declining.\n");
    //remove(WKP);
    exit(1);
  }

  printf("[server] handshake: received [%s]\n", buffer);

  remove(WKP);
  printf("[server] handshake: removed wkp\n");

  //connect to client, send message
  *to_client = open(buffer, O_WRONLY, 0);
  write(*to_client, buffer, sizeof(buffer));

  //read for client
  read(from_client, buffer, sizeof(buffer));
  printf("[server] handshake received: %s\n", buffer);

  return from_client;
}

/*=========================
  client_handshake
  args: int * to_server

  Performs the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {

  int from_server;
  char buffer[HANDSHAKE_BUFFER_SIZE];

  //send pp name to server
  printf("[client] handshake: connecting to wkp\n");
  *to_server = open(WKP, O_WRONLY, 0);
  if ( *to_server == -1 )
    exit(1);

  //make private pipe
  sprintf(buffer, "%d", getpid() );
  mkfifo(buffer, 0600);

  write(*to_server, buffer, sizeof(buffer));

  //open and wait for connection
  from_server = open(buffer, O_RDONLY, 0);
  read(from_server, buffer, sizeof(buffer));
  /*validate buffer code goes here */
  printf("[client] handshake: received [%s]\n", buffer);

  //remove pp
  remove(buffer);
  printf("[client] handshake: removed pp\n");

  //send ACK to server
  write(*to_server, ACK, sizeof(buffer));

  return from_server;
}
