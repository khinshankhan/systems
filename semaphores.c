#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>


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
    if(atoi(argv[2]) == 0){
      printf("Invalid Type of Arguments\n");
      return 1;
    }
    else{
      printf("%d c\n", atoi(argv[2]));
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
    printf("v\n");
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
    printf("r\n");
    return 0;
  }
  
  //Flag wasnt right
  printf("Invalid Flag\n");
  return 1;
}
