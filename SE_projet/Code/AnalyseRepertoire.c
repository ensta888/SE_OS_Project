#include<stdio.h>
#include<string.h>
#include"CreatBankImage.h"

#define MAXSIZEOFSET 1000
#define MINSIZE -1
#define MAXSIZE 100000000

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


void diviserRepertoire(const char * PathR,int * set,int nbset){
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
	
	*(set+nbset)=MaxSize;
	p=headImage;
	int num[nbset+1];
	memset(num,0,sizeof(num));
	int ans;
	while(p!=NULL){
		ans=find(p,set,count);
		//printf ("ans is %d\n",ans);
		num[ans]++;		
		p=p->next;	
	}
	//printf ("maxi is %d\n",maxi);
	for (i=0;i<=count;i++){
		if(i==0)
			printf ("In the set < %d, there are %d images\n",*(set+i), num[i]);
		else{
			if (i!=count)
				printf ("In the %d < set < %d, there are %d images\n",*(set+i-1),*(set+i), num[i]);
			else{
				set[i]>maxi?set[i]=set[i]:maxi;
				printf ("In the %d < set < %d, there are %d images\n",*(set+i-1),*(set+i), num[i]);
			}
		}
	}
	
		
}

/*

int main(){
	diviserRepertoire(PathInMyPC);
	return 0;
}*/
