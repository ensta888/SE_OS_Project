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


void diviserRepertoire(const char * PathR){
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
	printf ("Please input the size and terminted with -1\n");
	int set[MAXSIZEOFSET];
	memset(set,0,sizeof(set));
	int count=0;	
	int i,j;
	while(1){
		int size;
		scanf("%d",&size);
		if (size==-1){break;}
		else{
			set[count]=size;
			count++;
		}		
		//sort montant
		for (i=0;i<count;i++){
			for (j=i;j<count;j++){
				if (set[i]>set[j]){
					swap(&set[i],&set[j]);
				}
			}
		}
	}
	set[count]=MaxSize;
	p=headImage;
	int num[count+1];
	memset(num,0,sizeof(num));
	int ans;
	while(p!=NULL){
		ans=find(p,set,count);
		printf ("ans is %d\n",ans);
		num[ans]++;		
		p=p->next;	
	}

	for (i=0;i<=count;i++){
		printf ("In the set < %d, there are %d images\n",set[i], num[i]);
	}
	
		
}

int main(){
	diviserRepertoire(PathInMyPC);
	return 0;
}
