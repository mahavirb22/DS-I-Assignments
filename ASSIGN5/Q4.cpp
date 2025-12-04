#include <iostream>
#include <string>
using namespace std;

typedef struct node {
    char data;
    struct node* next;
} STACK;

// Create node
STACK* createNode(char c) {
    STACK* n = new STACK;
    n->data = c;
    n->next = NULL;
    return n;
}

// Push character onto stack
STACK* push(STACK* top, char c) {
    STACK* n = createNode(c);
    n->next = top;
    return n;   // new top
}

// Pop character from stack
STACK* pop(STACK* top, char &popped) {
    if (!top) {
        popped = '\0';
        return NULL;
    }
    STACK* temp = top;
    popped = temp->data;
    top = top->next;
    delete temp;
    return top;
}

// Check if stack is empty
bool isEmpty(STACK* top) {
    return (top == NULL);
}

// Check if closing bracket matches last opening bracket
bool isMatching(char open, char close) {
    return ((open == '(' && close == ')') ||
            (open == '{' && close == '}') ||
            (open == '[' && close == ']'));
}

int main() {
    string s;
    cout << "Enter string of parentheses: ";
    cin >> s;

    STACK* top = NULL;
    bool balanced = true;

    for (int i = 0; i < s.length(); i++) {
        char ch = s[i];

        // If opening bracket → push
        if (ch == '(' || ch == '{' || ch == '[') {
            top = push(top, ch);
        }
        // If closing bracket → pop and match
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (isEmpty(top)) {       // nothing to match
                balanced = false;
                break;
            }
            char open;
            top = pop(top, open);
            if (!isMatching(open, ch)) {
                balanced = false;
                break;
            }
        }
    }

    if (!isEmpty(top))
        balanced = false;

    if (balanced)
        cout << "Balanced\n";
    else
        cout << "Not Balanced\n";

    return 0;
}
