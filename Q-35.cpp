#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100

struct IndexBlock {
    int blockPointers[MAX_BLOCKS];
};

void writeFile(const char* filename, struct IndexBlock indexBlock, int numBlocks) {
    FILE* file = fopen(filename, "wb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write index block to the file
    fwrite(&indexBlock, sizeof(struct IndexBlock), 1, file);

    // Write block pointers to the file
    fwrite(indexBlock.blockPointers, sizeof(int), numBlocks, file);

    fclose(file);
}

void readFile(const char* filename, int numBlocks) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct IndexBlock indexBlock;

    // Read index block from the file
    fread(&indexBlock, sizeof(struct IndexBlock), 1, file);

    printf("File Pointers:\n");
    for (int i = 0; i < numBlocks; i++) {
        printf("Block %d: %d\n", i + 1, indexBlock.blockPointers[i]);
    }

    fclose(file);
}

int main() {
    struct IndexBlock indexBlock;
    int numBlocks;

    printf("Enter the number of blocks: ");
    scanf("%d", &numBlocks);

    if (numBlocks <= 0 || numBlocks > MAX_BLOCKS) {
        printf("Invalid number of blocks.\n");
        return 1;
    }

    // Input block pointers
    for (int i = 0; i < numBlocks; i++) {
        printf("Enter block pointer for Block %d: ", i + 1);
        scanf("%d", &indexBlock.blockPointers[i]);
    }

    // Write index block to the file
    writeFile("file.bin", indexBlock, numBlocks);

    printf("File created successfully.\n");

    // Read index block from the file
    readFile("file.bin", numBlocks);

    return 0;
}

