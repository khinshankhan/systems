#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  char buf[1024];

  from_server = client_handshake( &to_server );

  while (1) {
    printf("ENTER A MESSAGE TO SEND TO ADEEB: \n");
    if (fgets(buf, sizeof(buf), stdin) == 0) {
      printf("End Transmission\n");
      return 0;
    }
    *strchr(buf, '\n') = 0;
    write(to_server, buf, sizeof(buf));
    read(from_server, buf, sizeof(buf));
    printf("Received transmission: %s\n", buf);
  }

  return 0;
}
