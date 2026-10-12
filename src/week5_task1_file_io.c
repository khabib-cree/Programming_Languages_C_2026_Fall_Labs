/*
 * Name: Your Name
 * Surname: Your Surname
 * Student ID: Your ID
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    const char *filename = "data.txt";

    // 1. Open text file for writing
    printf("Writing lines to %s...\n", filename);
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return 1;
    }

    // 2. Write at least two lines of text
    fprintf(fp, "Hello, file I/O in C!\n");
    fprintf(fp, "This is another line.\n");

    // 3. Close the file properly
    fclose(fp);

    // 4. Open the same file again for reading
    printf("Reading contents:\n");
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return 1;
    }

    // 5. Read contents line by line using fgets() and print to console
    char buffer[256];
    int lines_read = 0;
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("%s", buffer);
        lines_read++;
    }

    // Close file
    fclose(fp);

    // Bonus summary line
    printf("Lines read: %d\n", lines_read);

    return 0;
}
