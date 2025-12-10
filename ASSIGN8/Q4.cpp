#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
#include <limits>
using namespace std;

typedef struct date {
    int y, m, d;
} Date;

typedef struct product {
    string code;
    string name;
    double price;
    int qty;
    Date received;
    Date expiry;
    struct product* left;
    struct product* right;
} PNode;

bool parseDate(const string &s, Date &dt) {
    if (s.size() < 8) return false;
    int y, m, d;
    if (sscanf(s.c_str(), "%d-%d-%d", &y, &m, &d) == 3) {
        dt.y = y; dt.m = m; dt.d = d;
        return true;
    }
    return false;
}

Date getSystemDate() {
    time_t t = time(NULL);
    tm *now = localtime(&t);
    Date d;
    d.y = now->tm_year + 1900;
    d.m = now->tm_mon + 1;
    d.d = now->tm_mday;
    return d;
}

int compareDate(const Date &a, const Date &b) {
    if (a.y < b.y) return -1;
    if (a.y > b.y) return 1;
    if (a.m < b.m) return -1;
    if (a.m > b.m) return 1;
    if (a.d < b.d) return -1;
    if (a.d > b.d) return 1;
    return 0;
}

string dateToString(const Date &dt) {
    char buf[16];
    sprintf(buf, "%04d-%02d-%02d", dt.y, dt.m, dt.d);
    return string(buf);
}

PNode* createProductNode(const string &code, const string &name, double price, int qty, const Date &rec, const Date &exp) {
    PNode* p = new PNode;
    p->code = code;
    p->name = name;
    p->price = price;
    p->qty = qty;
    p->received = rec;
    p->expiry = exp;
    p->left = p->right = NULL;
    return p;
}

PNode* insertProduct(PNode* root, PNode* node) {
    if (!node) return root;
    if (!root) return node;

    PNode* cur = root;
    PNode* parent = NULL;

    while (cur) {
        parent = cur;
        if (node->name == cur->name) {
            cout << "Product with name \"" << node->name << "\" already exists. Insert rejected.\n";
            delete node;
            return root;
        }
        if (node->name < cur->name) cur = cur->left;
        else cur = cur->right;
    }

    if (node->name < parent->name) parent->left = node;
    else parent->right = node;

    return root;
}

void inorderDisplay(PNode* root) {
    if (!root) return;
    inorderDisplay(root->left);
    cout << "-------------------------------------------\n";
    cout << "Product Code : " << root->code << "\n";
    cout << "Name         : " << root->name << "\n";
    cout << "Price        : " << root->price << "\n";
    cout << "Quantity     : " << root->qty << "\n";
    cout << "Received     : " << dateToString(root->received) << "\n";
    cout << "Expiry       : " << dateToString(root->expiry) << "\n";
    inorderDisplay(root->right);
}

void preorderListExpired(PNode* root, const Date &current) {
    if (!root) return;
    if (compareDate(root->expiry, current) < 0) {
        cout << "-------------------------------------------\n";
        cout << "Product Code : " << root->code << "\n";
        cout << "Name         : " << root->name << "\n";
        cout << "Price        : " << root->price << "\n";
        cout << "Quantity     : " << root->qty << "\n";
        cout << "Received     : " << dateToString(root->received) << "\n";
        cout << "Expiry       : " << dateToString(root->expiry) << "  (EXPIRED)\n";
    }
    preorderListExpired(root->left, current);
    preorderListExpired(root->right, current);
}

void freeTree(PNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

PNode* readProductFromUser() {
    string code, name;
    double price;
    int qty;
    string srec, sexp;

    cout << "Enter product code: ";
    cin >> ws;
    getline(cin, code);
    if (code.empty()) {
        cout << "Product code required.\n";
        return NULL;
    }

    cout << "Enter product name: ";
    getline(cin, name);
    if (name.empty()) {
        cout << "Product name required.\n";
        return NULL;
    }

    cout << "Enter price: ";
    if (!(cin >> price)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Invalid price.\n"; return NULL; }

    cout << "Enter quantity in stock (integer): ";
    if (!(cin >> qty)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Invalid quantity.\n"; return NULL; }
    cin.ignore(10000, '\n');

    cout << "Enter date received (YYYY-MM-DD): ";
    getline(cin, srec);
    Date rec;
    if (!parseDate(srec, rec)) {
        cout << "Invalid date format. Use YYYY-MM-DD.\n";
        return NULL;
    }

    cout << "Enter expiration date (YYYY-MM-DD): ";
    getline(cin, sexp);
    Date exp;
    if (!parseDate(sexp, exp)) {
        cout << "Invalid date format. Use YYYY-MM-DD.\n";
        return NULL;
    }

    return createProductNode(code, name, price, qty, rec, exp);
}

int main() {
    PNode* root = NULL;
    int choice;

    cout << "=== Product Inventory (BST keyed by Product Name) ===\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert a product\n";
        cout << "2. Display all items (inorder - sorted by name)\n";
        cout << "3. List expired items (preorder of names)\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(10000, '\n'); cout << "Invalid choice.\n"; continue; }

        cin.ignore(10000, '\n');

        if (choice == 1) {
            PNode* node = readProductFromUser();
            if (node) {
                root = insertProduct(root, node);
                cout << "Product inserted.\n";
            }
        }
        else if (choice == 2) {
            if (!root) cout << "(No products in inventory)\n";
            else {
                cout << "\nInventory (sorted by product name):\n";
                inorderDisplay(root);
                cout << "-------------------------------------------\n";
            }
        }
        else if (choice == 3) {
            if (!root) { cout << "No products in inventory.\n"; continue; }
            cout << "Enter current date (YYYY-MM-DD) or press Enter to use system date: ";
            string curline;
            getline(cin, curline);
            Date current;

            if (curline.empty()) {
                current = getSystemDate();
                cout << "Using system date: " << dateToString(current) << "\n";
            } else {
                if (!parseDate(curline, current)) {
                    cout << "Invalid date format. Use YYYY-MM-DD.\n";
                    continue;
                }
            }

            cout << "\nExpired items (preorder by name):\n";
            preorderListExpired(root, current);
            cout << "-------------------------------------------\n";
        }
        else if (choice == 4) {
            cout << "Exiting. Freeing memory.\n";
            freeTree(root);
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 4);

    return 0;
}
