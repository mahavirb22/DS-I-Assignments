#include <iostream>
using namespace std;

// Add element to queue
void enqueue(int q[], int size, int &front, int &rear, int value) {
    if (rear == size - 1) {
        cout << "Queue is full.\n";
        return;
    }
    if (front == -1) front = 0;
    q[++rear] = value;
    cout << value << " added to queue.\n";
}

// Delete element
void dequeue(int q[], int &front, int &rear) {
    if (front == -1 || front > rear) {
        cout << "Queue is empty.\n";
        return;
    }

    cout << "Deleted: " << q[front] << endl;
    front++;

    if (front > rear) front = rear = -1;
}

// Display queue
void display(int q[], int front, int rear) {
    if (front == -1 || front > rear) {
        cout << "Queue is empty.\n";
        return;
    }

    cout << "Queue elements: ";
    for (int i = front; i <= rear; i++)
        cout << q[i] << " ";
    cout << endl;
}

int main() {
    int size;
    cout << "Enter size of each queue: ";
    cin >> size;

    // Create two dynamic queues
    int* q1 = new int[size];
    int* q2 = new int[size];

    int front1 = -1, rear1 = -1;
    int front2 = -1, rear2 = -1;

    int choice, qChoice, value;

    do {
        cout << "\n---- Multiple Queue Menu ----\n";
        cout << "1. Add to Queue\n";
        cout << "2. Delete from Queue\n";
        cout << "3. Display Queue\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice >= 1 && choice <= 3) {
            cout << "Select Queue (1 or 2): ";
            cin >> qChoice;
        }

        switch (choice) {

            case 1:
                cout << "Enter value to add: ";
                cin >> value;

                if (qChoice == 1)
                    enqueue(q1, size, front1, rear1, value);
                else if (qChoice == 2)
                    enqueue(q2, size, front2, rear2, value);
                else
                    cout << "Invalid queue selection.\n";
                break;

            case 2:
                if (qChoice == 1)
                    dequeue(q1, front1, rear1);
                else if (qChoice == 2)
                    dequeue(q2, front2, rear2);
                else
                    cout << "Invalid queue selection.\n";
                break;

            case 3:
                if (qChoice == 1)
                    display(q1, front1, rear1);
                else if (qChoice == 2)
                    display(q2, front2, rear2);
                else
                    cout << "Invalid queue selection.\n";
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    delete[] q1;
    delete[] q2;

    return 0;
}
