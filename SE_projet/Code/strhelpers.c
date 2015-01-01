#include"strhelpers.h"

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

char * ToStringHis(int nbOfArgTab,char *argtab[]){
	int i;	
	char *input_final=argtab[0];
	printf ("input final is %s\n",input_final);
	for (i=1;i<nbOfArgTab;i++){
		char * mid=input_final;
		printf ("mid is %s\n",mid);
		sprintf(input_final,"%s<%s",mid,argtab[i]);
	}
	printf ("input final is %s\n",input_final);
	return input_final;
}

char * convertirString(char *str){
	int i;	
	for (i=0;i<strlen(str);i++){
		if (*(str+i)=='<'){
			*(str+i)=' ';
		}
	}
	return str;
}
