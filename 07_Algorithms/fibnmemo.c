#include<stdio.h>
#include<stdlib.h>

long long global_count;

long long fibmemo(long long memo[], int n) {
    global_count++;
    if (n <= 1) return n;

    if (memo[n] != -1) return memo[n];

    memo[n] = fibmemo(memo, n - 1) + fibmemo(memo, n - 2);

    return memo[n];
}


int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Loi\n");
        return 1;
    }
    int n = atoi(argv[1]);
    long long memo[n + 1];
    for (int i = 0; i <= n; i++) {
        memo[i] = -1;
    }
    global_count = 0;
    printf("Value is %lld\n", fibmemo(memo, n));
    printf("Count is %lld\n", global_count);
    return 0;
}  