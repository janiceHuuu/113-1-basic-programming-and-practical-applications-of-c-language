#include <stdlib.h>
#include <stdio.h>

int main(){
    int n,k;
    scanf("%d %d\n",&n,&k);
    int number[n],find[k];
    for(int i=0;i<n;i++){
        scanf("%d",&number[i]);
    }
    for(int i=0;i<k;i++){
        scanf("%d",&find[i]);
    }

    /*for(int i=0;i<n;i++){
        for(int j=0;j<n-i;j++){
            if(number[j]>number[j+1]){
                int temp = number[j];
                number[j]=number[j+1];
                number[j+1]=temp;
            }
        }
    }
    printf("number=");
    for(int i=0;i<n;i++){
        printf("%d",number[i]);
    }
    printf("\n");*/

    for(int i=0;i<k;i++){
        int s = find[i];
        int Isfound=0,min,max,c,mid;
        min=0;
        max=n;
        c=1;
        while(min<=max)
        {
            mid=(min+max)/2;
            
            if ( number[mid]==s)  //號碼相符
            {
            Isfound=1;
            c++;
            break;
            }
            c++;  //計算比對次數
            if (number[mid]>s)  //如果中間值大於輸入值
                max=mid-1;    //使用較小的一半區域繼續比對
            else             //如果中間值不大於輸入值
                min=mid+1;    //使用較大的一半區域繼續比對
        }

        if (Isfound==1)
            printf("%d\n",mid+1);
        else
            printf("0\n");
    }

    return 0;
}