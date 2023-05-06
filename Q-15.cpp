#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#define MAX_FILENAME_LENGTH 256

int main(int argc, char *argv[]) {
    char filename[MAX_FILENAME_LENGTH];
    char new_filename[MAX_FILENAME_LENGTH];
    char *dir_name1 = "organized";
    char *dir_name2 = "files";
    FILE *file_ptr, *new_file_ptr;
    struct stat st1 = {0}, st2 = {0};

    if (stat(dir_name1, &st1) == -1) {
        mkdir(dir_name1, 0700);
    }
    if (stat(dir_name2, &st2) == -1) {
        mkdir(dir_name2, 0700);
    }

    printf("Enter the file name: ");
    scanf("%s", filename);
    file_ptr = fopen(filename, "r");

    if (file_ptr == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    strcpy(new_filename, dir_name1);
    strcat(new_filename, "/");
    strcat(new_filename, dir_name2);
    strcat(new_filename, "/");
    strcat(new_filename, filename);
    new_file_ptr = fopen(new_filename, "w");

    if (new_file_ptr == NULL) {
        printf("Error: Unable to create new file.\n");
        fclose(file_ptr);
        return 1;
    }
    int c;
    while ((c = fgetc(file_ptr)) != EOF) {
        fputc(c, new_file_ptr);
    }
    fclose(file_ptr);
    fclose(new_file_ptr);
    printf("File successfully organized.\n");
    return 0;
}
