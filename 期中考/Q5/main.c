#include <stdio.h>
#include <stdlib.h>

int main(){
    int x,y,max=0,people,under=0;
    scanf("%d %d\n",&x,&y);
    int score[x][y];
    for(int i=0;i<x;i++){
        for(int j=0;j<y;j++){
            scanf("%d",&score[i][j]);
        }
    }

    for(int i=0;i<x;i++){
        int sum=0;
        for(int j=0;j<y;j++){
            //printf("score[%d][%d]=%d\n",i,j,score[i][j]);
            sum += score[i][j];
        }

        if(sum<60*y){
            under++;
        }

        if(sum>max){
            max=sum;
            people=i+1;
        }
        printf("%.2f ",(float)sum/y);
    }

    printf("\n");
    for(int i=0;i<y;i++){
        int sum=0;
        for(int j=0;j<x;j++){
            sum+=score[j][i];
        }
        printf("%.2f ",(float)sum/x);
    }
    printf("\n");
    printf("%d\n",people);
    printf("%d\n",under);
    return 0;
}