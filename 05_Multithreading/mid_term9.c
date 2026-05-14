#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

int global_prime_max;

typedef struct {
    int *Arr;
    int start, end;
    int n;
} Args;

int is_prime(int n) {
    int count = 0;
    for (int i = 1; i <= n; i++) {
        if (n % i == 0) {
            count++;
        }
    }
    if (count == 2) {
        return 1;
    }
    return 0;
}
    void *thread_func(void *arg) {
    Args *ap = (Args *)arg;
    int local_prime_max = -1; // Khởi tạo bằng -1 cho chuẩn bài
    
    for (int i = ap->start; i <= ap->end; i++) {
        for (int j = 0; j < ap->n; j++) {
            int current_val = *(ap->Arr + i * ap->n + j); // Lưu vào biến cho dễ đọc
            
            // Cứ là số nguyên tố VÀ lớn hơn max hiện tại thì múc
            if (is_prime(current_val) && current_val > local_prime_max) {
                local_prime_max = current_val;
            }
        }
    }
    
    // Khóa mutex và chốt sổ
    pthread_mutex_lock(&lock);
    if (local_prime_max > global_prime_max) {
        global_prime_max = local_prime_max;             
    }
    pthread_mutex_unlock(&lock);
    
    return NULL;
}

int main() {
    global_prime_max = -1;
    int m, n, K;
    scanf("%d %d %d", &m, &n, &K);
    int Arr[m][n];
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &Arr[i][j]);
        }
    }
    Args arg[K];
    pthread_t t[K];
    for (int i = 0; i < K; i++) {
        arg[i].n = n;
        arg[i].start = i * (m / K);
        if (i == K - 1) {
            arg[i].end = m - 1;
        } else {
            arg[i].end = (i + 1)*(m / K) - 1;
        }
        arg[i].Arr = &Arr[0][0];
        pthread_create(&t[i], NULL, thread_func, &arg[i]); 
    }
    for (int i = 0; i < K; i++) {
        pthread_join(t[i], NULL);
    }
    printf("%d\n", global_prime_max);
    return 0;
}

