#include "targa_image.h"

int main(){
	char * fName;
	fName=~/projet_os/SE_OS_Project/SE_projet/images/cerf.tga;
	image_desc iDesc;
	targa_header head;
	
	iDesc.pBlue=0;
	iDesc.pRed=0;
	iDesc.pGreen=0;

	iDesc.width=150;
	iDesc.height=150;

	writeImage (iDesc, head, fName);

	return 0;
}
