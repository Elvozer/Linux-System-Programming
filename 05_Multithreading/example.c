#include<stdio.h>

int total(int N) {
    if (N < 10) return N;
    return (N % 10) + total(N / 10); 
}

int main() {
    int N = 123456;
    printf("Total is %d\n", total(N));
    return 0;
}