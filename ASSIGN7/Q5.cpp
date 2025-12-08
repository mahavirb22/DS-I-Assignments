#include <iostream>
using namespace std;

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} BTNODE;

BTNODE* createNode(int val) {
    BTNODE* p = new BTNODE;
    p->data = val;
    p->left = p->right = NULL;
    return p;
}

BTNODE* buildTreeFromArray(int arr[], int n) {
    if (n == 0) return NULL;
    BTNODE** nodes = new BTNODE*[n];
    for (int i = 0; i < n; ++i) nodes[i] = createNode(arr[i]);
    for (int i = 0; i < n; ++i) {
        int li = 2*i + 1;
        int ri = 2*i + 2;
        if (li < n) nodes[i]->left = nodes[li];
        if (ri < n) nodes[i]->right = nodes[ri];
    }
    BTNODE* root = nodes[0];
    delete[] nodes; 
    return root;
}

void inorderRecursive(BTNODE* root) {
    if (!root) return;
    inorderRecursive(root->left);
    cout << root->data << " ";
    inorderRecursive(root->right);
}

void preorderRecursive(BTNODE* root) {
    if (!root) return;
    cout << root->data << " ";
    preorderRecursive(root->left);
    preorderRecursive(root->right);
}

int countLeafNodesRecursive(BTNODE* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return 1;        // it's a leaf
    return countLeafNodesRecursive(root->left) + countLeafNodesRecursive(root->right);
}

void mirrorRecursive(BTNODE* root) {
    if (!root) return;
    BTNODE* tmp = root->left;
    root->left = root->right;
    root->right = tmp;
    mirrorRecursive(root->left);
    mirrorRecursive(root->right);
}

void levelOrderDisplay(BTNODE* root) {
    if (!root) { cout << "(empty)\n"; return; }
    const int MAXQ = 1000; 
    BTNODE* q[MAXQ];
    int front = 0, rear = 0;
    q[rear++] = root;
    cout << "Level-order: ";
    while (front < rear) {
        BTNODE* cur = q[front++];
        cout << cur->data << " ";
        if (cur->left) q[rear++] = cur->left;
        if (cur->right) q[rear++] = cur->right;
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

    cout << "=== Binary Tree: Recursive Operations ===\n";
    do {
        cout << "\nMENU:\n";
        cout << "1. Create tree from array (level-order)\n";
        cout << "2. Inorder traversal (recursive)\n";
        cout << "3. Preorder traversal (recursive)\n";
        cout << "4. Display number of leaf nodes (recursive)\n";
        cout << "5. Mirror image (recursive, in-place)\n";
        cout << "6. Level-order display (verification)\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (root) { freeTree(root); root = NULL; }
            int n; cout << "Enter number of nodes (n): ";
            cin >> n;
            if (n <= 0) {
                cout << "Empty tree created.\n";
                continue;
            }
            int *arr = new int[n];
            cout << "Enter " << n << " integer values (level-order):\n";
            for (int i = 0; i < n; ++i) cin >> arr[i];
            root = buildTreeFromArray(arr, n);
            delete[] arr;
            cout << "Tree created (complete tree of " << n << " nodes).\n";
        }
        else if (choice == 2) {
            cout << "Inorder (recursive): ";
            if (!root) cout << "(empty)";
            else inorderRecursive(root);
            cout << "\n";
        }
        else if (choice == 3) {
            cout << "Preorder (recursive): ";
            if (!root) cout << "(empty)";
            else preorderRecursive(root);
            cout << "\n";
        }
        else if (choice == 4) {
            int cnt = countLeafNodesRecursive(root);
            cout << "Number of leaf nodes = " << cnt << "\n";
        }
        else if (choice == 5) {
            mirrorRecursive(root);
            cout << "Tree mirrored (in-place) recursively.\n";
        }
        else if (choice == 6) {
            levelOrderDisplay(root);
        }
        else if (choice == 7) {
            cout << "Exiting. Freeing tree memory.\n";
            freeTree(root);
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
