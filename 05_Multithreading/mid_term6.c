#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<pthread.h>
#include<stdlib.h>


typedef struct {
    int *Arr;
    int n;
    int start, end, chunk;
} Args;

void *thread_func(void *arg) {
    Args *a = (Args *)arg;
    int *sum = malloc(sizeof(int));
    *sum = 0;
    for (int i = a->start; i < a->end; i++) {
        *sum += a->Arr[i];
    }
    return sum;
}
int main() {
    int fd_file = open("data.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    int fd[2];
    pipe(fd);
    pid_t pid = fork();
    if (pid == 0) {
        close(fd[1]);
        int str2[6];
        read(fd[0], str2, sizeof(str2));
        pthread_t t[2];
        Args arg[2];
        for (int i = 0; i < 2; i++) {
            arg[i].Arr = str2;
            arg[i].n = sizeof(str2) / sizeof(str2[0]);
            arg[i].chunk = arg[i].n / 2;
            arg[i].start = i * arg[i].chunk;
            arg[i].end = arg[i].start + arg[i].chunk;
            pthread_create(&t[i], NULL, thread_func, &arg[i]);
        }
        void *sum_fake[2];
        int *sum_real[2];
        for (int i = 0; i < 2; i++) {
            pthread_join(t[i], &sum_fake[i]);
            sum_real[i] = (int *)sum_fake[i];
            printf("Tong cua nua %d la: %d\n", i + 1, *sum_real[i]);
        }
        printf("Tong cua day la: %d\n", *sum_real[0] + *sum_real[1]);
        free(sum_real[0]);
        free(sum_real[1]);
        exit(0);
    }
    int str1[] = {1, 1, 1, 1, 1, 4};
    close(fd[0]);
    write(fd[1], str1, sizeof(str1));
    close(fd_file);
    close(fd[1]);
    wait(NULL);
    return 0;
}