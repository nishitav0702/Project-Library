#include <iostream>
#include <fstream>
using namespace std;

class Book {
protected:
    string title, author, genre;

public:
    Book(string t, string a, string g)
        : title(t), author(a), genre(g) {}

    virtual void displayBook() const {
        cout << "Title: " << title
             << " | Author: " << author << " | Genre: " << genre << endl;
    }

    virtual void saveToFile(const string& filename) const {
        ofstream file(filename, ios::app);
        file << title << " | " << author << " | " << genre << endl;
        file.close();
    }

    virtual ~Book() {}
};

class OwnedBook : public Book {
private:
    int yearPublished;

public:
    OwnedBook(string t, string a, string g, int year)
        : Book(t, a, g), yearPublished(year) {}

    void displayBook() const override {
        cout << "Owned Book -> " << title << " (" << yearPublished << ")" << endl;
    }

    void saveToFile(const string& filename) const override {
        ofstream file(filename, ios::app);
        file << title << " | " << author << " | " << genre
             << " | " << yearPublished << endl;
        file.close();
    }
};

class ReadBook : public Book {
private:
    string dateFinished;
    int rating;

public:
    ReadBook(string t, string a, string g, string date, int rate)
        : Book(t, a, g), dateFinished(date), rating(rate) {}

    void displayBook() const override {
        cout << "Read Book -> " << title << " (Finished: " << dateFinished << ", Rating: " << rating << "/5)" << endl;
    }

    void saveToFile(const string& filename) const override {
        ofstream file(filename, ios::app);
        file << title << " | " << author << " | " << genre
             << " | " << dateFinished << " | " << rating << endl;
        file.close();
    }
};

class TBRBook : public Book {
public:
    TBRBook(string t, string a, string g) : Book(t, a, g) {}

    void displayBook() const override {
        cout << "TBR Book -> " << title << endl;
    }

    void saveToFile(const string& filename) const override {
        ofstream file(filename, ios::app);
        file << title << " | " << author << " | " << genre << endl;
        file.close();
    }
};

void addBookOption() {
    int choice;
    cout << "\nAdd a Book to:\n1. Owned Books\n2. Read Books\n3. TBR List\nChoose an option: ";
    cin >> choice;

    string title, author, genre, date;
    int year ;
    float rating;

    cin.ignore();

    cout << "Enter Title: "; getline(cin, title);
    cout << "Enter Author: "; getline(cin, author);
    cout << "Enter Genre: "; getline(cin, genre);

    if (choice == 1) {
        cout << "Enter Year Published: "; cin >> year;
        OwnedBook book(title, author, genre, year);
        book.saveToFile("books_owned.txt");

    } else if (choice == 2) {
        cout << "Enter Date Finished (YYYY-MM-DD): "; cin >> date;
        cout << "Enter Rating (1-5): "; cin >> rating;
        ReadBook book(title, author, genre, date, rating);
        book.saveToFile("books_read.txt");

    } else if (choice == 3) {
        TBRBook book(title, author, genre);
        book.saveToFile("tbr_list.txt");

    } else {
        cout << "Invalid option!" << endl;
    }

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
}

void showBooks(const string& filename, const string& listName) { 
    ifstream file(filename);
    if (!file) {
        cout << "Error: No books found in " << listName << ".\n";
    } else {
        cout << "\n=== " << listName << " ===\n";
        string line; 
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }

    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get(); 
}

int main() {
    int option;

    while (true) {
        cout << "\nPersonal Library Management System\n";
        cout << "1. Add Book\n2. Show Owned Books\n3. Show Read Books\n4. Show TBR List\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> option;

        if (option == 1) addBookOption();
        else if (option == 2) showBooks("books_owned.txt", "Owned Books");
        else if (option == 3) showBooks("books_read.txt", "Read Books");
        else if (option == 4) showBooks("tbr_list.txt", "TBR List");
        else if (option == 5) break;
        else cout << "Invalid option! Try again.\n";
    }

    return 0;
}