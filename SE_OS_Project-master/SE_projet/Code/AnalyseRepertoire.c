#include"AnalyseRepertoire.h"

void swap(int *a,int *b){
	int t;
	t=*a;
	*a=*b;
	*b=t;
}

int  find(NodeImage * p, int * set,int count){
	int i;	
	for (i=0;i<count;i++){
		if (set[i] > p->size){
			return i;
		}
	}
	return count;
}

void divisercolor(const char * PathR,int *num){
	int i;
	NodeImage* headImage=readBankImage(PathR);
	//printf ("headImage is %s\n",headImage->imageName);
	NodeImage* p=headImage;
	for (i=0;i<3;i++){
		*(num+i)=0;
		//printf ("num is %d\n",*(num+i));
	}
	int *col=(int *)malloc(sizeof(int)*3);
	while(p!=NULL){
		char * imagename=(char *)malloc(sizeof(char)*100);
		sprintf(imagename,"%s/%s",p->path,p->imageName);
		int cnt[3];
		memset(cnt,0,sizeof(cnt));
		identifyColor(imagename,cnt);
		int max=0;
		int indice=-1;
		for (i=0;i<3;i++){
			if (max<cnt[i]){
				max=cnt[i];
				indice=i;			
			}
		}
		//printf ("max is %d\n",max);
		(*(num+indice))++;
		p=p->next;
	}
}

void diviserRepertoire(const char * PathR,int * set,int * num,int nbset){
	NodeImage* headImage=readBankImage(PathR);
	NodeImage* p=headImage;
	int MinSize=MAXSIZE;
	int MaxSize=MINSIZE;
	
	while(p!=NULL){
		printf ("p->size is %d\n",p->size);
		MaxSize < p->size ? MaxSize=p->size : MaxSize ;
		MinSize > p->size ? MinSize=p->size : MinSize ;
		p=p->next;
	}
	printf ("The Maximum size is %d, and the minimum size is %d\n",MaxSize,MinSize);
	int count=nbset;	
	int i,j,maxi=0;
	for(i=0;i<nbset;i++){
		*(set+i) > maxi ? maxi=*(set+i) : maxi;
	}
	//sort montant
	for (i=0;i<count;i++){
		for (j=i;j<count;j++){
			if (*(set+i)>*(set+j)){
				swap(set+i,set+j);
			}
		}
	}
	if (*(set+nbset-1)<MaxSize){
		*(set+nbset)=MaxSize;
	}else{
		*(set+nbset)=MAXSIZE;
	}
	p=headImage;
	
	for (i=0;i<nbset+1;i++){
		*(num+i)=0;
	}
	int ans;
	while(p!=NULL){
		ans=find(p,set,count);
		//printf ("ans is %d\n",ans);
		*(num+ans)+=1;		
		p=p->next;	
	}
}

void afficherSizeDivise(int count,int *set,int *num){
	int i;
	for (i=0;i<count;i++){
		if(i==0)
			printf ("In the set < %d, there are %d images\n",*(set+i), *(num+i));
		else{
			
			printf ("In the %d < set < %d, there are %d images\n",*(set+i-1),*(set+i), *(num+i));
			
		}
	}
}

/*

int main(){
	diviserRepertoire(PathInMyPC);
	return 0;
}*/
