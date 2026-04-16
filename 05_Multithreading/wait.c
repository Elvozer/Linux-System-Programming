#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int store = 0;
pthread_mutex_t lock;
pthread_cond_t cond;

void *buyer(void *arg){
    pthread_mutex_lock(&lock);
    while(store == 0){
        printf("Waiting for goods...\n");
        pthread_cond_wait(&cond, &lock);
    }
    store--;
    pthread_mutex_unlock(&lock);
    return NULL;
}