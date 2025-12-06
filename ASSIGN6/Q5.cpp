#include <iostream>
#include <string>
using namespace std;

struct Node {
    string callName;   // customer name or call info
    Node* next;
};

Node* frontPtr = NULL;
Node* rearPtr = NULL;

// Add (enqueue) a customer call
void enqueue(string name) {
    Node* n = new Node;
    n->callName = name;
    n->next = NULL;

    if (rearPtr == NULL) {
        frontPtr = rearPtr = n;
    } else {
        rearPtr->next = n;
        rearPtr = n;
    }

    cout << "Call from " << name << " added to the queue.\n";
}

// Remove a customer call
void dequeue() {
    if (frontPtr == NULL) {
        cout << "No calls in the queue.\n";
        return;
    }

    Node* temp = frontPtr;
    cout << "Serving call of: " << frontPtr->callName << endl;

    frontPtr = frontPtr->next;
    if (frontPtr == NULL)
        rearPtr = NULL;

    delete temp;
}

// Display all calls waiting in queue
void display() {
    if (frontPtr == NULL) {
        cout << "No calls in the queue.\n";
        return;
    }

    cout << "Calls waiting in queue:\n";
    Node* temp = frontPtr;
    while (temp != NULL) {
        cout << "- " << temp->callName << endl;
        temp = temp->next;
    }
}

int main() {
    int choice;
    string name;

    do {
        cout << "\n--- Call Center Queue Menu ---\n";
        cout << "1. Add Customer Call (Enqueue)\n";
        cout << "2. Serve Next Call (Dequeue)\n";
        cout << "3. Display All Calls\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            
            case 1:
                cout << "Enter customer name: ";
                cin >> name;
                enqueue(name);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
