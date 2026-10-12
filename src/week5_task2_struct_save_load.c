/*
 * Name: Khabibullo 
 * Surname: Khudaykulov
 * Student ID: 251ADB033
 */

#include <stdio.h>

typedef struct {
    char name[50];
    int age;
    float gpa;
} Student;

// Save one student record to file (returns 0 on success, -1 on error)
int save_student(const Student *s, const char *filename) {
    if (s == NULL || filename == NULL) {
        return -1;
    }
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        return -1;
    }

    // Save data as one line: name age gpa
    fprintf(fp, "%s %d %.2f\n", s->name, s->age, s->gpa);
    fclose(fp);
    return 0;
}

// Load record from file into out (returns 0 on success, -1 on error)
int load_student(const char *filename, Student *out) {
    if (filename == NULL || out == NULL) {
        return -1;
    }
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        return -1;
    }

    // Use field width %49s to prevent overflow
    int items = fscanf(fp, "%49s %d %f", out->name, &out->age, &out->gpa);
    fclose(fp);

    if (items != 3) {
        return -1;
    }
    return 0;
}

int main(void) {
    Student original = {"Alice", 21, 3.75f};
    const char *filename = "student.txt";

    printf("Saving student to file...\n");
    if (save_student(&original, filename) != 0) {
        fprintf(stderr, "Failed to save student.\n");
        return 1;
    }

    Student loaded = {0};
    printf("Loading student from file...\n");
    if (load_student(filename, &loaded) != 0) {
        fprintf(stderr, "Failed to load student.\n");
        return 1;
    }

    printf("Loaded student: %s, %d, GPA %.2f\n", loaded.name, loaded.age, loaded.gpa);

    return 0;
}
