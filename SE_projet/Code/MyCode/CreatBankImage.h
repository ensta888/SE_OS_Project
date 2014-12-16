#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include"targa_image.h"
#include<error.h>

typedef struct _NodeImage{
	char * path;
	char  * imageName;
	int size; //taille du fichier en kilo-octets
	int height; //height of image
	int width; // width of image
	struct _NodeImage *next;
}NodeImage;

NodeImage * createNodeImage(char * imagename,const char * path);

NodeImage * readBankImage(const char *path);

void printListImage(NodeImage * head);
