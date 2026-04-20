#include<stdio.h>
#include<pthread.h>

int main(){
    int arr[20], n = 4, start;
    srand(time(NULL));
    printf("The array is: ");
    for (int i = 0; i < 20; i++) {
        arr[i] = rand() % 5; // 0 → 4
        printf("%d ", arr[i]);
    }
    printf("\n");
    pthread_t id[n];
    for(int i=0; i<n; i++){
        start = i*5;
        pthread_create(&id[i], NULL, )
    }
}