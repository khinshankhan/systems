#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 13579

//creates a semaphore... or doesnt.
void create(char * n){
  int id = semget(KEY, 1, IPC_CREAT | IPC_EXCL | 0664);
  // if -1, it existed, if not, semaphore didnt exist
  if (id != -1){
    // create a semaphore
    int semaphore;
    sscanf(n, "%d", &semaphore);
    semctl(id, 0, SETVAL, semaphore);
    printf("semaphore created: %d\n", id);
    printf("value set: %s\n", n);
  } 
  else{
    // semaphore exists
    printf("semaphore already exists\n");
  }
}

//gets the value of the semaphore... or doesnt
void value(){
  int id = semget(KEY, 0, 0);
  //error
  if(id == -1){
    printf("error: semaphore doesnt exist or no access to it\n");
  }
  else{
    printf("semaphore value: %d\n", semctl(id, 0, GETVAL));
  }
}

//removes the semaphore... or doesnt. also, remove() is already a thing
void removes(){
  int id = semget(KEY, 0, 0);
  //error
  if(id == -1){
    printf("error: semaphore doesnt exist or no access to it\n");
  }
  else{
    printf("semaphore removed %d\n", semctl(id, 0, IPC_RMID)); 
  }
}

//actual main. it'll check provided arguments. i got lazy w/ checking if int
int main(int argc, char *argv[]){
  /*
    -c N
    Create a semaphore and set its value to N
    If the semaphore already exists, it should pint a message saying so
  */
  if(!strcmp(argv[1],"-c")){
    if(argc != 3){
      printf("Invalid number of Arguments\n");
      return 1;
    }
    else{
      create(argv[2]);
      return 0;
    }
  }

  /*
    -v
    View the current value of the semaphore
  */
  if(!strcmp(argv[1],"-v")){
    if(argc != 2){
      printf("Invalid number of Arguments\n");
      return 1;
    }
    value();
    return 0;
  }

  /*
    -r
    remove the semaphore
  */
  if(!strcmp(argv[1],"-r")){
    if(argc != 2){
      printf("Invalid number of Arguments\n");
      return 1;
    }
    removes();
    return 0;
  }
  
  //Flag wasnt right
  printf("Invalid Flag\n");
  return 1;
}
