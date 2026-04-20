#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define size 5

pthread_mutex_t lock;
int totalSum = 0;

void *sumOfArr(void *arg){
    int *res = (int *)malloc(sizeof(int));
    *res = 0;
    int *Arr = ((int *)arg);
    for (int i=0; i<size; i++){
        *res += *(Arr+i);
    }
    pthread_mutex_lock(&lock);
    totalSum += *res;
    pthread_mutex_unlock(&lock);
    return res;
}

int main(){
    int A[] = {1, 2, 3, 4, 5}, B[] = {6, 7, 8, 9, 10};
    pthread_t t1, t2;
    void *res1, *res2;
    pthread_mutex_init(&lock, NULL);
    pthread_create(&t1, NULL, sumOfArr, A);
    pthread_create(&t2, NULL, sumOfArr, B);
    pthread_join(t1, &res1);
    pthread_join(t2, &res2);
    printf("Sum of A: %d\n", *(int *)res1);
    printf("Sum of B: %d\n", *(int *)res2);
    printf("Total sum: %d\n", totalSum);
    free(res1);
    free(res2);
    pthread_mutex_destroy(&lock);
    return 0;
}