#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void sighandler(int signo){
  if(signo == SIGINT){
    printf("Oh man. It was SIGINT.\n");
    exit(1);
  }
  if(signo == SIGUSR1){
    printf("Parent process #: %d\n", getppid());
  }
}

void forever(){
  while(1){
    printf("Process #: %d\n", getpid());
    sleep(1);
  }
}

int main(){
  signal(SIGINT, sighandler);
  signal(SIGUSR1, sighandler);
  forever();

  return 0;
}
