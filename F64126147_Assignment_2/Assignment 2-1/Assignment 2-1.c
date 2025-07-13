#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    int n;
    scanf("%d",&n);
    int score[n],my,bigger=0,smaller=0,same=0;
    for(int i=0;i<n;i++){
        scanf("%d",&score[i]);
    }
    my = score[0];
    for(int i=1;i<n;i++){
        if(score[i]>my){
            bigger++;
        }
        if(score[i]<my){
            smaller++;
        }
        if(score[i]==my){
            same++;
        }
    }
    printf("%d\n%d\n%d\n",smaller,same,bigger);
    return 0;
}