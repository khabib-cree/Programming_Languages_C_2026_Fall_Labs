/*
 * Name: Your Name
 * Surname: Your Surname
 * Student ID: Your ID
 */

#include <stdio.h>
#include <string.h>

typedef struct {
    char name[50];
    int age;
    float gpa;
} Student;

// Returns file size in bytes, or -1 on error
long file_size(const char *filename) {
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }
    if (fseek(fp, 0, SEEK_END) != 0) {
        fclose(fp);
        return -1;
    }
    long size = ftell(fp);
    fclose(fp);
    return size;
}

int save_student_binary(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) {
        return -1;
    }
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        return -1;
    }
    size_t written = fwrite(s, sizeof(Student), 1, fp);
    fclose(fp);
    return (written == 1) ? 0 : -1;
}

int load_student_binary(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) {
        return -1;
    }
    FILE *fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }
    size_t read_count = fread(out, sizeof(Student), 1, fp);
    fclose(fp);
    return (read_count == 1) ? 0 : -1;
}

int main(void) {
    // Zero-initialize struct so unused name bytes don't write leftover memory
    Student original = {0};
    strcpy(original.name, "Alice");
    original.age = 21;
    original.gpa = 3.75f;

    const char *bin_filename = "student.bin";
    const char *txt_filename = "student.txt";

    printf("Saving student in binary format...\n");
    if (save_student_binary(&original, bin_filename) != 0) {
        fprintf(stderr, "Error saving binary file.\n");
        return 1;
    }

    // Also save text version to compare sizes
    FILE *txt_fp = fopen(txt_filename, "w");
    if (txt_fp != NULL) {
        fprintf(txt_fp, "%s %d %.2f\n", original.name, original.age, original.gpa);
        fclose(txt_fp);
    }

    Student loaded = {0};
    printf("Loading student from binary file...\n");
    if (load_student_binary(bin_filename, &loaded) != 0) {
        fprintf(stderr, "Error loading binary file.\n");
        return 1;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    long txt_sz = file_size(txt_filename);
    long bin_sz = file_size(bin_filename);

    printf("Text file size: %ld bytes\n", txt_sz);
    printf("Binary file size: %ld bytes\n", bin_sz);

    return 0;
}
