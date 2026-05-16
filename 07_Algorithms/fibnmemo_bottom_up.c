#include<stdio.h>
#include<stdlib.h>

long long global_count;

long long fibnmemo(int n) {
    global_count++;
    int curr;
    int prev1 = 0;
    int prev2 = 1;
    for (int i = 2; i <= n; i++) {
        curr = prev1 + prev2;
        prev1 = prev2;
        prev2 = curr;
    }
    return curr;
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    global_count = 0;
    printf("Value is %lld\n", fibnmemo(n));
    printf("Count is %lld\n", global_count);
    return 0;
}