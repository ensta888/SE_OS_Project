#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int func(int *array, int m, int n) {
    int i,j;
    for(i=0;i<m;i++) {
        for(j=0;j<n;j++)
            printf("\t%d", *(array +i*n +j));
        printf("\n");
    }
    return 0;
}

int main(int argc,char** argv) {
    int m=3,n=3,i;
    int array[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    func(*array,m,n);
    return 0;
}
