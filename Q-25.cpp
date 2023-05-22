#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

int main() {
    int fileDescriptor;
    off_t seekPosition;
    struct stat fileStat;
    DIR *dir;
    struct dirent *entry;

    // Open a file using fcntl
    fileDescriptor = open("sample.txt", O_RDONLY);

    if (fileDescriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    // Get the current seek position using lseek
    seekPosition = lseek(fileDescriptor, 0, SEEK_CUR);

    if (seekPosition == -1) {
        perror("Error getting seek position");
        close(fileDescriptor);
        return 1;
    }

    printf("Current seek position: %ld\n", seekPosition);

    // Get file information using stat
    if (stat("sample.txt", &fileStat) == -1) {
        perror("Error getting file information");
        close(fileDescriptor);
        return 1;
    }

    printf("File size: %ld bytes\n", fileStat.st_size);
    printf("File permissions: %o\n", fileStat.st_mode);

    // Open a directory using opendir
    dir = opendir(".");

    if (dir == NULL) {
        perror("Error opening directory");
        return 1;
    }

    // Read directory entries using readdir
    printf("Directory entries:\n");
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    // Close the directory
    closedir(dir);

    // Close the file
    if (close(fileDescriptor) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}

