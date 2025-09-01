#ifndef STUDENT_H
#define STUDENT_H

#include <string>
using namespace std;

// Data structure for student
struct Student {
    int id;
    string name;
    string course;
    int year;
};

// Function declarations
void addStudent();
void viewStudents();
void searchStudent();
void deleteStudent();

#endif