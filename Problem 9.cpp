// Problem Statement
// You are given a circular singly linked list where each node contains an integer value and a pointer next that points to the next node in the 
//list. The last node's next pointer points back to the first node, making the list circular. Write a function in C++ that detects and removes 
//the first node with a specified value from the circular linked list. If the value is not present, you should handle it properly.
// Constraints:
// The function should return the head of the modified list.
// The circular linked list may be empty.
// Example:
// Given the circular linked list: 1 -> 2 -> 3 -> 4 -> 5 -> (back to 1)
// Removing the node with value 3 should result in the list: 1 -> 2 -> 4 -> 5 -> (back to 1)
// Removing the node with value 1 should result in the list: 2 -> 3 -> 4 -> 5 -> (back to 2)

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

Node* insert(Node* head, int val) {
    Node* newNode = new Node;
    newNode->data = val;

    if (head == nullptr) {
        newNode->next = newNode; 
        return newNode;
    }

    Node* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->next = head;

    return head;
}

Node* removeNode(Node* head, int key) {
    if (head == nullptr) {
        return nullptr;
    }

    Node* curr = head;
    Node* prev = nullptr;

    do {
        if (curr->data == key) {
            if (curr == head) {
                Node* temp = head;
                while (temp->next != head) {
                    temp = temp->next;
                }

                // If only one node exists
                if (head->next == head) {
                    delete head;
                    return nullptr;
                }

                temp->next = head->next;
                head = head->next;
                delete curr;
                return head;
            } else {
                prev->next = curr->next;
                delete curr;
                return head;
            }
        }

        prev = curr;
        curr = curr->next;

    } while (curr != head);

    return head;
}

void display(Node* head) {
    if (head == nullptr) {
        cout << "List is empty" << endl;
        return;
    }

    Node* temp = head;
    do {
        cout << temp->data << " ";
        temp = temp->next;
    } while (temp != head);

    cout << endl;
}

int main() {
    Node* head = nullptr;
    int n, val, key;

    cout << "Enter number of nodes: ";
    cin >> n;

    cout << "Enter values: ";
    for (int i = 0; i < n; i++) {
        cin >> val;
        head = insert(head, val);
    }

    cout << "Enter value to remove: ";
    cin >> key;

    head = removeNode(head, key);

    cout << "Circular Linked List after removal: ";
    display(head);

    return 0;
}
