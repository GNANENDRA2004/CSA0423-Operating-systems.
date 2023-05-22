#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;
int in = 0;
int out = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int item;

    for (int i = 0; i < BUFFER_SIZE * 2; i++) {
        item = rand() % 100; // Generate a random item

        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            pthread_cond_wait(&full, &mutex);
        }

        buffer[in] = item;
        printf("Produced item: %d\n", item);

        in = (in + 1) % BUFFER_SIZE;
        count++;

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;

    for (int i = 0; i < BUFFER_SIZE * 2; i++) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            pthread_cond_wait(&empty, &mutex);
        }

        item = buffer[out];
        printf("Consumed item: %d\n", item);

        out = (out + 1) % BUFFER_SIZE;
        count--;

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producerThread, consumerThread;

    // Create producer and consumer threads
    if (pthread_create(&producerThread, NULL, producer, NULL) != 0) {
        perror("Error creating producer thread");
        return 1;
    }

    if (pthread_create(&consumerThread, NULL, consumer, NULL) != 0) {
        perror("Error creating consumer thread");
        return 1;
    }

    // Wait for the threads to finish
    if (pthread_join(producerThread, NULL) != 0) {
        perror("Error joining producer thread");
        return 1;
    }

    if (pthread_join(consumerThread, NULL) != 0) {
        perror("Error joining consumer thread");
        return 1;
    }

    return 0;
}

