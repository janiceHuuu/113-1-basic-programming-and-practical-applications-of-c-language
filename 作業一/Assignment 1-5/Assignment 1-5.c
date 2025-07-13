#include <stdlib.h>
#include <stdio.h>

int main(){
    int n,s;
    scanf("%d\n%d",&n,&s);
    if(n<=0 || n>45){
        printf("Error");
    }
    else{
        for(int i=1;i<=n;i++){
            printf("%d: %d\n",i,s+i);
        }
    }
    return 0;
}