#include"ReadWriteInMyWay.h"


char * delSpaceBeforeEnd(char * str){
	char * begin=str;
	int len=strlen(str);
	char * end=str+len-1;
	while(1){
		if (*(end)==' '){
			*end='\0';
			end--;

		}else break;
	}
	while(1){
		if ((*begin)==' '){
			begin++;
		}else break;
	}
	str=begin;
	
	
	return str;
}

/*
void sepArgv(char * str){
	char * begin=str;
	while(1){
		if (*(begin)!=' ')
			begin++;
		else{
			*argv=
		}
	}
}*/

char * readInMyWay(){
	char * com=(char *) malloc (sizeof(char)*MaxText);
	char * begcom=com;
	char c;
	do{

		c=getchar();
		*com=c;
		com++;
		if(c=='\n'){
			com-=1;
			*com='\0';
			com=begcom;
		}
	}while(c!='\n');
	com=delSpaceBeforeEnd(com);
	return com;
}

/*
int main(){
	readInMyWay();
	return 0;
}*/
