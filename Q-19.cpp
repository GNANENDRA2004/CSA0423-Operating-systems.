#include <stdio.h>
#include <pthread.h>

#define NUM_THREADS 2

pthread_t threads[NUM_THREADS];
int shared_resource = 0;
pthread_mutex_t mutex;

void *thread_func(void *arg) {
    int thread_id = *(int *) arg;
    printf("Thread %d is attempting to acquire the mutex lock.\n", thread_id);
    pthread_mutex_lock(&mutex);
    printf("Thread %d has acquired the mutex lock.\n", thread_id);
    shared_resource++;
    printf("Thread %d has incremented the shared resource to %d.\n", thread_id, shared_resource);
    pthread_mutex_unlock(&mutex);
    printf("Thread %d has released the mutex lock.\n", thread_id);
    pthread_exit(NULL);
}

int main() {
    pthread_mutex_init(&mutex, NULL);
    int i, args[NUM_THREADS];
    for (i = 0; i < NUM_THREADS; i++) {
        args[i] = i;
        pthread_create(&threads[i], NULL, thread_func, (void *) &args[i]);
    }
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    pthread_mutex_destroy(&mutex);
    printf("Final value of shared resource: %d\n", shared_resource);
    return 0;
}

