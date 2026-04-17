#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    int pd[2];
    pipe(pd);
    pid_t childPid  = fork();
    if (childPid == 0){
        close(pd[0]);
        dup2(pd[1], 1);
        execlp("ls", "ls", NULL);
    }
    else{
        close(pd[1]);
        dup2(pd[0], 0);
        execlp("wc", "wc", "-l", NULL);
    }
    return 0;
}