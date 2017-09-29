#include <stdio.h>
#include <string.h>
// strcmp vs strncmp lesson

void print(int x){
  printf("%d\n", x);
}

int main(){
  //Remember the compareTo from Java? Same concept with strcmp
  //takes in two strings
  //short circuits as soon as there is an inequality
  
  //if first input is less than second, returns a number < 0
  //if first input is greater than second, returns a number > 0 
  //if both inputs are equal, returns 0
  int value;
  char str1[]= "Apple";
  char str2[]= "apple";
  char str3[] = "appLe";
  
  printf("strcmp demo:\n");
  value = strcmp(str1, str2);
  print(value);
  value = strcmp(str2, str1);
  print(value);
  value = strcmp(str1, str1);
  print(value);
  prinf("Clincher: ");
  value = strcmp(str2, str3);
  print(value);

  //strncmp has a similar concept, but it takes in one more input (total: 3)
  // the third is the maximum number of characters to compare up to

  printf("strncmp demo:\n");
  value = strncmp(str1, str2, 5);
  print(value);
  value = strncmp(str2, str1, 5);
  print(value);
  value = strncmp(str1, str1, 5);
  print(value);
  value = strncmp(str2, str3, 5);
  print(value);
  value = strncmp(str2, str3, 3);
  print(value);


  return 0;
}
