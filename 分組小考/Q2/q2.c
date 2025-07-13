#include <stdio.h>

// 費伯那西數列的遞迴函數
unsigned long long fibonacci(int n) {
    if (n == 1 || n == 2) {
        return 1; 
    }
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    int n;
    scanf("%d", &n);

    if (n <= 0 || n > 100) {
        printf("請輸入 1 到 100 之間的數字。\n");
        return 1; 
    }

    printf("%llu\n", fibonacci(n));
    return 0;
}
