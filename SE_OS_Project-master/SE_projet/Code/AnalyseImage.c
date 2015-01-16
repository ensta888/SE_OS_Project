#include"AnalyseImage.h"

int max_min(int a,int b,int c,int minormax){//0 is max, 0 is min
	int max=a,min=a;
	if (max<b)max=b;
	if (max<c)max=c;
	if (min>b)min=b;
	if (min>c)min=c;
	if (minormax==0)return max;
	if (minormax==1)return min;
}

int histogramme(const char * imageName,int * his,int m,int n){
	targa_header * pHead= (targa_header *) malloc(sizeof(targa_header));
	image_desc * pDesc=(image_desc *) malloc(sizeof(image_desc));	
	int ans=readImage(pDesc,pHead, imageName);
	int nb;
	
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
		nb=pDesc->width*pDesc->height;
		for (i=0;i<3;i++){
			for (j=0;j<32;j++){
				*(his+i*32+j)=*(his+i*32+j)*500/nb;
			}
		}
	}
	freeImage(pDesc);
	return nb;

}

void identifyColor(const char *imageName,int *cnt){
	printf ("name is %s\n",imageName);
	targa_header  * pHead= (targa_header *) malloc(sizeof(targa_header));
	image_desc  * pDesc=(image_desc *) malloc(sizeof(image_desc));	
	int ans=readImage(pDesc,pHead,imageName);
	if (ans!=1){
		perror("Read file failed!");
	}else{
		int i,j;
		double hh,s,v;int h;
		int count_b=0,count_g=0,count_r=0;
		for (i=0;i<pDesc->width*pDesc->height;i++){
			double b=*(pDesc->pBlue+i)/255.0;
			double g=*(pDesc->pGreen+i)/255.0;	
			double r=*(pDesc->pRed+i)/255.0; 
			//transforme rgb to hsv 
//https://moodle.ensta-bretagne.fr/pluginfile.php/41168/mod_resource/content/1/ImageOpenCV35_Color.pdf
			v=max_min(b,g,r,0);
			
			if (v!=0){
				s=(v-max_min(b,g,r,1))/v;			
			}else {s=0;}
			
			if (v==r)
				hh=60*(g-b)/s;
			if (v==g)
				hh=120+60*(b-r)/s;
			if (v==b)
				hh=240+60*(r-g)/s;
			h=(int)(hh*60);
			h=h%361;
//the range of colors http://mkweb.bcgsc.ca/color_summarizer/?faq
			if ((0<=h && h<90) || (330<=h && h<=360))(*(cnt+2))++;//red
			if (90<=h && h<210) (*(cnt+1))++;//green
			if (210<=h && h<330) (*cnt)++;	//blue
			
		}
		
		int nb=pDesc->width*pDesc->height;
		for (i=0;i<3;i++){
			*(cnt+i)=*(cnt+i)*200/nb;
		}
	}
}


