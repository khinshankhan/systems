#include <stdio.h>
#include <string.h>
// strcmp vs strncmp lesson

void print11(int x){
  printf("str1 compared to str1 is: %d\n", x);
}
void print12(int x){
  printf("str1 compared to str2 is: %d\n", x);
}
void print21(int x){
  printf("str2 compared to str1 is: %d\n", x);
}
void print23(int x){
  printf("str2 compared to str3 is: %d\n", x);
}



int main(){
  //Remember the compareTo from Java? Same concept with strcmp
  //takes in two strings
  //compares both strings lexicographically
  //short circuits as soon as there is an inequality
  
  //if first input is less than second, returns a number < 0
  //if first input is greater than second, returns a number > 0 
  //if both inputs are equal, returns 0
  int value;
  char str1[]= "Apple";
  char str2[]= "apple";
  char str3[] = "appLe";

  printf("Please note:\nstr1[]= \"Apple\"\nstr2[]= \"apple\"\nstr3[] = \"appLe\"\n");
  
  printf("\nstrcmp demo:\n");
  value = strcmp(str1, str2);
  print12(value);
  value = strcmp(str2, str1);
  print21(value);
  value = strcmp(str1, str1);
  print11(value);
  value = strcmp(str2, str3);
  print23(value);

  //strncmp has a similar concept, but it takes in one more input (total: 3)
  // the third is the maximum number of characters to compare up to

  printf("\nstrncmp demo:\n");
  value = strncmp(str1, str2, 5);
  print12(value);
  value = strncmp(str2, str1, 5);
  print21(value);
  value = strncmp(str1, str1, 5);
  print11(value);
  value = strncmp(str2, str3, 5);
  print23(value);
  printf("\nClincher (only up to 3 letters): ");
  value = strncmp(str2, str3, 3);
  print23(value);


  return 0;
}
