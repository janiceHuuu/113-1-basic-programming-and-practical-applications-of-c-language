#include <stdlib.h>
#include <stdio.h>

int main(){
    int a;
    printf("請輸入一個整數：");
    scanf("%d",&a);
    if(a%3 == 0){
        printf("你輸入的數「是」3的倍數\n");
    }
    else{
        printf("你輸入的數「不是」3的倍數\n");
    }
    return 0;
}