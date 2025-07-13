#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(){
    clock_t start = clock();
    float sum=0;

    for(int i=0;i<10000;i++){
        for(int j=0;j<10000;j++){
            sum=5.6*5.6;
        }
    }
    clock_t end = clock();
    double time = (double) (end-start)/CLOCKS_PER_SEC;

    printf("程式執行的時間：%f秒\n",time);
    return 0;
}