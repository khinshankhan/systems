#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

void childwrite(int *fd, int READ, int WRITE){
  printf("child number: %d\n", getpid());
}

void childread(int *fd, int READ, int WRITE){
  printf("child number: %d\n", getpid());
}

void parentwrite(int *fd, int READ, int WRITE){
  printf("parent number: %d\n", getpid());
}

void parentread(int *fd, int READ, int WRITE){
  printf("parent number: %d\n", getpid());
}

int main(){
  //pipes
  int *fd1 = malloc(2 * sizeof *fd1);
  int *fd2 = malloc(2 * sizeof *fd2);

  pipe(fd1); //for child to write into
  pipe(fd2); //for parent to write into
  
  int READ = 0; // for using read end
  int WRITE = 1; // for using write end

  //forking to make child
  int f = fork();
  
  //error printing
  if (f < 0) {
    printf("Errno number: %d\n", errno);
    printf("Something went wrong with fork, likely memory issue\nMessage: %s\n", strerror(errno));
    exit (1);
  }
  
  //parent
  if(f){
    printf("PID number: %d\n", getpid());
    parentread(fd1, READ, WRITE);
    parentwrite(fd2, READ, WRITE);
  }
  //child
  if(!f){
    printf("PID number: %d\n", getpid());
    childwrite(fd1, READ, WRITE);
    childread(fd2, READ, WRITE);
  }

  return 0;
}
