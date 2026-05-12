#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define MAX_CAPACITY 3

typedef struct {
    int id;
    int producer_id;
} Package; 

typedef struct {
    Package items[MAX_CAPACITY];
    int head, tail;
    int count;
    int done;
    pthread_mutex_t lock;
    pthread_cond_t not_full;
    pthread_cond_t not_empty;
} Warehouse;

typedef struct {
    int id_thread;
    Warehouse *wq;
    Package *pq;
} Args;


void queue_init(Warehouse *q) {
    q->head = q->tail = q->count = q->done = 0;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->not_full, NULL);
    pthread_cond_init(&q->not_empty, NULL);
}

void queue_push(Args *aq) {
    pthread_mutex_t *lock = &aq->wq->lock;
    pthread_cond_t *not_empty = &aq->wq->not_empty;
    pthread_cond_t *not_full = &aq->wq->not_full;
    pthread_mutex_lock(lock);
    while (aq->wq->count == MAX_CAPACITY) {
        pthread_cond_wait(not_full, lock);
    }
    aq->wq->items[aq->wq->head] = *(aq->pq);
    aq->wq->head = (aq->wq->head + 1) % MAX_CAPACITY;
    aq->wq->count++;
    printf("[Nha may %d] San xuat kien hang #%d. Kho hien tai: %d/%d\n", aq->pq->producer_id, aq->pq->id, aq->wq->count, MAX_CAPACITY); 
    pthread_cond_signal(not_empty);
    pthread_mutex_unlock(lock);
}

int queue_take(Warehouse *wq, Package *pq) {
    pthread_mutex_lock(&wq->lock);
    while (wq->count == 0 && !wq->done) {
        pthread_cond_wait(&wq->not_empty, &wq->lock);
    }
    if (wq->count == 0 && wq->done) {
        pthread_mutex_unlock(&wq->lock);
        return 0;
    }
    *pq = wq->items[wq->tail];
 
    wq->tail = (wq->tail + 1) % MAX_CAPACITY;
 
    wq->count--;
    pthread_cond_signal(&wq->not_full);

    pthread_mutex_unlock(&wq->lock);
    return
     1;
}

void *producer_func(void *arg) {
    Args *aq = (Args *)arg;
    for(int i = 0; i < MAX_CAPACITY; i++) {
        aq->pq = aq->pq + i;
        queue_push(aq);
    }
    return NULL;
}

void *consumer_func(void *arg) {
    Args *aq = (Args *)arg;
    Warehouse *wq = aq->wq;
    Package pq;
    while (queue_take(wq, &pq)) {
        printf("[Xe tai %d] Lay kien hang #%d cua nha may %d . Kho hien tai: %d/%d\n", aq->id_thread, pq.id, pq.producer_id, wq->count, MAX_CAPACITY);
    }
    return NULL;
}

int main() {
    Warehouse wq;
    queue_init(&wq);
    Package arr[MAX_CAPACITY];
    for (int i = 0; i < MAX_CAPACITY; i++) {
        printf("Tao goi hang %d\n", i + 1);
        printf("Nhap id goi hang\n");
        scanf("%d", &arr[i].id);
        printf("Nhap id producer\n");
        scanf("%d", &arr[i].producer_id);
    }
    Args arg[2];
    int consumer_id[] = {1, 2};
    pthread_t t1[2], t2[2];
    for (int i = 0; i < 2; i++) {
        arg[i].wq = &wq;
        arg[i].pq = arr;
        pthread_create(&t1[i], NULL, producer_func, &arg[i]);
    }
    for (int i = 0; i < 2; i++) {
        arg[i].id_thread = consumer_id[i];
        pthread_create(&t2[i], NULL, consumer_func, &arg[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(t1[i], NULL);
    }
    pthread_mutex_lock(&wq.lock);
    wq.done = 1;
    pthread_cond_broadcast(&wq.not_empty);
    pthread_mutex_unlock(&wq.lock);
    for (int i = 0; i < 2; i++) {
        pthread_join(t2[i], NULL);
    }
    return 0;
}