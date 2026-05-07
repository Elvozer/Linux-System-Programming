#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

#define N 4

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t signal = PTHREAD_COND_INITIALIZER;

int arrived = 0;

void *thread_func (void *arg) {
    int id = *(int *)arg;
    printf("Thread %d doing Phase 1\n", id);
    pthread_mutex_lock(&lock);
    arrived++;
    if (arrived == N) pthread_cond_broadcast(&signal);
    else {
        while (arrived != N) {
            pthread_cond_wait(&signal, &lock);
        }
    }
    pthread_mutex_unlock(&lock);
    printf("Thread %d doing Phase 2\n");
    return NULL;
}
int main() {
    if (fork() == 0) {
        printf("I am a child 1.\n");
        exit(0);
    }
    if (fork() == 0) {
        printf("Im a child 2.\n");
        exit(0);
    }
    wait(NULL);
    wait(NULL);
    printf("Parent complete\n");
    return 0;
}