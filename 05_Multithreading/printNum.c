#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

void *printNum(void *arg){
    long Num = *((long *)arg);
    for (long i=1; i<=Num; i++){
        printf("%ld\n", i);
    }
    return NULL;
}

int main(int argc, char *argv[]){
    long Num = strtol(argv[1], NULL, 10);
    pthread_t t;
    pthread_create(&t, NULL, printNum, &Num);
    pthread_join(t, NULL);
    printf("Main thread exiting.\n");
    return 0;
}