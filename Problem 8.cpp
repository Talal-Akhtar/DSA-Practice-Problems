//You are given an unsorted doubly linked list where each node contains an integer value and two pointers: prev (pointing to the previous node) 
//and next (pointing to the next node). Write a function to remove all duplicate nodes from the list. The resulting list should contain only 
//unique values, preserving the order of their first occurrence.
// Constraints:
// •	The doubly linked list may be empty.
// Example:
// Given the doubly linked list: 4 <-> 2 <-> 4 <-> 3 <-> 2 <-> 1 <-> 3
// The resulting list after removing duplicates should be: 4 <-> 2 <-> 3 <-> 1

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;

    // Constructor
    Node(int val) {
        data = val;
        prev = nullptr;
        next = nullptr;
    }
};

class DoublyLinkedList {
public:
    Node* head;

    // Constructor
    DoublyLinkedList() {
        head = nullptr;
    }

    void insert(int val) {
        Node* newNode = new Node(val);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = newNode;
        newNode->prev = temp;
    }

    void removeDuplicates() {
        if (head == nullptr) return;

        Node* current = head;

        while (current != nullptr) {
            Node* runner = current->next;

            while (runner != nullptr) {
                if (runner->data == current->data) {
                    Node* temp = runner;

                    if (runner->prev != nullptr)
                        runner->prev->next = runner->next;

                    if (runner->next != nullptr)
                        runner->next->prev = runner->prev;

                    runner = runner->next;
                    delete temp;
                } else {
                    runner = runner->next;
                }
            }
            current = current->next;
        }
    }

    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data;
            if (temp->next != nullptr) cout << " -> ";
            temp = temp->next;
        }
        cout << endl;
    }
};

int main() {
    DoublyLinkedList list;
    int n, value;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements:" << endl;
    for (int i = 0; i < n; i++) {
        cin >> value;
        list.insert(value);
    }

    cout << "Original List:" << endl;
    list.display();

    list.removeDuplicates();

    cout << "After Removing Duplicates:" << endl;
    list.display();

    return 0;
}
