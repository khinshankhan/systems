#include <string.h>

#include "stringy.h"

int strlenA( char *s ) {
  int i = 0;
  while (s[i]) {
    i++;
  }
  return i;
}
//NEED TO TEST
char * strcpyA( char *dest, char *source ){
  return strncpyA(dest, source, strlenA(source));
}
char * strncpyA( char *dest, char *source, int n){
  int i = 0;
  for(i = 0; i < n && source[i] != 0; i++)
    *(dest + i) = source[i];
  return dest;
}

char * strcatA( char *dest, char *source ) {
  return strncatA( dest, source, strlen(source) );
}

char * strncatA( char *dest, char *source, int n) {
  int dest_len = strlen(dest);
  int i;
  
  for (i = 0; i < n && source[i] != 0; i++) {
    dest[dest_len+i] = source[i];
  }
  dest[dest_len+i] = 0;

  return dest;
}

//NEED TO DO
int strcmp( char *s1, char *s2 ) {
  int val=0;
}

char * strchrA( char *s, char c ) {
  int str_len = strlen(s);
  int i;
  
  for (i = 0; i < str_len; i++) {
    if (s[i] == c) {
      return s+i;
    }
  }

  return 0;
}
