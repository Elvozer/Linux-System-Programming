#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void *sum(void *arg){
    long *result = (long *)malloc(sizeof(long));
    *result = 0;
    long num = *((long*)arg);
    for (long i=1; i<=num; i++){
        *result += i;
    }
    return result;
}

int main(int argc, char *argv[]){
    long num = strtol(argv[1], NULL, 10);
    void *result;
    pthread_t t;
    pthread_create(&t, NULL, sum, &num);
    pthread_join(t, &result);
    printf("The result is %ld\n", *(long*)result);
    free(result);
    return 0;
}
