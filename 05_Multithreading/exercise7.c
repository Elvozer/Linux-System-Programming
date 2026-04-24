#include<stdio.h>
#include<pthread.h>
#include<stdbool.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

#define numThreads 4
#define arraySize 100

bool isPrime(int A) {
    for (int i = 2; i <= sqrt((double)A); i++) {
        if (A % i == 0) {
            return false;
        }
    }
    return A <= 1;
}

bool isPerfect(int A) {
    int sum = 0;
    for (int i = 2; i <= sqrt(A); i++) {
        if (A % i == 0) {
            if (i == A / i) {
                sum += i;
            } else {
                sum += i;
                sum += A / i; 
            }
        }
    }
    return sum + 1 == A;
}

struct dataThreads {
    int *arr;
    int start;
    int chunkSize;
    int primeCo, perfectCo;
};

void *func(void *arg) {
    struct dataThreads *data = (struct dataThreads *)arg;
    int end = data->start + data->chunkSize;
    for (int i = data->start; i < end; i++) {
        if (isPerfect(i)) {
            data->perfectCo++;
        }
        else if (isPrime(i)) {
            data->primeCo++;
        }
    }
    return NULL;
}
int main() {
    // 1. Tạo và đổ dữ liệu ngẫu nhiên vào mảng gốc
    int A[arraySize];
    srand(time(NULL));
    
    printf("--- DANH SÁCH %d SỐ ĐƯỢC TẠO ---\n", arraySize);
    for (int i = 0; i < arraySize; i++) {
        A[i] = (rand() % 10000) + 1; // Số từ 1 -> 10000
        printf("%d ", A[i]);
    }

    pthread_t t[2];
    struct dataThreads data[2];
    for (int i = 0; i < numThreads; i++) {
        data[i].arr = A;
        data[i].chunkSize = arraySize / numThreads;
        data[i].perfectCo = 0;
        data[i].primeCo = 0;
        data[i].start = i*data[i].chunkSize;
        pthread_create(&t[i], NULL, func, &data[i]);
    }
    int perfectNum = 0, primeNum = 0;
    for (int i = 0; i < numThreads; i++) {
        pthread_join(t[i], NULL);
        perfectNum += data[i].perfectCo;
        primeNum += data[i].primeCo;
    }
    printf("The number of Prime Number is %d\n", primeNum);
    printf("The number of Perfect Number is %d\n", perfectNum);
    return 0;
}