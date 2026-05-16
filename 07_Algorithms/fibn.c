#include<stdio.h>
#include<stdlib.h>

long long global_count;

long long fibn(int n) {
    global_count++;
    if (n <= 1) return n;
    return fibn(n - 1) + fibn(n - 2); 
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Loi\n");
        return 1;
    }
    global_count = 0;
    int n = atoi(argv[1]);
    printf("Value is %lld\n", fibn(n));
    printf("Count is %lld\n", global_count);
    return 0;
}