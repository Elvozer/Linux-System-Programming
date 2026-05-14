#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

typedef struct {
    int start, end;
    int *Arr;
    int n;
} Args;

int global_sum;

void *thread_func(void *arg) {
    Args *ar = (Args *)arg;
    int sum_local = 0;
    for (int i = ar->start; i <= ar->end; i++) {
        for (int j = 0; j < ar->n; j++) {
            sum_local += ar->Arr[i * ar->n + j];
        }
    }
    pthread_mutex_lock(&lock);
    global_sum += sum_local;
    pthread_mutex_unlock(&lock);
    return NULL;
}

int main() {
    int m, n;
    scanf("%d %d", &m, &n);
    int Arr[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &Arr[i][j]);
        }
    }
    int num_thread;
    scanf("%d", &num_thread);
    pthread_t t[num_thread];
    Args arg[num_thread];
    for (int i = 0; i < num_thread; i++) {
        arg[i].start = (i * (m / num_thread));
        if (i == num_thread - 1) {
            arg[i].end = m - 1;
        } else {
            arg[i].end = (i + 1)*(m / num_thread) - 1;
        }
        arg[i].n = n;
        arg[i].Arr = (int *)Arr;
        pthread_create(&t[i], NULL, thread_func, &arg[i]);
    }
    for (int i = 0; i < num_thread; i++) {
        pthread_join(t[i], NULL);
    }
    printf("%d\n", global_sum);
    return 0;
}