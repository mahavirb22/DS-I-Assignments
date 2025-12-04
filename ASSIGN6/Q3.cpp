#include <iostream>
#include <string>
using namespace std;

struct Node {
    string name;
    Node* next;
};

Node* frontPtr = NULL;
Node* rearPtr = NULL;

// Insert passenger at rear
void enqueue(string name) {
    Node* n = new Node;
    n->name = name;
    n->next = NULL;

    if (rearPtr == NULL) {
        frontPtr = rearPtr = n;
    } else {
        rearPtr->next = n;
        rearPtr = n;
    }
    cout << name << " added to the queue.\n";
}

// Display front passenger
void showFront() {
    if (frontPtr == NULL) {
        cout << "Queue is empty.\n";
    } else {
        cout << "Front passenger: " << frontPtr->name << "\n";
    }
}

// Remove front passenger
void dequeue() {
    if (frontPtr == NULL) {
        cout << "Queue is empty.\n";
        return;
    }

    Node* temp = frontPtr;
    cout << "Removing: " << frontPtr->name << "\n";

    frontPtr = frontPtr->next;

    if (frontPtr == NULL)
        rearPtr = NULL;

    delete temp;
}

// Count passengers
int countPassengers() {
    int count = 0;
    Node* temp = frontPtr;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

int main() {
    int choice;
    string pname;

    do {
        cout << "\n---- Passenger Queue Menu ----\n";
        cout << "1. Insert new passenger\n";
        cout << "2. Show front passenger\n";
        cout << "3. Remove front passenger\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                cout << "Enter passenger name: ";
                cin >> pname;
                enqueue(pname);
                break;

            case 2:
                showFront();
                break;

            case 3:
                dequeue();
                break;

            case 4:
                cout << "\nProgram ending...\n";
                cout << "Passengers left in queue: " << countPassengers() << "\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
