#include <iostream>
using namespace std;

typedef struct node {
    int key;
    struct node* left;
    struct node* right;
} BST;

BST* createNode(int k) {
    BST* p = new BST;
    p->key = k;
    p->left = p->right = NULL;
    return p;
}

BST* insertNode(BST* root, int k) {
    if (root == NULL) return createNode(k);
    if (k < root->key)
        root->left = insertNode(root->left, k);
    else if (k > root->key)
        root->right = insertNode(root->right, k);
    else
        cout << "Key already exists. Ignored.\n";
    return root;
}

bool searchNode(BST* root, int k) {
    if (!root) return false;
    if (k == root->key) return true;
    if (k < root->key) return searchNode(root->left, k);
    return searchNode(root->right, k);
}

BST* findMin(BST* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

BST* deleteNode(BST* root, int k) {
    if (!root) {
        cout << "Key not found.\n";
        return NULL;
    }
    if (k < root->key)
        root->left = deleteNode(root->left, k);
    else if (k > root->key)
        root->right = deleteNode(root->right, k);
    else {
        if (!root->left && !root->right) {
            delete root;
            return NULL;
        }
        else if (!root->left) {
            BST* temp = root->right;
            delete root;
            return temp;
        }
        else if (!root->right) {
            BST* temp = root->left;
            delete root;
            return temp;
        }
        else {
            BST* succ = findMin(root->right);
            root->key = succ->key;
            root->right = deleteNode(root->right, succ->key);
        }
    }
    return root;
}

void inorder(BST* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

int main() {
    BST* root = NULL;
    int choice, key;

    cout << "=== BST Operations: Insert | Delete | Find | Show ===\n";

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert key\n";
        cout << "2. Delete key\n";
        cout << "3. Find key\n";
        cout << "4. Show (Inorder Traversal)\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter key to insert: ";
            cin >> key;
            root = insertNode(root, key);
            break;

        case 2:
            cout << "Enter key to delete: ";
            cin >> key;
            root = deleteNode(root, key);
            break;

        case 3:
            cout << "Enter key to search: ";
            cin >> key;
            if (searchNode(root, key))
                cout << "Key FOUND in BST.\n";
            else
                cout << "Key NOT FOUND.\n";
            break;

        case 4:
            cout << "BST (Inorder): ";
            inorder(root);
            cout << "\n";
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
