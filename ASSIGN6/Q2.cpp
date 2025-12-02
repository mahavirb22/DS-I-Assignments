#include <iostream>
using namespace std;

typedef struct {
    int *arr;    
    int size;    
    int front;   
    int rear;    
} CQUEUE;

// Initialize queue
void initQueue(CQUEUE &q, int n) {
    q.size = n;
    q.arr = new int[n];
    q.front = -1;
    q.rear  = -1;
}

// Check if queue is full
bool isFull(CQUEUE &q) {
    return ( (q.front == 0 && q.rear == q.size - 1) ||
             (q.rear + 1 == q.front) );
}

// Check if queue is empty
bool isEmpty(CQUEUE &q) {
    return (q.front == -1);
}

// Enqueue (place new order)
void enqueue(CQUEUE &q, int orderId) {
    if (isFull(q)) {
        cout << "Cannot place order " << orderId << ". QUEUE OVERFLOW (Parlour full).\n";
        return;
    }

    if (isEmpty(q)) {
        q.front = q.rear = 0;
    } else {
        q.rear = (q.rear + 1) % q.size;
    }

    q.arr[q.rear] = orderId;
    cout << "Order " << orderId << " placed successfully.\n";
}

// Dequeue (serve next order)
int dequeue(CQUEUE &q) {
    if (isEmpty(q)) {
        cout << "No orders to serve. QUEUE UNDERFLOW.\n";
        return -1;
    }

    int servedOrder = q.arr[q.front];

    if (q.front == q.rear) {
        q.front = q.rear = -1;
    } else {
        q.front = (q.front + 1) % q.size;
    }

    cout << "Order " << servedOrder << " served.\n";
    return servedOrder;
}

// Display all orders in queue
void display(CQUEUE &q) {
    if (isEmpty(q)) {
        cout << "No pending orders. Queue is empty.\n";
        return;
    }

    cout << "Pending orders (front to rear): ";
    int i = q.front;
    while (true) {
        cout << q.arr[i];
        if (i == q.rear) break;
        cout << " <- ";
        i = (i + 1) % q.size;
    }
    cout << "\n";
}

int main() {
    int n;
    cout << "Enter maximum number of orders (queue size): ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid size.\n";
        return 0;
    }

    CQUEUE q;
    initQueue(q, n);

    int choice;
    int orderId;
    int autoId = 1;   

    do {
        cout << "\n--- PIZZA PARLOUR MENU ---\n";
        cout << "1. Place Order\n";
        cout << "2. Serve Order\n";
        cout << "3. Display Pending Orders\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter order ID (or 0 to auto-generate): ";
                cin >> orderId;
                if (orderId == 0) {
                    orderId = autoId++;
                }
                enqueue(q, orderId);
                break;

            case 2:
                dequeue(q);
                break;

            case 3:
                display(q);
                break;

            case 4:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    delete[] q.arr;
    return 0;
}
