#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char ** parse_args( char * line ){
  char **args = calloc(6, sizeof(char *));
  int i;
  for(i = 0; line; i++){
    //printf("%s\n", strsep(&line, " "));
    args[i] = strsep(&line, " ");
  }
  return args;
}
  

int main(){
  char arg[] = "ls -a -l";
  char **args = parse_args(arg);
  execvp(args[0], args);
  return 0;
}
