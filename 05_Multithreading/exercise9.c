#include<stdio.h>
#include<sys/wait.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

#define MAX_SIZE 5

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
int count ;

typedef struct {
    int num;
    pthread_t id;
} Data;

void *thread_pro(void *arg) {
    Data *infor = (Data *)arg;
    for (int i = 0; i < infor->num; i++) {
        // Add mutex
        pthread_mutex_lock(&lock);
        // Check cond
        while (count == MAX_SIZE) {
            // Enter wait
            pthread_cond_wait(&full, &lock);
        }
        // Out of wait
        printf("Making bread for store %ld\n", infor->id);
        sleep(1);
        count++;
        printf("Done!!\n");
        printf("Total cakes in store %ld is %d\n", infor->id, count);
        // Send signal
        if (count == MAX_SIZE - 4) {
            pthread_cond_signal(&empty);
        }
        //Unlock mutex
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *thread_con(void *arg) {
    Data *infor = (Data *)arg;
    for (int i = 0; i < infor->num; i++) {
        // Add mutex
        pthread_mutex_lock(&lock);
        // Check cond
        while (count == 0) {
            // Enter wait
            pthread_cond_wait(&empty, &lock);
        }
        // Out of wait
        printf("Taking bread from store %ld\n", infor->id);
        sleep(1);
        count--;
        printf("Total cakes in store %ld is %d\n", infor->id, count);
        // Send signal
        if (count == MAX_SIZE - 1) {
            pthread_cond_signal(&full);
        }
        //Unlock mutex
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

int main() {
    pthread_t t[2];
    Data infor[2];
    if (fork() == 0) {
        for (int i = 0; i < 2; i++) {
            infor[i].id = 1;
            infor[i].num = 15;
            if (i == 0) {
                pthread_create(&t[i], NULL, thread_pro, &infor[i]);
            } else {
                pthread_create(&t[i], NULL, thread_con, &infor[i]);
            }
        }
        // Wait for other thread
        for (int i =0; i < 2; i++) {
            pthread_join(t[i], NULL);
        }
        printf("Store 1 is closing!\n");
        //
        exit(0);
    }

    if (fork() == 0) {
        for (int i = 0; i < 2; i++) {
            infor[i].id = 2;
            infor[i].num = 10;
            if (i == 0) {
                pthread_create(&t[i], NULL, thread_pro, &infor[i]);
            } else {
                pthread_create(&t[i], NULL, thread_con, &infor[i]);
            }
        }
        // Wait for other thread
        for (int i =0; i < 2; i++) {
            pthread_join(t[i], NULL);
        }
        printf("Store 2 is closing!\n");
        //
        exit(0);
    }
    // Parent waits.
    wait(NULL);
    wait(NULL);
    return 0;
}