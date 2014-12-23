#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Split the string 'string' into an array argtab of strings, 
   using the space delimiter */
int str_split(char * string, char * argtab[]) {
  int i = 0;
  char seps[]=" ";
  char * token;
  char * strtosplit = strdup(string);
  token = strtok( string, seps );
  while( token != NULL )
  {
	argtab[i] = malloc(sizeof(char)*strlen(token));
	strcpy(argtab[i], token);  
	token = strtok( NULL, seps );
	i++;
  }
  argtab[i] = NULL;
  return i;
}


int startswith(char * prefix, char * str) {
  if (prefix == NULL || str == NULL) 
	return -1;
  if (strncmp(prefix, str, strlen(prefix))==0)
	return 1;
  return 0;
}
