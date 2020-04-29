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
  //will serve as index for all loops
  int i;
  
  //populate array with get_num()
  int nums[10];
  printf("Generating random numbers:\n");
  for (i = 0; i < 10; i++){
    //debugging get_num()
    //num_printer(i, get_num());
    nums[i] = get_num();
  }
  //print out the array
  for (i = 0; i < 10; i++){
    num_printer(i, nums[i]);
  }
  
  //open, write to, and close num_file
  int fd = open("num_file", O_CREAT | O_RDWR, 0644);
  printf("\nWriting numbers to file...\n");
  write(fd, nums, sizeof(nums));
  close(fd);
  
  //reads the nums from num_file and populate check with it
  int check[10];
  fd = open("num_file", O_RDONLY, 0644);
  printf("\nReading numbers from file...\n");
  read(fd, check, sizeof(check));
  close(fd);

  //Finally, checks if both arrays have equal numbers
  printf("\nVerification that written values are the same:\n");
  for (i = 0; i < 10; i++) {
    if(nums[i] == check[i])
      num_printer(i, check[i]);
  }
  
  return 0;
}
  
 
