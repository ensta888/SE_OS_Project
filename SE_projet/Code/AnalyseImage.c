#include"AnalyseImage.h"

void histogramme(const char * imageName,int * his,int m,int n){
	targa_header * pHead= (targa_header *) malloc(sizeof(targa_header));
	image_desc * pDesc=(image_desc *) malloc(sizeof(image_desc));	
	if (readImage(pDesc,pHead, imageName)!=1){
		perror("Read file failed!");
	}else{
		int i,j;
		int a,b;
		memset(his,0,3*256*sizeof(int));
		for (i=0;i<pDesc->width*pDesc->height;i++){
			(*(his+0*n+*(pDesc->pRed+i)))++;
			(*(his+1*n+*(pDesc->pRed+i)))++;
			(*(his+2*n+*(pDesc->pRed+i)))++;
	/*
			his[0][*(pDesc->pRed+i)]++;
			his[1][*(pDesc->pGreen+i)]++;
			his[2][*(pDesc->pBlue+i)]++;	
	*/
		}
		
	
	}

}


