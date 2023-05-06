#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NUM_PHILOSOPHERS 5
sem_t chopsticks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *(int *) arg;
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;
    while (1) {
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 5 + 1); 
        printf("Philosopher %d is hungry and waiting for chopsticks...\n", id);
        sem_wait(&chopsticks[left]); 
        sem_wait(&chopsticks[right]); 
        printf("Philosopher %d is eating...\n", id);
        sleep(rand() % 5 + 1); 
        sem_post(&chopsticks[left]); 
        sem_post(&chopsticks[right]); 
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];
    int i;
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_init(&chopsticks[i], 0, 1); 
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]); 
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL); 
    }
    for (i = 0; i < NUM_PHILOSOPHERS; i++) {
        sem_destroy(&chopsticks[i]); 
    }
    return 0;
}
