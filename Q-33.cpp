#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

int main() {
    int pages[MAX_PAGES];
    int frames[MAX_FRAMES];
    int pageHits = 0;
    int pageFaults = 0;
    int nextUse[MAX_FRAMES];
    int i, j, k;

    // Initialize pages and frames
    printf("Enter the reference string:\n");
    for (i = 0; i < MAX_PAGES; i++) {
        scanf("%d", &pages[i]);
    }

    for (i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
        nextUse[i] = 0;
    }

    // Perform Optimal paging simulation
    for (i = 0; i < MAX_PAGES; i++) {
        int page = pages[i];
        int found = 0;

        // Check if page is already in a frame
        for (j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                found = 1;
                pageHits++;
                break;
            }
        }

        // Page not found, find optimal replacement
        if (found == 0) {
            int maxIndex = 0;
            int max = nextUse[0];

            for (j = 1; j < MAX_FRAMES; j++) {
                int foundNext = 0;
                for (k = i + 1; k < MAX_PAGES; k++) {
                    if (pages[k] == frames[j]) {
                        nextUse[j] = k;
                        foundNext = 1;
                        break;
                    }
                }
                if (foundNext == 0) {
                    max = nextUse[j];
                    maxIndex = j;
                    break;
                } else if (nextUse[j] > max) {
                    max = nextUse[j];
                    maxIndex = j;
                }
            }

            frames[maxIndex] = page;
            nextUse[maxIndex] = i;
            pageFaults++;
        }

        // Print current page frames
        printf("Page Frames: ");
        for (j = 0; j < MAX_FRAMES; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Page Hits: %d\n", pageHits);
    printf("Page Faults: %d\n", pageFaults);

    return 0;
}

