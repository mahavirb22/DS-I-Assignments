#include <iostream>
using namespace std;

struct GLL {
    int flag;
    string data;
    GLL* next;
    GLL* down;
    
    GLL() : flag(0), data(""), next(NULL), down(NULL) {}
};

GLL* createAtom() {
    GLL* node = new GLL();
    node->flag = 0;
    cout << "Enter atom: ";
    cin >> node->data;
    node->down = NULL;
    return node;
}

GLL* createSublist() {
    GLL* node = new GLL();
    node->flag = 1;
    node->data = "";
    cout << "-> Creating sublist:\n";
    return node;
}

GLL* create() {
    int choice;
    cout << "\n[0] Atom  [1] Sublist  [2] Stop\nChoice: ";
    cin >> choice;
    
    if (choice == 2) return NULL;
    
    GLL* node = NULL;
    if (choice == 0) {
        node = createAtom();
    } else if (choice == 1) {
        node = createSublist();
        node->down = create();
        cout << "<- Back to parent level\n";
    } else {
        cout << "Invalid! Try again.\n";
        return create();
    }
    
    node->next = create();
    return node;
}

void display(GLL* head) {
    cout << "{";
    while (head) {
        if (head->flag == 0)
            cout << head->data;
        else
            display(head->down);
        
        if (head->next) cout << ", ";
        head = head->next;
    }
    cout << "}";
}

void destroy(GLL* head) {
    while (head) {
        GLL* temp = head;
        if (head->flag == 1)
            destroy(head->down);
        head = head->next;
        delete temp;
    }
}

int main() {
    int choice;
    GLL* head = NULL;
    
    cout << "SET IMPLEMENTATION USING GLL (C++)  \n";
    
    do {
        cout << "\n[1] Create Set\n[2] Display Set\n[3] Exit\nChoice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                if (head != NULL) destroy(head);
                cout << "\nStart building your set...\n";
                head = create();
                cout << "\nSet created successfully!\n";
                break;
                
            case 2:
                if (head == NULL) {
                    cout << "\nSet is empty! Create a set first.\n";
                } else {
                    cout << "\nSet = ";
                    display(head);
                    cout << "\n";
                }
                break;
                
            case 3:
                if (head != NULL) destroy(head);
                cout << "\nExiting...\n";
                break;
                
            default:
                cout << "\nInvalid choice! Try again.\n";
        }
        
    } while(choice != 3);
    
    return 0;
}