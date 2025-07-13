#include <stdio.h>
#include <stdlib.h>

int main(){
    int r,m,n,b=0;
    scanf("%d %d %d",&r,&m,&n);
    int a = r/m;
    //printf("a= %d\n",a);
    if(a ==0 ){
        printf("Bumbler government is not a neccesary evil.");
    }
    else{
        for(int i=0;i<=a;i++){
            //printf("%d\n",i);
            if(i == 0){
                printf("S");
            }
            else if(b==0 || b%n != 0){
                printf("T");
                b++;
            } 
            else if(b%n == 0){
                printf("X");
                b=0;
            }
                  
        }
    }
    return 0;
}