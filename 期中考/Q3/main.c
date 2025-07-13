#include <stdlib.h>
#include <stdio.h>

int main(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        int a,b=0;
        scanf("%d",&a);
        for(int j=a-2;j>0;j--){
            if(j>1){
                for(int k=j+1;k>0;k--){
                    printf(" ");
                    
                }
                for(int r=1+2*b;r>0;r--){
                    printf("*");
                }
            }
            if(j==1){
                for(int l=2*a-1;l>0;l--){
                    printf("*");
                }
            }
            b++;
            printf("\n");
        }

        printf(" ");
        for(int j=0;j<a+a-3;j++){
            printf("*");
        }
        printf("\n");

        for(int j=a-2;j>0;j--){
            if(j!=a-2){
                for(int k=a-j;k>0;k--){
                    printf(" ");
                }
                for(int v=j*2-1;v>0;v--){
                    printf("*");
                }
            }
            else{
                for(int l=2*a-1;l>0;l--){
                    printf("*");
                }
            }
            printf("\n");
        }
        printf("\n");
        
    }
}