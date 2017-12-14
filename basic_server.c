#include "pipe_networking.h"


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
