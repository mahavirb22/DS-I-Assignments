#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    
    Node(int d) : data(d), next(NULL) {}
};

Node* head = NULL;

void insert(int v) {
    Node* t = new Node(v);
    if (!head) {
        head = t;
        cout << "Inserted!\n";
        return;
    }
    Node* p = head;
    while (p->next) p = p->next;
    p->next = t;
    cout << "Inserted!\n";
}

void display(Node* h) {
    if (!h) {
        cout << "Empty";
        return;
    }
    cout << "{";
    while (h) {
        cout << h->data;
        if (h->next) cout << ", ";
        h = h->next;
    }
    cout << "}";
}

int getLength(Node* h) {
    int count = 0;
    while (h) {
        count++;
        h = h->next;
    }
    return count;
}

void frontBackSplit(Node* source, Node** front, Node** back) {
    if (!source) {
        *front = NULL;
        *back = NULL;
        return;
    }
    
    if (!source->next) {
        *front = source;
        *back = NULL;
        return;
    }
    
    int len = getLength(source);
    int frontLen = (len + 1) / 2;
    
    Node* current = source;
    for (int i = 1; i < frontLen; i++) {
        current = current->next;
    }
    
    *front = source;
    *back = current->next;
    current->next = NULL;
}

void destroy(Node* h) {
    while (h) {
        Node* temp = h;
        h = h->next;
        delete temp;
    }
}

int main() {
    int ch, v;
    Node *front = NULL, *back = NULL;
    
    cout << "      FRONT-BACK SPLIT (C++)          \n";
    
    do {
        cout << "\n[1] Insert Element\n[2] Display List\n";
        cout << "[3] Split List\n[4] Clear List\n[5] Exit\n";
        cout << "Choice: ";
        cin >> ch;
        
        switch(ch) {
            case 1:
                cout << "Value: ";
                cin >> v;
                insert(v);
                break;
                
            case 2:
                cout << "\nCurrent List: ";
                display(head);
                cout << "\n";
                break;
                
            case 3:
                if (!head) {
                    cout << "\nList is empty! Insert elements first.\n";
                    break;
                }
                
                if (front) destroy(front);
                if (back) destroy(back);
                
                cout << "\nOriginal List: ";
                display(head);
                cout << "\n";
                
                frontBackSplit(head, &front, &back);
                head = NULL;
                
                cout << "\nSplit Complete!\n";
                cout << "Front Half   : ";
                display(front);
                cout << "\nBack Half    : ";
                display(back);
                cout << "\n";
                break;
                
            case 4:
                destroy(head);
                destroy(front);
                destroy(back);
                head = front = back = NULL;
                cout << "\nList cleared!\n";
                break;
                
            case 5:
                destroy(head);
                destroy(front);
                destroy(back);
                cout << "\nExiting...\n";
                break;
                
            default:
                cout << "\nInvalid choice!\n";
        }
        
    } while(ch != 5);
    
    return 0;
}