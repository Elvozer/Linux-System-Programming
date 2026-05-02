#include<stdio.h>
#include<unistd.h>
#include<pthread.h>
#include<stdlib.h>

#define MAX_SIZE 5

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t data_available = PTHREAD_COND_INITIALIZER;
pthread_cond_t space_available = PTHREAD_COND_INITIALIZER;

typedef struct {
    int packet_id;
    int data;
} Packet;

Packet ring_buffer[MAX_SIZE];

int head = 0;
int tail = 0;
int count = 0;
int total_packet = 10;

void *thread_pro (void *arg) {
    int i = 0;
    // Create new packet.
    while(total_packet) {
        Packet new_packet;
        new_packet.packet_id = i + 1;
        new_packet.data = rand() % 100;
        // Lock door.
        pthread_mutex_lock(&lock);
        // Check cond if full data
        while (count == MAX_SIZE) {
            printf("Wait for the space...\n");
            pthread_cond_wait(&space_available, &lock);
        }
        // Add data into buffer
        printf("Adding data to the buffer...\n");
        ring_buffer[tail] = new_packet;
        tail = (tail + 1) % MAX_SIZE;
        // Increasing number of packets.
        count++; 
        // Reducing total packets.
        total_packet--;
        // Wake up consumer
        pthread_cond_signal(&data_available);
        // Unlock door
        pthread_mutex_unlock(&lock);

        sleep(1);
    }
    return NULL;
}

void *thread_con (void *arg) {
    while (total_packet) {
        pthread_mutex_lock(&lock);
        // Check cond if no data
        while (count == 0) {
            printf("Wait for data...\n");
            pthread_cond_wait(&data_available, &lock);
        }
        // Read data from buffer
        printf("The packet having id %d has data is %d\n", ring_buffer[head].packet_id, ring_buffer[head].data);
        head = (head + 1) % MAX_SIZE;
        //Decreasing number of packets.
        count--;
        // Wake up producer.
        pthread_cond_signal(&space_available);
        // Unlock door.
        pthread_mutex_unlock(&lock);

        sleep(1);
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thread_con, NULL);
    pthread_create(&t2, NULL, thread_pro, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}

