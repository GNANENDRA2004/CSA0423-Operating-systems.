#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#define SHM_SIZE 1024
int main() {
    int shmid;
    key_t key;
    char *shm, *s;
    key = ftok(".", 'a');
    shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("shmget");
        exit(1);
    }
    shm = shmat(shmid, NULL, 0);
    if (shm == (char *) -1) {
        perror("shmat");
        exit(1);
    }
    strcpy(shm, "Hello, world!");
    for (s = shm; *s != '\0'; s++) {
        putchar(*s);
    }
    putchar('\n');
    shmdt(shm);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
