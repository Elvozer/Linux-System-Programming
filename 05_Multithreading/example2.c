#include<stdio.h>
#include<pthread.h>
#include<stdlib.h>

#define BALANCE 1000
#define NUM_TRANS 5
#define NUM_ACC 2

typedef struct {
    char action;
    int acc1;
    int acc2;
    int amount;
} Transfer;

typedef struct {
    pthread_mutex_t lock_acc;
    int balance;
    int id;
} Account;

typedef struct {
    Transfer buffer[NUM_TRANS];
    pthread_mutex_t lock_buf;
    int index;
} Buffer;

typedef struct {
    Buffer *buf;
    Account *acc;
} Thread_Args;

void account_init(Account *acc) {
    for (int i = 0; i < NUM_ACC; i++) {
        pthread_mutex_init(&acc[i].lock_acc, NULL);
        acc[i].balance = BALANCE;
        acc[i].id = i;
    }
}

void buffer_init(Buffer *ptr) {
    pthread_mutex_init(&ptr->lock_buf, NULL);
    ptr->index = 0;
}

void take_buffer(Buffer *buf, Transfer *res) {
    pthread_mutex_lock(&buf->lock_buf);
    *res = buf->buffer[buf->index];
    buf->index = (buf->index + 1);
    pthread_mutex_unlock(&buf->lock_buf);
}

void *thread_func(void *arg) {
    Thread_Args *ptr = (Thread_Args *)arg;
    Transfer res; 
    Account *acc = ptr->acc;
    Buffer *buf = ptr->buf;
    take_buffer(buf, &res);
    if (res.acc2 == -1) {
        if (res.action == 'D') {
            pthread_mutex_lock(&acc[res.acc1].lock_acc);
            acc[res.acc1].balance += res.amount;
            printf("Deposit  vào acc%d: +%d  | acc%d=%d\n", res.acc1, res.amount, res.acc1, acc[res.acc1].balance);
            pthread_mutex_unlock(&acc[res.acc1].lock_acc);
        } 
        else if (res.action == 'W') {
            pthread_mutex_lock(&acc[res.acc1].lock_acc);
            if (acc[res.acc1].balance < res.amount) {
                pthread_mutex_unlock(&acc[res.acc1].lock_acc);
                printf("Khong du tien de rut.\n");
                return NULL;
            }
            acc[res.acc1].balance -= res.amount;
            printf("Withdraw tu acc%d: -%d  | acc%d=%d\n", res.acc1, res.amount, res.acc1, acc[res.acc1].balance);
            pthread_mutex_unlock(&acc[res.acc1].lock_acc);
        }
    }
    else {
        int id1 = res.acc1;
        int id2 = res.acc2;
        pthread_mutex_t *fir_lock = &acc[res.acc1].lock_acc;
        pthread_mutex_t *sec_lock = &acc[res.acc2].lock_acc;
        if (id1 > id2) {
            pthread_mutex_t *temp = &acc[res.acc1].lock_acc;
            fir_lock = sec_lock;
            sec_lock = temp;
        }
        pthread_mutex_lock(fir_lock);
        pthread_mutex_lock(sec_lock);
        if (acc[res.acc1].balance < res.amount) {
            pthread_mutex_unlock(sec_lock);
            pthread_mutex_unlock(fir_lock);
            printf("Khong du tien de chuyen.\n");
            return NULL;
        }
        acc[res.acc1].balance -= res.amount;
        acc[res.acc2].balance += res.amount;
        printf("Transfer acc%d→acc%d: %d | acc%d=%d, acc%d=%d\n", res.acc1, res.acc2, res.amount, res.acc1, acc[res.acc1].balance, res.acc2, acc[res.acc2].balance);
        pthread_mutex_unlock(sec_lock);
        pthread_mutex_unlock(fir_lock);
    }
    return NULL;
}

int main() {
    Buffer buf;
    buffer_init(&buf);
    for (int i = 0; i < NUM_TRANS; i++) {
        printf("Nhap giao dich vao:\n");
        scanf(" %c %d %d %d", &buf.buffer[i].action, &buf.buffer[i].acc1, &buf.buffer[i].acc2, &buf.buffer[i].amount);
    }
    Account acc[NUM_ACC];
    account_init(acc);
    pthread_t t[NUM_TRANS];
    Thread_Args a[NUM_TRANS];
    for (int i = 0; i < NUM_TRANS; i++) {
        a[i].buf = &buf;
        a[i].acc = acc;
        pthread_create(&t[i], NULL, thread_func, &a[i]);
    }
    for (int i = 0; i < NUM_TRANS; i++) {
        pthread_join(t[i], NULL);
    }
    return 0;
}