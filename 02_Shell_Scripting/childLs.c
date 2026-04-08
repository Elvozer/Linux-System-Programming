#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
    pid_t childPid = fork();
    if (childPid == 0){
        execlp("ls", "ls", "-l", "/home/el_vozer", NULL);
    }
    else{
        wait(NULL);
    }
    return 0;
}