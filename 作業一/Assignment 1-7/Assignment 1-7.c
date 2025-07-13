#include <stdlib.h>
#include <stdio.h>

int main(){
    int X;
    scanf("%d",&X);
    for(int r=X;r>0;r--){
        for(int p=X-r;p>0;p--){
            printf(" ");
        }
        for(int k=r*2-1;k>0;k--){
            printf("*");
        }
        printf("\n");
    }
    for(int r=1;r<X;r++){
        for(int p=r;p<X-1;p++){
            printf(" ");
        }
        for(int k=2*(r+1)-1;k>0;k--){
            printf("*");
        }
        printf("\n");
    }
    return 0;
}