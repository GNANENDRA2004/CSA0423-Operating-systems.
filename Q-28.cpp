#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100

int main(int argc, char *argv[]) {
    // Check if pattern and file name are specified
    if (argc < 3) {
        printf("Usage: %s <pattern> <file>\n", argv[0]);
        return 1;
    }

    // Open the file for reading
    FILE *file;
    file = fopen(argv[2], "r");

    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    char line[MAX_LINE_LENGTH];
    int lineNum = 1;
    int found = 0;

    // Read each line from the file and search for the pattern
    while (fgets(line, sizeof(line), file) != NULL) {
        if (strstr(line, argv[1]) != NULL) {
            printf("%d: %s", lineNum, line);
            found = 1;
        }
        lineNum++;
    }

    // Close the file
    fclose(file);

    if (!found) {
        printf("Pattern not found.\n");
    }

    return 0;
}

