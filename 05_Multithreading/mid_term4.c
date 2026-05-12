#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

void get_input(int *arr, int n) {
    printf("Nhap cac phan tu vao:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
}

int main() {
    int fd1[2], fd2[2];
    int n;
    printf("Nhap kich thuoc mang\n");
    scanf("%d", &n);
    int arr[n];
    int load = n / 2;
    get_input(arr, n);
    pipe(fd1);
    pipe(fd2);
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == 0) {
        close(fd1[0]);
        close(fd2[0]);
        close(fd2[1]);
        int sum_total = 0;
        int start = 0;
        int end = start + load;
        for (int i = start; i < end; i++) {
            sum_total += arr[i];
        }
        write(fd1[1], &sum_total, sizeof(int));
        close(fd1[1]);
        exit(0);
    }
    pid2 = fork();
    if (pid2 == 0) {
        close(fd1[0]);
        close(fd1[1]);
        close(fd2[0]);
        int sum_product = 1;
        int end = n;
        for (int i = load; i < n; i++) {
            sum_product *= arr[i];
        }
        write(fd2[1], &sum_product, sizeof(int));
        close(fd2[1]);
        exit(0);
    }
    wait(NULL);
    wait(NULL);
    close(fd1[1]);
    close(fd2[1]);
    int sum_product, sum_total;
    read(fd1[0], &sum_total, sizeof(int));
    read(fd2[0], &sum_product, sizeof(int));
    close(fd1[0]);
    close(fd2[0]);
    printf("Tong nua dau: %d\nTich nua sau: %d", sum_total, sum_product);
    return 0;
}