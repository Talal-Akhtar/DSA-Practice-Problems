// Given string num representing a non-negative integer num, and an integer k, return the smallest possible integer after removing k digits from num. You have to remove the leading zeros if left any.
// Logic of RemoveKDigits:
// 1.	Initialize a Stack: The function starts by creating an instance of the Stack class, which is defined to handle characters.
// 2.	Iterate through the input string num: The function iterates through each character of the input string num.
// 3.	Push characters onto the stack with conditions: For each character digit in num, the function checks the following conditions:
// •	If k > 0 (i.e., we still need to remove more digits), and the stack is not empty, and the top element of the stack (stk.top()) is greater than the current digit, it pops elements from the stack until one of the conditions is not met. This step effectively removes larger digits from the stack to minimize the value.
// •	After popping, it pushes the current digit onto the stack
// 4.	Remove remaining digits to meet k requirement: After iterating through all the digits in the input string, the function checks if there are still remaining digits to be removed (k >0). If so, it continues popping elements from the stack until either k becomes zero or the stack becomes empty.
// 5.	Build the result string: The function then constructs the result string by popping elements from the stack. Since the digits were pushed onto the stack in reverse order, popping them off gives them in the correct order.
// 6.	Remove leading zeros: After constructing the result string, the function removes any leading zeros.

#include <iostream>
#include <string>
using namespace std;

class Stack {
    char* arr;   
    int top;    
    int cap;     

public:
    // Constructor
    Stack(int n) {
        cap = n;
        arr = new char[cap];
        top = -1;
    }

    // Destructor
    ~Stack() {
        delete[] arr;
    }

    // Check if stack is empty
    bool empty() const {
        return top == -1;
    }

    void push(char c) {
        if (top < cap - 1) arr[++top] = c;
    }

    // Pop element from stack
    void pop() {
        if (!empty()) top--;
    }

    // Peek at top element
    char peek() const {
        return arr[top];
    }

    string toString() const {
        string s;
        for (int i = 0; i <= top; i++) s += arr[i];
        return s;
    }
};

string removeKdigits(string num, int k) {
    Stack st((int)num.size());

    for (char d : num) {
        while (k > 0 && !st.empty() && st.peek() > d) {
            st.pop();
            k--;
        }
        st.push(d);
    }

    while (k > 0 && !st.empty()) {
        st.pop();
        k--;
    }

    // Build result string
    string res = st.toString();

    int i = 0;
    while (i < (int)res.size() && res[i] == '0') i++;
    res = res.substr(i);

    return res.empty() ? "0" : res;
}

int main() {
    string num, kStr;
    cout << "Enter num: ";
    cin >> num;

    cout << "Enter k: ";
    cin >> kStr;

    int k = stoi(kStr);

    cout << "Output Number: " << removeKdigits(num, k) << endl;

    return 0;
}
