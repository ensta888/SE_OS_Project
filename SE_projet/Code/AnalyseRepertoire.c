#include<stdio.h>
#include"CreatBankImage.h"

#define MAXSIZEOFSET 1000


void swap_int(int *a,int *b){
	int t;
	t=*a;
	*a=*b;
	*b=t;
}


void diviserRepertoire(const char * PathR){
	NodeImage* headImage=readBankImage(PathR);
	printf ("Please input the size and terminted with -1\n");
	int set[MAXSIZEOFSET];
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
					swap_int(&set[i],&set[j]);
				}
			}
		}
	}
/* test the order of set
	printf ("sort result\n");
	for (i=0;i<count;i++){
		printf ("%d ",set[i]);
	}
	printf ("\n");*/
	//sort les images
	NodeImage *p,*q;
	for (p=headImage;p!=NULL;p=p->next){
		for (q=p;q!=NULL;q=q->next){
			if (q->size<p->size){
				swapNodeImage(q,p);
			}
		}
	}
//test the order of image
	for (p=headImage;p!=NULL;p=p->next){
		printf("Image info:\n");
		printf ("Image id is %d, size is %d\n",p->id,p->size);
	}
		
}

int main(){
	diviserRepertoire(PathInMyPC);
	return 0;
}
