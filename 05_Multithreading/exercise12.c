#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>  

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_proc = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_anten = PTHREAD_COND_INITIALIZER;

int signals[] = {0, 0, 0};
int count = 0;

void *thread_child(void *arg) {
    int id = *((int *)arg);
    while (1) {
        sleep(1);
        int value = rand() % 100;
        pthread_mutex_lock(&lock);
        while (signals[id] != 0) {
            pthread_cond_wait(&cond_anten, &lock);
        }
        signals[id] = value;
        count++;
        pthread_cond_signal(&cond_proc);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *thread_parent(void *arg) {
    while (1) {
        pthread_mutex_lock(&lock);
        while (count != 3) {
            pthread_cond_wait(&cond_proc, &lock);
        }
        int total = 0;
        for (int i = 0; i < 3; i++) {
            total += signals[i];
            signals[i] = 0;
        }
        count = 0;
        printf("The trung binh value is %d\n", total / 3);
        pthread_cond_signal(&cond_anten);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2, t3, t4;
    int id1 = 0, id2 = 1, id3 = 2;
    pthread_create(&t1, NULL, thread_child, &id1);
    pthread_create(&t1, NULL, thread_child, &id2);
    pthread_create(&t1, NULL, thread_child, &id3);
    pthread_create(&t4, NULL, thread_parent, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_join(t4, NULL);
    return 0;
}