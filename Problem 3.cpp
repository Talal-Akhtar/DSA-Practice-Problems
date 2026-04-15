// Problem Statement
// You are given a singly linked list and an integer. Write a function to reverse the nodes of the list k at a k time and return its modified 
// list. If the number of nodes is not a multiple of, then left-out nodes at k the end should remain as they are. 
// Requirements
// •	You cannot alter the values in the nodes, only the nodes themselves may be changed.
// •	Do not use any extra memory (i.e., no arrays, no copying data, etc.), you must change the pointers in the linked list itself.

#include <iostream>
using namespace std;

// Node structure for singly linked list
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
public:
    // Reverse nodes in groups of k
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (!head || k <= 1) return head;

        ListNode* check = head;
        for (int i = 0; i < k; i++) {
            if (!check) return head;
            check = check->next;
        }

        ListNode* prev = nullptr;
        ListNode* curr = head;
        ListNode* nxt = nullptr;
        int count = 0;

        while (count < k && curr) {
            nxt = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nxt;
            count++;
        }

        head->next = reverseKGroup(curr, k);
        return prev;
    }
};

// Insert node at tail
void insertAtTail(ListNode*& head, int val) {
    ListNode* node = new ListNode(val);
    if (!head) {
        head = node;
        return;
    }
    ListNode* t = head;
    while (t->next) t = t->next;
    t->next = node;
}

void printList(ListNode* head) {
    while (head) {
        cout << head->val;
        if (head->next) cout << " -> ";
        head = head->next;
    }
    cout << endl;
}

void freeList(ListNode* head) {
    while (head) {
        ListNode* nxt = head->next;
        delete head;
        head = nxt;
    }
}

int main() {
    int n;
    cout << "Enter number of nodes: ";
    cin >> n;

    if (n <= 0) {
        cout << "List is empty." << endl;
        return 0;
    }

    ListNode* head = nullptr;
    cout << "Enter " << n << " node values: ";
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        insertAtTail(head, x);
    }

    int k;
    cout << "Enter k: ";
    cin >> k;

    cout << "Original list: ";
    printList(head);

    Solution sol;
    head = sol.reverseKGroup(head, k);

    cout << "Modified list: ";
    printList(head);

    freeList(head);
    return 0;
}
