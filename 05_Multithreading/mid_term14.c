#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    int Arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &Arr[i]);
    }
    pid_t child[K];
    int fd[K][2];
    int chunk = N / K;
    int start[K];
    for (int i = 0; i < K; i++) {
        start[i] = i * chunk;
    }
    for (int i = 0; i < K; i++) {
        pipe(fd[i]);
        child[i] = fork()
        if (child[i] == 0) {
            close(fd[i][0]);
            int max_local = -1;
            for (i = start[i]; i < start[i] + chunk; i++) {
                if (Arr[i] > max) {
                    max_local = Arr[i];
                }
            }
            write(fd[i][1], &max, sizeof(int));
            exit(0);
        }
    }
    for (int i = 0; i < K; i++) {
        wait(NULL);
    }
    int max_global = -1;
    for (int i = 0; i < K; i++) {
        close(fd[i][1]);
        int buffer;
        read(fd[i][0]; &buffer; sizeof(int));
        if (buffer > max_global) {
            max_global = buffer;
        }
    }
    printf("%d\n", max_global);
    return 0;
}