#include<stdio.h>
#include<pthread.h>
#include <stdlib.h>
#include <time.h>

struct infor {
    int *A;
    int res[5];
    int start;
    int chunkSize;
};

struct infor data[4] = {0};

void *compare(void *arg){
    struct infor *data = (struct infor *)arg;
    int i = 0;
    while(i != data->chunkSize){
        data->res[data->A[data->start + i]]++;
        i++;
    }
    return NULL;
}

int main(){
    int arr[20], n = 4, start;
    srand(time(NULL));
    printf("The array is: ");
    for (int i = 0; i < 20; i++) {
        arr[i] = rand() % 5; // 0 → 4
        printf("%d ", arr[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++){
        data[i].A = arr;
    }
    pthread_t id[n];
    for(int i=0; i<n; i++){
        data[i].chunkSize = 20/n;
        data[i].start = i*5;
        pthread_create(&id[i], NULL, compare, &data[i]);
    }
    for(int i=0; i<n; i++){
        pthread_join(id[i], NULL);
    }
    int global_histogram[5] = {0};

    for (int i = 0; i < n; i++){
        for (int j = 0; j < data[0].chunkSize; j++){
            global_histogram[j] += data[i].res[j];
        }
    }
    for(int i=0; i < data[i].chunkSize; i++){
        printf("Number %d has f is: %d\n", i, global_histogram[i]); 
    }
    return 0;
}