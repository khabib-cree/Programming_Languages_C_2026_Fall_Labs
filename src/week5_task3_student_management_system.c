/*
 * Name: Your Name
 * Surname: Your Surname
 * Student ID: Your ID
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_STUDENTS 100

typedef struct {
    char name[50];
    int id;
    float gpa;
} Student;

// Safe helper function to read a line of input
int read_line(char *buf, int size) {
    if (fgets(buf, size, stdin) == NULL) {
        return 0;
    }
    size_t len = strlen(buf);
    if (len > 0 && buf[len - 1] == '\n') {
        buf[len - 1] = '\0';
    }
    return 1;
}

// Load existing data from students.txt (returns number of records loaded)
int load_students(Student arr[], int max) {
    FILE *fp = fopen("students.txt", "r");
    if (fp == NULL) {
        return 0; // Not an error if file doesn't exist yet
    }

    char line[256];
    int count = 0;
    while (count < max && fgets(line, sizeof(line), fp) != NULL) {
        // Strip trailing newline
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        if (strlen(line) == 0) {
            continue; // Skip blank lines
        }

        Student s;
        if (sscanf(line, "%49[^,],%d,%f", s.name, &s.id, &s.gpa) == 3) {
            arr[count++] = s;
        }
    }

    fclose(fp);
    return count;
}

// Save all students back to the file (returns 0 on success, -1 on error)
int save_students(const Student arr[], int count) {
    FILE *fp = fopen("students.txt", "w");
    if (fp == NULL) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%d,%.2f\n", arr[i].name, arr[i].id, arr[i].gpa);
    }

    fclose(fp);
    return 0;
}

// List all students
void list_students(const Student arr[], int count) {
    if (count == 0) {
        printf("No students found.\n");
        return;
    }
    printf("%-5s %-20s %s\n", "ID", "Name", "GPA");
    for (int i = 0; i < count; i++) {
        printf("%-5d %-20s %.2f\n", arr[i].id, arr[i].name, arr[i].gpa);
    }
}

// Add a student with input validations
void add_student(Student arr[], int *count) {
    if (*count >= MAX_STUDENTS) {
        printf("Cannot add more students (limit reached).\n");
        return;
    }

    char name_buf[100];
    char id_buf[50];
    char gpa_buf[50];

    printf("Enter name: ");
    if (!read_line(name_buf, sizeof(name_buf)) || strlen(name_buf) == 0 || strchr(name_buf, ',') != NULL) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    printf("Enter ID: ");
    if (!read_line(id_buf, sizeof(id_buf))) {
        printf("Invalid input. Student not added.\n");
        return;
    }
    // Validate ID is numeric
    char *endptr;
    int id = (int)strtol(id_buf, &endptr, 10);
    if (*endptr != '\0' || id <= 0) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    printf("Enter GPA: ");
    if (!read_line(gpa_buf, sizeof(gpa_buf))) {
        printf("Invalid input. Student not added.\n");
        return;
    }
    float gpa = strtof(gpa_buf, &endptr);
    if (*endptr != '\0' || gpa < 0.0f || gpa > 4.0f) {
        printf("Invalid input. Student not added.\n");
        return;
    }

    // Success: store student
    strcpy(arr[*count].name, name_buf);
    arr[*count].id = id;
    arr[*count].gpa = gpa;
    (*count)++;

    printf("Student added successfully!\n");
}

int main(void) {
    Student students[MAX_STUDENTS];
    int count = load_students(students, MAX_STUDENTS);

    printf("Loaded %d student(s) from students.txt\n", count);

    int choice = 0;
    do {
        printf("\n=== Student Management System ===\n");
        printf("1. List students\n");
        printf("2. Add student\n");
        printf("3. Save and Exit\n");
        printf("Select an option: ");

        char line[50];
        if (!read_line(line, sizeof(line))) {
            break;
        }
        choice = atoi(line);

        switch (choice) {
            case 1:
                list_students(students, count);
                break;
            case 2:
                add_student(students, &count);
                break;
            case 3:
                if (save_students(students, count) != 0) {
                    fprintf(stderr, "Error saving data.\n");
                }
                printf("Data saved. Goodbye!\n");
                break;
            default:
                printf("Invalid option. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}
