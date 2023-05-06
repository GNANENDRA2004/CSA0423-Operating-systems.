#include <stdio.h>

#define MAX_PROCESS 10
#define TIME_QUANTUM 2

struct process {
    int pid;
    int burst_time;
    int remaining_time;
};

int main() {
    int n, i, time = 0, total_burst_time = 0;
    float avg_waiting_time = 0, avg_turnaround_time = 0;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct process p[MAX_PROCESS];

    for (i = 0; i < n; i++) {
        printf("Enter the burst time for process %d: ", i + 1);
        scanf("%d", &p[i].burst_time);
        p[i].pid = i + 1;
        p[i].remaining_time = p[i].burst_time;
        total_burst_time += p[i].burst_time;
    }

    while (time < total_burst_time) {
        for (i = 0; i < n; i++) {
            if (p[i].remaining_time > 0) {
                if (p[i].remaining_time <= TIME_QUANTUM) {
                    time += p[i].remaining_time;
                    p[i].remaining_time = 0;
                    avg_waiting_time += time - p[i].burst_time;
                    avg_turnaround_time += time;
                } else {
                    time += TIME_QUANTUM;
                    p[i].remaining_time -= TIME_QUANTUM;
                    avg_waiting_time += time - p[i].burst_time;
                }
            }
        }
    }

    avg_waiting_time /= n;
    avg_turnaround_time /= n;

    printf("Average waiting time: %.2f\n", avg_waiting_time);
    printf("Average turnaround time: %.2f\n", avg_turnaround_time);

    return 0;
}
