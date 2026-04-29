#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t lock;

typedef struct {
    int *Arr;
    int cond;
} Foo;

void *print_first (void *arg) {
    Foo *arr = (Foo *)arg;
    // Function's value.
    int local = 1, index;
    // Find index.

    for (int i = 0; i < 3; i++) {
        if (local == arr->Arr[i]) {
            index = i;
            break;
        }
    }
    while (1) {
        pthread_mutex_lock(&lock);
        // Check cond.
        if (arr->cond == index) {
            // Add mutex.
            printf("first");
            arr->cond++;
            // Unlock mutex.
            pthread_mutex_unlock(&lock);
            break;
        } else {
            pthread_mutex_unlock(&lock);
        }
        usleep(100);
    }
    return NULL;
}

void *print_second (void *arg) {
    Foo *arr = (Foo *)arg;
    // Function's value.
    int local = 2, index;
    // Find index.

    for (int i = 0; i < 3; i++) {
        if (local == arr->Arr[i]) {
            index = i;
            break;
        }
    }
    while (1) {
        pthread_mutex_lock(&lock);
        // Check cond.
        if (arr->cond == index) {
            // Add mutex.
            printf("second");
            arr->cond++;
            // Unlock mutex.
            pthread_mutex_unlock(&lock);
            break;
        } else {
            pthread_mutex_unlock(&lock);
        }
        usleep(100);
    }
    return NULL;
}

void *print_third (void *arg) {
    Foo *arr = (Foo *)arg;
    // Function's value.
    int local = 3, index;
    // Find index.

    for (int i = 0; i < 3; i++) {
        if (local == arr->Arr[i]) {
            index = i;
            break;
        }
    }
    while (1) {
        // Add mutex.
        pthread_mutex_lock(&lock);
        // Check cond.
        if (arr->cond == index) {
            // Add mutex.
            printf("third");
            arr->cond++;
            // Unlock mutex.
            pthread_mutex_unlock(&lock);
            break;
        } else {
            pthread_mutex_unlock(&lock);
        }
        usleep(100);
    }
    return NULL;
}

int main () {
    pthread_t t1, t2, t3;
    int arr[] = {3, 1, 2};
    Foo data;
    pthread_mutex_init(&lock, NULL);
    data.cond = 0;
    data.Arr = arr;
    pthread_create(&t1, NULL, print_first, &data);
    pthread_create(&t2, NULL, print_second, &data);
    pthread_create(&t3, NULL, print_third, &data);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);
    pthread_mutex_destroy(&lock);
    return 0;
}