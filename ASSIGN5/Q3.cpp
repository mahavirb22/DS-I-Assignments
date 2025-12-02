#include <iostream>
using namespace std;

int main() {
    int N, k;
    cout << "Enter total array size N: ";
    cin >> N;
    cout << "Enter number of stacks k (>1): ";
    cin >> k;
    if (k <= 1) {
        cout << "Number of stacks should be > 1. Exiting.\n";
        return 0;
    }
    if (N < k) {
        cout << "Array size must be >= number of stacks. Exiting.\n";
        return 0;
    }

    // allocate array and metadata
    int *arr = new int[N];

    int *baseIndex = new int[k];
    int *capacity = new int[k];
    int *topIndex = new int[k];

    int baseCap = N / k;
    int rem = N % k;

    // compute capacities and base indices
    int idx = 0;
    for (int i = 0; i < k; ++i) {
        capacity[i] = baseCap + (i < rem ? 1 : 0);
        baseIndex[i] = idx;
        // initialize top to one position below base (empty)
        topIndex[i] = baseIndex[i] - 1;
        idx += capacity[i];
    }

    cout << "\nConfiguration:\n";
    cout << "Total size N = " << N << ", stacks k = " << k << "\n";
    for (int i = 0; i < k; ++i) {
        cout << " Stack " << i+1 << ": base = " << baseIndex[i]
             << ", capacity = " << capacity[i] << "\n";
    }
    cout << "\n";

    // menu
    int choice;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Push\n";
        cout << "2. Pop\n";
        cout << "3. Latest/Top (peek)\n";
        cout << "4. isEmpty\n";
        cout << "5. isFull (stack overflow check)\n";
        cout << "6. Display all stacks\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int s, val;
            cout << "Enter stack number (1.." << k << "): ";
            cin >> s;
            if (s < 1 || s > k) { cout << "Invalid stack number.\n"; continue; }
            int si = s - 1;
            // check overflow
            if (topIndex[si] >= baseIndex[si] + capacity[si] - 1) {
                cout << "Stack Overflow on stack " << s << ". Cannot push.\n";
            } else {
                cout << "Enter value to push: ";
                cin >> val;
                topIndex[si]++;
                arr[topIndex[si]] = val;
                cout << "Pushed " << val << " into stack " << s << ".\n";
            }
        }
        else if (choice == 2) {
            int s;
            cout << "Enter stack number (1.." << k << "): ";
            cin >> s;
            if (s < 1 || s > k) { cout << "Invalid stack number.\n"; continue; }
            int si = s - 1;
            // check underflow
            if (topIndex[si] < baseIndex[si]) {
                cout << "Stack Underflow on stack " << s << ". Nothing to pop.\n";
            } else {
                int val = arr[topIndex[si]];
                topIndex[si]--;
                cout << "Popped " << val << " from stack " << s << ".\n";
            }
        }
        else if (choice == 3) {
            int s;
            cout << "Enter stack number (1.." << k << "): ";
            cin >> s;
            if (s < 1 || s > k) { cout << "Invalid stack number.\n"; continue; }
            int si = s - 1;
            if (topIndex[si] < baseIndex[si]) {
                cout << "Stack " << s << " is empty.\n";
            } else {
                cout << "Top of stack " << s << " = " << arr[topIndex[si]] << "\n";
            }
        }
        else if (choice == 4) {
            int s;
            cout << "Enter stack number (1.." << k << "): ";
            cin >> s;
            if (s < 1 || s > k) { cout << "Invalid stack number.\n"; continue; }
            int si = s - 1;
            if (topIndex[si] < baseIndex[si]) cout << "Stack " << s << " is EMPTY.\n";
            else cout << "Stack " << s << " is NOT empty.\n";
        }
        else if (choice == 5) {
            int s;
            cout << "Enter stack number (1.." << k << "): ";
            cin >> s;
            if (s < 1 || s > k) { cout << "Invalid stack number.\n"; continue; }
            int si = s - 1;
            if (topIndex[si] >= baseIndex[si] + capacity[si] - 1)
                cout << "Stack " << s << " is FULL (Overflow condition).\n";
            else
                cout << "Stack " << s << " is NOT full.\n";
        }
        else if (choice == 6) {
            cout << "\nStacks content (top shown first):\n";
            for (int i = 0; i < k; ++i) {
                cout << "Stack " << i+1 << ": ";
                if (topIndex[i] < baseIndex[i]) {
                    cout << "(empty)\n";
                    continue;
                }
                // print from top down to base
                for (int p = topIndex[i]; p >= baseIndex[i]; --p) {
                    cout << arr[p];
                    if (p > baseIndex[i]) cout << " ";
                }
                cout << "\n";
            }
        }
        else if (choice == 7) {
            cout << "Exiting.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    delete[] arr;
    delete[] baseIndex;
    delete[] capacity;
    delete[] topIndex;
    return 0;
}
