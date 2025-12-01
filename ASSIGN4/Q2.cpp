#include<iostream>
using namespace std;

struct Node {
    int coef, exp;
    Node* next;
};

Node* insert(Node* h, int c, int e) {
    if (c == 0) return h;
    
    Node* t = new Node{c, e, NULL};
    
    if (!h || h->exp < e) {
        t->next = h;
        return t;
    }
    
    Node* p = h;
    while (p->next && p->next->exp > e) {
        p = p->next;
    }
    
    if (p->exp == e) {
        p->coef += c;
        delete t;
        return h;
    }
    
    t->next = p->next;
    p->next = t;
    return h;
}

void display(Node* h) {
    if (!h) {
        cout << "0";
        return;
    }
    
    bool first = true;
    while (h) {
        if (h->coef != 0) {
            if (!first && h->coef > 0) cout << " + ";
            if (h->coef < 0) cout << " - ";
            
            int absCoef = abs(h->coef);
            
            if (h->exp == 0) {
                if (!first) cout << absCoef;
                else cout << h->coef;
            } else if (h->exp == 1) {
                if (absCoef != 1) {
                    if (!first) cout << absCoef << "x";
                    else cout << h->coef << "x";
                } else {
                    if (first && h->coef < 0) cout << "x";
                    else if (!first) cout << "x";
                    else cout << "x";
                }
            } else {
                if (absCoef != 1) {
                    if (!first) cout << absCoef << "x^" << h->exp;
                    else cout << h->coef << "x^" << h->exp;
                } else {
                    if (first && h->coef < 0) cout << "x^" << h->exp;
                    else if (!first) cout << "x^" << h->exp;
                    else cout << "x^" << h->exp;
                }
            }
            first = false;
        }
        h = h->next;
    }
}

Node* add(Node* a, Node* b) {
    Node* r = NULL;
    
    while (a && b) {
        if (a->exp == b->exp) {
            int sumCoef = a->coef + b->coef;
            if (sumCoef != 0) {
                r = insert(r, sumCoef, a->exp);
            }
            a = a->next;
            b = b->next;
        } else if (a->exp > b->exp) {
            r = insert(r, a->coef, a->exp);
            a = a->next;
        } else {
            r = insert(r, b->coef, b->exp);
            b = b->next;
        }
    }
    
    while (a) {
        r = insert(r, a->coef, a->exp);
        a = a->next;
    }
    
    while (b) {
        r = insert(r, b->coef, b->exp);
        b = b->next;
    }
    
    return r;
}

void destroy(Node* h) {
    while (h) {
        Node* temp = h;
        h = h->next;
        delete temp;
    }
}

int main() {
    Node *p1 = NULL, *p2 = NULL, *sum = NULL;
    int ch, c, e;
    
    cout << "   POLYNOMIAL ADDITION USING SLL (C++) \n";
    
    do {
        cout << "\n[1] Insert in P1\n[2] Insert in P2\n[3] Add Polynomials\n";
        cout << "[4] Display All\n[5] Exit\nChoice: ";
        cin >> ch;
        
        switch(ch) {
            case 1:
                cout << "Coeff Exp: ";
                cin >> c >> e;
                p1 = insert(p1, c, e);
                break;
                
            case 2:
                cout << "Coeff Exp: ";
                cin >> c >> e;
                p2 = insert(p2, c, e);
                break;
                
            case 3:
                if (sum) destroy(sum);
                sum = add(p1, p2);
                cout << "Polynomials added successfully!\n";
                break;
                
            case 4:
                cout << "\nP1  : ";
                display(p1);
                cout << "\nP2  : ";
                display(p2);
                cout << "\nSum : ";
                display(sum);
                cout << "\n";
                break;
                
            case 5:
                destroy(p1);
                destroy(p2);
                destroy(sum);
                cout << "\nExiting...\n";
                break;
                
            default:
                cout << "\nInvalid choice!\n";
        }
    } while(ch != 5);
    
    return 0;
}