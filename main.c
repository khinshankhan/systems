#include <stdio.h>
#include <string.h>

#include "stringy.h"

int main() {

  char s1[] = "hello";
  char s2[] = "testing";
  char c = 's';
  
  printf("s1: %s\n", s1);
  printf("s2: %s\n", s2);
  printf("c: %c\n", c);
  printf("\n");
  
  printf("Testing strlen( s1 ):\n");
  printf("[standard]: %lu\n", strlen(s1));
  printf("[mine]: %d\n", strlenA(s1));
  printf("\n");
  
  printf("Testing strncat( s1, s2, 2 ):\n");
  printf("[standard]: %s\n", strncat(s1, s2, 2));
  s1[5] = 0;
  printf("[mine]: %s\n", strncatA(s1, s2, 2));
  printf("\n");
  
  printf("Testing strcat( s1, s2 ):\n");
  s1[5] = 0;
  printf("[standard]: %s\n", strcat(s1, s2));
  s1[5] = 0;
  printf("[mine]: %s\n", strcatA(s1, s2));
  printf("\n");
  
  s1[5] = 0;
  
  printf("Testing strchr( s, c ):\n");
  printf("[standard]: %p\n", strchr(s2, c));
  printf("[mine]: %p\n", strchrA(s2, c));
  printf("\n");

  char u[] = "spicy";
  char v[] = "12345";
  char w[] = "hello";
  char x[] = "apple";
  char y[] = "hello";
  char z[] = "apple";
  
  printf("Testing strcpy( dest, source ):\n");
  printf("[standard]: %s\n", strcpy(w, x));
  printf("[mine]: %s\n", strcpyA(y, z));
  printf("[standard]: %s\n", strcpy(w, v));
  printf("[mine]: %s\n", strcpyA(y, v));
  printf("\n");

  printf("Testing strncpy( dest, source ):\n");
  printf("[standard]: %s\n", strncpy(w, u, 3));
  printf("[mine]: %s\n", strncpyA(y, u, 3));
  printf("[standard]: %s\n", strncpy(u, w, 2));
  printf("[mine]: %s\n", strncpyA(u, w, 2));
  printf("\n");

  printf("Testing strcmp( s1, s2 ):\n");
  printf("[standard]: %d\n", strcmpA(s1, s2));
  printf("[mine]: %d\n", strcmp(s1, s2));
  printf("[standard]: %d\n", strcmpA(s2, s1));
  printf("[mine]: %d\n", strcmp(s2, s1));
  printf("\n");
  printf("Done");

  return 0;

}
