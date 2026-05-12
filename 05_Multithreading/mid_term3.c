#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define NUM_BUYER 5
#define NUM_REFUND 2
#define SEAT 100

typedef struct {
    int available_seat;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    int id_thread;
    int done;
} Args;

void func_init(Args *a) {
    a->available_seat = SEAT;
    pthread_mutex_init(&a->lock, NULL);
    pthread_cond_init(&a->not_empty, NULL);
    a->id_thread = 0;
    a->done = 0;
}

void *buyer_thread(void *arg) {
    Args *a = (Args *)arg;
    pthread_mutex_lock(&a->lock);
    while (a->available_seat < 30 && !a->done) {
        pthread_cond_wait(&a->not_empty, &a->lock);
    }
    if (a->available_seat < 30 && a->done) {
        pthread_mutex_unlock(&a->lock);
        printf("Het ve de mua.\n");
        return NULL;
    }
    a->available_seat -= 30;
    a->id_thread++; 
    printf(" Dai ly %d: dat 30 ve | Con lai: %d ve\n", a->id_thread, a->available_seat);
    pthread_mutex_unlock(&a->lock);
    return NULL;
}

void *refund_thread(void *arg) {
    Args *a = (Args *)arg;
    pthread_mutex_lock(&a->lock);
    a->available_seat += 20;
    a->id_thread++;
    printf(" Dai ly %d: hoan 20 ve | Con lai: %d ve\n", a->id_thread, a->available_seat);
    pthread_cond_broadcast(&a->not_empty);
    pthread_mutex_unlock(&a->lock);
    return NULL;
}

int main() {
    Args arg;
    pthread_t id_buyer[NUM_BUYER];
    pthread_t id_refund[NUM_REFUND];
    func_init(&arg);
    for (int i = 0; i < NUM_BUYER; i++) {
        pthread_create(&id_buyer[i], NULL, buyer_thread, &arg);
    }
    for (int i = 0; i < NUM_REFUND; i++) {
        pthread_create(&id_refund[i], NULL, refund_thread, &arg);
    }
    for (int i = 0; i < NUM_REFUND; i++) {
        pthread_join(id_refund[i], NULL);
    }
    pthread_mutex_lock(&arg.lock);
    arg.done = 1;
    pthread_cond_broadcast(&arg.not_empty);
    pthread_mutex_unlock(&arg.lock);
    for (int i = 0; i < NUM_BUYER; i++) {
        pthread_join(id_buyer[i], NULL);
    }
    return 0;
}