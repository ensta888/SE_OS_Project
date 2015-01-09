#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include"targa_image.h"
#include<error.h>

#ifndef PathInMyPC 
#define PathInMyPC "/home/tao/acdemaic_ENSTA_Bretagne/Year_2/Semestre_3/UV3.6/OS_system_explotation/SE_OS_Project/SE_projet/images"
#endif

#ifndef PathInSchoolPc 
#define PathInSchoolPc "/home23/zhengta/semestre3/UV3.6/system_exploitation/SE_projet/images"
#endif

#ifndef _NodeImage
#define _NodeImage
typedef struct NodeImage_{
	int id;
	char * path;
	char  * imageName;
	int size; //taille du fichier en kilo-octets
	int height; //height of image
	int width; // width of image
	struct NodeImage_ *next;
}NodeImage;
#endif

void UpdateList(char *imagename, char * path,NodeImage *head);

NodeImage * createNodeImage(char * imagename,const char * path);

NodeImage * readBankImage(const char *path);

void printListImage(NodeImage * head);
