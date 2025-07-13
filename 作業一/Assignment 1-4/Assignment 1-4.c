#include <stdlib.h>
#include <stdio.h>

int main(){
    float time,hurt=0;
    scanf("%f",&time);
    if(time>=0 && time<=1000){
        if(time<=120){
            hurt = time*2.1;
        }
        else if(330>=time && time>120){
            hurt = 120*2.1+(time-120)*3.02;
        }
        else if(500>=time && time>330){
            hurt = 120*2.1+330*3.02+(time-330)*4.39;
        }
        else if(700>=time && time>500){
            hurt = 120*2.1+330*3.02+500*4.39+(time-500)*4.97;
        }
        else if(time>700){
            hurt = 120*2.1+330*3.02+700*4.39+(time-700)*5.63;
        }
        printf("%.2f",hurt);
    }
    else if(time>1000 && time<10000){
        printf("RIP!!");
    }
    else if(time<0 || time>10000){
        printf("Get out!!");
    }
    return 0;
}