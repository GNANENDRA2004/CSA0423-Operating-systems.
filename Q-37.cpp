#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the absolute difference between two numbers
int absDiff(int a, int b) {
    return abs(a - b);
}

// Function to calculate the total head movement for FCFS algorithm
int calculateTotalHeadMovement(int initialHeadPosition, int requests[], int numRequests) {
    int totalHeadMovement = 0;
    int currentHeadPosition = initialHeadPosition;

    for (int i = 0; i < numRequests; i++) {
        totalHeadMovement += absDiff(requests[i], currentHeadPosition);
        currentHeadPosition = requests[i];
    }

    return totalHeadMovement;
}

int main() {
    int numRequests;
    int initialHeadPosition;

    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    int* requests = (int*)malloc(numRequests * sizeof(int));

    printf("Enter the disk requests: ");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &initialHeadPosition);

    int totalHeadMovement = calculateTotalHeadMovement(initialHeadPosition, requests, numRequests);

    printf("Total head movement: %d\n", totalHeadMovement);

    free(requests);

    return 0;
}

