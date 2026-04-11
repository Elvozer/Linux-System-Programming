#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>
#include<signal.h>
#include<stdlib.h>

void hearing(int sig){
    printf("Dạ đại ca gọi, em xin phép logout!\n");
    exit(0);
}
int main(){
    pid_t childPid = fork();
    if(childPid == 0){
        signal(SIGUSR1, hearing);
        while(1){
            printf("Đang cày rank, không về đâu....\n");
            sleep(1);
        }
    }
    else{
        sleep(3);
        kill(childPid, SIGUSR1);
        wait(NULL);
        printf("Thế mới ngoan chứ!\n");
    }
    return 0;
}