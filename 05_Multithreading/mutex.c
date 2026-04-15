#include<stdio.h>
#include<pthread.h>

#define LOOP 1000

int counter = 0;
pthread_mutex_t lock;

void *increase(void *arg){
    for(int i=0; i<LOOP; i++){
        pthread_mutex_lock(&lock);
        counter++;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main(){
    pthread_t t1, t2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&t1, NULL, increase, NULL);
    pthread_create(&t2, NULL, increase, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("Counter is %d\n", counter);
    pthread_mutex_destroy(&lock);
    return 0;
}