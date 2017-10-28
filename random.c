#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//return a random int from the random file
int get_num(){
  //can skip mode if using flags and default mask is okay
  int fd = open("/dev/random", O_RDONLY);
  if(fd == -1){
    printf("/dev/random not found, check os configs?");
    exit(0);
  }
  int temp;
  read(fd, &temp, sizeof(temp));
  close(fd);
  return temp;
}
  
void num_printer(int index, int num){
  printf("random %d: %d\n", index, num);
  return;
}
int main(){
  int i;
  int nums[10];
  printf("Generating random numbers:\n");
  for (i = 0; i < 10; i++){
    //debugging get_num()
    //num_printer(i, get_num());
    nums[i] = get_num();
  }
  for (i = 0; i < 10; i++){
    num_printer(i, nums[i]);
  }
  //NEEDS A MODE, UNSURE WHAT IT IS YET
  //int fd = open("num_file", O_CREAT | O_RDWR, );

  return 0;
}
  
 
