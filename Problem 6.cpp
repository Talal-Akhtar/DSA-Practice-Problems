// Implement a queue using a linked list and write a function isPalindrome() to determine if a given sequence of characters is a palindrome. For example:
// • r->a->d->a->r is palindrome.
// • a->p->p->l->e is not a palindrome.
// Note: You must use the Queue class for this function.

#include <iostream>
using namespace std;

struct Node {
    char data;
    Node* next;
};

// Queue class using linked list
class Queue {
private:
    Node* front;   
    Node* rear;    

public:
    // Constructor
    Queue() {
        front = nullptr;
        rear = nullptr;
    }

    bool isEmpty() {
        return (front == nullptr);
    }

    // Add element to the queue
    void enqueue(char value) {
        Node* temp = new Node;
        temp->data = value;
        temp->next = nullptr;

        if (isEmpty()) {
            front = rear = temp;
        } else {
            rear->next = temp;
            rear = temp;
        }
    }

    // Remove element from the queue
    char dequeue() {
        if (isEmpty()) {
            return '\0'; 
        }

        Node* temp = front;
        char value = temp->data;
        front = front->next;

        if (front == nullptr) {
            rear = nullptr;
        }

        delete temp;
        return value;
    }
    
    void display() {
        Node* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    bool isPalindrome() {
        if (isEmpty()) {
            return true;
        }

        string str = "";
        Node* temp = front;

        while (temp != nullptr) {
            str += temp->data;
            temp = temp->next;
        }

        // Check palindrome by comparing characters from both ends
        int i = 0;
        int j = str.length() - 1;

        while (i < j) {
            if (str[i] != str[j]) {
                return false;
            }
            i++;
            j--;
        }
        return true;
    }
};

// Main function
int main() {
    Queue q;
    string input;

    cout << "Enter a string: ";
    cin >> input;

    // Enqueue each character of the string
    for (char c : input) {
        q.enqueue(c);
    }

    cout << "Queue Elements: ";
    q.display();

    if (q.isPalindrome()) {
        cout << "It is a Palindrome" << endl;
    } else {
        cout << "It is NOT a Palindrome" << endl;
    }

    return 0;
}
