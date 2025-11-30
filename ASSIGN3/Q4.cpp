/* Mahavir Manoj Bhandari */
#include <iostream>
using namespace std;

struct CricketNode {
    string sname;
    CricketNode* next;

    CricketNode(string nm) {
        sname = nm;
        next = NULL;
    }
};

struct FootballNode {
    string sname;
    FootballNode* next;

    FootballNode(string nm) {
        sname = nm;
        next = NULL;
    }
};

class VITCollege {
    CricketNode* head1;
    FootballNode* head2;

public:
    VITCollege() {
        head1 = NULL;
        head2 = NULL;
    }

    void insertCricket(string name) {
        CricketNode* newNode = new CricketNode(name);
        if (!head1) {
            head1 = newNode;
            return;
        }
        CricketNode* temp = head1;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    void insertFootball(string name) {
        FootballNode* newNode = new FootballNode(name);
        if (!head2) {
            head2 = newNode;
            return;
        }
        FootballNode* temp = head2;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    // Helper: check if name in Cricket list
    bool inCricket(string name) {
        CricketNode* t = head1;
        while (t) {
            if (t->sname == name) return true;
            t = t->next;
        }
        return false;
    }

    // Helper: check if name in Football list
    bool inFootball(string name) {
        FootballNode* t = head2;
        while (t) {
            if (t->sname == name) return true;
            t = t->next;
        }
        return false;
    }

    void bothCriFoot() {
        cout << "\n\tStudents who like BOTH Cricket and Football:\n";
        bool found = false;

        CricketNode* c = head1;
        while (c) {
            if (inFootball(c->sname)) {
                cout << "  " << c->sname << endl;
                found = true;
            }
            c = c->next;
        }

        if (!found) cout << "  None\n";
    }

    void eitherButNotBoth() {
        cout << "\n\tStudents who like EITHER Cricket or Football BUT NOT BOTH:\n";
        bool found = false;

        CricketNode* c = head1;
        while (c) {
            if (!inFootball(c->sname)) {
                cout << "  " << c->sname << endl;
                found = true;
            }
            c = c->next;
        }

        FootballNode* f = head2;
        while (f) {
            if (!inCricket(f->sname)) {
                cout << "  " << f->sname << endl;
                found = true;
            }
            f = f->next;
        }

        if (!found) cout << "  None\n";
    }

    void neither(int total) {
        cout << "\n\tStudents who like NEITHER Cricket nor Football:\n";

        string name;
        bool found = false;

        for (int i = 0; i < total; i++) {
            cout << "Enter student name: ";
            cin >> name;

            if (!inCricket(name) && !inFootball(name)) {
                cout << "  " << name << endl;
                found = true;
            }
        }

        if (!found) cout << "  None\n";
    }
};

int main() {
    VITCollege clg;
    int total, n, ch;
    string name;

    cout << "Enter total number of students: ";
    cin >> total;

    cout << "\nEnter number of students who like Cricket: ";
    cin >> n;
    cout << "Enter names:\n";
    for (int i = 0; i < n; i++) {
        cin >> name;
        clg.insertCricket(name);
    }

    cout << "\nEnter number of students who like Football: ";
    cin >> n;
    cout << "Enter names:\n";
    for (int i = 0; i < n; i++) {
        cin >> name;
        clg.insertFootball(name);
    }

    do {
        cout << "\n\n=== Sports Preference Menu ===\n";
        cout << "1. Students who like BOTH Cricket and Football\n";
        cout << "2. Students who like EITHER Cricket or Football but NOT BOTH\n";
        cout << "3. Students who like NEITHER Cricket nor Football\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch) {
            case 1:
                clg.bothCriFoot();
                break;
            case 2:
                clg.eitherButNotBoth();
                break;
            case 3:
                clg.neither(total);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (ch != 4);

    return 0;
}
