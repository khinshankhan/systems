#include <string.h>
#include "stringy.h"

int strlenA( char *s ) {
  int i = 0;
  while (s[i]) {
    i++;
  }
  return i;
}

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

int strcmpA( char *s1, char *s2 ) {
  int len = (strlenA(s1) > strlenA(s2)) ? strlenA(s1): strlenA(s2); 
  int val = 0;
  int i;
  for(i = 0; i < len; i++){
    i = (int)s1[i] -(int) s2[i];
    if(i != 0)
      break;
  }
  
  return i;
  
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
