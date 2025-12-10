#include <iostream>
#include <string>
#include <ctime>
#include <cstdio>
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
    int y, m, d;
    if (sscanf(s.c_str(), "%d-%d-%d", &y, &m, &d) == 3) {
        dt.y = y; dt.m = m; dt.d = d;
        return true;
    }
    return false;
}

string dateToString(const Date &dt) {
    char buf[16];
    sprintf(buf, "%04d-%02d-%02d", dt.y, dt.m, dt.d);
    return string(buf);
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

    if (node->code < root->code) root->left = insertProduct(root->left, node);
    else if (node->code > root->code) root->right = insertProduct(root->right, node);
    else {
        root->name = node->name;
        root->price = node->price;
        root->qty = node->qty;
        root->received = node->received;
        root->expiry = node->expiry;
        delete node;
        cout << "Product code exists: record updated.\n";
    }
    return root;
}

void displayProduct(const PNode* p) {
    cout << "-------------------------------------------\n";
    cout << "Code    : " << p->code << "\n";
    cout << "Name    : " << p->name << "\n";
    cout << "Price   : " << p->price << "\n";
    cout << "Qty     : " << p->qty << "\n";
    cout << "Received: " << dateToString(p->received) << "\n";
    cout << "Expiry  : " << dateToString(p->expiry) << "\n";
}

void inorderDisplay(PNode* root) {
    if (!root) return;
    inorderDisplay(root->left);
    displayProduct(root);
    inorderDisplay(root->right);
}

PNode* findMinNode(PNode* root) {
    while (root && root->left) root = root->left;
    return root;
}

PNode* deleteByCode(PNode* root, const string &code) {
    if (!root) {
        cout << "Product with code '" << code << "' not found.\n";
        return NULL;
    }

    if (code < root->code) root->left = deleteByCode(root->left, code);
    else if (code > root->code) root->right = deleteByCode(root->right, code);
    else {
        if (!root->left && !root->right) {
            delete root;
            cout << "Deleted product '" << code << "'.\n";
            return NULL;
        }
        else if (!root->left) {
            PNode* t = root->right;
            delete root;
            cout << "Deleted product '" << code << "'.\n";
            return t;
        }
        else if (!root->right) {
            PNode* t = root->left;
            delete root;
            cout << "Deleted product '" << code << "'.\n";
            return t;
        }
        else {
            PNode* succ = findMinNode(root->right);
            root->code = succ->code;
            root->name = succ->name;
            root->price = succ->price;
            root->qty = succ->qty;
            root->received = succ->received;
            root->expiry = succ->expiry;
            root->right = deleteByCode(root->right, succ->code);
        }
    }
    return root;
}

PNode* deleteExpired(PNode* root, const Date &current) {
    if (!root) return NULL;

    root->left = deleteExpired(root->left, current);
    root->right = deleteExpired(root->right, current);

    if (compareDate(root->expiry, current) < 0) {
        string code = root->code;
        root = deleteByCode(root, code);
    }

    return root;
}

void freeTree(PNode* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

PNode* readProductFromUser() {
    string code, name, srec, sexp;
    double price;
    int qty;

    cout << "Enter product code (unique): ";
    if (!getline(cin, code) || code.empty()) return NULL;

    cout << "Enter product name: ";
    if (!getline(cin, name) || name.empty()) return NULL;

    cout << "Enter price: ";
    if (!(cin >> price)) { cin.clear(); cin.ignore(10000, '\n'); return NULL; }

    cout << "Enter quantity (integer): ";
    if (!(cin >> qty)) { cin.clear(); cin.ignore(10000, '\n'); return NULL; }
    cin.ignore(10000, '\n');

    cout << "Enter date received (YYYY-MM-DD): ";
    getline(cin, srec);
    Date rec;
    if (!parseDate(srec, rec)) return NULL;

    cout << "Enter expiration date (YYYY-MM-DD): ";
    getline(cin, sexp);
    Date exp;
    if (!parseDate(sexp, exp)) return NULL;

    return createProductNode(code, name, price, qty, rec, exp);
}

int main() {
    PNode* root = NULL;
    int choice;

    cout << "=== Product Inventory: Deletion Operations (BST keyed by product code) ===\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert a product\n";
        cout << "2. Display all products (inorder)\n";
        cout << "3. Delete a product by code\n";
        cout << "4. Delete all expired products\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) { cin.clear(); cin.ignore(10000, '\n'); continue; }
        cin.ignore(10000, '\n');

        if (choice == 1) {
            PNode* node = readProductFromUser();
            if (node) {
                root = insertProduct(root, node);
                cout << "Inserted/Updated.\n";
            }
        }
        else if (choice == 2) {
            if (!root) cout << "(Inventory empty)\n";
            else inorderDisplay(root);
        }
        else if (choice == 3) {
            cout << "Enter code: ";
            string code; getline(cin, code);
            if (!code.empty()) root = deleteByCode(root, code);
        }
        else if (choice == 4) {
            cout << "Enter date (YYYY-MM-DD) or press Enter: ";
            string s; getline(cin, s);
            Date cur;

            if (s.empty()) cur = getSystemDate();
            else if (!parseDate(s, cur)) continue;

            root = deleteExpired(root, cur);
            cout << "Expired items removed.\n";
        }
        else if (choice == 5) {
            freeTree(root);
        }

    } while (choice != 5);

    return 0;
}
