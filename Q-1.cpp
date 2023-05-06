#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t child_pid, parent_pid;

    child_pid = fork();

    if (child_pid == 0) { // child process
        printf("Child process: PID=%d, Parent PID=%d\n", getpid(), getppid());
    } else if (child_pid > 0) { // parent process
        printf("Parent process: PID=%d, Child PID=%d\n", getpid(), child_pid);
    } else { // fork failed
        printf("Failed to create new process.\n");
        return 1;
    }

    return 0;
}
