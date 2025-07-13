#include <stdlib.h>
#include <stdio.h>
void arr(int *,int);

int main(){
    int score[] = {65,73,45,92,79,52};
    int size = sizeof(score)/sizeof(score[1]);

    printf("排序前成績：");
    for(int i=0;i<size;i++){
        printf("%d ",score[i]);
    }
    printf("\n排序後成績：");
    arr(score,size);
    for(int i=0;i<size;i++){
        printf("%d ",score[i]);
    }
    printf("\n");
    return 0;
}

void arr(int *s,int n){
    for(int r=0;r<n-1;r++){
        for(int k=0;k<n-r-1;k++){
            if(s[k]>s[k+1]){
                int b=s[k+1];
                s[k+1]=s[k];
                s[k]=b;
            }
        }
    }
}