#include <iostream>
using namespace std;

typedef struct node {
    int data;
    struct node* left;
    struct node* right;
} BTNODE;

typedef struct snode {
    BTNODE* tn;
    struct snode* next;
} SNode;

SNode* push(SNode* top, BTNODE* t) {
    SNode* n = new SNode;
    n->tn = t;
    n->next = top;
    return n;
}

SNode* pop(SNode* top, BTNODE* &out) {
    if (!top) { out = NULL; return NULL; }
    out = top->tn;
    SNode* tmp = top;
    top = top->next;
    delete tmp;
    return top;
}

bool isStackEmpty(SNode* top) {
    return top == NULL;
}

void freeStack(SNode* top) {
    while (top) {
        SNode* t = top;
        top = top->next;
        delete t;
    }
}

typedef struct qnode {
    BTNODE* tn;
    struct qnode* next;
} QNode;

void enqueue(QNode* &front, QNode* &rear, BTNODE* t) {
    QNode* n = new QNode;
    n->tn = t; n->next = NULL;
    if (!front) { front = rear = n; }
    else { rear->next = n; rear = n; }
}

BTNODE* dequeue(QNode* &front, QNode* &rear) {
    if (!front) return NULL;
    QNode* tmp = front;
    BTNODE* t = tmp->tn;
    front = front->next;
    if (!front) rear = NULL;
    delete tmp;
    return t;
}

bool isQueueEmpty(QNode* front) { return front == NULL; }

void freeQueue(QNode* front) {
    while (front) {
        QNode* t = front;
        front = front->next;
        delete t;
    }
}

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

void freeTree(BTNODE* root) {
    if (!root) return;
    SNode* st = NULL;
    st = push(st, root);
    while (!isStackEmpty(st)) {
        BTNODE* cur;
        st = pop(st, cur);
        if (!cur) continue;
        if (cur->left) st = push(st, cur->left);
        if (cur->right) st = push(st, cur->right);
        delete cur;
    }
    freeStack(st);
}

void inorderNonRecursive(BTNODE* root) {
    cout << "Inorder (non-recursive): ";
    SNode* st = NULL;
    BTNODE* cur = root;
    while (cur != NULL || !isStackEmpty(st)) {
        while (cur != NULL) {
            st = push(st, cur);
            cur = cur->left;
        }
        st = pop(st, cur);
        if (!cur) break;
        cout << cur->data << " ";
        cur = cur->right;
    }
    cout << "\n";
    freeStack(st);
}

void preorderNonRecursive(BTNODE* root) {
    cout << "Preorder (non-recursive): ";
    if (!root) { cout << "(empty)\n"; return; }
    SNode* st = NULL;
    st = push(st, root);
    while (!isStackEmpty(st)) {
        BTNODE* cur;
        st = pop(st, cur);
        cout << cur->data << " ";
        if (cur->right) st = push(st, cur->right);
        if (cur->left)  st = push(st, cur->left);
    }
    cout << "\n";
    freeStack(st);
}

int countLeafNodesNonRecursive(BTNODE* root) {
    if (!root) return 0;
    int count = 0;
    SNode* st = NULL;
    st = push(st, root);
    while (!isStackEmpty(st)) {
        BTNODE* cur;
        st = pop(st, cur);
        if (!cur) continue;
        if (!cur->left && !cur->right) count++;
        if (cur->right) st = push(st, cur->right);
        if (cur->left)  st = push(st, cur->left);
    }
    freeStack(st);
    return count;
}

void mirrorNonRecursive(BTNODE* root) {
    if (!root) return;
    SNode* st = NULL;
    st = push(st, root);
    while (!isStackEmpty(st)) {
        BTNODE* cur;
        st = pop(st, cur);
        if (!cur) continue;
        BTNODE* tmp = cur->left;
        cur->left = cur->right;
        cur->right = tmp;
        if (cur->left)  st = push(st, cur->left);
        if (cur->right) st = push(st, cur->right);
    }
    freeStack(st);
}

void levelOrderDisplay(BTNODE* root) {
    cout << "Level-order: ";
    if (!root) { cout << "(empty)\n"; return; }
    QNode* front = NULL; QNode* rear = NULL;
    enqueue(front, rear, root);
    while (!isQueueEmpty(front)) {
        BTNODE* cur = dequeue(front, rear);
        cout << cur->data << " ";
        if (cur->left) enqueue(front, rear, cur->left);
        if (cur->right) enqueue(front, rear, cur->right);
    }
    cout << "\n";
    freeQueue(front);
}

int main() {
    BTNODE* root = NULL;
    int choice;

    cout << "=== Binary Tree: Non-recursive operations ===\n";
    cout << "We will build a binary tree from input array (level order).\n";

    do {
        cout << "\nMENU:\n";
        cout << "1. Create tree from array (level-order)\n";
        cout << "2. Non-recursive Inorder traversal\n";
        cout << "3. Non-recursive Preorder traversal\n";
        cout << "4. Display number of leaf nodes (non-recursive)\n";
        cout << "5. Mirror image (non-recursive, in-place)\n";
        cout << "6. Level-order display (verification)\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (root) { freeTree(root); root = NULL; }
            int n;
            cout << "Enter number of nodes (n): ";
            cin >> n;
            if (n <= 0) { cout << "Empty tree created.\n"; continue; }
            int *arr = new int[n];
            cout << "Enter " << n << " integer values (level-order):\n";
            for (int i = 0; i < n; ++i) cin >> arr[i];
            root = buildTreeFromArray(arr, n);
            delete[] arr;
            cout << "Tree created (complete tree of " << n << " nodes).\n";
        }
        else if (choice == 2) {
            inorderNonRecursive(root);
        }
        else if (choice == 3) {
            preorderNonRecursive(root);
        }
        else if (choice == 4) {
            int leafCount = countLeafNodesNonRecursive(root);
            cout << "Number of leaf nodes = " << leafCount << "\n";
        }
        else if (choice == 5) {
            mirrorNonRecursive(root);
            cout << "Tree mirrored in-place.\n";
        }
        else if (choice == 6) {
            levelOrderDisplay(root);
        }
        else if (choice == 7) {
            cout << "Exiting. Freeing memory.\n";
            freeTree(root);
            root = NULL;
        }
        else {
            cout << "Invalid choice.\n";
        }

    } while (choice != 7);

    return 0;
}
