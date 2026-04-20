#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#define MAX_CAPACITY 5
// Shared Variables
int cakes_in_case = 0;
// Synchronization Primitives
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_baker = PTHREAD_COND_INITIALIZER;
pthread_cond_t cond_customer = PTHREAD_COND_INITIALIZER;
void* baker_thread(void* arg) {
    for (int i = 1; i <= 10; i++) {
    usleep(200000); // Simulate time taken to bake a cake (200ms)
    // --------------------------------------------------
    // TODO: Add synchronization logic here
    pthread_mutex_lock(&mutex);// 1. Lock the mutex.
    while(cakes_in_case == MAX_CAPACITY){
        pthread_cond_wait(&cond_baker, &mutex);
    }
    // 2. While cakes_in_case == MAX_CAPACITY, wait on cond_baker.
    cakes_in_case++;
    // 3. Increment cakes_in_case.
    printf("Baker baked cake %d. Case has %d cakes.\n", i, cakes_in_case);
    // 4. Print: “Baker baked cake %d. Case has %d cakes.\n”
    pthread_cond_signal(&cond_customer);
    // 5. Signal the customer (cond_customer) that a cake is available.
    pthread_mutex_unlock(&mutex);
    // 6. Unlock the mutex.
    // --------------------------------------------------
}
return NULL;
}
void* customer_thread(void* arg) {
    for (int i = 1; i <= 10; i++) {
    usleep(300000); // Simulate time taken to eat/decide (300ms)
    // --------------------------------------------------
    // TODO: Add synchronization logic here
    pthread_mutex_lock(&mutex);
    // 1. Lock the mutex.
    while(cakes_in_case == 0){
        pthread_cond_wait(&cond_customer, &mutex);
    }
    // 2. While cakes_in_case == 0, wait on cond_customer.
    cakes_in_case--;
    // 3. Decrement cakes_in_case.
    printf("Customer bought a cake. Case has %d cakes.\n", cakes_in_case);
    // 4. Print: "Customer bought a cake. Case has %d cakes.\n"
    pthread_cond_signal(&cond_baker);
    // 5. Signal the baker (cond_baker) that there is free space.
    pthread_mutex_unlock(&mutex);
    // 6. Unlock the mutex.
    // --------------------------------------------------
        }
    return NULL;
}
int main() {
    // --------------------------------------------------
    // Expected Output: Output order might look slightly different
    printf("Bakery is opening!\n");
    pthread_t cus, bak;
    pthread_create(&bak, NULL, baker_thread, NULL);
    pthread_create(&cus, NULL, customer_thread, NULL);
    pthread_join(bak, NULL);
    pthread_join(cus, NULL);
    printf("Bakery is closing! All cakes sold out.\n");
    // Bakery is opening!
    return 0;
}