// Problem Statement
//You're tasked with creating a C++ program for a bookstore that dynamically manages its inventory. The program should allow the user to perform various operations using pointer notation:
// 1.	Add Book to Inventory:
// •	Implement a function to add a new book to the inventory. Prompt the user to input the book's title, author, and quantity. Utilize dynamic memory allocation to store the book information efficiently.
// 2.	Sell Book:
// •	Develop a function to sell a book from the inventory. Prompt the user to input the title of the book they wish to purchase and update the inventory accordingly.
// 3.	Find Book by Author:
// •	Write a function to search for books by a specific author. Prompt the user to input the author's name and display all books written by that author.
// 4.	Display Inventory:
// •	Create a function to display the current inventory, including the title, author, and quantity of each book.
// 5.	Update Book Quantity:
// •	Implement a function to update the quantity of a book in the inventory. Prompt the user to input the title of the book and the new quantity.
// 6.	Delete Book from Inventory:
// •	Provide functionality to remove a book from the inventory. Prompt the user to input the book's unique identifier and confirm the deletion.
// 7.	Sales Reporting:
// •	Implement a feature to generate sales reports for a specified time period. Calculate total sales revenue and display top-selling books based on sales volume.
// 8.	Exit Program:
// •	Provide an option to exit the program gracefully. Implement efficient memory management techniques to prevent memory leaks and optimize resource usage.
// Ensure error handling for invalid inputs and dynamic memory management for the inventory. Your program should provide an efficient and user-friendly interface for managing the bookstore's inventory dynamically.

#include <iostream>
#include <string>
using namespace std;

struct Book {
    string title;
    string author;
    int quantity;
    float price;
};

class Bookstore {
private:
    Book* inventory;       
    int size;             
    float totalSales;     

public:
    // Constructor
    Bookstore() : inventory(nullptr), size(0), totalSales(0.0) {}

    // Function to add a new book to inventory
    void addBook() {
        string title, author;
        int quantity;
        float price;

        cout << "Enter the book title: ";
        cin.ignore();
        getline(cin, title);

        cout << "Enter the author's name: ";
        getline(cin, author);

        cout << "Enter the quantity: ";
        cin >> quantity;

        cout << "Enter the price: ";
        cin >> price;

        // Create new inventory with one extra slot
        Book* newInventory = new Book[size + 1];
        for (int i = 0; i < size; i++) {
            newInventory[i] = inventory[i];
        }

        // Add new book
        newInventory[size] = { title, author, quantity, price };

        delete[] inventory;
        inventory = newInventory;
        size++;

        cout << "Book added to inventory." << endl;
    }

    // Function to sell a book
    void sellBook() {
        string title;
        cout << "Enter the title of the book to sell: ";
        cin.ignore();
        getline(cin, title);

        for (int i = 0; i < size; i++) {
            if (inventory[i].title == title) {
                if (inventory[i].quantity > 0) {
                    inventory[i].quantity--;
                    totalSales += inventory[i].price;
                    cout << "Book sold! Remaining quantity: " << inventory[i].quantity << endl;
                    return;
                } else {
                    cout << "Sorry, this book is out of stock." << endl;
                    return;
                }
            }
        }
        cout << "Book not found in inventory." << endl;
    }

    // Function to find books by author
    void findBooks() {
        string author;
        cout << "Enter the author's name: ";
        cin.ignore();
        getline(cin, author);

        bool found = false;
        for (int i = 0; i < size; i++) {
            if (inventory[i].author == author) {
                cout << "Title: " << inventory[i].title
                     << ", Quantity: " << inventory[i].quantity
                     << ", Price: $" << inventory[i].price << endl;
                found = true;
            }
        }
        if (!found) cout << "No books found by this author." << endl;
    }

    // Function to display all books in inventory
    void displayInventory() {
        if (size == 0) {
            cout << "Inventory is empty." << endl;
            return;
        }
        cout << "Current Inventory:" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Title: " << inventory[i].title
                 << ", Author: " << inventory[i].author
                 << ", Quantity: " << inventory[i].quantity
                 << ", Price: $" << inventory[i].price << endl;
        }
    }

    // Function to update book quantity
    void updateBookQuantity() {
        string title;
        cout << "Enter the title of the book to update quantity: ";
        cin.ignore();
        getline(cin, title);

        int newQuantity;
        for (int i = 0; i < size; i++) {
            if (inventory[i].title == title) {
                cout << "Enter the new quantity: ";
                cin >> newQuantity;
                inventory[i].quantity = newQuantity;
                cout << "Quantity updated." << endl;
                return;
            }
        }
        cout << "Book not found in inventory." << endl;
    }

    // Function to delete a book from inventory
    void deleteBook() {
        string title;
        cout << "Enter the title of the book to delete: ";
        cin.ignore();
        getline(cin, title);

        int index = -1;
        for (int i = 0; i < size; i++) {
            if (inventory[i].title == title) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << "Book not found in inventory." << endl;
            return;
        }

        Book* newInventory = new Book[size - 1];
        for (int i = 0, j = 0; i < size; i++) {
            if (i != index) {
                newInventory[j++] = inventory[i];
            }
        }

        delete[] inventory;
        inventory = newInventory;
        size--;

        cout << "Book deleted from inventory." << endl;
    }

    // Function to generate sales report
    void generateSalesReport() {
        cout << "Total Sales Revenue: $" << totalSales << endl;
        cout << "Books in Inventory (remaining quantities):" << endl;
        for (int i = 0; i < size; i++) {
            cout << "Title: " << inventory[i].title
                 << ", Remaining Quantity: " << inventory[i].quantity << endl;
        }
    }

    // Function to exit program and free memory
    void exitProgram() {
        delete[] inventory;
        inventory = nullptr;
        size = 0;
        cout << "All books deleted. Program exiting." << endl;
    }
};

int main() {
    Bookstore bookstore;
    int choice;

    do {
        cout << endl << "Bookstore Menu" << endl;
        cout << "1. Add Book to Inventory" << endl;
        cout << "2. Sell Book" << endl;
        cout << "3. Find Book by Author Name" << endl;
        cout << "4. Display Inventory" << endl;
        cout << "5. Update Book Quantity" << endl;
        cout << "6. Delete Book from Inventory" << endl;
        cout << "7. Generate Sales Report" << endl;
        cout << "8. Exit Program" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: bookstore.addBook(); break;
            case 2: bookstore.sellBook(); break;
            case 3: bookstore.findBooks(); break;
            case 4: bookstore.displayInventory(); break;
            case 5: bookstore.updateBookQuantity(); break;
            case 6: bookstore.deleteBook(); break;
            case 7: bookstore.generateSalesReport(); break;
            case 8: bookstore.exitProgram(); break;
            default: cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
