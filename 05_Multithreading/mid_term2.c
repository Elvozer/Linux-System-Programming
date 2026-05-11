#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define NUM_FL 3
#define BUFFER_SIZE 5


typedef struct {
    int f1_id;
    int f2_id;
    int customer_id;
} Booking_Request;

typedef struct {
    Booking_Request buffer[BUFFER_SIZE];
    int head, tail, count;
    int done;
    pthread_mutex_t lock;
    pthread_cond_t not_empty;
    pthread_cond_t not_full;
} Queue;

typedef struct {
    int flight_id;
    int available_seat;
    int price;
    pthread_mutex_t lock;
} Flight;

typedef struct {
    Flight flights[NUM_FL];
    long total_revenue;
    pthread_mutex_t lock_rev;
} Agency;

typedef struct {
    Booking_Request *items;
    Queue *q;
} Producer_Args;

typedef struct {
    Agency *data;
    Queue *q;
} Consumer_Args;

void agency_init(Agency *ptr) {
    int id_fl[] = {1, 2, 3};
    for (int i = 0; i < NUM_FL; i++) {
        ptr->flights[i].flight_id = id_fl[i];
        ptr->flights[i].available_seat = 100;
        ptr->flights[i].price = 1000 + i*200;
        pthread_mutex_init(ptr->flights[i].lock, NULL);
    }
    total_revenue = 0;
    pthread_mutex_init(ptr->lock_rev);
}

void queue_init(Queue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    q->done = 0;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
}

void queue_push(Booking_Request *data, Queue *q) {
    pthread_mutex_lock(&q->lock);
    while (count == BUFFER_SIZE) {
        pthread_cond_wait(&q->not_full, &q->lock);
    }
    q->buffer[q->head] = *data;
    q->head = (q->head + 1) % BUFFER_SIZE;
    q->count++;
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->lock);
}

int queue_take(Queue *q, Booking_Request *res) {
    pthread_mutex_lock(&q->lock);
    while (q->count == 0 && !q->done) {
        pthread_cond_wait(&q->not_empty, &q->lock);
    }
    if (q->count == 0 && q->done) {
        pthread_mutex_unlock(&q->lock);
        return 0;
    }
    *res = q->buffer[q->tail];
    q->tail = (q->tail + 1) % BUFFER_SIZE;
    q->count--;
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->lock);
    return 1;
}

void *producer_routine(void *arg) {
    Producer_Args *ptr = (Producer_Args *)arg;
    for (int i = 0; i < NUM_FL; i++) {
        queue_push(ptr->items[i], ptr->q);
    }
    return NULL;
}

void *consumer_routine(void *arg) {
    Consumer_Args *ptr = (Consumer_Args *)arg;
    Booking_Request res;
    while (queue_take(ptr->q, &res)) {
        printf("Khach %d: Dang dat ve noi chuyen %d -> %d...\n", res.customer_id, res.f1_id, res.f2_id);
        pthread_mutex_t *first_lock, *second_lock;
        (ptr->flights[res.f1_id].flight_id > ptr->flights[res.f2_id].flight_id) ? first_lock = &ptr->flights[res.f1_id].lock : first_lock = &ptr->flights[res.f2_id].lock;
        (ptr->flights[res.f1_id].flight_id > ptr->flights[res.f2_id].flight_id) ? second_lock = &ptr->flights[res.f2_id].lock : second_lock = &ptr->flights[res.f1_id].lock;
        pthread_mutex_lock(first_lock);
        pthread_mutex_lock(second_lock);
        if (ptr->flights[res.f1_id].available_seat > 0 && ptr->flights[res.f2_id].available_seat > 0) {
            tr->flights[res.f1_id].available_seat -= 1;
            ptr->flights[res.f2_id].available_seat -= 1;
        }
    }
    return NULL;
}
int main() {
    
}
