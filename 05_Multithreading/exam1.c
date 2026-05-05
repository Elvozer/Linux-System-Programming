#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>
#include<time.h>

#define ARRAY_SIZE 1000
#define K 4

typedef struct {
    int id_thread;
    int start;
    int end;
    int *Arr;
} data_input;

typedef struct {
    int alert_count;
    int total_temp;
    int index_min;
} data_output;

void *thread_func(void *arg) {
    data_input input = (*(data_input *)arg);
    // Initializes struct for output
    data_output *output = (data_output *)(sizeof(data_output)));
    // Check for infor
    for (int i = input; i < end; i++) {
        
    }
}
int Arr[ARRAY_SIZE] = {0};

int main() {
    srand(time(NULL)); // seed random

    for (int i = 0; i < 1000; i++) {
        Arr[i] = rand(); // random số nguyên
    }
    // Array stores id_thread
    pthread_t t[4];
    // Create 4 threads
    for (int i = 0; i < K; i++) {
        pthread_create(&t[i], NULL, )
    }

}