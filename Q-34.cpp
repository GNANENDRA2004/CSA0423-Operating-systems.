#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 100

struct Record {
    int recordNumber;
    char data[50];
};

void writeFile(const char* filename, struct Record records[], int numRecords) {
    FILE* file = fopen(filename, "wb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write records to the file
    fwrite(records, sizeof(struct Record), numRecords, file);

    fclose(file);
}

void readFile(const char* filename) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    struct Record record;
    int recordCount = 0;

    // Read records from the file
    while (fread(&record, sizeof(struct Record), 1, file) == 1) {
        printf("Record Number: %d\n", record.recordNumber);
        printf("Data: %s\n", record.data);
        printf("------------------------\n");
        recordCount++;
    }

    printf("Total Records: %d\n", recordCount);

    fclose(file);
}

int main() {
    struct Record records[MAX_RECORDS];
    int numRecords;

    printf("Enter the number of records: ");
    scanf("%d", &numRecords);

    if (numRecords <= 0 || numRecords > MAX_RECORDS) {
        printf("Invalid number of records.\n");
        return 1;
    }

    // Input records
    for (int i = 0; i < numRecords; i++) {
        printf("Enter data for Record %d: ", i + 1);
        scanf("%s", records[i].data);
        records[i].recordNumber = i + 1;
    }

    // Write records to the file
    writeFile("file.bin", records, numRecords);

    printf("File created successfully.\n");

    // Read records from the file
    readFile("file.bin");

    return 0;
}

