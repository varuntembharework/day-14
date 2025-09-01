#include <iostream>
#include <fstream>
#include <ctime>
#include "transaction.h"
#include "book.h"
#include "student.h"
using namespace std;

const string TRANSACTION_FILE = "transactions.txt";

// Get current timestamp
string currentDateTime() {
    time_t now = time(0);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return buf;
}

// Borrow book
void borrowBook() {
    int studentId, bookId;
    cout << "\nEnter Student ID: ";
    cin >> studentId;
    cout << "Enter Book ID: ";
    cin >> bookId;

    if (updateBookQuantity(bookId, -1)) {
        ofstream fout(TRANSACTION_FILE, ios::app);
        fout << "BORROW|" << studentId << "|" << bookId << "|" << currentDateTime() << "\n";
        fout.close();
        cout << "✅ Book borrowed successfully!\n";
    } else {
        cout << "❌ Failed! Book not found.\n";
    }
}

// Return book
void returnBook() {
    int studentId, bookId;
    cout << "\nEnter Student ID: ";
    cin >> studentId;
    cout << "Enter Book ID: ";
    cin >> bookId;

    if (updateBookQuantity(bookId, 1)) {
        ofstream fout(TRANSACTION_FILE, ios::app);
        fout << "RETURN|" << studentId << "|" << bookId << "|" << currentDateTime() << "\n";
        fout.close();
        cout << "✅ Book returned successfully!\n";
    } else {
        cout << "❌ Failed! Book not found.\n";
    }
}

// View all transactions
void viewTransactions() {
    ifstream fin(TRANSACTION_FILE);
    if (!fin) {
        cout << "No transactions available.\n";
        return;
    }

    cout << "\n=========== Transactions ===========\n";
    string type, studentId, bookId, datetime;
    while (getline(fin, type, '|')) {
        getline(fin, studentId, '|');
        getline(fin, bookId, '|');
        getline(fin, datetime);

        cout << type << " | StudentID: " << studentId 
             << " | BookID: " << bookId 
             << " | " << datetime << "\n";
    }
    fin.close();
}