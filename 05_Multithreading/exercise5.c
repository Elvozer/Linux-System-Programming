#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/wait.h>
#include<string.h>

void *print(void *arg){
    pid_t pro = getpid();
    pthread_t t = pthread_self();
    printf("I'm a thread in process %d, thread ID: %ld\n", pro, t);
    return NULL;
}

int main(){
    pthread_t t1, t2;
    pid_t child = fork();
    if (child == 0){
        pthread_create(&t1, NULL, print, NULL);
        pthread_join(t1, NULL);
        return 0;
    }
    else{
        pthread_create(&t2, NULL, print, NULL);
        pthread_join(t2, NULL);
        wait(NULL);
    }
    return 0;
}