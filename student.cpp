#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "student.h"
using namespace std;

const string STUDENT_FILE = "students.txt"; // unified & fixed

// --- helpers ---
static int readInt(const string& prompt) {
    while (true) {
        cout << prompt;
        int x;
        if (cin >> x) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return x;
        }
        cout << "❌ Invalid number. Try again.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

static bool studentIdExists(int id) {
    ifstream fin(STUDENT_FILE);
    if (!fin) return false;
    string line;
    while (getline(fin, line)) {
        size_t p = line.find("|");
        if (p == string::npos) continue;
        int existing = stoi(line.substr(0, p));
        if (existing == id) return true;
    }
    return false;
}
// ---------------

// Add a new student
void addStudent() {
    Student s;
    s.id = readInt("\nEnter Student ID: ");

    if (studentIdExists(s.id)) {
        cout << "⚠️  A student with ID " << s.id << " already exists. Use a new ID or delete the old one.\n";
        return;
    }

    cout << "Enter Name: ";
    getline(cin, s.name);
    cout << "Enter Course: ";
    getline(cin, s.course);
    s.year = readInt("Enter Year: ");

    ofstream fout(STUDENT_FILE, ios::app);
    fout << s.id << "|" << s.name << "|" << s.course << "|" << s.year << "\n";
    fout.close();

    cout << "✅ Student added successfully!\n";
}

// View all students
void viewStudents() {
    ifstream fin(STUDENT_FILE);
    if (!fin) {
        cout << "No students available.\n";
        return;
    }

    cout << "\n=========== Student List ===========\n";
    cout << left << setw(10) << "ID" << setw(30) << "Name"
         << setw(25) << "Course" << setw(6) << "Year" << "\n";
    cout << "-----------------------------------------------\n";

    string line; bool any = false;
    while (getline(fin, line)) {
        size_t p1 = line.find("|");
        size_t p2 = line.find("|", p1 + 1);
        size_t p3 = line.find("|", p2 + 1);
        if (p1 == string::npos || p2 == string::npos || p3 == string::npos) continue;

        int id = stoi(line.substr(0, p1));
        string name = line.substr(p1 + 1, p2 - p1 - 1);
        string course = line.substr(p2 + 1, p3 - p2 - 1);
        int year = stoi(line.substr(p3 + 1));

        cout << left << setw(10) << id << setw(30) << name
             << setw(25) << course << setw(6) << year << "\n";
        any = true;
    }
    if (!any) cout << "(empty)\n";
    fin.close();
}

// Search student by ID
void searchStudent() {
    int searchId = readInt("\nEnter Student ID to search: ");

    ifstream fin(STUDENT_FILE);
    if (!fin) {
        cout << "No students available.\n";
        return;
    }

    string line;
    while (getline(fin, line)) {
        size_t p1 = line.find("|");
        size_t p2 = line.find("|", p1 + 1);
        size_t p3 = line.find("|", p2 + 1);
        if (p1 == string::npos || p2 == string::npos || p3 == string::npos) continue;

        int id = stoi(line.substr(0, p1));
        if (id == searchId) {
            string name = line.substr(p1 + 1, p2 - p1 - 1);
            string course = line.substr(p2 + 1, p3 - p2 - 1);
            int year = stoi(line.substr(p3 + 1));

            cout << "\nStudent Found ✅\n";
            cout << "ID: " << id << "\nName: " << name
                 << "\nCourse: " << course << "\nYear: " << year << "\n";
            fin.close();
            return;
        }
    }
    fin.close();
    cout << "❌ Student not found.\n";
}

// Delete student by ID
void deleteStudent() {
    int deleteId = readInt("\nEnter Student ID to delete: ");

    ifstream fin(STUDENT_FILE);
    if (!fin) {
        cout << "No students available.\n";
        return;
    }

    ofstream temp("temp.txt");
    string line; bool deleted = false;

    while (getline(fin, line)) {
        size_t p = line.find("|");
        if (p == string::npos) continue;
        int id = stoi(line.substr(0, p));
        if (id != deleteId) temp << line << "\n";
        else deleted = true;
    }

    fin.close();
    temp.close();

    remove(STUDENT_FILE.c_str());
    rename("temp.txt", STUDENT_FILE.c_str());

    if (deleted) cout << "✅ Student deleted successfully!\n";
    else cout << "❌ Student not found.\n";
}