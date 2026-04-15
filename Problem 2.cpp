// Create a program in C++ that implements a singly linked list. The task is to add a node at the end of the linked list. 
// Instructions:
// Each node in the linked list should have two fields:
// •	An integer field to store data.
// •	A pointer to the next node.
// Implement a class LinkedList that contains the following methods:
// •	void insertEnd (int value): This method will add a new node with the given value to the end of the list.
// •	void display (): This method will display the contents of the linked list.
// Implement the following functions for linked list:
// 1)	Insert front
// 2)	Insert End
// 3)	Insert after number
// 4)	List is full
// 5)	List is empty
// 6)	Display all element
// 7)	Sort the list
// 8)	Limit user so that he/she can only add 10 numbers in the list. After that give error that list is full.
// 9)	Delete a specific node entered by user

#include <iostream>
using namespace std;

class Node {
public:
    int val;
    Node* next;

    Node(int v) : val(v), next(nullptr) {}
};

class LinkedList {
public:
    static const int MAX_SIZE = 10; 

private:
    Node* head;
    int length;

public:
    LinkedList() : head(nullptr), length(0) {}
    ~LinkedList() { clear(); }

    bool isEmpty() const { return head == nullptr; }
    bool isFull() const { return length >= MAX_SIZE; }

    void insertFront(int value) {
        if (isFull()) {
            cout << "Error: List is already full (max " << MAX_SIZE << " elements)." << endl;
            return;
        }
        Node* temp = new Node(value);
        temp->next = head;
        head = temp;
        length++;
    }

    void insertEnd(int value) {
        if (isFull()) {
            cout << "Error: List is full (max " << MAX_SIZE << " elements)." << endl;
            return;
        }
        Node* temp = new Node(value);
        if (isEmpty()) {
            head = temp;
            length++;
            return;
        }
        Node* curr = head;
        while (curr->next != nullptr) {
            curr = curr->next;
        }
        curr->next = temp;
        length++;
    }

    void insertAfterNumber(int afterValue, int newValue) {
        if (isFull()) {
            cout << "Error: List is full (max " << MAX_SIZE << " elements)." << endl;
            return;
        }
        if (isEmpty()) {
            cout << "Error: List is empty. Cannot insert after " << afterValue << "." << endl;
            return;
        }
        Node* curr = head;
        while (curr != nullptr && curr->val != afterValue) {
            curr = curr->next;
        }
        if (curr == nullptr) {
            cout << "Error: " << afterValue << " not found in the list." << endl;
            return;
        }
        Node* temp = new Node(newValue);
        temp->next = curr->next;
        curr->next = temp;
        length++;
    }

    void display() const {
        if (isEmpty()) {
            cout << "List is empty." << endl;
            return;
        }
        Node* curr = head;
        cout << "List: ";
        while (curr != nullptr) {
            cout << curr->val;
            if (curr->next != nullptr) cout << " -> ";
            curr = curr->next;
        }
        cout << endl;
    }

    void sortList() {
        if (length < 2) {
            cout << "List is already sorted (0 or 1 element)." << endl;
            return;
        }
        bool swapped;
        do {
            swapped = false;
            Node* curr = head;
            while (curr != nullptr && curr->next != nullptr) {
                if (curr->val > curr->next->val) {
                    int tmp = curr->val;
                    curr->val = curr->next->val;
                    curr->next->val = tmp;
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
        cout << "List sorted successfully." << endl;
    }

    bool deleteValue(int value) {
        if (isEmpty()) {
            cout << "Error: List is empty. Nothing to delete." << endl;
            return false;
        }
        if (head->val == value) {
            Node* toDelete = head;
            head = head->next;
            delete toDelete;
            length--;
            cout << "Deleted: " << value << endl;
            return true;
        }
        Node* prev = head;
        Node* curr = head->next;
        while (curr != nullptr && curr->val != value) {
            prev = curr;
            curr = curr->next;
        }
        if (curr == nullptr) {
            cout << "Error: " << value << " not found in the list." << endl;
            return false;
        }
        prev->next = curr->next;
        delete curr;
        length--;
        cout << "Deleted: " << value << endl;
        return true;
    }

    void clear() {
        Node* curr = head;
        while (curr != nullptr) {
            Node* nxt = curr->next;
            delete curr;
            curr = nxt;
        }
        head = nullptr;
        length = 0;
    }

    int size() const { return length; }
};

int main() {
    LinkedList list;
    int choice;

    do {
        cout << endl << "=== Singly Linked List Menu ===" << endl;
        cout << "1. Insert Front" << endl;
        cout << "2. Insert End" << endl;
        cout << "3. Insert After a Number" << endl;
        cout << "4. Display All Elements" << endl;
        cout << "5. Sort the List" << endl;
        cout << "6. Delete a Specific Node (by value)" << endl;
        cout << "7. Check if List is Empty" << endl;
        cout << "8. Check if List is Full" << endl;
        cout << "0. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (!cin) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input." << endl;
            continue;
        }

        if (choice == 1) {
            int x;
            cout << "Enter value: ";
            cin >> x;
            list.insertFront(x);
        }
        else if (choice == 2) {
            int x;
            cout << "Enter value: ";
            cin >> x;
            list.insertEnd(x);
        }
        else if (choice == 3) {
            int afterVal, newVal;
            cout << "Insert after which number? ";
            cin >> afterVal;
            cout << "Enter new value: ";
            cin >> newVal;
            list.insertAfterNumber(afterVal, newVal);
        }
        else if (choice == 4) {
            list.display();
        }
        else if (choice == 5) {
            list.sortList();
            list.display();
        }
        else if (choice == 6) {
            int x;
            cout << "Enter value to delete: ";
            cin >> x;
            list.deleteValue(x);
        }
        else if (choice == 7) {
            cout << (list.isEmpty() ? "List is empty." : "List is not empty.") << endl;
        }
        else if (choice == 8) {
            cout << (list.isFull() ? "List is full." : "List is not full.") << endl;
        }
        else if (choice == 0) {
            cout << "Exit the program" << endl;
        }
        else {
            cout << "Invalid choice." << endl;
        }
    } while (choice != 0);

    return 0;
}
