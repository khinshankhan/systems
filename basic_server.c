#include "pipe_networking.h"

#ifndef FAMOUSPIPE
#define FAMOUSPIPE "imfamous"
#endif

static void sighandler(int signo){
  //user wants to exit
  if (signo == SIGINT){
    printf("\nlogout\n");
    remove(FAMOUSPIPE);
    exit(0);
  }
}

void reverse(char *string) {
  int i, j, temp;

  for (i = 0, j = strlen(string) - 1; i < j; i++, j--) {
    temp = string[i];
    string[i] = string[j];
    string[j] = temp;
  }
}

int main() {

  int to_client;
  int from_client;

  char buf[1024];
  int status;

  //loop allows for other clients to connect later
  while(1){
    int f = fork();
    if(f){
      wait(&status);
      signal(SIGINT, sighandler);
      printf("\n\n\n");
    }
    else{
      from_client = server_handshake( &to_client );

      while (1) {
	read(from_client, buf, sizeof(buf));
	printf("Received a message: %s\n", buf);
	reverse(buf);
	write(to_client, buf, sizeof(buf));
      }
    }
  }

  return 0;
}
