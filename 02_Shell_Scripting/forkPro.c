#include<stdio.h>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    __pid_t pid = fork(); 
    int status;
    if (pid>0){
        wait(&status);
        printf("Tien trinh con ket thuc.");
    }
    else{
        printf("Tien trinh con dang chay.");
    }
    return 0;
}