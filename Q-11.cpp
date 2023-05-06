#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message(void *ptr) {
    char *message;
    message = (char *) ptr;
    printf("%s\n", message);
    pthread_exit(NULL);
}

int main() {
    pthread_t thread1, thread2;
    char *message1 = "Thread 1";
    char *message2 = "Thread 2";
    int rc;

    // Create thread 1
    rc = pthread_create(&thread1, NULL, print_message, (void *) message1);
    if (rc) {
        perror("pthread_create");
        exit(1);
    }

    // Create thread 2
    rc = pthread_create(&thread2, NULL, print_message, (void *) message2);
    if (rc) {
        perror("pthread_create");
        exit(1);
    }

    // Wait for threads to finish
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}
