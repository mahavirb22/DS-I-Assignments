#include<iostream>
using namespace std;

// Function to convert matrix to sparse representation
void convertToSparse(int mat[10][10], int rows, int cols, int sparse[100][3], int &nonZeroCount) {
    nonZeroCount = 0;
    sparse[0][0] = rows;
    sparse[0][1] = cols;

    // Traverse matrix
    for(int i = 0;i < rows;i++) {
        for(int j = 0;j < cols;j++) {
            if(mat[i][j] != 0) {
                nonZeroCount++;
                sparse[nonZeroCount][0] = i;      
                sparse[nonZeroCount][1] = j;      
                sparse[nonZeroCount][2] = mat[i][j];
            }
        }
    }
    sparse[0][2] = nonZeroCount;
}

// Function to display sparse matrix
void displaySparse(int sparse[100][3]) {
    int n = sparse[0][2];
    cout<<"\nSparse Matrix:\n";
    for(int i = 0;i <= n;i++) {
        cout<<sparse[i][0]<<" "<<sparse[i][1]<<" "<<sparse[i][2]<<endl;
    }
}

// Function for simple transpose
void simpleTranspose(int sparse[100][3], int trans[100][3]) {
    int n = sparse[0][2];

    trans[0][0] = sparse[0][1];
    trans[0][1] = sparse[0][0];
    trans[0][2] = n;

    int k = 1;
    for(int col = 0;col < sparse[0][1];col++) {
        for(int i = 1;i <= n;i++) {
            if(sparse[i][1] == col) {
                trans[k][0] = sparse[i][1];
                trans[k][1] = sparse[i][0];
                trans[k][2] = sparse[i][2];
                k++;
            }
        }
    }
}

int main() {
    int m[10][10], rows, cols;

    cout<<"Enter number of rows and columns: ";
    cin>>rows>>cols;

    cout<<"Enter matrix elements:\n";
    for(int i = 0;i < rows;i++) {
        for(int j = 0;j < cols;j++) {
            cin>>m[i][j];
        }
    }

    int sparse[100][3], trans[100][3], nonZeroCount;

    convertToSparse(m, rows, cols, sparse, nonZeroCount);

    displaySparse(sparse);

    // Transpose
    simpleTranspose(sparse, trans);

    cout<<"\nTranspose of Sparse Matrix:\n";
    displaySparse(trans);

    return 0;
}
