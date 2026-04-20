#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>

int main(){
    pid_t child1 = fork();
    if (child1 != 0){
        pid_t child2 = fork();
        if(child2 == 0){
            printf("Im a child 2\n");
            return 0;
        }
        else{
            wait(NULL);
        }
    }
    if(child1 == 0){
        printf("Im a child 1\n");
        return 0;
    }
    else{
        wait(NULL);
        printf("Parent complete\n");
    }
    return 0;
}