#include<pthread.h>
#include<stdio.h>

void *print(void *arg){
    char *s = (char *)arg;
    pthread_t t;
    t = pthread_self();
    printf("My message is %s and my thread ID is %ld\n", s, t);
    return NULL;
}

int main(){
    pthread_t t1, t2, t3;
    pthread_create(&t1, NULL, print, "hello");
    pthread_create(&t2, NULL, print, "hi");
    pthread_create(&t3, NULL, print, "hallo");
    printf("Main thread is running\n");
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    return 0;
}