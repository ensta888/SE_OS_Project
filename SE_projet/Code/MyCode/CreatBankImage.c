//http://blog.csdn.net/lin_fs/article/details/7335573
#include<stdio.h>
#include<sys/types.h>
#include<dirent.h>
#include"targa_image.h"
#include<error.h>

//ListImage * head;

/*
void insertImageName(ListImage current,){
	
	
}*/

typedef struct _NodeImage{
	char * path;
	char  * imageName;
	int size; //taille du fichier en kilo-octets
	int height; //height of image
	int width; // width of image
	struct _NodeImage *next;
}NodeImage;

void createNodeImage(char * imagename,const char * path){
	//ajouter le nom complet avec la repertoire
	char * filename= (char *) malloc(sizeof(char)*255);
	sprintf(filename,"%s/%s",path,imagename);

	NodeImage * img=(NodeImage *) malloc(sizeof(NodeImage));
	img->path=(char *) malloc(sizeof(char)*100);
	img->imageName=(char *) malloc(sizeof(char)*100);
	img->path=path;
	img->imageName=imagename;
	//printf ("Path is %s\n",img->path);
	

	//ouvrir l'image avec un type d'targa   la fonction est dans un autre fichier
	targa_header headImage;
	image_desc imgdesc;

	int ans;
	ans=readImage(&imgdesc,&headImage,filename);
	if (ans!=1){
		perror("read image failed!");
		exit(1);  //comment traiter les erreurs ????
	}

	img->width=headImage.width;
	img->height=headImage.height;
	int size=img->width*img->height*3/1000;
	img->size=size;
	printf ("Image Info:\n");
	printf ("-----------------------\n");
	printf ("image Name is %s\n",img->imageName);
	printf("image width is %d, height is %d\n",img->width,img->height);
	printf ("image size is %d ko\n",img->size);
	
}

char* readBankImage(const char *path){
	DIR *dir=NULL;
	struct dirent * enter;
	int i=1;
	//const char *path="/home23/zhengta/semestre3/UV3.6/system_exploitation/SE_projet/images";
	if((dir=opendir(path))==NULL){
		printf("opendir failed!");
		return NULL;
	}
	else{
		while(enter=readdir(dir)){
			char * backImageName1=".";
			char * backImageName2="..";

			if (strcmp(enter->d_name,backImageName1)==0 || strcmp(enter->d_name,backImageName2)==0){
				//printf("filename%d=%s is the same\n",i,enter->d_name);
				continue;
			}else{
//Ici a l'instant on n'a pas considere si l'image n'a pas une format targa

				createNodeImage(enter->d_name,path);
				//printf("filename%d=%s\n",i,enter->d_name);//afficher les noms des images
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
