// You are given a circular singly linked list where each node contains an integer value and a pointer next that points to the next node in the list. The last node's next pointer points back to the first node, making the list circular. Write a function in C++ that detects and removes the first node with a specified value from the circular linked list. If the value is not present, you should handle it properly.
// Constraints:
// The function should return the head of the modified list.
// The circular linked list may be empty.
// Example:
// Given the circular linked list: 1 -> 2 -> 3 -> 4 -> 5 -> (back to 1)
// Removing the node with value 3 should result in the list: 1 -> 2 -> 4 -> 5 -> (back to 1)
// Removing the node with value 1 should result in the list: 2 -> 3 -> 4 -> 5 -> (back to 2)

#include <iostream> 
using namespace std; 
 
struct Node 
{ 
    int data; 
    Node* next; 
}; 
 
Node* insert(Node* head, int val) 
{ 
    Node* newNode = new Node; 
    newNode->data = val; 
    newNode->next = nullptr; 
 
    if (head == nullptr) 
    { 
        newNode->next = newNode; 
        return newNode; 
    } 
 
    Node* temp = head; 
    while (temp->next != head) 
    { 
        temp = temp->next; 
    } 
 
    temp->next = newNode; 
    newNode->next = head; 
 
    return head; 
} 
 
// Improved removeNode with proper memory management
Node* removeNode(Node* head, int key) 
{ 
    if (head == nullptr) 
    { 
        return nullptr; 
    } 
 
    // Special case: only one node in the list
    if (head->next == head) 
    { 
        if (head->data == key) 
        { 
            delete head; 
            return nullptr; 
        } 
        return head; 
    } 
 
    // Case 1: Removing the head node
    if (head->data == key) 
    { 
        Node* temp = head; 
        while (temp->next != head) 
        { 
            temp = temp->next; 
        } 
 
        Node* newHead = head->next; 
        temp->next = newHead; 
        delete head; 
        return newHead; 
    } 
 
    // Case 2: Removing a non-head node
    Node* curr = head->next; 
    Node* prev = head; 
 
    while (curr != head) 
    { 
        if (curr->data == key) 
        { 
            prev->next = curr->next; 
            delete curr; 
            return head; 
        } 
        prev = curr; 
        curr = curr->next; 
    } 
 
    // Node not found
    return head; 
} 
 
void display(Node* head) 
{ 
    if (head == nullptr) 
    { 
        cout << "List is empty" << endl; 
        return; 
    } 
 
    Node* temp = head; 
 
    do 
    { 
        cout << temp->data << " "; 
        temp = temp->next; 
    } while (temp != head); 
 
    cout << endl; 
} 

// Clean up entire list
void deleteList(Node* head) 
{ 
    if (head == nullptr) return; 
 
    Node* temp = head->next; 
    head->next = nullptr; // Break the circle
 
    while (temp != nullptr) 
    { 
        Node* toDelete = temp; 
        temp = temp->next; 
        delete toDelete; 
    } 
 
    delete head; 
} 
 
int main() 
{ 
    Node* head = nullptr; 
    int n, val, key; 
 
    cout << "Enter number of nodes: "; 
    cin >> n; 
 
    if (n < 0) 
    { 
        cout << "Invalid input: n must be non-negative" << endl; 
        return 1; 
    } 
 
    for (int i = 0; i < n; i++) 
    { 
        cin >> val; 
        head = insert(head, val); 
    } 
 
    cout << "Enter value to remove: "; 
    cin >> key; 
 
    head = removeNode(head, key); 
 
    display(head); 
    
    deleteList(head); // Clean up memory
 
    return 0; 
}
