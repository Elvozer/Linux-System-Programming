#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX_SIZE 5

pthread_mutex_t lock;
pthread_cond_t full;
pthread_cond_t empty;

int count;
void *thread_pro(void *arg) {
    for (int i = 1; i <= 20; i++) {
        //Add mutex
        pthread_mutex_lock(&lock);
        //Check cond
        if (count == MAX_SIZE) {
            pthread_cond_wait(&full, &lock);
            sleep(1);
            count++;
            printf("Add 1 cake in buffer, total cakes is %d\n", count);
        } else if (count == 0) {
            sleep(1);
            count++;
            printf("Add 1 cake in buffer, total cakes is %d\n", count);
            pthread_cond_signal(&empty);
        } else {
            sleep(1);
            count++;
            printf("Add 1 cake in buffer, total cakes is %d\n", count);
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *thread_con(void *arg) {
    for (int i = 1; i <= 20; i++) {
        //Add mutex
        pthread_mutex_lock(&lock);
        //Check cond
        if (count == MAX_SIZE) {
            sleep(1);
            count--;
            printf("Take 1 cake in buffer, total cakes is %d\n", count);
            pthread_cond_signal(&full);
        } else if (count == 0) {
            pthread_cond_wait(&empty, &lock);
            sleep(1);
            count--;
            printf("Take 1 cake in buffer, total cakes is %d\n", count);
        } else {
            sleep(1);
            count--;
            printf("Take 1 cake in buffer, total cakes is %d\n", count);
        }
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    count = 5;
    pthread_create(&t1, NULL, thread_pro, NULL);
    pthread_create(&t2, NULL, thread_con, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}