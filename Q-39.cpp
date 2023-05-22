#include <stdio.h>
#include <stdlib.h>

// Function to sort an array of integers in ascending order
void sortArray(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// Function to find the index of the disk request just greater than the head position
int findNextRequestIndex(int requests[], int numRequests, int headPosition) {
    int nextIndex = -1;

    for (int i = 0; i < numRequests; i++) {
        if (requests[i] > headPosition) {
            nextIndex = i;
            break;
        }
    }

    // If no request found greater than head position, wrap around to the beginning
    if (nextIndex == -1) {
        nextIndex = 0;
    }

    return nextIndex;
}

// Function to simulate the C-SCAN disk scheduling algorithm
int simulateCSCAN(int requests[], int numRequests, int headPosition, int diskSize) {
    int totalHeadMovement = 0;

    // Sort the requests in ascending order
    sortArray(requests, numRequests);

    int nextIndex = findNextRequestIndex(requests, numRequests, headPosition);

    // Calculate head movement towards the end of the disk
    while (nextIndex != numRequests) {
        totalHeadMovement += abs(requests[nextIndex] - headPosition);
        headPosition = requests[nextIndex];
        nextIndex++;
    }

    // Calculate head movement from the beginning to the last request
    totalHeadMovement += (diskSize - 1 - headPosition);

    // Wrap around to the beginning of the disk
    totalHeadMovement += (diskSize - 1);

    // Calculate head movement for remaining requests
    nextIndex = 0;
    while (nextIndex < numRequests && requests[nextIndex] < headPosition) {
        totalHeadMovement += abs(requests[nextIndex] - headPosition);
        headPosition = requests[nextIndex];
        nextIndex++;
    }

    return totalHeadMovement;
}

int main() {
    int numRequests;
    int headPosition;
    int diskSize;

    printf("Enter the number of disk requests: ");
    scanf("%d", &numRequests);

    int* requests = (int*)malloc(numRequests * sizeof(int));

    printf("Enter the disk requests: ");
    for (int i = 0; i < numRequests; i++) {
        scanf("%d", &requests[i]);
    }

    printf("Enter the initial head position: ");
    scanf("%d", &headPosition);

    printf("Enter the disk size: ");
    scanf("%d", &diskSize);

    int totalHeadMovement = simulateCSCAN(requests, numRequests, headPosition, diskSize);

    printf("Total head movement: %d\n", totalHeadMovement);

    free(requests);

    return 0;
}

