#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_STUDENTS 100

typedef struct {
    int id;
    char name[50];
    int age;
} Student;

Student students[MAX_STUDENTS];
int studentCount = 0;

const char *filename = "students.dat";

void loadStudentsFromFile();
void saveStudentsToFile();
void printStudentList();
void addStudent();
void editStudent();
void deleteStudent();
void searchStudent();
void sortStudents();

int main() {
    int choice;
    loadStudentsFromFile();

    do {
        printf("\nMENU\n");
        printf("1. In ra danh sach sinh vien \n");
        printf("2. Them sinh vien\n");
        printf("3. Sua thong tin sinh vien\n");
        printf("4. Xoa sinh vien\n");
        printf("5. TIm kiem sinh vien\n");
        printf("6. Sap xep danh sach sinh vien\n");
        printf("7. Thoat chuong trinh\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printStudentList();
                break;
            case 2:
                addStudent();
                break;
            case 3:
                editStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                searchStudent();
                break;
            case 6:
                sortStudents();
                break;
            case 7:
                printf("Exiting program.\n");
                break;
            default:
                printf("Khong hop le \n");
        }
    } while (choice != 7);

    return 0;
}

void loadStudentsFromFile() {
    FILE *file = fopen(filename, "rb");
    if (file) {
        studentCount = fread(students, sizeof(Student), MAX_STUDENTS, file);
        fclose(file);
    } else {
        studentCount = 0;
    }
}

void saveStudentsToFile() {
    FILE *file = fopen(filename, "wb");
    if (file) {
        fwrite(students, sizeof(Student), studentCount, file);
        fclose(file);
    } else {
        printf("Error saving data to file.\n");
    }
}

void printStudentList() {
    if (studentCount == 0) {
        printf("No students to display.\n");
        return;
    }

    printf("\nStudent List:\n");
    for (int i = 0; i < studentCount; i++) {
        printf("ID: %d, Name: %s, Age: %d\n", students[i].id, students[i].name, students[i].age);
    }
}

void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Student list is full. Cannot add more students.\n");
        return;
    }

    Student newStudent;
    printf("Enter ID: ");
    scanf("%d", &newStudent.id);
    printf("Enter Name: ");
    scanf(" %s", newStudent.name);
    printf("Enter Age: ");
    scanf("%d", &newStudent.age);

    students[studentCount++] = newStudent;
    saveStudentsToFile();
    printf("Student added successfully.\n");
}

void editStudent() {
    int id, found = 0;
    printf("Enter ID of the student to edit: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("Enter new Name: ");
            scanf(" %s", students[i].name);
            printf("Enter new Age: ");
            scanf("%d", &students[i].age);
            saveStudentsToFile();
            printf("Student information updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

void deleteStudent() {
    int id, found = 0;
    printf("Enter ID of the student to delete: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            for (int j = i; j < studentCount - 1; j++) {
                students[j] = students[j + 1];
            }
            studentCount--;
            saveStudentsToFile();
            printf("Student deleted successfully.\n");
            break;
        }
    }
    
    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

void searchStudent() {
    int id, found = 0;
    printf("Enter ID of the student to search: ");
    scanf("%d", &id);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].id == id) {
            found = 1;
            printf("Student found: ID: %d, Name: %s, Age: %d\n", students[i].id, students[i].name, students[i].age);
            break;
        }
    }

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

void sortStudents() {
    for (int i = 0; i < studentCount - 1; i++) {
        for (int j = i + 1; j < studentCount; j++) {
            if (students[i].id > students[j].id) {
                Student temp = students[i];
                students[i] = students[j];
                students[j] = temp;
            }
        }
    }
    saveStudentsToFile();
    printf("Student list sorted by ID successfully.\n");
}


