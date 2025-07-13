#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(){
    int a,b,c;
    float test;
    scanf("%d %d %d",&a,&b,&c);
    if(b*b-4*a*c>=0){
        test = sqrt(b*b-4*a*c);
    }
    else{
        test = -1;
    }
    if(test>0){
        int x1,x2;
        x1 = (b*(-1)+test)/(2*a);
        x2 = (b*(-1)-test)/(2*a);
        if (x1>=x2){
            printf("Two different roots x1=%d, x2=%d",x1,x2);
        }
        else{
            printf("Two different roots x1=%d, x2=%d",x2,x1);
        }
    }
    else if(test==0){
        int x1;
        x1 = b*(-1)/(2*a);
        printf("Two same roots x=%d",x1);
    }
    else if(test<0){
        printf("No real root");
    }
    return 0;
}
