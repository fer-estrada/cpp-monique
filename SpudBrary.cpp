#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Book {
    string title;
    string author;
    int pubYear;
    int id;
};

void addBook(Book books[], int& count, int& nextId) {
    if (count >= 10) {
        cout << "Library is full" << endl;
        return;
    }

    string title, author;
    int pubYear;

    cout << "Enter book title (15 characters max): ";
    cin.ignore();
    getline(cin, title);
    if (title.length() > 15) {
        title = title.substr(0, 15);
        cout << "Note: Title has been truncated to 15 characters" << endl;
    }

    cout << "Enter book author (30 characters max): ";
    getline(cin, author);
    if (author.length() > 30) {
        author = author.substr(0, 30);
        cout << "Note: Author has been truncated to 30 characters" << endl;
    }

    cout << "Enter publication year: ";
    cin >> pubYear;

    books[count].title = title;
    books[count].author = author;
    books[count].pubYear = pubYear;
    books[count].id = nextId;

    count++;
    nextId++;

    cout << "Book added succesfully!" << endl;
};

void displayBooks(const Book books[], int count) {
    if (count == 0) {
        cout << "No books in the library" << endl;
        return;
    }

    cout << left << setw(5) << "ID" << setw(17) << "Title" << setw(32) << "Author" << "Year" << endl;
    cout << string(60, '-') << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(5) << books[i].id
             << setw(17) << books[i].title
             << setw(32) << books[i].author
             << books[i].pubYear << endl;
    }
}

void removeBook(Book books[], int& count) {
    if (count == 0) {
        cout << "No books to remove" << endl;
        return;
    }

    int removeId;
    cout << "Enter book ID to remove: ";
    cin >> removeId;

    int removeIdx = -1;
    for (int i = 0; i < count; i++) {
        if (books[i].id == removeId) {
            removeIdx = i;
            break;
        }
    }

    if (removeIdx == -1) {
        cout << "Book with ID" << removeIdx << " not found" << endl;
        return;
    }

    for (int i = removeIdx; i < count; i++) {
        books[i] = books[i + 1];
    }

    count--;
    cout << "Book removed successfully" << endl;
}

int main() {
    Book books[10];
    int count = 0;
    int nextId = 0;
    int choice;

    while (true) {
        cout << "Welcome to the Library Management System" << endl;
        cout << "1. Add book" << endl;
        cout << "2. Remove book" << endl;
        cout << "3. Display books" << endl;
        cout << "4. Exit" << endl;
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice) {
            case 1:
                if (count >= 10) {
                    cout << "Library is full" << endl;
                } else {
                    addBook(books, count, nextId);
                }
                break;
            case 2:
                removeBook(books, count);
                break;
            case 3:
                displayBooks(books, count);
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid option. Please try again" << endl;
        }
        cout << endl;
    }
    return 0;
}
