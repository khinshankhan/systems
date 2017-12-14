#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;
  char buf[1024];

  from_server = client_handshake( &to_server );

  while (1) {
    printf("ENTER A MESSAGE TO SEND TO ADEEB: ");
    memset(buf,0,sizeof(buf));
    if(fgets(buf, sizeof(buf), stdin) == 0) {
      printf("Nothing entered. Exiting client.\n");
      return 0;
    }

    int length = strlen(buf); 

    if (buf[length - 1] == '\n') {
      buf[length - 1] = '\0';
    }

    printf("Buffer: %s", buf);
    write(to_server, buf, sizeof(buf));
    read(from_server, buf, sizeof(buf));
    printf("\nReceived transmission: %s\n", buf);
  }

  return 0;
}
