#include<stdio.h>
#include<sys/wait.h>
#include<unistd.h>

int main(){
    int childToPa[2], paToChild[2];
    char buffer[512];
    int bytesRead;
    pipe(childToPa);
    pipe(paToChild);
    pid_t childPid = fork();
    if (childPid == 0){
        close(childToPa[0]);
        write(childToPa[1], "Hello parent\n", 14);
        close(childToPa[1]);
        close(paToChild[1]);
        while((bytesRead = read(paToChild[0], buffer, sizeof(buffer)))>0){
            write(1, buffer, bytesRead);
        }
    }
    else{
        close(childToPa[1]);
        while((bytesRead = read(childToPa[0], buffer, sizeof(buffer)))>0){
            write(1, buffer, bytesRead);
        }
        close(paToChild[0]);
        write(paToChild[1], "Hello children\n", 16);
        close(paToChild[1]);
        wait(NULL);
    }
    return 0;
}