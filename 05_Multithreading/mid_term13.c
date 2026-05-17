#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
int global_count = 0;

typedef struct {
    int *Arr;
    int start, end;
} Args;

int is_prime(int n) {
    if (n <= 1) return 0; // 0 và 1 không phải số nguyên tố
    for (int i = 2; i * i <= n; i++) { // Tối ưu: chỉ chạy đến căn bậc 2 của n
        if (n % i == 0) return 0; 
    }
    return 1;
}

int is_Super_Prime(int n) {
    return is_prime(n) && is_prime(n / 10);
}
void *thread_func(void *arg) {
    Args *ap = (Args *)arg;
    int start = ap->start;
    int end = ap->end;
    int *Arr = ap->Arr;
    int local_count = 0;
    for (int i = start; i <= end; i++) {
        if (is_Super_Prime(Arr[i])) {
            local_count++;
        }
    }
    pthread_mutex_lock(&lock);
    global_count += local_count;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    int K, N;
    scanf("%d %d", &K, &N);
    int Arr[N];
    for (int i = 0; i < N; i++) {
        scanf("%d", &Arr[i]);
    }
    pthread_t t[K];
    Args arg[K];
    int chunk = N / K;
    for (int i = 0; i < K; i++) {
        arg[i].Arr = Arr;
        arg[i].start = i * chunk;
        if (i == K - 1) {
            arg[i].end = N - 1;
        } else {
            arg[i].end = (i + 1) * chunk - 1;
        }
        pthread_create(&t[i], NULL, thread_func, &arg[i]);
    }
    for (int i = 0; i < K; i++) {
        pthread_join(t[i], NULL);
    }
    printf("%d\n", global_count);
    return 0;
}