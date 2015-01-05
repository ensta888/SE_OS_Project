#include "targa_image.h"
#include<stdlib.h>

void drawHisto(char * filename){
	char * fName;
	char * Name;
	int p;
	int x;
	int y;
	image_desc iDesc;
	image_desc *pDesc=malloc(sizeof(image_desc)*1);;
	targa_header *pHead=malloc(sizeof(targa_header)*1);;

	Name="/home/tao/acdemaic_ENSTA_Bretagne/Year_2/Semestre_3/UV3.6/OS_system_explotation/SE_OS_Project/SE_projet/images/cerf.tga";
 	readImage(pDesc, pHead, Name);

	iDesc.width=350;
	iDesc.height=350;

	iDesc.pRed   = malloc(sizeof(uint8_t)*iDesc.width*iDesc.height);
	iDesc.pGreen = malloc(sizeof(uint8_t)*iDesc.width*iDesc.height);
	iDesc.pBlue  = malloc(sizeof(uint8_t)*iDesc.width*iDesc.height);

	for(p=0;p<=iDesc.width*iDesc.height;p++){
		if(p==50*350+50){
			y=1;
			while(y<256){
				if(p==(50+y)*350+50){
					*(iDesc.pBlue+p)=255;
					*(iDesc.pRed+p)=100;
					*(iDesc.pGreen+p)=250;
					y++;
				}
			}
		}else	
		if(p==100*350+50){
			
			while(p<100*350+50+256){
				*(iDesc.pBlue+p)=255;
				*(iDesc.pRed+p)=100;
				*(iDesc.pGreen+p)=250;
				p++;
		
			}
		}		
		*(iDesc.pBlue+p)=255;
		*(iDesc.pRed+p)=255;
		*(iDesc.pGreen+p)=255;
	}
	writeImage (iDesc, *pHead, fName);

}

int main(){
	fName="/home/tao/acdemaic_ENSTA_Bretagne/Year_2/Semestre_3/UV3.6/OS_system_explotation/SE_OS_Project/SE_projet/test_cerf.tga";
	drawHisto(fName);
	return 0;
}
