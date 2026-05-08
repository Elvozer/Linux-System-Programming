#include<stdio.h>
#include<pthread.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_writer = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_reader = PTHREAD_COND_INITIALIZER;

int shared_data = 0;
int readers = 0;
int writers = 0;

void *thread_reader(void *arg) {
    int id = *(int *)arg;
    pthread_mutex_lock(&lock);
    while (writers) {
        pthread_cond_wait(&cond_reader, &lock);
    }
    readers++;
    pthread_mutex_unlock(&lock);
    printf("Reader %d read: %d\n", id, shared_data);
    pthread_mutex_lock(&lock);
    readers--;
    if (readers == 0) {
        pthread_cond_broadcast(&cond_writer);
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void *thread_writer(void *arg) {
    int id = *(int *)arg;
    pthread_mutex_lock(&lock);
    while (writers || readers > 0) {
        pthread_cond_wait(&cond_writer, &lock);
    }
    writers++;
    shared_data += 10;
    pthread_mutex_unlock(&lock);

    printf("Writer %d writes: %d\n", id, shared_data);
    pthread_mutex_lock(&lock);
    writers--;
    pthread_cond_signal(&cond_writer);
    pthread_cond_broadcast(&cond_reader);
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    pthread_t rd[4], wr[2];
    int id_rd[4] = {1, 2, 3, 4};
    int id_wr[2] = {1, 2};
    for (int i = 0; i < 4; i++) {
        pthread_create(&rd[i], NULL, thread_reader, &id_rd[i]);
    }
    for (int i = 0; i < 2; i++) {
        pthread_create(&wr[i], NULL, thread_writer, &id_wr[i]);
    }
    for (int i = 0; i < 4; i++) {
        pthread_join(rd[i], NULL);
    }
    for (int i = 0; i < 2; i++) {
        pthread_join(wr[i], NULL);
    }
    return 0;
}