#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#define CMDSIZ 32

 void process_command(char* cmdbuf){
    pid_t childPid = fork();
    if (childPid == 0){
        execlp(cmdbuf, cmdbuf, NULL);
        printf("Lenh khong ton tai.");
        exit(1);
    }
    else{
        wait(NULL);
    }
}
int main(){
    int logout = 0, cmdsiz;
    char cmdbuf[CMDSIZ] ;
    while(!logout){
        write (1, "myshell> ", 9) ;
        cmdsiz = read(0, cmdbuf, CMDSIZ) ;
        cmdbuf[cmdsiz-1] = '\0' ;
        if (strcmp("logout", cmdbuf) == 0)
            ++logout ;
        else 
            process_command(cmdbuf) ;
    }
}