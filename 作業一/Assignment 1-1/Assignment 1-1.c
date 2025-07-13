#include <stdio.h>
#include <stdlib.h>

int main(){
    float up, down, height, area;
    printf("請輸入梯形的上底（公分）：");
    scanf("%f",&up);
    printf("請輸入梯形的下底（公分）：");
    scanf("%f",&down);
    printf("請輸入梯形的高（公分）：");
    scanf("%f",&height);
    area = (up+down)*height/2;
    printf("梯形的面積：%f 平方公分",area);
    
    return 0;
}
