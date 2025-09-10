#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to hold student data
struct Student {
    int id;
    char name[50];
    int age;
    char department[30];
};

// Function to add a student
void addStudent() {
    struct Student s;
    FILE *f = fopen("students.dat", "ab");
    if (f == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Department: ");
    scanf(" %[^\n]", s.department);

    fwrite(&s, sizeof(s), 1, f);
    fclose(f);
    printf("Student record added successfully!\n");
}

// Function to display all students
void displayStudents() {
    struct Student s;
    FILE *f = fopen("students.dat", "rb");
    if (f == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\nStudent Records:\n");
    printf("ID\tName\t\tAge\tDepartment\n");
    printf("--------------------------------------------------\n");
    while (fread(&s, sizeof(s), 1, f)) {
        printf("%d\t%s\t\t%d\t%s\n", s.id, s.name, s.age, s.department);
    }
    fclose(f);
}

// Function to search for a student by ID
void searchStudent() {
    struct Student s;
    int searchId;
    printf("Enter Student ID to search: ");
    scanf("%d", &searchId);

    FILE *f = fopen("students.dat", "rb");
    if (f == NULL) {
        printf("No records found!\n");
        return;
    }

    int found = 0;
    while (fread(&s, sizeof(s), 1, f)) {
        if (s.id == searchId) {
            printf("\nStudent Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nDepartment: %s\n", s.id, s.name, s.age, s.department);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student with ID %d not found.\n", searchId);
    }
    fclose(f);
}

// Function to update a student record
void updateStudent() {
    struct Student s;
    int updateId;
    printf("Enter Student ID to update: ");
    scanf("%d", &updateId);

    FILE *f = fopen("students.dat", "rb+");
    if (f == NULL) {
        printf("No records found!\n");
        return;
    }

    int found = 0;
    while (fread(&s, sizeof(s), 1, f)) {
        if (s.id == updateId) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new Age: ");
            scanf("%d", &s.age);
            printf("Enter new Department: ");
            scanf(" %[^\n]", s.department);

            fseek(f, -sizeof(s), SEEK_CUR);
            fwrite(&s, sizeof(s), 1, f);
            printf("Student record updated successfully!\n");
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Student with ID %d not found.\n", updateId);
    }
    fclose(f);
}

// Function to delete a student record
void deleteStudent() {
    struct Student s;
    int deleteId;
    printf("Enter Student ID to delete: ");
    scanf("%d", &deleteId);

    FILE *f = fopen("students.dat", "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (f == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int found = 0;
    while (fread(&s, sizeof(s), 1, f)) {
        if (s.id != deleteId) {
            fwrite(&s, sizeof(s), 1, temp);
        } else {
            found = 1;
        }
    }
    fclose(f);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) {
        printf("Student record deleted successfully!\n");
    } else {
        printf("Student with ID %d not found.\n", deleteId);
    }
}

int main() {
    int choice;
    do {
        printf("\n=== Student Record Management ===\n");
        printf("1. Add Student\n");
        printf("2. Display Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != 6);

    return 0;
}