#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>

int factorial(int n) {
    if (n == 1) return n;
    else return n * factorial(n-1);
}

int main() {
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    if (fork() == 0) {
        close(fd1[0]);
        close(fd2[1]);
        close(fd2[0]);
        int res = factorial(5);
        write(fd1[1], &res, sizeof(int));
        close(fd1[1]);
        exit(0);
    }

    if (fork() == 0) {
        close(fd2[0]);
        close(fd1[1]);
        close(fd1[0]);
        int res = factorial(6);
        write(fd2[1], &res, sizeof(int));
        close(fd2[1]);
        exit(0);
    }
    wait(NULL);
    wait(NULL);
    close(fd1[1]);
    close(fd2[1]);
    int res1, res2;
    read(fd1[0], &res1, sizeof(int));
    read(fd2[0], &res2, sizeof(int));
    close(fd1[0]);
    close(fd2[0]);
    printf("The value is %d and %d\n", res1, res2);
    return 0;
}