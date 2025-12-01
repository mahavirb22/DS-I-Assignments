#include<iostream>
using namespace std;

struct Node {
    int data;
    Node* prev;
    Node* next;
};

Node* head = NULL;

void insert(int v) {
    Node* t = new Node{v, NULL, NULL};
    if (!head) {
        head = t;
        cout << "Inserted!\n";
        return;
    }
    Node* p = head;
    while (p->next) p = p->next;
    p->next = t;
    t->prev = p;
    cout << "Inserted!\n";
}

void bubbleSort() {
    if (!head || !head->next) return;
    
    bool swapped;
    Node* p;
    Node* last = NULL;

    do {
        swapped = false;
        p = head;

        while (p->next != last) {
            if (p->data > p->next->data) {
                swap(p->data, p->next->data);
                swapped = true;
            }
            p = p->next;
        }
        last = p;
    } while(swapped);
}

void display() {
    if (!head) {
        cout << "List is empty!\n";
        return;
    }
    Node* p = head;
    while (p) {
        cout << p->data << " ";
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
    int ch, v;
    
    cout << "   BUBBLE SORT USING DLL (C++)        \n";

    do {
        cout << "\n[1] Insert\n[2] Sort (Bubble)\n[3] Display\n[4] Exit\nChoice: ";
        cin >> ch;

        switch(ch) {
            case 1:
                cout << "Value: ";
                cin >> v;
                insert(v);
                break;

            case 2:
                bubbleSort();
                cout << "Sorted!\n";
                break;

            case 3:
                cout << "List: ";
                display();
                break;
                
            case 4:
                destroy();
                cout << "Exiting...\n";
                break;
                
            default:
                cout << "Invalid choice!\n";
        }
    } while(ch != 4);

    return 0;
}