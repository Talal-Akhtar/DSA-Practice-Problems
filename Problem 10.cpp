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
 
    if (head == NULL) 
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
 
Node* removeNode(Node* head, int key) 
{ 
    if (head == NULL) 
    { 
        return NULL; 
    } 
 
    Node* curr = head; 
    Node* prev = NULL; 
 
    do 
    { 
        if (curr->data == key) 
        { 
            if (curr == head) 
            { 
                Node* temp = head; 
                while (temp->next != head) 
                { 
                    temp = temp->next; 
                } 
 
                if (head->next == head) 
                { 
                    delete head; 
                    return NULL; 
                } 
 
                temp->next = head->next; 
                head = head->next; 
                delete curr; 
                return head; 
            } 
            else 
            { 
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
 
void display(Node* head) 
{ 
    if (head == NULL) 
    { 
        cout << "List is empty"; 
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
 
int main() 
{ 
    Node* head = NULL; 
    int n, val, key; 
 
    cout << "Enter number of nodes: "; 
    cin >> n; 
 
    for (int i = 0; i < n; i++) 
    { 
        cin >> val; 
        head = insert(head, val); 
    } 
 
    cout << "Enter value to remove: "; 
    cin >> key; 
 
    head = removeNode(head, key); 
 
    display(head); 
 
    return 0; 
}