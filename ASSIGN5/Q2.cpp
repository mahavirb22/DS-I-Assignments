#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// ---------------- Linked List Stack ----------------
struct Node {
    char data;
    Node* next;
};

Node* push(Node* head, char c) {
    Node* n = new Node;
    n->data = c;
    n->next = head;
    return n;
}

Node* pop(Node* head, char &val) {
    if (!head) {
        val = '\0';
        return NULL;
    }
    Node* temp = head;
    val = head->data;
    head = head->next;
    delete temp;
    return head;
}

char peek(Node* head) {
    return head ? head->data : '\0';
}

bool isEmpty(Node* head) {
    return head == NULL;
}

// ---------------- Precedence ----------------
int precedence(char c) {
    switch (c) {
        case '^': return 3;
        case '*': 
        case '/': return 2;
        case '+': 
        case '-': return 1;
        default : return 0;
    }
}

// ---------------- Infix → Postfix ----------------
string infixToPostfix(const string &infix) {
    Node* stack = NULL;
    string post = "";

    for (int i = 0; i < infix.length(); i++) {
        char c = infix[i];

        if (c == ' ') continue; // ignore spaces

        // -------- Operand → directly append --------
        if (isalnum(c)) {
            post += c;
        }
        else {
            switch (c) {

                // -------- Left parenthesis --------
                case '(':
                    stack = push(stack, c);
                    break;

                // -------- Right parenthesis --------
                case ')': {
                    char x;
                    while (!isEmpty(stack) && peek(stack) != '(') {
                        stack = pop(stack, x);
                        post += x;
                    }
                    stack = pop(stack, x);   // pop '('
                    break;
                }

                // -------- Operators --------
                case '+':
                case '-':
                case '*':
                case '/':
                case '^': {
                    char x;
                    while (!isEmpty(stack) &&
                           precedence(peek(stack)) >= precedence(c)) {
                        stack = pop(stack, x);
                        post += x;
                    }
                    stack = push(stack, c);
                    break;
                }

                // -------- Default --------
                default:
                    break;
            }
        }
    }

    // -------- Pop remaining operators --------
    char x;
    while (!isEmpty(stack)) {
        stack = pop(stack, x);
        post += x;
    }

    return post;
}

// ---------------- Main ----------------
int main() {
    string infix;
    cout << "Enter infix expression: ";
    getline(cin, infix);

    string postfix = infixToPostfix(infix);
    cout << "Postfix: " << postfix << endl;

    return 0;
}
