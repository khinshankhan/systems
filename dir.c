#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void reading(char * filename){
  //attempt to open dir
  DIR * pointer; 
  pointer = opendir(".");
  // in case of failure
  if (pointer == NULL){
    printf ("Can't open directory here.\n");
    return;
  }
  //set up to be iterated through
  struct dirent * point;
  point = readdir(pointer);
  printf("The directories:\n");
  //because it's a pointer, it messes if not compared to
  while (point != NULL){
    //it's a dir if...
    if (point -> d_type == DT_DIR) {
      printf("\t\t%s\n", point -> d_name);
      
      //recursion isn't working out nicely..
      /*
	if((strcmp(point -> d_name, ".") != 0) && (strcmp(point -> d_name, "..") != 0)){
	char next[256];
	printf("\t\t%s\n", point -> d_name);
	sprintf(next, "%s/.",point -> d_name);
	reading(next);
	}
      */
      
    }
    point = readdir(pointer);
  }
  //closes it when done
  closedir(pointer);
  
  //variables for stats
  int size = 0;
  struct stat sb;
  
  //reopen for files this time
  //same logic as before...

  //reuse, reduce, recycle
  pointer = opendir(".");
  if (pointer == NULL){
    printf ("Can't open directory here.\n");
    return;
  }

  //reuse, reduce, recycle
  point = readdir(pointer);
  
  printf("The files:\n");
  while (point != NULL) {
    //only this changed because we want file instead of dir
    if (point -> d_type == DT_REG) {
      //add this to nicely add the file size each time
      stat(point -> d_name, &sb);
      size += sb.st_size;
      printf("\t\t%s\n", point -> d_name);
    }
    point = readdir(pointer);
  }
  closedir(pointer);
  
  printf("Total size of regular files is: %d\n", size);
    
  return;
}

int main(){
  reading(".");
  return 0;
}
