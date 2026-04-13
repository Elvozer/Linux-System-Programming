#include<sys/mman.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<signal.h>
#include<string.h>
#include<stdlib.h>

char *state;
int fd[2];

void waitForSig(int sig){
    strcpy(state, "Opened the lock!\n");
    close(fd[0]);
    write(fd[1], "Pass is: 1233\n", 14);
    execl("ls", "ls", "-l", NULL);
}

int main(){
    pipe(fd);
    state = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    pid_t childPid = fork();
    if (childPid == 0){
        signal(SIGUSR1, waitForSig);
        while(1){
            printf("Unlocking...\n");
            sleep(1);
        }
    }
    else{
        sleep(3);
        kill(childPid, SIGUSR1);
        wait(NULL);
        close(fd[1]);
        char buf[100];
        read(fd[0], buf, 14);
        printf("Password is %s\n", buf);
        printf("State of lock: %s\n", state);
        munmap(state, 100);
    }
    return 0;
}