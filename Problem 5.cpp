//Scenario: AI Game Script Validator
// In an AI-powered game engine, the behavior of characters is controlled through script commands written inside special tags. Each command is enclosed in start and end tags, similar to XML. The supported commands are:
// 	<MOVE> ... </MOVE>: Move the character.
// 	<ATTACK> ... </ATTACK>: Attack an opponent.
// 	<DEFEND> ... </DEFEND>: Defend against an attack.
// 	<LOOP> ... </LOOP>: Repeat actions.
// The game engine requires that scripts follow strict validation rules before they can run.
// Rules for Validation
// 	Matching Tags
// Every start tag must have a corresponding end tag of the same type.
// Example: <MOVE> </MOVE> is valid, but <MOVE> </ATTACK> is not.
// 	Proper Nesting
// Tags must be properly nested (last opened = first closed).
// Example: <LOOP><MOVE></MOVE></LOOP> valid. <LOOP><MOVE></LOOP></MOVE> is invalid.
// 	Restricted Nesting
// 	<ATTACK> cannot be placed inside <DEFEND>.
// 	<MOVE> must always be placed inside <LOOP> if <LOOP> is present.
// 	Nesting Depth Limit
// The maximum allowed nesting depth (d) is 4.
// Example:
// 	<LOOP><MOVE></MOVE></LOOP> (d= 2)
// 	<LOOP><LOOP><LOOP><MOVE></MOVE></LOOP></LOOP></LOOP> (d = 4).
// You are required to implement a script validator that checks whether a given sequence of tags forms a valid game script.

#include <iostream>
#include <string>
using namespace std;

class ActionsValidator {
private:
    string stack[100];      
    int top;               
    int maxDepthAllowed;    

public:
    ActionsValidator() {
        top = -1;
        maxDepthAllowed = 4;
    }

    // Check if stack is empty
    bool isEmpty() {
        return (top == -1);
    }

    bool isFull() {
        return (top == 99);
    }

    // Push a tag onto the stack
    void push(string tag) {
        if (!isFull()) {
            stack[++top] = tag;
        }
    }

    string pop() {
        if (!isEmpty()) {
            return stack[top--];
        }
        return "";
    }

    // Peek at the top tag
    string peek() {
        if (!isEmpty())
            return stack[top];
        return "";
    }

    int currentDepth() {
        return top + 1;
    }

    // Check if a tag is inside the stack
    bool isInside(string tagName) {
        for (int i = 0; i <= top; i++) {
            if (stack[i] == tagName)
                return true;
        }
        return false;
    }

    // Validate the input script
    bool validate(string input) {
        top = -1; 

        for (int i = 0; i < input.length(); i++) {
            if (input[i] != '<' && !isspace(input[i])) {
                return false;
            }

            if (input[i] == '<') {
                string tag = "";
                while (i < input.length() && input[i] != '>') {
                    tag += input[i];
                    i++;
                }

                if (i >= input.length())
                    return false;

                tag += '>';

              
                if (tag == "<MOVE>" || tag == "<ATTACK>" ||
                    tag == "<DEFEND>" || tag == "<LOOP>") {

                    if (currentDepth() >= maxDepthAllowed)
                        return false;

                    if (tag == "<ATTACK>" && isInside("<DEFEND>"))
                        return false;

                    if (tag == "<MOVE>" && !isInside("<LOOP>"))
                        return false;

                    push(tag);
                }
                // Closing tags
                else if (tag == "</MOVE>" || tag == "</ATTACK>" ||
                         tag == "</DEFEND>" || tag == "</LOOP>") {

                    if (isEmpty())
                        return false;

                    string topTag = peek();

                    if ((tag == "</MOVE>" && topTag != "<MOVE>") ||
                        (tag == "</ATTACK>" && topTag != "<ATTACK>") ||
                        (tag == "</DEFEND>" && topTag != "<DEFEND>") ||
                        (tag == "</LOOP>" && topTag != "<LOOP>"))
                        return false;

                    pop();
                }
                else {
                    return false;
                }
            }
        }

        if (!isEmpty())
            return false;

        return true;
    }
};

// Main function
int main() {
    ActionsValidator validator;
    string input;

    cout << "Enter script: ";
    getline(cin, input);

    if (validator.validate(input))
        cout << "Valid" << endl;
    else
        cout << "Invalid" << endl;

    return 0;
}
