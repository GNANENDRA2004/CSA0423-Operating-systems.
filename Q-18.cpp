#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define BUFFER_SIZE 10 // buffer size
#define NUM_PRODUCERS 2 // number of producers
#define NUM_CONSUMERS 2 // number of consumers
#define NUM_ITEMS 20 // number of items to produce and consume

// shared buffer and associated variables
int buffer[BUFFER_SIZE];
int buffer_index = 0;
sem_t empty;
sem_t full;
pthread_mutex_t mutex;

void *producer(void *arg) {
    int i;
    for (i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&empty); // decrement empty
        pthread_mutex_lock(&mutex); // acquire mutex lock
        buffer[buffer_index++] = i; // add item to buffer
        printf("Producer %d produced %d\n", *((int *)arg), i);
        pthread_mutex_unlock(&mutex); // release mutex lock
        sem_post(&full); // increment full
    }
    return NULL;
}

void *consumer(void *arg) {
    int i, item;
    for (i = 0; i < NUM_ITEMS; i++) {
        sem_wait(&full); // decrement full
        pthread_mutex_lock(&mutex); // acquire mutex lock
        item = buffer[--buffer_index]; // remove item from buffer
        printf("Consumer %d consumed %d\n", *((int *)arg), item);
        pthread_mutex_unlock(&mutex); // release mutex lock
        sem_post(&empty); // increment empty
    }
    return NULL;
}

int main() {
    pthread_t producers[NUM_PRODUCERS];
    pthread_t consumers[NUM_CONSUMERS];
    int i, ids[NUM_PRODUCERS + NUM_CONSUMERS];

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    pthread_mutex_init(&mutex, NULL);

    for (i = 0; i < NUM_PRODUCERS; i++) {
        ids[i] = i + 1;
        pthread_create(&producers[i], NULL, producer, &ids[i]);
    }

    for (i = 0; i < NUM_CONSUMERS; i++) {
        ids[i + NUM_PRODUCERS] = i + 1;
        pthread_create(&consumers[i], NULL, consumer, &ids[i + NUM_PRODUCERS]);
    }

    for (i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producers[i], NULL);
    }

    for (i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&empty);
    sem_destroy(&full);
    pthread_mutex_destroy(&mutex);

    return 0;
}

