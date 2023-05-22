#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define NUM_THREADS 5

// Function executed by each thread
void *threadFunction(void *arg) {
    int threadId = *(int *)arg;
    printf("Thread %d: Hello, World!\n", threadId);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[NUM_THREADS];
    int threadIds[NUM_THREADS];

    // Create threads
    for (int i = 0; i < NUM_THREADS; i++) {
        threadIds[i] = i;
        if (pthread_create(&threads[i], NULL, threadFunction, &threadIds[i]) != 0) {
            perror("Error creating thread");
            return 1;
        }
    }

    // Wait for threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        if (pthread_join(threads[i], NULL) != 0) {
            perror("Error joining thread");
            return 1;
        }
    }

    printf("All threads have completed.\n");

    return 0;
}

