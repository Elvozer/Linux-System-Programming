#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define NUM_ORDER 20
#define MAX_CAPACITY 5

typedef struct {
    int order_id;
    int value;
} Order;

typedef struct {
    Order buffer[MAX_CAPACITY];
    int head, tail, count;
    int is_sale_ended;
    pthread_mutex_t lock;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} Flash_Sale_System;

typedef struct {
    Flash_Sale_System *fp;
    Order *input;
    int id_thread;
} Args;

void system_init(Flash_Sale_System *q) {
    q->head = q->tail = q->count = q->is_sale_ended = 0;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_full, NULL);
    pthread_cond_init(&q->not_empty, NULL);
}

void system_push(Flash_Sale_System *fp, Order order) {
    pthread_mutex_lock(&fp->lock);
    while (fp->count == MAX_CAPACITY) {
        pthread_cond_wait(&fp->not_full, &fp->lock);
    }
    fp->buffer[fp->tail] = order;
    fp->tail = (fp->tail + 1) % MAX_CAPACITY;
    fp->count++;
    pthread_cond_signal(&fp->not_empty);
    pthread_mutex_unlock(&fp->lock);
}

int system_take(Flash_Sale_System *fp, Order *op) {
    pthread_mutex_lock(&fp->lock);
    while (fp->count == 0 && !fp->is_sale_ended) {
        pthread_cond_wait(&fp->not_empty, &fp->lock);
    }
    if (fp->count == 0 && fp->is_sale_ended) {
        pthread_mutex_unlock(&fp->lock);
        return 0;
    }
    *op = fp->buffer[fp->head];
    fp->head = (fp->head + 1) % MAX_CAPACITY;
    fp->count--;
    pthread_cond_signal(&fp->not_full);
    pthread_mutex_unlock(&fp->lock);
    return 1;
}

void *producer_func(void *arg) {
    Args *ap = (Args *)arg;
    for (int i = 0; i < NUM_ORDER; i++) {
        printf("[Nhan vien %d] Day don hang #%d vao trong system\n", ap->id_thread, ap->input[i].order_id);
        system_push(ap->fp, ap->input[i]);
    }
    return NULL;
}

void *process_func(void *arg) {
    Args *ap = (Args *)arg;
    Flash_Sale_System *fp = ap->fp;
    Order order;
    while (system_take(fp, &order)) {
        printf("[Nhan vien %d] Dong goi don #%d Gia tri: %d\n", ap->id_thread, order.order_id, order.value);
    }
    return NULL;
}
void take_input(Order *op) {
    int value = 100;
    for (int i = 0; i < NUM_ORDER; i++) {
        op[i].order_id = i + 1;
        op[i].value = value * i + 1;
    }
}

int main() {
    Flash_Sale_System fs;
    system_init(&fs);
    Order input[NUM_ORDER];
    take_input(input);
    pthread_t t[4];
    int id_producer  = 0;
    int id_processor[3] = {1, 2, 3};
    Args a[4];
    for (int i = 0; i < 4; i++) {
        a[i].id_thread = i + 1;
        a[i].input = input;
        a[i].fp = &fs;
    }
    pthread_create(&t[0], NULL, producer_func, &a[0]);
    for (int i = 1; i < 4; i++) {
        pthread_create(&t[i], NULL, process_func, &a[i]);
    }
    pthread_join(t[0], NULL);
    printf("Ket thuc su kien.\n");
    pthread_mutex_lock(&fs.lock);
    fs.is_sale_ended = 1;
    pthread_cond_broadcast(&fs.not_empty);
    pthread_mutex_unlock(&fs.lock);
    for (int i = 1; i < 4; i++) {
        pthread_join(t[i], NULL);
    }
    return 0;
}