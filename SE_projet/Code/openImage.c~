//http://blog.csdn.net/lin_fs/article/details/7335573
#include"openImage.h"

//ListImage * head;

/*
void insertImageName(ListImage current,){
	
	
}*/

char* readBankImage(const char *path){
	DIR*dir=NULL;
	struct dirent * enter;
	int i=0;
	//const char *path="/home23/zhengta/semestre3/UV3.6/system_exploitation/SE_projet/images";
	if((dir=opendir(path))==NULL){
		printf("opendir failed!");
		return NULL;
	}
	else
	{
		while(enter=readdir(dir)){
			printf("filename%d=%s\n",i,enter->d_name);
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
	readBankImage("/home23/zhengta/semestre3/UV3.6/system_exploitation/SE_projet/images");
	return 1;
}
