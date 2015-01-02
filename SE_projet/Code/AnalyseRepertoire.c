
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
	//printf ("maxi is %d\n",maxi);
	
	
		
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
