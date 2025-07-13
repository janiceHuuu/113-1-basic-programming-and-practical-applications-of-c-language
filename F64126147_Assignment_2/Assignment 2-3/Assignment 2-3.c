#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
bool prime(int a);

int main(){
    int n;
    scanf("%d",&n);
    printf("%d\n",prime(n));
    return 0;
}

bool prime(int a){
    int sum=0;
    for(int i=2;i<a;i++){
        if(a%i == 0){
            sum++;
        }
    }
    if(sum>0){
        return false;
    }
    else if(a==0){
        return false;
    }
    else if(a==1){
        return false;
    }
    else{
        return true;
    }
}