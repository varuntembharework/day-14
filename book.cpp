#include <iostream>
#include <fstream>
#include <iomanip>
#include "book.h"
using namespace std;

const string BOOK_FILE = "books.txt";

// Add a new book
void addBook() {
    Book b;
    cout << "\nEnter Book ID: ";
    cin >> b.id;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, b.title);
    cout << "Enter Author: ";
    getline(cin, b.author);
    cout << "Enter Quantity: ";
    cin >> b.quantity;

    ofstream fout(BOOK_FILE, ios::app);
    fout << b.id << "|" << b.title << "|" << b.author << "|" << b.quantity << "\n";
    fout.close();

    cout << "✅ Book added successfully!\n";
}

// View all books
void viewBooks() {
    ifstream fin(BOOK_FILE);
    if (!fin) {
        cout << "No books available.\n";
        return;
    }

    cout << "\n=========== Book List ===========\n";
    cout << left << setw(10) << "ID" << setw(25) << "Title" 
         << setw(20) << "Author" << setw(12) << "Quantity" << "\n";
    cout << "------------------------------------------------------------\n";

    string line;
    while (getline(fin, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1+1);
        size_t pos3 = line.find("|", pos2+1);

        int id = stoi(line.substr(0, pos1));
        string title = line.substr(pos1+1, pos2-pos1-1);
        string author = line.substr(pos2+1, pos3-pos2-1);
        int qty = stoi(line.substr(pos3+1));

        cout << left << setw(10) << id << setw(25) << title 
             << setw(20) << author << setw(12) << qty << "\n";
    }

    fin.close();
}

// Search book by ID
void searchBook() {
    int searchId;
    cout << "\nEnter Book ID to search: ";
    cin >> searchId;

    ifstream fin(BOOK_FILE);
    if (!fin) {
        cout << "No books available.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(fin, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1+1);
        size_t pos3 = line.find("|", pos2+1);

        int id = stoi(line.substr(0, pos1));
        string title = line.substr(pos1+1, pos2-pos1-1);
        string author = line.substr(pos2+1, pos3-pos2-1);
        int qty = stoi(line.substr(pos3+1));

        if (id == searchId) {
            cout << "\nBook Found ✅\n";
            cout << "ID: " << id << "\nTitle: " << title 
                 << "\nAuthor: " << author << "\nQuantity: " << qty << "\n";
            found = true;
            break;
        }
    }
    fin.close();

    if (!found) cout << "❌ Book not found.\n";
}

// Delete book by ID
void deleteBook() {
    int deleteId;
    cout << "\nEnter Book ID to delete: ";
    cin >> deleteId;

    ifstream fin(BOOK_FILE);
    ofstream temp("temp.txt");
    string line;
    bool deleted = false;

    while (getline(fin, line)) {
        size_t pos1 = line.find("|");
        int id = stoi(line.substr(0, pos1));
        if (id != deleteId) {
            temp << line << "\n";
        } else {
            deleted = true;
        }
    }

    fin.close();
    temp.close();

    remove(BOOK_FILE.c_str());
    rename("temp.txt", BOOK_FILE.c_str());

    if (deleted) cout << "✅ Book deleted successfully!\n";
    else cout << "❌ Book not found.\n";
}

// Update book quantity (borrow/return)
bool updateBookQuantity(int bookId, int change) {
    ifstream fin(BOOK_FILE);
    if (!fin) return false;

    ofstream temp("temp.txt");
    string line;
    bool updated = false;

    while (getline(fin, line)) {
        size_t pos1 = line.find("|");
        size_t pos2 = line.find("|", pos1+1);
        size_t pos3 = line.find("|", pos2+1);

        int id = stoi(line.substr(0, pos1));
        string title = line.substr(pos1+1, pos2-pos1-1);
        string author = line.substr(pos2+1, pos3-pos2-1);
        int qty = stoi(line.substr(pos3+1));

        if (id == bookId) {
            qty += change;
            if (qty < 0) qty = 0; // avoid negatives
            updated = true;
        }

        temp << id << "|" << title << "|" << author << "|" << qty << "\n";
    }

    fin.close();
    temp.close();

    remove(BOOK_FILE.c_str());
    rename("temp.txt", BOOK_FILE.c_str());

    return updated;
}