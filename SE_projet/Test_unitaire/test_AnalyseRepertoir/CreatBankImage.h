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

//const char * PathInMyPC="/home/tao/acdemaic_ENSTA_Bretagne/Year_2/Semestre 3/UV3.6/OS_system_explotation/SE_OS_Project/SE_projet/images";
//const char * PathInSchoolPc="/home23/zhengta/semestre3/UV3.6/system_exploitation/SE_projet/images";

typedef struct _NodeImage{
	int id;
	char * path;
	char  * imageName;
	int size; //taille du fichier en kilo-octets
	int height; //height of image
	int width; // width of image
	struct _NodeImage *next;
}NodeImage;

NodeImage * createNodeImage(char * imagename,const char * path,int i);

NodeImage * readBankImage(const char *path);

void printListImage(NodeImage * head);
