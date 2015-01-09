#include"AnalyseImage.h"

int histogramme(const char * imageName,int * his,int m,int n){
	targa_header * pHead= (targa_header *) malloc(sizeof(targa_header));
	image_desc * pDesc=(image_desc *) malloc(sizeof(image_desc));	
	int ans=readImage(pDesc,pHead, imageName);

	if (ans!=1){
		perror("Read file failed!");
	}else{
		int i,j;
		int a,b;
		memset(his,0,3*32*sizeof(int));
		for (i=0;i<pDesc->width*pDesc->height;i++){
			a=*(pDesc->pBlue+i);
			(*(his+0*32+a/8))++;
			a=*(pDesc->pGreen+i);
			(*(his+1*32+a/8))++;
			a=*(pDesc->pRed+i);
			(*(his+2*32+a/8))++;
			//*(his+0*n+*(pDesc->pGreen+i))=( *(his+0*n+*(pDesc->pGreen+i)) )/8+1;
			//*(his+0*n+*(pDesc->pRed+i))=( *(his+0*n+*(pDesc->pRed+i)) )/8+1;
	/*
			his[0][*(pDesc->pRed+i)]++;
			his[1][*(pDesc->pGreen+i)]++;
			his[2][*(pDesc->pBlue+i)]++;	
	*/
		}
		for (i=0;i<3;i++){
			for (j=0;j<32;j++){
				*(his+i*32+j)=*(his+i*32+j)*500/(pDesc->width*pDesc->height);
			}
		}
		
	
	}
	return pDesc->width*pDesc->height;

}

void identifyColor(const char *imageName,int *cnt){
	targa_header * pHead= (targa_header *) malloc(sizeof(targa_header));
	image_desc * pDesc=(image_desc *) malloc(sizeof(image_desc));	
	int ans=readImage(pDesc,pHead, imageName);

	if (ans!=1){
		perror("Read file failed!");
	}else{
		int i,j;
		int count_b=0,count_g=0,count_r=0;
		
		for (i=0;i<pDesc->width*pDesc->height;i++){
			int b=*(pDesc->pBlue+i);
			int g=*(pDesc->pGreen+i);	
			int r=*(pDesc->pRed+i); 
			if (b-g>=100 && b-r>=100){
				(*cnt)++;
			}else{
				if (g-b>=100 && g-r>=100){
					(*(cnt+1))++;
				}else{
					if (r-g>=100 && r-b>=100){
						(*(cnt+2))++;
					}
				}
			}
		}
		for (i=0;i<3;i++){
			*(cnt+i)=*(cnt+i)*200/(pDesc->width*pDesc->height);
		}
	}
}


