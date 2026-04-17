#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

long numelOfS;
int numOfThr, partSum[8], myid[8];
pthread_mutex_t lock;

void *sumMutex(void *arg){
    long myid = *((long *)arg);
    long start = myid * numelOfS + 1;
    long end = start + numelOfS;
    for(long i=start; i<end; i++){
        pthread_mutex_lock(&lock);
        partSum[myid] += i;
        
    }
}

int main(int argc, char *argv[]){
    long numEl = 1<<20;
    numOfThr = (int)strtol(argv[1], NULL, 10);
    numelOfS = numEl/numOfThr;
    pthread_t tid[8];
    for(int i=0; i<numOfThr; i++){
        myid[i] = i;
        pthread_create(&tid[i], NULL, sumMutex, &myid[i]);
    }
}