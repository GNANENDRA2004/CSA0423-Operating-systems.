#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#define MSG_SIZE 1024
struct message {
    long mtype;
    char mtext[MSG_SIZE];
};
int main() {
    int msqid;
    key_t key;
    struct message msg;
    key = ftok(".", 'a');
    msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid < 0) {
        perror("msgget");
        exit(1);
    }
    msg.mtype = 1;
    strcpy(msg.mtext, "Hello, world!");
    if (msgsnd(msqid, &msg, strlen(msg.mtext) + 1, 0) < 0) {
        perror("msgsnd");
        exit(1);
    }
    if (msgrcv(msqid, &msg, MSG_SIZE, 0, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }
    printf("Received message: %s\n", msg.mtext);
    if (msgctl(msqid, IPC_RMID, NULL) < 0) {
        perror("msgctl");
        exit(1);
    }

    return 0;
}
