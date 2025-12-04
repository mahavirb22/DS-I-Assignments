#include <iostream>
#include <string>
#include <limits>
using namespace std;

/* Patient node for queue */
typedef struct patient {
    int id;             
    string name;
    struct patient* next;
} PAT;

typedef struct doctor {
    int id;           
    string name;      
    bool busy;          
    int pid;            
    string pname;        
} DOCT;

PAT* enqueue(PAT* head, PAT*& tail, int id, const string &name) {
    PAT* node = new PAT;
    node->id = id;
    node->name = name;
    node->next = NULL;
    if (!head) {
        head = tail = node;
    } else {
        tail->next = node;
        tail = node;
    }
    return head;
}

PAT* dequeue(PAT* head, PAT*& tail, int &outId, string &outName, bool &found) {
    if (!head) { found = false; return NULL; }
    PAT* tmp = head;
    outId = tmp->id;
    outName = tmp->name;
    head = head->next;
    if (!head) tail = NULL;
    delete tmp;
    found = true;
    return head;
}

// check if queue empty
bool isQueueEmpty(PAT* head) {
    return head == NULL;
}

// display queue
void displayQueue(PAT* head) {
    if (!head) {
        cout << "(No waiting patients)\n";
        return;
    }
    cout << "Waiting queue (front -> back):\n";
    PAT* cur = head;
    while (cur) {
        cout << "  [" << cur->id << "] " << cur->name;
        if (cur->next) cout << "  ->";
        cout << "\n";
        cur = cur->next;
    }
}

// display doctors and their statuses
void displayDoctors(DOCT docs[], int D) {
    cout << "Doctors status:\n";
    for (int i = 0; i < D; ++i) {
        cout << " Doctor " << docs[i].id << " (" << docs[i].name << "): ";
        if (docs[i].busy) cout << "BUSY with [" << docs[i].pid << "] " << docs[i].pname << "\n";
        else cout << "FREE\n";
    }
}

bool assignNext(PAT*& head, PAT*& tail, DOCT docs[], int D, int dIndex) {
    if (dIndex < 0 || dIndex >= D) return false;
    if (docs[dIndex].busy) {
        cout << "Doctor " << docs[dIndex].id << " is currently busy.\n";
        return false;
    }
    int pid; string pname;
    bool found;
    head = dequeue(head, tail, pid, pname, found);
    if (!found) {
        cout << "No patients waiting to assign.\n";
        return false;
    }
    docs[dIndex].busy = true;
    docs[dIndex].pid = pid;
    docs[dIndex].pname = pname;
    cout << "Assigned patient [" << pid << "] " << pname << " to Doctor " << docs[dIndex].id << ".\n";
    return true;
}

bool finishPatient(DOCT docs[], int D, int dIndex) {
    if (dIndex < 0 || dIndex >= D) return false;
    if (!docs[dIndex].busy) {
        cout << "Doctor " << docs[dIndex].id << " is already free.\n";
        return false;
    }
    cout << "Doctor " << docs[dIndex].id << " finished with patient [" << docs[dIndex].pid << "] "
         << docs[dIndex].pname << ".\n";
    docs[dIndex].busy = false;
    docs[dIndex].pid = 0;
    docs[dIndex].pname = "";
    return true;
}

int main() {
    cout << "=== Clinic Patient Queue (FIFO) ===\n\n";

    int D;
    cout << "Enter number of doctors in clinic: ";
    cin >> D;
    while (D <= 0) {
        cout << "Please enter a positive integer for doctors: ";
        cin >> D;
    }

    // consume newline
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    DOCT *docs = new DOCT[D];
    for (int i = 0; i < D; ++i) {
        docs[i].id = i + 1;
        cout << "Enter name for Doctor " << docs[i].id << " (or press enter to keep 'Dr" << docs[i].id << "'): ";
        string dname;
        getline(cin, dname);
        if (dname.empty()) dname = "Dr" + to_string(docs[i].id);
        docs[i].name = dname;
        docs[i].busy = false;
        docs[i].pid = 0;
        docs[i].pname = "";
    }

    PAT* head = NULL;
    PAT* tail = NULL;
    int nextPatientId = 1;

    int choice;
    do {
        cout << "\n--- MENU ---\n";
        cout << "1. Check-in patient (enqueue)\n";
        cout << "2. Assign next waiting patient to a doctor (dequeue -> assign)\n";
        cout << "3. Finish current patient for a doctor (doctor becomes free)\n";
        cout << "4. Display waiting queue\n";
        cout << "5. Display doctors status\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            cout << "Enter patient name: ";
            string pname; getline(cin, pname);
            if (pname.empty()) { cout << "Name required. Cancelled.\n"; continue; }
            head = enqueue(head, tail, nextPatientId, pname);
            cout << "Patient checked in: [" << nextPatientId << "] " << pname << "\n";
            nextPatientId++;
        }
        else if (choice == 2) {
            cout << "Choose doctor number to assign (1.." << D << "): ";
            int dnum; cin >> dnum;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (dnum < 1 || dnum > D) { cout << "Invalid doctor number.\n"; continue; }
            assignNext(head, tail, docs, D, dnum - 1);
        }
        else if (choice == 3) {
            cout << "Choose doctor number who finished (1.." << D << "): ";
            int dnum; cin >> dnum;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            if (dnum < 1 || dnum > D) { cout << "Invalid doctor number.\n"; continue; }
            finishPatient(docs, D, dnum - 1);
        }
        else if (choice == 4) {
            displayQueue(head);
        }
        else if (choice == 5) {
            displayDoctors(docs, D);
        }
        else if (choice == 6) {
            cout << "Exiting. Goodbye.\n";
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    // cleanup memory
    while (head) { PAT* t = head; head = head->next; delete t; }
    delete[] docs;
    return 0;
}
