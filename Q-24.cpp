#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fileDescriptor;
    ssize_t bytesRead;
    char buffer[100];

    // Open the file in read-only mode
    fileDescriptor = open("sample.txt", O_RDONLY);

    if (fileDescriptor == -1) {
        perror("Error opening file");
        return 1;
    }

    // Read from the file
    bytesRead = read(fileDescriptor, buffer, sizeof(buffer) - 1);

    if (bytesRead == -1) {
        perror("Error reading file");
        close(fileDescriptor);
        return 1;
    }

    buffer[bytesRead] = '\0'; // Null-terminate the buffer

    printf("File content:\n%s\n", buffer);

    // Close the file
    if (close(fileDescriptor) == -1) {
        perror("Error closing file");
        return 1;
    }

    return 0;
}

