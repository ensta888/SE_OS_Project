#include<sys/types.h>
#include<dirent.h>
#include<stdio.h>

typedef struct imageNameList{
	const char * imageName;
	struct imageNameList *next;
	//struct imageNameList *prev=NULL;
}ListImage;

char* readBankImage(const char *path);
