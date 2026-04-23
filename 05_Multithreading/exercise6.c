#include<stdio.h>
#include<pthread.h>

struct infor {
    int start;
    int end;
    int local_max;
    int *arr;
};

void *findMax(void *arg) {
    struct infor *data = (struct infor *)arg;
    data->local_max = data->arr[data->start];
    for (int i=data->start; i<data->end; i++) {
        if (i > data->local_max) {
            data->local_max = i;
        }
    }
    return NULL;
}

int main(){
    int A[] = {0, 1, 4, 6, 8, 9, 4, 5, 2, 1};
    int chunk = sizeof(A)/sizeof(A[0])/2;
    printf("%d\n", chunk);
    pthread_t t[2];
    struct infor data[2];
    for(int i=0; i<2; i++){
        data[i].arr = A;
        data[i].start = i*(chunk);
        data[i].end =  (i+1)*chunk;
        pthread_create(&t[i], NULL, findMax, &data[i]);
    }
    for (int i=0; i<2; i++) {
        pthread_join(t[i], NULL);
    }
    if (data[0].local_max > data[1].local_max) {
        printf("The maxium value is %d\n", data[0].local_max);
    }
    else {
        printf("The maxium value is %d\n", data[1].local_max);
    }
    return 0;
}