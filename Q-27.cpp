#include <stdio.h>
#include <dirent.h>

int main(int argc, char *argv[]) {
    // Check if a directory is specified
    if (argc < 2) {
        printf("Usage: %s <directory>\n", argv[0]);
        return 1;
    }

    // Open the specified directory
    DIR *dir;
    struct dirent *entry;

    dir = opendir(argv[1]);

    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    // Read directory entries and print their names
    printf("Directory entries:\n");

    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    return 0;
}

