#include<string.h>
#include<sys/mman.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdio.h>
#include<stdlib.h>

int main(){
    char *state = mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    pid_t childPid = fork();
    if (childPid == 0){
        strcpy(state, "Daddy i have gold right here!");
        exit(0);
    }
    else{
        wait(NULL);
        printf("%s", state);
        munmap(state, 100);
    }
    return 0;
}