#include <iostream>
#include <string>
#include <limits>
using namespace std;

typedef struct sNode {
    string name;
    struct sNode* next;
} SNode;

typedef struct bstNode {
    int marks;
    SNode* students;
    struct bstNode* left;
    struct bstNode* right;
} BSTNode;

typedef struct aNode {
    int roll;
    string name;
    int marks;
    struct aNode* next;
} ANode;

SNode* createStudentNode(const string &name) {
    SNode* p = new SNode;
    p->name = name;
    p->next = NULL;
    return p;
}

BSTNode* createBSTNode(int marks, const string &name) {
    BSTNode* p = new BSTNode;
    p->marks = marks;
    p->students = createStudentNode(name);
    p->left = p->right = NULL;
    return p;
}

ANode* createAssignedNode(int roll, const string &name, int marks) {
    ANode* p = new ANode;
    p->roll = roll;
    p->name = name;
    p->marks = marks;
    p->next = NULL;
    return p;
}

BSTNode* insertStudent(BSTNode* root, const string &name, int marks) {
    if (!root) return createBSTNode(marks, name);
    if (marks < root->marks) root->left = insertStudent(root->left, name, marks);
    else if (marks > root->marks) root->right = insertStudent(root->right, name, marks);
    else {
        SNode* cur = root->students;
        while (cur->next) cur = cur->next;
        cur->next = createStudentNode(name);
    }
    return root;
}

void assignRollsReverseInorder(BSTNode* root, ANode*& assignedHead, ANode*& assignedTail, int &rollCounter) {
    if (!root) return;
    assignRollsReverseInorder(root->right, assignedHead, assignedTail, rollCounter);
    SNode* s = root->students;
    while (s) {
        ANode* an = createAssignedNode(++rollCounter, s->name, root->marks);
        if (!assignedHead) assignedHead = assignedTail = an;
        else {
            assignedTail->next = an;
            assignedTail = an;
        }
        s = s->next;
    }
    assignRollsReverseInorder(root->left, assignedHead, assignedTail, rollCounter);
}

void displayAssignedList(ANode* head) {
    if (!head) {
        cout << "No assignments yet. Please 'Assign Roll Numbers' first.\n";
        return;
    }
    cout << "\nAssigned Roll Numbers (roll -> name -> marks):\n";
    ANode* cur = head;
    while (cur) {
        cout << cur->roll << " -> " << cur->name << " -> " << cur->marks << "\n";
        cur = cur->next;
    }
}

void displayMarksGroups(BSTNode* root) {
    if (!root) return;
    displayMarksGroups(root->left);
    cout << "Marks = " << root->marks << " : ";
    SNode* s = root->students;
    bool first = true;
    while (s) {
        if (!first) cout << ", ";
        cout << s->name;
        first = false;
        s = s->next;
    }
    cout << "\n";
    displayMarksGroups(root->right);
}

void freeAssignedList(ANode* head) {
    while (head) {
        ANode* t = head;
        head = head->next;
        delete t;
    }
}

void freeStudentList(SNode* head) {
    while (head) {
        SNode* t = head;
        head = head->next;
        delete t;
    }
}

void freeBST(BSTNode* root) {
    if (!root) return;
    freeBST(root->left);
    freeBST(root->right);
    freeStudentList(root->students);
    delete root;
}

int main() {
    BSTNode* root = NULL;
    ANode* assignedHead = NULL;
    ANode* assignedTail = NULL;
    int choice;

    cout << "=== Assign Roll Numbers by Previous Year Results (Topper = Roll 1) ===\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Add student (name and marks)\n";
        cout << "2. Display marks groups (BST nodes)\n";
        cout << "3. Assign roll numbers now and display assignments\n";
        cout << "4. Clear assigned list\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            string name;
            int marks;
            cout << "Enter student name: ";
            getline(cin, name);
            if (name.empty()) {
                cout << "Name cannot be empty.\n";
                continue;
            }
            cout << "Enter marks (integer): ";
            cin >> marks;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            root = insertStudent(root, name, marks);
            cout << "Added student: " << name << " with marks " << marks << ".\n";

            if (assignedHead) {
                freeAssignedList(assignedHead);
                assignedHead = assignedTail = NULL;
                cout << "(Previous assignments cleared.)\n";
            }
        }
        else if (choice == 2) {
            if (!root) cout << "No students added yet.\n";
            else {
                cout << "\nMarks groups (ascending marks):\n";
                displayMarksGroups(root);
            }
        }
        else if (choice == 3) {
            if (!root) {
                cout << "No students to assign.\n";
                continue;
            }
            if (assignedHead) {
                freeAssignedList(assignedHead);
                assignedHead = assignedTail = NULL;
            }
            int rollCounter = 0;
            assignRollsReverseInorder(root, assignedHead, assignedTail, rollCounter);
            cout << "Assigned " << rollCounter << " roll numbers.\n";
            displayAssignedList(assignedHead);
        }
        else if (choice == 4) {
            if (!assignedHead) cout << "No existing assignments to clear.\n";
            else {
                freeAssignedList(assignedHead);
                assignedHead = assignedTail = NULL;
                cout << "Cleared assigned list.\n";
            }
        }
        else if (choice == 5) {
            cout << "Exiting. Freeing memory.\n";
            freeAssignedList(assignedHead);
            freeBST(root);
        }
        else {
            cout << "Invalid choice.\n";
        }
    } while (choice != 5);

    return 0;
}
