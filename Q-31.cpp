#include <stdio.h>

#define MAX_FRAMES 3
#define MAX_PAGES 10

int main() {
    int pages[MAX_PAGES];
    int frames[MAX_FRAMES];
    int pageHits = 0;
    int pageFaults = 0;
    int nextFrame = 0;
    int i, j;

    // Initialize pages and frames
    printf("Enter the reference string:\n");
    for (i = 0; i < MAX_PAGES; i++) {
        scanf("%d", &pages[i]);
    }

    for (i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    // Perform FIFO paging simulation
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

        // Page not found, replace the oldest page
        if (found == 0) {
            frames[nextFrame] = page;
            nextFrame = (nextFrame + 1) % MAX_FRAMES;
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

