#include <stdio.h>

#define MAX_BLOCKS 100
#define MAX_PROCESSES 100

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[MAX_PROCESSES], i, j;

    for (i = 0; i < n; i++) {
        allocation[i] = -1;
        for (j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    printf("\nProcess No.\tProcess Size\tBlock no.\n");
    for (i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1) {
            printf("%d\n", allocation[i] + 1);
        } else {
            printf("Not Allocated\n");
        }
    }
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_PROCESSES], m, n, i;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &m);
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    printf("Enter the sizes of memory blocks: \n");
    for (i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the sizes of processes: \n");
    for (i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    firstFit(blockSize, m, processSize, n);

    return 0;
}

