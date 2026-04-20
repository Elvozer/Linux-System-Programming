#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t lock;
pthread_cond_t cond;
int counter, des;

void *threadfun(void *arg){
    int tid = *((int *)arg);
    pthread_mutex_lock(&lock);
    des++;
    if(des == counter){
            printf("All threads reached the barrier! Releasing them...\n");
            pthread_cond_broadcast(&cond);
        }
        else{
            printf("Thread %d reached the barrier\n", tid);
            while(des != counter){
                pthread_cond_wait(&cond, &lock);
            }
        }
    printf("Thread %d passed the barrier\n", tid);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_cond_init(&cond, NULL);
    pthread_mutex_init(&lock, NULL);
    int n = atoi(argv[1]);
    counter = n, des = 0;
    pthread_t a[n];
    int b[n];
    for(int i=0; i<n; i++){
        b[i] = i;
        pthread_create(&a[i], NULL, threadfun, &b[i]);
    }
    for(int i=0; i<n; i++){
        pthread_join(a[i], NULL);
    }
    pthread_mutex_destroy(&lock);
    pthread_cond_destroy(&cond);
    return 0;
}