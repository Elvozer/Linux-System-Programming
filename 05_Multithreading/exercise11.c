#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define MAX_SIZE 20

pthread_mutex_t lock;
pthread_cond_t sig;

typedef struct {
    int packet_id;
    int data[50];
    int checkSum;
} Packet;

Packet ring_buffer[MAX_SIZE];

int head = 0;
int tail = 0;
int count = 0;

void *thread_pro (void *arg) {
    Packet *data = (Packet *)arg;
    int i = 0;
    pthread_mutex_lock(&lock);
    // Create new packet.
    while(1) {
        Packet new_data;
        new_data.packet_id = i + 1;
    }

}
