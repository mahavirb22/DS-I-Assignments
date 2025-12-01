#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
    
    Node(int d) : data(d), prev(NULL), next(NULL) {}
};

Node* head = NULL;

void insertAtBegin(int v) {
    Node* t = new Node(v);
    if (!head) {
        head = t;
        cout << "Inserted at beginning!\n";
        return;
    }
    t->next = head;
    head->prev = t;
    head = t;
    cout << "Inserted at beginning!\n";
}

void insertAtEnd(int v) {
    Node* t = new Node(v);
    if (!head) {
        head = t;
        cout << "Inserted at end!\n";
        return;
    }
    Node* p = head;
    while (p->next) p = p->next;
    p->next = t;
    t->prev = p;
    cout << "Inserted at end!\n";
}

void insertAtPosition(int v, int pos) {
    if (pos <= 0) {
        cout << "Invalid position!\n";
        return;
    }
    
    if (pos == 1) {
        insertAtBegin(v);
        return;
    }
    
    Node* t = new Node(v);
    Node* p = head;
    
    for (int i = 1; i < pos - 1 && p; i++) {
        p = p->next;
    }
    
    if (!p) {
        cout << "Position out of range!\n";
        delete t;
        return;
    }
    
    t->next = p->next;
    t->prev = p;
    
    if (p->next) p->next->prev = t;
    p->next = t;
    
    cout << "Inserted at position " << pos << "!\n";
}

void insertAfterValue(int v, int val) {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }
    
    Node* p = head;
    while (p && p->data != val) {
        p = p->next;
    }
    
    if (!p) {
        cout << "Value " << val << " not found!\n";
        return;
    }
    
    Node* t = new Node(v);
    t->next = p->next;
    t->prev = p;
    
    if (p->next) p->next->prev = t;
    p->next = t;
    
    cout << "Inserted after value " << val << "!\n";
}

void insertBeforeValue(int v, int val) {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }
    
    Node* p = head;
    while (p && p->data != val) {
        p = p->next;
    }
    
    if (!p) {
        cout << "Value " << val << " not found!\n";
        return;
    }
    
    Node* t = new Node(v);
    t->next = p;
    t->prev = p->prev;
    
    if (p->prev) p->prev->next = t;
    else head = t;
    
    p->prev = t;
    
    cout << "Inserted before value " << val << "!\n";
}

void deleteAtBegin() {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }
    
    Node* temp = head;
    head = head->next;
    
    if (head) head->prev = NULL;
    
    delete temp;
    cout << "Deleted from beginning!\n";
}

void deleteAtEnd() {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }
    
    if (!head->next) {
        delete head;
        head = NULL;
        cout << "Deleted from end!\n";
        return;
    }
    
    Node* p = head;
    while (p->next) p = p->next;
    
    p->prev->next = NULL;
    delete p;
    cout << "Deleted from end!\n";
}

void deleteAtPosition(int pos) {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }
    
    if (pos <= 0) {
        cout << "Invalid position!\n";
        return;
    }
    
    if (pos == 1) {
        deleteAtBegin();
        return;
    }
    
    Node* p = head;
    for (int i = 1; i < pos && p; i++) {
        p = p->next;
    }
    
    if (!p) {
        cout << "Position out of range!\n";
        return;
    }
    
    if (p->prev) p->prev->next = p->next;
    if (p->next) p->next->prev = p->prev;
    
    delete p;
    cout << "Deleted from position " << pos << "!\n";
}

void deleteByValue(int val) {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }
    
    Node* p = head;
    while (p && p->data != val) {
        p = p->next;
    }
    
    if (!p) {
        cout << "Value " << val << " not found!\n";
        return;
    }
    
    if (p == head) {
        head = head->next;
        if (head) head->prev = NULL;
    } else {
        if (p->prev) p->prev->next = p->next;
        if (p->next) p->next->prev = p->prev;
    }
    
    delete p;
    cout << "Deleted value " << val << "!\n";
}

void display() {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }
    
    Node* p = head;
    cout << "List: ";
    while (p) {
        cout << p->data;
        if (p->next) cout << " ";
        p = p->next;
    }
    cout << "\n";
}

void destroy() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    int ch, v, pos, val;
    
    cout << "     DOUBLY LINKED LIST (C++)         \n";
    
    do {
        cout << "\n--- INSERT MENU ---\n";
        cout << "[1] Insert at Beginning\n[2] Insert at End\n";
        cout << "[3] Insert at Position\n[4] Insert After Value\n";
        cout << "[5] Insert Before Value\n";
        cout << "\n--- DELETE MENU ---\n";
        cout << "[6] Delete at Beginning\n[7] Delete at End\n";
        cout << "[8] Delete at Position\n[9] Delete by Value\n";
        cout << "\n--- DISPLAY MENU ---\n";
        cout << "[10] Display\n";
        cout << "[11] Exit\n";
        cout << "\nChoice: ";
        cin >> ch;
        
        switch(ch) {
            case 1:
                cout << "Value: ";
                cin >> v;
                insertAtBegin(v);
                break;
                
            case 2:
                cout << "Value: ";
                cin >> v;
                insertAtEnd(v);
                break;
                
            case 3:
                cout << "Value: ";
                cin >> v;
                cout << "Position: ";
                cin >> pos;
                insertAtPosition(v, pos);
                break;
                
            case 4:
                cout << "Value to insert: ";
                cin >> v;
                cout << "After value: ";
                cin >> val;
                insertAfterValue(v, val);
                break;
                
            case 5:
                cout << "Value to insert: ";
                cin >> v;
                cout << "Before value: ";
                cin >> val;
                insertBeforeValue(v, val);
                break;
                
            case 6:
                deleteAtBegin();
                break;
                
            case 7:
                deleteAtEnd();
                break;
                
            case 8:
                cout << "Position: ";
                cin >> pos;
                deleteAtPosition(pos);
                break;
                
            case 9:
                cout << "Value: ";
                cin >> val;
                deleteByValue(val);
                break;
                
            case 10:
                display();
                break;
                
            case 11:
                destroy();
                cout << "\nExiting...\n";
                break;
                
            default:
                cout << "\nInvalid choice!\n";
        }
        
    } while(ch != 11);
    
    return 0;
}



/*
SLL:
#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int d) : data(d), next(NULL) {}
};

Node* head = NULL;

void insertAtBegin(int v) {
    Node* t = new Node(v);
    t->next = head;
    head = t;
    cout << "Inserted at beginning!\n";
}

void insertAtEnd(int v) {
    Node* t = new Node(v);
    if (!head) {
        head = t;
        cout << "Inserted at end!\n";
        return;
    }
    Node* p = head;
    while (p->next) p = p->next;
    p->next = t;

    cout << "Inserted at end!\n";
}

void insertAtPosition(int v, int pos) {
    if (pos <= 0) {
        cout << "Invalid position!\n";
        return;
    }

    if (pos == 1) {
        insertAtBegin(v);
        return;
    }

    Node* p = head;
    for (int i = 1; i < pos - 1 && p; i++) {
        p = p->next;
    }

    if (!p) {
        cout << "Position out of range!\n";
        return;
    }

    Node* t = new Node(v);
    t->next = p->next;
    p->next = t;

    cout << "Inserted at position " << pos << "!\n";
}

void insertAfterValue(int v, int val) {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }

    Node* p = head;
    while (p && p->data != val) {
        p = p->next;
    }

    if (!p) {
        cout << "Value " << val << " not found!\n";
        return;
    }

    Node* t = new Node(v);
    t->next = p->next;
    p->next = t;
    cout << "Inserted after value " << val << "!\n";
}

void insertBeforeValue(int v, int val) {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }

    if (head->data == val) {
        insertAtBegin(v);
        return;
    }

    Node* p = head;
    while (p->next && p->next->data != val) {
        p = p->next;
    }

    if (!p->next) {
        cout << "Value " << val << " not found!\n";
        return;
    }

    Node* t = new Node(v);
    t->next = p->next;
    p->next = t;

    cout << "Inserted before value " << val << "!\n";
}

void deleteAtBegin() {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }

    Node* temp = head;
    head = head->next;
    delete temp;

    cout << "Deleted from beginning!\n";
}

void deleteAtEnd() {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }

    if (!head->next) {
        delete head;
        head = NULL;
        cout << "Deleted from end!\n";
        return;
    }

    Node* p = head;
    while (p->next->next) {
        p = p->next;
    }

    delete p->next;
    p->next = NULL;

    cout << "Deleted from end!\n";
}

void deleteAtPosition(int pos) {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }

    if (pos <= 0) {
        cout << "Invalid position!\n";
        return;
    }

    if (pos == 1) {
        deleteAtBegin();
        return;
    }

    Node* p = head;
    for (int i = 1; i < pos - 1 && p; i++) {
        p = p->next;
    }

    if (!p || !p->next) {
        cout << "Position out of range!\n";
        return;
    }

    Node* t = p->next;
    p->next = t->next;
    delete t;

    cout << "Deleted from position " << pos << "!\n";
}

void deleteByValue(int val) {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }

    if (head->data == val) {
        deleteAtBegin();
        return;
    }

    Node* p = head;
    while (p->next && p->next->data != val) {
        p = p->next;
    }

    if (!p->next) {
        cout << "Value " << val << " not found!\n";
        return;
    }

    Node* t = p->next;
    p->next = t->next;
    delete t;

    cout << "Deleted value " << val << "!\n";
}

void display() {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }

    Node* p = head;
    cout << "List: ";
    while (p) {
        cout << p->data;
        if (p->next) cout << " ";
        p = p->next;
    }
    cout << "\n";
}

void destroy() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    int ch, v, pos, val;

    cout << "     SINGLY LINKED LIST (C++)         \n";

    do {
        cout << "\n--- INSERT MENU ---\n";
        cout << "[1] Insert at Beginning\n[2] Insert at End\n";
        cout << "[3] Insert at Position\n[4] Insert After Value\n";
        cout << "[5] Insert Before Value\n";
        cout << "\n--- DELETE MENU ---\n";
        cout << "[6] Delete at Beginning\n[7] Delete at End\n";
        cout << "[8] Delete at Position\n[9] Delete by Value\n";
        cout << "\n--- DISPLAY MENU ---\n";
        cout << "[10] Display\n";
        cout << "[11] Exit\n";
        cout << "\nChoice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                cout << "Value: ";
                cin >> v;
                insertAtBegin(v);
                break;

            case 2:
                cout << "Value: ";
                cin >> v;
                insertAtEnd(v);
                break;

            case 3:
                cout << "Value: ";
                cin >> v;
                cout << "Position: ";
                cin >> pos;
                insertAtPosition(v, pos);
                break;

            case 4:
                cout << "Value to insert: ";
                cin >> v;
                cout << "After value: ";
                cin >> val;
                insertAfterValue(v, val);
                break;

            case 5:
                cout << "Value to insert: ";
                cin >> v;
                cout << "Before value: ";
                cin >> val;
                insertBeforeValue(v, val);
                break;

            case 6:
                deleteAtBegin();
                break;

            case 7:
                deleteAtEnd();
                break;

            case 8:
                cout << "Position: ";
                cin >> pos;
                deleteAtPosition(pos);
                break;

            case 9:
                cout << "Value: ";
                cin >> val;
                deleteByValue(val);
                break;

            case 10:
                display();
                break;

            case 11:
                destroy();
                cout << "\nExiting...\n";
                break;

            default:
                cout << "\nInvalid choice!\n";
        }

    } while (ch != 11);

    return 0;
}

*/