#include<stdio.h>
#include<pthread.h>

pthread_mutex_t lock;

typedef struct {
    int *Arr;
    int cond = 1;
} Foo;

void *print_first (void *arg) {
    Foo *arr = (Foo *)arg;
    while (1) {
        if (arr->cond == 1) {
            printf("first");
            arr->cond++;
            break;
        }
    }
    return NULL;
}

void *print_Second (void *arg) {
    Foo *arr = (Foo *)arg;
    while (1) {
        if (arr->cond == 2) {
            printf("second");
            arr->cond++;
            break;
        }
    }
    return NULL;
}

void *print_third (void *arg) {
    Foo *arr = (Foo *)arg;
    while (1) {
        if (arr->cond == 3) {
            printf("third");
            arr->cond++;
            break;
        }
    }
    return NULL;
}

int main () {
    pthread_t t1, t2, t3;
    arr[] = {}
    Foo data
    pthread_create(t1, NULL, print_first, )
}