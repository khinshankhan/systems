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

  from_client = server_handshake( &to_client );

  while (1) {
    read(from_client, buf, sizeof(buf));
    printf("Received a message: %s\n", buf);
    reverse(buf);
    write(to_client, buf, sizeof(buf));
  }

  return 0;
}
