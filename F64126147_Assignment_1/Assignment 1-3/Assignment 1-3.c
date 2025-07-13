#include <stdio.h>
#include <stdlib.h>

int main(){
    printf("月份\t預計花費  實際花費\t結餘\n");
    printf("三月\t  %d\t    %d      %+d\n",48000,52000,(48000-52000));
    printf("六月\t  %d\t    %d     %+d\n",70000,58000,(70000-58000));
    printf("九月\t  %d\t    %d      %+d\n",52000,56000,(52000-56000));
    printf("十二月\t  %d\t    %d      %+d\n",48000,52000,(50000-48000));
    return 0;
}