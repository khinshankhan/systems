#include "pipe_networking.h"
#include <signal.h>

void process(char *s);
void subserver(int from_client);

static void sighandler(int signo) {
  if (signo == SIGINT) {
    remove(WKP);
    exit(0);
  }
}

void process(char * s) {
  int i, j, temp;

  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    temp = s[i];
    s[i] = s[j];
    s[j] = temp;
  }
}

void subserver(int from_client) {
  int to_client = server_connect(from_client);
  char buffer[BUFFER_SIZE];
  while (read(from_client, buffer, sizeof(buffer))) {
    //should we print pid?
    printf("[subserver %d] received from client: %s\n", getpid(), buffer);
    process(buffer);
    write(to_client, buffer, sizeof(buffer));
  }
}

int main() {
  signal(SIGINT, sighandler);
  //the ints we've seen everywhere int the code finally have a starting point
  int from_client;
  int to_client;
  while(1){
    //looking for clients
    //should block if none are found because the method has blocking in it
    from_client = server_setup();
    //split!
    int f = fork();
    //parent removes WKP, and goes back on prowl for more clients
    if(f){
      remove(WKP);
      printf("[server] handshake: removed WKP\n");
      close(from_client);
    }
    else{
      //child plays with current client
      subserver(from_client);
    }
  }
}
