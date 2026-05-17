#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

typedef struct {
    int *Arr;
    int start, end;
    int n;
} Args;

int global_peak_count = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *thread_func(void *arg) {
    Args *ap = (Args *)arg;
    
    // Đã được xử lý sạch sẽ từ main, không cần +1 hay -1 gì ở đây nữa
    int start = ap->start; 
    int end = ap->end;
    int n = ap->n;
    int *Arr = ap->Arr;
    
    int local_peak = 0; // Biến cục bộ để tối ưu Mutex (quan trọng!)

    // Kiểm tra an toàn: nếu start > end thì luồng này không cần làm gì cả
    if (start > end) return NULL; 

    for (int j = start; j <= end; j++) {
        for (int i = 1; i < n - 1; i++) { // Cắt viền trái/phải ở đây
            // Gộp if cho gọn mắt
            if (Arr[j * n + i] > Arr[j * n + i + 1] && 
                Arr[j * n + i] > Arr[j * n + i - 1] &&
                Arr[j * n + i] > Arr[(j + 1) * n + i] && 
                Arr[j * n + i] > Arr[(j - 1) * n + i]) {
                
                local_peak++; // Cộng vào biến cục bộ
            }
        }
    }
    
    // Ra khỏi 2 vòng lặp mới được khóa Mutex ĐÚNG 1 LẦN
    pthread_mutex_lock(&lock);
    global_peak_count += local_peak;
    pthread_mutex_unlock(&lock);
    
    return NULL;   
}

int main() {
    int M, N, K;
    if (scanf("%d %d %d", &M, &N, &K) != 3) return 1;
    
    int Arr[M][N];
    for (int i = 0; i < M; i++) {
        for (int j = 0; j < N; j++) {
            scanf("%d", &Arr[i][j]);
        }
    }
    
    Args arg[K];
    pthread_t t[K];
    int chunk = M / K;
    
    for (int i = 0; i < K; i++) {
        arg[i].Arr = (int *)Arr;
        arg[i].n = N; // BẮT BUỘC PHẢI CÓ DÒNG NÀY
        
        // 1. Chia toán học thuần túy
        arg[i].start = i * chunk;
        if (i == K - 1) {
            arg[i].end = M - 1;
        } else {
            arg[i].end = (i + 1) * chunk - 1;
        }
        
        // 2. Gọt viền trên/dưới (Ép giới hạn)
        if (arg[i].start == 0) {
            arg[i].start = 1; // Né hàng 0
        }
        if (arg[i].end == M - 1) {
            arg[i].end = M - 2; // Né hàng cuối
        }
        
        pthread_create(&t[i], NULL, thread_func, &arg[i]);
    }
    
    for (int i = 0; i < K; i++) {
        pthread_join(t[i], NULL);
    }
    
    printf("%d\n", global_peak_count);
    return 0;
}