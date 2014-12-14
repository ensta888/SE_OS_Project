//http://blog.csdn.net/lin_fs/article/details/7335573
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include"targa_image.h"

//ListImage * head;

/*
void insertImageName(ListImage current,){
	
	
}*/

typedef struct _NodeImage{
	char  imageName[100];
	int size; //taille du fichier en kilo-octets
	int height; //height of image
	int width; // width of image
	struct _NodeImage *next;
}NodeImage;

NodeImage createNodeImage(char * imagename){
	NodeImage * img;
	*(img->imageName)=*(imagename);
	//ouvrir l'image avec un type d'targa   la fonction est dans un autre fichier
	targa_header * headImage;
	image_desc * imgdesc;
	readImage(headImage,imgdesc,imagename);
	printf("[mem_targa] Header : %u %u %u %u %u\n", headImage->idlength, headImage->colourmaptype, headImage->datatypecode, headImage->width, headImage->height);
}

char* readBankImage(const char *path){
	DIR *dir=NULL;
	struct dirent * enter;
	int i=0;
	//const char *path="/home23/zhengta/semestre3/UV3.6/system_exploitation/SE_projet/images";
	if((dir=opendir(path))==NULL){
		printf("opendir failed!");
		return NULL;
	}
	else{
		while(enter=readdir(dir)){
			char * backImageName1=".";
			char * backImageName2="..";
			if (strcmp(enter->d_name,backImageName1)==1 || strcmp(enter->d_name,backImageName2)==1){
				continue;
			}else{
//Ici a l'instant on n'a pas considere si l'image n'a pas une format targa
				createNodeImage(enter->d_name);
				printf("filename%d=%s\n",i,enter->d_name);//afficher les noms des images
			}
			/*
			if (){

			}
			myListImage.imageName=enter->d_name;
			myListImage.
*/
			i++;
		}
		closedir(dir);
	}
	return 0;
}

int main(){
	const char * PathInMyPC="/home/tao/acdemaic_ENSTA_Bretagne/Year_2/Semestre 3/UV3.6/OS_system_explotation/SE_OS_Project/SE_projet/images";
	const char * PathInSchoolPc="/home23/zhengta/semestre3/UV3.6/system_exploitation/SE_projet/images";
	readBankImage(PathInMyPC);
	return 1;
}
