#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define NUM_READERS 3 // number of readers
#define NUM_WRITERS 2 // number of writers

int shared_resource = 0; // the shared resource
int num_readers = 0; // the number of active readers
sem_t resource_mutex; // protects access to shared resource
sem_t num_readers_mutex; // protects access to num_readers

void *reader(void *arg) {
    int id = *((int *)arg);
    while (1) {
        sem_wait(&num_readers_mutex); // acquire num_readers_mutex
        num_readers++; // increment num_readers
        if (num_readers == 1) {
            sem_wait(&resource_mutex); // if first reader, acquire resource_mutex
        }
        sem_post(&num_readers_mutex); // release num_readers_mutex

        // read shared resource
        printf("Reader %d read resource: %d\n", id, shared_resource);

        sem_wait(&num_readers_mutex); // acquire num_readers_mutex
        num_readers--; // decrement num_readers
        if (num_readers == 0) {
            sem_post(&resource_mutex); // if last reader, release resource_mutex
        }
        sem_post(&num_readers_mutex); // release num_readers_mutex

        // sleep for random interval to simulate other activity
        int sleep_time = rand() % 3;
        sleep(sleep_time);
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);
    while (1) {
        sem_wait(&resource_mutex); // acquire resource_mutex

        // write to shared resource
        shared_resource++;
        printf("Writer %d wrote resource: %d\n", id, shared_resource);

        sem_post(&resource_mutex); // release resource_mutex

        // sleep for random interval to simulate other activity
        int sleep_time = rand() % 3;
        sleep(sleep_time);
    }
    return NULL;
}

int main() {
    pthread_t readers[NUM_READERS];
    pthread_t writers[NUM_WRITERS];
    int i, reader_ids[NUM_READERS], writer_ids[NUM_WRITERS];

    sem_init(&resource_mutex, 0, 1);
    sem_init(&num_readers_mutex, 0, 1);

    for (i = 0; i < NUM_READERS; i++) {
        reader_ids[i] = i + 1;
        pthread_create(&readers[i], NULL, reader, &reader_ids[i]);
    }

    for (i = 0; i < NUM_WRITERS; i++) {
        writer_ids[i] = i + 1;
        pthread_create(&writers[i], NULL, writer, &writer_ids[i]);
    }

    for (i = 0; i < NUM_READERS; i++) {
        pthread_join(readers[i], NULL);
    }

    for (i = 0; i < NUM_WRITERS; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&resource_mutex);
    sem_destroy(&num_readers_mutex);

    return 0;
}

