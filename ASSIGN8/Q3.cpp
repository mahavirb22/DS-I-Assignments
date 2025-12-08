#include <iostream>
#include <string>
#include <limits>
using namespace std;

typedef struct emp {
    int empid;
    string name;
    string dept;
    double salary;
    struct emp* left;
    struct emp* right;
} EMPNODE;

EMPNODE* createEmpNode(int id, const string &name, const string &dept, double sal) {
    EMPNODE* p = new EMPNODE;
    p->empid = id;
    p->name = name;
    p->dept = dept;
    p->salary = sal;
    p->left = p->right = NULL;
    return p;
}

EMPNODE* insertEmployee(EMPNODE* root, int id, const string &name, const string &dept, double sal) {
    if (!root) return createEmpNode(id, name, dept, sal);

    if (id < root->empid)
        root->left = insertEmployee(root->left, id, name, dept, sal);
    else if (id > root->empid)
        root->right = insertEmployee(root->right, id, name, dept, sal);
    else {
        root->name = name;
        root->dept = dept;
        root->salary = sal;
        cout << "Updated existing employee record with empid " << id << ".\n";
    }
    return root;
}

EMPNODE* searchEmployee(EMPNODE* root, int id) {
    if (!root) return NULL;
    if (id == root->empid) return root;
    if (id < root->empid) return searchEmployee(root->left, id);
    return searchEmployee(root->right, id);
}

void inorderDisplay(EMPNODE* root) {
    if (!root) return;
    inorderDisplay(root->left);
    cout << "EmpID: " << root->empid
         << " | Name: " << root->name
         << " | Dept: " << root->dept
         << " | Salary: " << root->salary << "\n";
    inorderDisplay(root->right);
}

void freeBST(EMPNODE* root) {
    if (!root) return;
    freeBST(root->left);
    freeBST(root->right);
    delete root;
}

int main() {
    EMPNODE* root = NULL;
    int choice;

    cout << "=== Employee Records using BST (search & sort by empid) ===\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert / Update employee\n";
        cout << "2. Search employee by empid\n";
        cout << "3. Show all employees (sorted by empid)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            string name, dept;
            double sal;

            cout << "Enter empid (integer): ";
            cin >> id;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Enter name: ";
            getline(cin, name);

            cout << "Enter department: ";
            getline(cin, dept);

            cout << "Enter salary: ";
            cin >> sal;

            root = insertEmployee(root, id, name, dept, sal);
            cout << "Employee inserted/updated.\n";
        }

        else if (choice == 2) {
            int id;
            cout << "Enter empid to search: ";
            cin >> id;

            EMPNODE* found = searchEmployee(root, id);

            if (!found)
                cout << "Employee with empid " << id << " NOT found.\n";
            else
                cout << "Found: EmpID: " << found->empid
                     << " | Name: " << found->name
                     << " | Dept: " << found->dept
                     << " | Salary: " << found->salary << "\n";
        }

        else if (choice == 3) {
            if (!root) cout << "(No employee records)\n";
            else {
                cout << "\nEmployees sorted by empid (ascending):\n";
                inorderDisplay(root);
            }
        }

        else if (choice == 4) {
            cout << "Exiting. Freeing memory.\n";
            freeBST(root);
        }

        else {
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 4);

    return 0;
}
