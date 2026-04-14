#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

void *count_num(void *arg){
    printf("Starting to count!\n");
    for(int i=1; i<=4; i++){
        printf("%d\n", i);
        sleep(1);
        }
    printf("Finish!");
    return NULL;
}

int main(){
    pthread_t tid;
    pthread_create(&tid, NULL, count_num, NULL);
    pthread_join(tid, NULL);
    return 0;
}