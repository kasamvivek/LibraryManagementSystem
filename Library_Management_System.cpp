#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Book
{
public:
    int bookID;
    string title;
    string author;
    int quantity;
};

class Library
{
private:
    Book library[100];
    int count;

    void saveToFile()
    {
        ofstream file("library.txt");

        if(!file)
        {
            cout << "Error opening file!" << endl;
            return;
        }

        for(int i = 0; i < count; i++)
        {
            file << library[i].bookID << endl;
            file << library[i].title << endl;
            file << library[i].author << endl;
            file << library[i].quantity << endl;
        }

        file.close();
    }

    void loadFromFile()
    {
        ifstream file("library.txt");

        if(!file)
            return;

        count = 0;

        while(file >> library[count].bookID)
        {
            file.ignore();
            getline(file, library[count].title);
            getline(file, library[count].author);
            file >> library[count].quantity;
            count++;

            if(count >= 100) break;
        }

        file.close();
    }

public:
    Library()
    {
        count = 0;
        loadFromFile();
    }

    void addBook()
    {
        if(count >= 100)
        {
            cout << "Library is full!" << endl;
            return;
        }

        cout << "Enter Book ID: ";
        cin >> library[count].bookID;
        cin.ignore();

        cout << "Enter Title: ";
        getline(cin, library[count].title);

        cout << "Enter Author: ";
        getline(cin, library[count].author);

        cout << "Enter Quantity: ";
        cin >> library[count].quantity;

        count++;
        saveToFile();

        cout << "Book added successfully!" << endl;
    }

    void displayBooks()
    {
        if(count == 0)
        {
            cout << "No books available" << endl;
            return;
        }

        cout << "\n--- Book List ---\n";

        for(int i = 0; i < count; i++)
        {
            cout << "------------------" << endl;
            cout << "ID: " << library[i].bookID << endl;
            cout << "Title: " << library[i].title << endl;
            cout << "Author: " << library[i].author << endl;
            cout << "Quantity: " << library[i].quantity << endl;
        }
    }

    void searchBook()
    {
        int id;
        cout << "Enter Book ID to search: ";
        cin >> id;

        for(int i = 0; i < count; i++)
        {
            if(library[i].bookID == id)
            {
                cout << "\nBook Found!" << endl;
                cout << "Title: " << library[i].title << endl;
                cout << "Author: " << library[i].author << endl;
                cout << "Quantity: " << library[i].quantity << endl;
                return;
            }
        }

        cout << "Book not found!" << endl;
    }

    void updateBook()
    {
        int id;
        cout << "Enter Book ID to update: ";
        cin >> id;
        cin.ignore();

        for(int i = 0; i < count; i++)
        {
            if(library[i].bookID == id)
            {
                cout << "Enter new Title: ";
                getline(cin, library[i].title);

                cout << "Enter new Author: ";
                getline(cin, library[i].author);

                cout << "Enter new Quantity: ";
                cin >> library[i].quantity;

                saveToFile();
                cout << "Book updated successfully!" << endl;
                return;
            }
        }

        cout << "Book not found!" << endl;
    }

    void deleteBook()
    {
        int id;
        cout << "Enter Book ID to delete: ";
        cin >> id;

        for(int i = 0; i < count; i++)
        {
            if(library[i].bookID == id)
            {
                for(int j = i; j < count - 1; j++)
                {
                    library[j] = library[j + 1];
                }

                count--;
                saveToFile();
                cout << "Book deleted successfully!" << endl;
                return;
            }
        }

        cout << "Book not found!" << endl;
    }
};

int main()
{
    Library lib;
    int choice;

    do
    {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Search Book\n";
        cout << "4. Update Book\n";
        cout << "5. Delete Book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice)
        {
            case 1: lib.addBook(); break;
            case 2: lib.displayBooks(); break;
            case 3: lib.searchBook(); break;
            case 4: lib.updateBook(); break;
            case 5: lib.deleteBook(); break;
            case 6: cout << "Exiting program..." << endl; break;
            default: cout << "Invalid choice! Try again." << endl;
        }

    } while(choice != 6);

    return 0;
}