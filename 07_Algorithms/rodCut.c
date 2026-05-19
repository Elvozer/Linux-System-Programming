#include<stdio.h>
#include<stdlib.h>

void build_max_price(int price_table[], int p[], int s[]) {
    for (int i = 0; i <= 10; i++) {
        for (int j = 1; j <= i; j++) {
            if ((price_table[j] + p[i - j]) > p[i]) {
                p[i] = price_table[j] + p[i - j];
                s[i] = j;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    int n = atoi(argv[1]);
    int price_table[11] = {0, 1, 5, 8, 9, 10, 17, 17, 20, 24, 30};
    int p[11], s[11];
    for (int i = 0; i <= 10; i++) {
        if (i == 0) {
            p[i] = 0;
        } else {
            p[i] = -1;
        }
    }
    build_max_price(price_table, p, s);
    int cut = 1;
    printf("Max price is %d\n", p[n]);
    while (n != 0) {
        printf("Cut %d is index %d\n", cut, s[n]);
        n = n - s[n];
        printf("Length after that is %d\n", n);
        cut++;
    }
    return 0;
}