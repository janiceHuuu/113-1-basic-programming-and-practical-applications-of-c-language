#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void star(int a);

int main(){
    int n;
    scanf("%d",&n);
    int score[n],max,sum=0,number=1;
    for(int i=0;i<n;i++){
        scanf("%d",&score[i]);
        sum += score[i];
    }
    printf("%.2f\n",(float)sum/n);

    max = score[0];
    for(int i=0;i<n;i++){
        if(score[i]>max){
            number = i+1;
            max = score[i];
        }
    }
    printf("%d\n",number);

    int a=0,b=0,c=0,d=0,e=0;
     for(int i=0;i<n;i++){
        if(score[i]>=90 && score[i]<=100){
            a++;
        }
        else if(score[i]>=80 && score[i]<=89){
            b++;
        }
        else if(score[i]>=70 && score[i]<=79){
            c++;
        }
        else if(score[i]>=60 && score[i]<=69){
            d++;
        }
        else{
            e++;
        }
     }
     printf("A:");
     star(a);
     printf("B:");
     star(b);
     printf("C:");
     star(c);
     printf("D:");
     star(d);
     printf("E:");
     star(e);
    return 0;
}

void star(int a){
    for(int i=0;i<a;i++){
        printf("*");
    }
    printf("\n");
}