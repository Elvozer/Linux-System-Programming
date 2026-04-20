#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<sys/types.h>

int main() {
    int n;
    printf("Nhập N vào:\n");
    scanf("%d", &n);

    // TẠO 2 ỐNG RIÊNG BIỆT (Phải có 2 ống để 2 thằng con ko tranh nhau)
    int fd1[2], fd2[2];
    pipe(fd1);
    pipe(fd2);
    if(fork() == 0){
        int sum1 = 0;
        close(fd1[0]);
        for(int i=1; i<=n; i++){
            sum1 += i;
        }
        write(fd1[1], &sum1, sizeof(int));
        close(fd1[1]);
        return 0;
    }
    if(fork() == 0){
        int sum1 = 0;
        close(fd2[0]);
        for(int i=1; i<=n; i++){
            if(i%2 != 0){
                sum1 += i;
            }
        }
        write(fd2[1], &sum1, sizeof(int));
        close(fd2[1]);
        return 0;
    }

    int sum, sumodd;
    close(fd1[1]);
    close(fd2[1]);

    wait(NULL);
    wait(NULL);
    read(fd1[0], &sum, sizeof(int));
    read(fd2[0], &sumodd, sizeof(int));

    printf("The value sum and odd is %d and %d\n", sum, sumodd);
    return 0;
}
