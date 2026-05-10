#include<pthread.h>
#include<stdlib.h>
#include<stdio.h>

#define QUEUE_CAP 8

typedef struct {
    int data[QUEUE_CAP];
    int head, tail, count;
    int done;
    pthread_mutex_t lock;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} Queue;

typedef struct {
    Queue *q;
    int *items;
    int n;
} producer_args;

void queue_init(Queue *q) {
    q->head = 0;
    q->tail = 0;
    q->count = 0;
    q->done = 0;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_empty, NULL);
    pthread_cond_init(&q->not_full, NULL);
}

void queue_push(Queue *q, int val) {
    pthread_mutex_lock(&q->lock);
    while (q->count == QUEUE_CAP) {
        pthread_cond_wait(&q->not_full, &q->lock);
    }
    q->data[q->tail] = val;
    q->tail = (q->tail + 1) % QUEUE_CAP;
    q->count++;
    pthread_cond_signal(&q->not_empty);
    pthread_mutex_unlock(&q->lock); 
}

int queue_pop(Queue *q, long *val) {
    pthread_mutex_lock(&q->lock);
    while (q->count == 0 && !q->done) {
        pthread_cond_wait(&q->not_empty, &q->lock);
    }
    if (q->count == 0 && q->done == 1) {
        pthread_mutex_unlock(&q->lock);
        return 0;
    }
    *val = q->data[q->head];
    q->head = (q->head + 1) % QUEUE_CAP;
    q->count--;
    pthread_cond_signal(&q->not_full);
    pthread_mutex_unlock(&q->lock);
    return 1;
}

void *producer(void *arg) {
    producer_args *data = (producer_args *)arg;
    for (int i = 0; i < data->n; i++) {
        queue_push(data->q, data->items[i]);
    }
    return NULL;
}

void *consumer(void *arg) {
    Queue *q = (Queue *)arg;
    long *sum = malloc(sizeof(long));
    long temp;
    *sum = 0;
    while (queue_pop(q, &temp)){
        *sum += temp; 
    }
    return sum;
}

int main() {
    int n; 
    void *sum;
    long real_sum;
    int items[n];
    printf("Nhap so phan tu mang vao duoi day:\n");
    scanf("%d", &n);
    printf("Nhap mang vao: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &items[i]);
    }
    Queue q;
    queue_init(&q);
    producer_args data;
    data.items = items;
    data.n = n;
    data.q = &q;
    pthread_t pro_tid, con_tid;
    pthread_create(&pro_tid, NULL, producer, &data);
    pthread_create(&con_tid, NULL, consumer, &q);
    pthread_join(pro_tid, NULL);
    pthread_mutex_lock(&q.lock);
    q.done = 1;
    pthread_cond_signal(&q.not_empty);
    pthread_mutex_unlock(&q.lock);
    pthread_join(con_tid, &sum);
    real_sum = *((long *)sum);
    printf("Total is: %ld\n", real_sum);
    free(sum);
    return 0;
}