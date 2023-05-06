#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILENAME_LENGTH 256

int main(int argc, char *argv[]) {
    char filename[MAX_FILENAME_LENGTH];
    char new_filename[MAX_FILENAME_LENGTH];
    char *dir_name = "organized";
    FILE *file_ptr, *new_file_ptr;
    struct stat st = {0};

    // Check if the organized directory exists and create it if necessary
    if (stat(dir_name, &st) == -1) {
        mkdir(dir_name, 0700);
    }

    // Prompt the user for the file name
    printf("Enter the file name: ");
    scanf("%s", filename);

    // Open the file
    file_ptr = fopen(filename, "r");

    if (file_ptr == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    // Construct the new file name by prepending "organized/" to the original file name
    strcpy(new_filename, dir_name);
    strcat(new_filename, "/");
    strcat(new_filename, filename);

    // Open the new file for writing
    new_file_ptr = fopen(new_filename, "w");

    if (new_file_ptr == NULL) {
        printf("Error: Unable to create new file.\n");
        fclose(file_ptr);
        return 1;
    }

    // Read from the original file and write to the new file
    int c;
    while ((c = fgetc(file_ptr)) != EOF) {
        fputc(c, new_file_ptr);
    }

    // Close the files
    fclose(file_ptr);
    fclose(new_file_ptr);

    printf("File successfully organized.\n");

    return 0;
}
