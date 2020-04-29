#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>

static void sighandler(int signo){
  if(signo == SIGINT){
    char msg[256];
    time_t mytime;
    mytime = time(NULL);
    
    sprintf(msg, "\nOh man. It was SIGINT.\n%s\n", ctime(&mytime));
    printf("%s", msg);
    FILE * msgs = fopen("messages", "a");
    fprintf(msgs, "%s", msg);
    fclose(msgs);
   
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
