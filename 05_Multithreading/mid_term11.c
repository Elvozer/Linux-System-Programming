#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int *Arr;
    int start, end;
} Args;

int global_count[10];

void *thread_func(void *arg) {
    Args *ap = (Args *)arg;
    int local_count[10] = {0};
    for (int i = ap->start; i <= ap->end; i++) {
        local_count[ap->Arr[i]]++;
    }
    pthread_mutex_lock(&lock);
    for (int i = 0; i <= 9; i++) {
        global_count[i] += local_count[i];
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    int N, K;
    scanf("%d %d", &N, &K);
    int Arr[N];
    Args arg[K];
    pthread_t t[K];
    for (int i = 0; i < N; i++) {
        scanf("%d", &Arr[i]);
    }
    for (int i = 0; i < K; i++) {
        int chunk = N / K;
        arg[i].Arr = Arr;
        arg[i].start = i * chunk;
        if (i == K - 1) {
        arg[i].end = N - 1; // Luồng cuối ôm hết đến phần tử cuối cùng
        } else {
        arg[i].end = (i + 1) * chunk - 1;
        }
        pthread_create(&t[i], NULL, thread_func, &arg[i]);
    }
    for (int i = 0; i < K; i++) {
        pthread_join(t[i], NULL);
    }
    for (int i = 0; i <= 9; i++) {
        printf("Ung vien %d: %d phieu\n", i, global_count[i]);
    }
    return 0;
}