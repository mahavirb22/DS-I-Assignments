#include <iostream>
using namespace std;

typedef struct node {
    int key;
    struct node* left;
    struct node* right;
} BTNODE;

BTNODE* createNode(int k) {
    BTNODE* n = new BTNODE;
    n->key = k;
    n->left = n->right = NULL;
    return n;
}

BTNODE* insertNode(BTNODE* root, int key) {
    if (root == NULL) return createNode(key);
    if (key < root->key) root->left = insertNode(root->left, key);
    else if (key > root->key) root->right = insertNode(root->right, key);
    else cout << "Key " << key << " already exists. Ignored.\n";
    return root;
}

int countNodes(BTNODE* root) {
    if (!root) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int treeHeight(BTNODE* root) {
    if (!root) return 0;
    int lh = treeHeight(root->left);
    int rh = treeHeight(root->right);
    return 1 + ( (lh > rh) ? lh : rh );
}

BTNODE* mirrorTree(BTNODE* root) {
    if (!root) return NULL;
    BTNODE* leftMir = mirrorTree(root->left);
    BTNODE* rightMir = mirrorTree(root->right);
    root->left = rightMir;
    root->right = leftMir;
    return root;
}

void inorder(BTNODE* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

void freeTree(BTNODE* root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    delete root;
}

int main() {
    BTNODE* root = NULL;
    int choice;

    cout << "=== BST: Count nodes, Height, Mirror Image ===\n";
    do {
        cout << "\nMENU:\n";
        cout << "1. Create tree (insert multiple keys)\n";
        cout << "2. Insert key\n";
        cout << "3. Count total nodes\n";
        cout << "4. Compute height of BST\n";
        cout << "5. Mirror image (convert tree to its mirror)\n";
        cout << "6. Display\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int n; cout << "How many keys to insert? "; cin >> n;
            cout << "Enter keys (space separated):\n";
            for (int i = 0; i < n; ++i) {
                int k; cin >> k; root = insertNode(root, k);
            }
            cout << "Tree created/updated.\n";
        }
        else if (choice == 2) {
            int k; cout << "Enter key to insert: "; cin >> k;
            root = insertNode(root, k);
        }
        else if (choice == 3) {
            int total = countNodes(root);
            cout << "Total number of nodes = " << total << "\n";
        }
        else if (choice == 4) {
            int h = treeHeight(root);
            cout << "Height of BST = " << h << "\n";
        }
        else if (choice == 5) {
            root = mirrorTree(root);
            cout << "Tree mirrored (in-place).\n";
        }
        else if (choice == 6) {
            cout << "Inorder: ";
            if (!root) cout << "(empty)";
            else inorder(root);
            cout << "\n";
        }
        else if (choice == 7) {
            cout << "Exiting. Freeing memory.\n";
            freeTree(root);
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 8);

    return 0;
}
