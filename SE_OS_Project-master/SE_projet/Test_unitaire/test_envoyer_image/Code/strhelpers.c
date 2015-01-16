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

void argStringToNb(int nb,char * argtab_class[],int *set){
	int i,j,a,sum;
	for (i=2;i<nb;i++){
		sum=0;
		//printf ("argtab is %s\n",argtab_class[i]);
		int len=strlen(argtab_class[i]);
		//printf ("len is %d\n",len);
		for (j=0;j<len;j++){
			char b=*(argtab_class[i]+j);
			//printf ("b is %c\n",b);
			a=(int) (b)-48;
			//printf ("a is %d\n");
			sum=sum*10+a;		
		}
		*(set+i-2)=sum;
		//printf ("set %d is %d\n",i-2,*(set+i-2));
	}
}

char * ToStringHis(int nbOfArgTab,char *argtab[]){
	int i;	
	char *input_final=argtab[0];
	//printf ("input final is %s\n",input_final);
	for (i=1;i<nbOfArgTab;i++){
		char * mid=input_final;
		//printf ("mid is %s\n",mid);
		sprintf(input_final,"%s<%s",mid,argtab[i]);
	}
	//printf ("input final is %s\n",input_final);
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

int calculBgr(char *str){
	int len =strlen(str);
	int count=0;
	int i;
	for (i=0;i<len;i++){
		if (str[i]=='b' || str[i]=='B'){
			count+=1;
		}else{
			if (str[i]=='g' || str[i]=='G'){
				count+=10;
			}else{
				if (str[i]=='r' || str[i]=='R'){
					count+=100;
				}
			}
		}
		
	}
	return count;
}
