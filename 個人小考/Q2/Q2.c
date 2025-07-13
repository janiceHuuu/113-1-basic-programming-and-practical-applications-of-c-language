#include <stdio.h>
#include <stdlib.h>

int main(){
    int work,level;
    int a=0;
    while (a==0){
        scanf("%d %d",&work,&level);
        int sum=0;
        if (work==0){
            printf("0");
            continue;
        }
        else if (work !=0 && work !=2){
            if (level >=10 && level<30){
                sum=sum+1;
            }
            if (level >=30 && level<70){
                sum=sum+1+1;
            }
            if (level >=70 && level<120){
                sum=sum+1+1+1;
            }
            if (level >=120){
                sum=sum+3+1+1+1;
            }
            sum=sum+(level-10)*3;  
        }
        else if (work==2){
            if (level >=8 && level<30){
                sum=sum+1;
            }
            if (level >=30 && level<70){
                sum=sum+1+1;
            }
            if (level >=70 && level<120){
                sum=sum+1+1+1;
            }
            if (level >=120){
                sum=sum+3+1+1+1;
            }
            sum=sum+(level-8)*3;
        }   
        printf("%d",sum);
        continue;
    }
    return 0;
}
