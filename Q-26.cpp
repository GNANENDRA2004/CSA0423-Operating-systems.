#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];
    char content[100];

    // Create a new file
    printf("Enter the name of the file to create: ");
    scanf("%s", filename);

    file = fopen(filename, "w");

    if (file == NULL) {
        perror("Error creating file");
        return 1;
    }

    printf("Enter the content to write in the file: ");
    scanf(" %[^\n]", content);

    fprintf(file, "%s", content);

    fclose(file);

    // Read file content
    printf("Reading file content:\n");

    file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);

    // Append content to the file
    printf("\nEnter additional content to append to the file: ");
    scanf(" %[^\n]", content);

    file = fopen(filename, "a");

    if (file == NULL) {
        perror("Error opening file for appending");
        return 1;
    }

    fprintf(file, "\n%s", content);

    fclose(file);

    // Delete the file
    if (remove(filename) != 0) {
        perror("Error deleting file");
        return 1;
    }

    printf("\nFile deleted successfully.\n");

    return 0;
}

