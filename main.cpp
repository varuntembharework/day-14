#include <iostream>
#include "book.h"
#include "student.h"
#include "transaction.h"
using namespace std;

void bookMenu() {
    int choice;
    do {
        cout << "\n========== Book Management ==========\n";
        cout << "1. Add Book\n";
        cout << "2. View Books\n";
        cout << "3. Search Book\n";
        cout << "4. Delete Book\n";
        cout << "0. Back to Main Menu\n";
        cout << "=====================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: viewBooks(); break;
            case 3: searchBook(); break;
            case 4: deleteBook(); break;
            case 0: break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

void studentMenu() {
    int choice;
    do {
        cout << "\n========== Student Management ==========\n";
        cout << "1. Add Student\n";
        cout << "2. View Students\n";
        cout << "3. Search Student\n";
        cout << "4. Delete Student\n";
        cout << "0. Back to Main Menu\n";
        cout << "========================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: deleteStudent(); break;
            case 0: break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

void transactionMenu() {
    int choice;
    do {
        cout << "\n========== Borrow & Return ==========\n";
        cout << "1. Borrow Book\n";
        cout << "2. Return Book\n";
        cout << "3. View Transactions\n";
        cout << "0. Back to Main Menu\n";
        cout << "=====================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: borrowBook(); break;
            case 2: returnBook(); break;
            case 3: viewTransactions(); break;
            case 0: break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

int main() {
    int choice;
    do {
        cout << "\n========== Library Management System ==========\n";
        cout << "1. Book Management\n";
        cout << "2. Student Management\n";
        cout << "3. Borrow & Return\n";
        cout << "0. Exit\n";
        cout << "===============================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bookMenu(); break;
            case 2: studentMenu(); break;
            case 3: transactionMenu(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}