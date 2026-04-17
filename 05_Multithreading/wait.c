#include<stdio.h>
#include<pthread.h>
#include<unistd.h>

int ready = 0;
pthread_mutex_t lock;
pthread_cond_t cond;

void *prodfun(void *arg){
    pthread_mutex_lock(&lock);
    ready = 1;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);
}

void *consfun(void *arg){
    pthread_mutex_lock(&lock);
    while(!ready){
        printf("Waiting for goods...\n");
        pthread_cond_wait(&cond, &lock);
    }
    printf("Data received!\n");
    pthread_mutex_unlock(&lock);
}

void main(){
    pthread_t prod, cons;
    pthread_create(&prod, NULL, prodfun, NULL);
    pthread_create(&cons, NULL, consfun, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
}