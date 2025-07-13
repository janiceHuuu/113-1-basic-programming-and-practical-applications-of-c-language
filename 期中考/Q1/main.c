#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(){
    char password[500];
    gets(password);
    int n;
    scanf("%d",&n);
    int length;
    length=strlen(password);
    for(int i=0;i<length;i++){
        if(password[i]>=97 && password[i]<=122){
            if(password[i]+n > 122){
                password[i]=password[i]+n-122+96;
            }
            else{
                password[i] = password[i]+n;
            }
        }
    }
    for(int i=0;i<length;i++){
        printf("%c",password[i]);
    }
    printf("\n");
    return 0;
}