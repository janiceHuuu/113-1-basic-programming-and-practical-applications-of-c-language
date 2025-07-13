#include <stdlib.h>
#include <stdio.h>
int Fibonacci(int a);

int main(){
    int n;
    scanf("%d",&n);
    printf("%d\n",Fibonacci(n));

    return 0;
}

int Fibonacci(int a){
    if(a==1){
        return 1;
    }
    else if(a == 2){
        return 1;
    }
    else{
        return Fibonacci(a-1)+Fibonacci(a-2);
    }
    
}