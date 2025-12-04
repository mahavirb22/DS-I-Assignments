#include <iostream>
#include <string>
using namespace std;

typedef struct node {
    int val;
    struct node* next;
} STACK;

// push value onto stack 
STACK* push(STACK* top, int v) {
    STACK* n = new STACK;
    n->val = v;
    n->next = top;
    return n;
}

// pop value
STACK* pop(STACK* top, int &popped, bool &poppedFlag) {
    if (!top) { poppedFlag = false; return NULL; }
    STACK* tmp = top;
    popped = top->val;
    poppedFlag = true;
    top = top->next;
    delete tmp;
    return top;
}

// peek top value 
int peek(STACK* top) {
    return top->val;
}

// isEmpty
bool isEmpty(STACK* top) {
    return top == NULL;
}

// free stack
void freeStack(STACK* top) {
    while (top) {
        STACK* t = top;
        top = top->next;
        delete t;
    }
}

int main() {
    cout << "Enter postfix expression (single-digit operands, operators + - * /), e.g. 231*+9- :\n";
    string expr;
    if (!getline(cin, expr)) return 0;

    string s;
    for (char c : expr) if (!isspace((unsigned char)c)) s.push_back(c);

    STACK* top = NULL;
    bool error = false;
    string errmsg;

    for (size_t i = 0; i < s.size(); ++i) {
        char c = s[i];

        if (c >= '0' && c <= '9') {
            int val = c - '0';
            top = push(top, val);
        }
        else if (c=='+' || c=='-' || c=='*' || c=='/') {
            // need two operands
            int b, a;
            bool ok;
            top = pop(top, b, ok);
            if (!ok) { error = true; errmsg = "Error: insufficient operands (missing second operand)."; break; }
            top = pop(top, a, ok);
            if (!ok) { error = true; errmsg = "Error: insufficient operands (missing first operand)."; break; }

            int res = 0;
            if (c == '+') res = a + b;
            else if (c == '-') res = a - b;
            else if (c == '*') res = a * b;
            else if (c == '/') {
                if (b == 0) { error = true; errmsg = "Error: division by zero."; break; }
                res = a / b; // integer division
            }
            top = push(top, res);
        }
        else {
            error = true;
            errmsg = string("Error: invalid character '") + c + "' in expression.";
            break;
        }
    }

    if (!error) {
        int finalVal;
        bool ok;
        top = pop(top, finalVal, ok);
        if (!ok) {
            cout << "Error: empty expression or no operands.\n";
            freeStack(top);
            return 0;
        }
        if (!isEmpty(top)) {
            cout << "Error: malformed expression - extra operands remain.\n";
            freeStack(top);
            return 0;
        }
        cout << "Result = " << finalVal << "\n";
    } else {
        cout << errmsg << "\n";
    }

    freeStack(top);
    return 0;
}
