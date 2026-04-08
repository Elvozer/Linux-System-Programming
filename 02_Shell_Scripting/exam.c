#include <stdio.h>
#include <fcntl.h>
#include<sys/wait.h>
#include <unistd.h>
static int idata = 1000; //Alocated in data segment

int main() {
    int istack = 150; //Alocated in stack segment
    int fd = open("Hello.txt", O_RDWR);
    int status;
    pid_t childPid = fork();
    if (childPid ==0){
        printf(" Value of idata and istack in child process is : %d %d\n", idata, istack);
        idata = 10;
        istack = 1;
        printf(" Value of idata and istack in child process after that is : %d %d\n", idata, istack);
        lseek(fd, 6, SEEK_SET);
    }
    else{
        wait(&status);
        printf(" Value of idata and istack parent process is : %d %d\n", idata, istack);
        int bytes_read;
        char buffer[512];
        while((bytes_read = read(fd, buffer, sizeof(buffer)))>0){
            write(1, buffer, bytes_read);
            }
        }
        return 0;
}
