#include<stdio.h>
#include<pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_pro = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_con = PTHREAD_COND_INITIALIZER;

int circular_buffer[16] = {0};
int head = 0, tail = 0;

void *thread_pro(void *arg) {
    while (head != 8) {
        pthread_mutex_lock(&lock);
        if (head == 7) {
            circular_buffer[head+1] = -1;
            circular_buffer[head+2] = -1;
            circular_buffer[head+3] = -1;
        }
        circular_buffer[head++] = head + 1;
        pthread_cond_broadcast(&cond_con);
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *thread_con(void *arg) {
    int id = *(int *)arg;
    while (circular_buffer[tail] != -1){
        pthread_mutex_lock(&lock);
        while (head == tail) {
            pthread_cond_wait(&cond_con, &lock);
        }
        int temp = tail;
        tail++;
        pthread_cond_signal(&cond_pro);
        pthread_mutex_unlock(&lock);
}