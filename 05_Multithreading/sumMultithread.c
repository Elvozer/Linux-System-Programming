#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

long numelOfS;
long partSum[8] = {0}, myid[8];
int numOfThr;
pthread_mutex_t lock;

void *sumMutex(void *arg){
    long myid = *((long *)arg);
    long start = myid * numelOfS + 1;
    long end = start + numelOfS;
    for(long i=start; i<end; i++){
        partSum[myid] += i;
    }
}

int main(int argc, char *argv[]){
    long numEl = 1<<20, result = 0;
    numOfThr = (int)strtol(argv[1], NULL, 10);
    numelOfS = numEl/numOfThr;
    pthread_t tid[8];
    for(int i=0; i<numOfThr; i++){
        myid[i] = i;
        pthread_create(&tid[i], NULL, sumMutex, &myid[i]);
    }
    for(int i=0; i<numOfThr; i++){
        pthread_join(tid[i], NULL);
        result += partSum[i];
    }
    printf("Total sum is %ld\n", result);
    return 0;
}