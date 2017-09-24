#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
  //first and second arrays
  int first[10];
  int second[10];
  
  srand(time(NULL)); //initiate random
  int i, j; //counters
  
  //populate first
  for(i = 0; i < 9; i++)
    first[i] = rand();
  first[9] = 0;

  //print first
  printf("The original array: \n");
  for(i = 0; i < 10; i++)
    printf("arr[%d]: %d\n", i, first[i]);

  //populate second
  for(i = 0, j = 9; i < 10; i++, j--)
    *(second + i) = *(&first[j]); //* and & to dereference and obtain val
  
  //print second
  printf("The second array: \n");
  for(i = 0; i < 10; i++)
    printf("arr2[%d]: %d\n", i, second[i]);
  /*
  //DEBGUG
  printf("DEBUGGING: \n");
  for(i = 0, j = 9; i < 10; i++, j--)
    printf("RESULT: %s\n", (first[i] == second[j]) ? "TRUE": "FALSE" );
  */
  return 0;
}
