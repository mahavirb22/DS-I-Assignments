#include <iostream>
using namespace std;

typedef struct node {
    int key;
    struct node* left;
    struct node* right;
} BTNODE;

// create a new tree node
BTNODE* createNode(int k) {
    BTNODE* n = new BTNODE;
    n->key = k;
    n->left = n->right = NULL;
    return n;
}

// insert key into BST
BTNODE* insertNode(BTNODE* root, int key) {
    if (root == NULL) {
        return createNode(key);
    }
    if (key < root->key) {
        root->left = insertNode(root->left, key);
    } else if (key > root->key) {
        root->right = insertNode(root->right, key);
    } else {
        cout << "Key " << key << " already exists. Ignored.\n";
    }
    return root;
}

// find minimum node in subtree 
BTNODE* findMin(BTNODE* root) {
    if (!root) return NULL;
    while (root->left) root = root->left;
    return root;
}

// delete a key from BST
BTNODE* deleteNode(BTNODE* root, int key) {
    if (!root) {
        cout << "Key " << key << " not found.\n";
        return NULL;
    }
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
    } else if (key > root->key) {
        root->right = deleteNode(root->right, key);
    } else {
        if (!root->left && !root->right) {
            delete root;
            return NULL;
        }
        if (!root->left) {
            BTNODE* tmp = root->right;
            delete root;
            return tmp;
        } else if (!root->right) {
            BTNODE* tmp = root->left;
            delete root;
            return tmp;
        }
        BTNODE* succ = findMin(root->right);
        root->key = succ->key;
        root->right = deleteNode(root->right, succ->key);
    }
    return root;
}

typedef struct qnode {
    BTNODE* treenode;
    struct qnode* next;
} QNODE;

QNODE* qCreateNode(BTNODE* t) {
    QNODE* qn = new QNODE;
    qn->treenode = t;
    qn->next = NULL;
    return qn;
}

void qEnqueue(QNODE*& front, QNODE*& rear, BTNODE* t) {
    QNODE* qn = qCreateNode(t);
    if (!front) { front = rear = qn; }
    else { rear->next = qn; rear = qn; }
}

BTNODE* qDequeue(QNODE*& front, QNODE*& rear) {
    if (!front) return NULL;
    QNODE* tmp = front;
    BTNODE* t = front->treenode;
    front = front->next;
    if (!front) rear = NULL;
    delete tmp;
    return t;
}

bool qIsEmpty(QNODE* front) {
    return front == NULL;
}

void inorder(BTNODE* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

void levelOrderDisplay(BTNODE* root) {
    if (!root) {
        cout << "(Tree is empty)\n";
        return;
    }
    QNODE* front = NULL; QNODE* rear = NULL;
    qEnqueue(front, rear, root);
    cout << "Level-order: ";
    while (!qIsEmpty(front)) {
        BTNODE* cur = qDequeue(front, rear);
        cout << cur->key << " ";
        if (cur->left) qEnqueue(front, rear, cur->left);
        if (cur->right) qEnqueue(front, rear, cur->right);
    }
    cout << "\n";
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

    cout << "=== Binary Search Tree Operations ===\n";
    do {
        cout << "\nMENU:\n";
        cout << "1. Create tree (insert multiple keys)\n";
        cout << "2. Insert key\n";
        cout << "3. Delete key\n";
        cout << "4. Level-wise display\n";
        cout << "5. Inorder display (sorted)\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int n;
            cout << "How many keys to insert initially? ";
            cin >> n;
            cout << "Enter keys (space separated):\n";
            for (int i = 0; i < n; ++i) {
                int k; cin >> k;
                root = insertNode(root, k);
            }
            cout << "Tree created/updated.\n";
        }
        else if (choice == 2) {
            int k;
            cout << "Enter key to insert: ";
            cin >> k;
            root = insertNode(root, k);
            cout << "Inserted " << k << ".\n";
        }
        else if (choice == 3) {
            int k;
            cout << "Enter key to delete: ";
            cin >> k;
            root = deleteNode(root, k);
        }
        else if (choice == 4) {
            levelOrderDisplay(root);
        }
        else if (choice == 5) {
            cout << "Inorder: ";
            if (!root) cout << "(empty)";
            else inorder(root);
            cout << "\n";
        }
        else if (choice == 6) {
            cout << "Exiting. Freeing tree memory.\n";
            freeTree(root);
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 6);

    return 0;
}
