#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

void childwrite(int *fd, int READ, int WRITE, int val){
  close(fd[READ]);
  printf("[child] doing quick maths (x + 2 -1): x = %d\n", val);
  int num = val + 2 -1;
  printf("[child] sending: %d\n", num);
  write(fd[WRITE], &num, sizeof(num));
  close(fd[WRITE]);
  return;
}

void childread(int *fd, int *fd2, int READ, int WRITE){
  close(fd[WRITE]);
  int val;
  read(fd[READ], &val, sizeof(val));
  printf("[child] received: %d\n", val);
  childwrite(fd2, READ, WRITE, val);
  close(fd[READ]);
  return;
}

void parentwrite(int *fd, int READ, int WRITE){
  close(fd[READ]);
  int num = 2;
  printf("[parent] sending: %d\n", num);
  write(fd[WRITE], &num, sizeof(num));
  close(fd[WRITE]);
  return;
}

void parentread(int *fd, int READ, int WRITE){
  close(fd[WRITE]);
  int val;
  read(fd[READ], &val, sizeof(val));
  printf("[parent] received: %d\n", val);
  close(fd[READ]);
  return;
}

int main(){
  //pipes
  int paren[2];
  int child[2];

  pipe(paren); //for paren to write into
  pipe(child); //for child to write into
  
  int READ = 0; // for using read end
  int WRITE = 1; // for using write end

  int status;
  //forking to make child
  int f = fork();
  
  //error printing
  if (f < 0) {
    printf("Errno number: %d\n", errno);
    printf("Something went wrong with fork, likely memory issue\nMessage: %s\n", strerror(errno));
    exit (1);
  }
  if(f){
    parentwrite(paren, READ, WRITE);
    wait(&status);
    parentread(child, READ, WRITE);
  }

  if(!f){
    childread(paren, child, READ, WRITE);
  }
  
  return 0;
}
