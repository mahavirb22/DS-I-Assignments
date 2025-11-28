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

// Fast Transpose function
void fastTranspose(int sparse[100][3], int trans[100][3]) {
    int rows = sparse[0][0];
    int cols = sparse[0][1];
    int n = sparse[0][2];

    trans[0][0] = cols; 
    trans[0][1] = rows; 
    trans[0][2] = n;    

    if(n > 0) {
        int count[50] = {0};   
        int index[50];       

        for(int i = 1;i <= n;i++) {
            count[sparse[i][1]]++;
        }

        index[0] = 1;
        for(int i = 1; i < cols; i++) {
            index[i] = index[i-1] + count[i-1];
        }

        for(int i = 1;i <= n;i++) {
            int col = sparse[i][1];
            int pos = index[col];
            trans[pos][0] = sparse[i][1];  
            trans[pos][1] = sparse[i][0];  
            trans[pos][2] = sparse[i][2]; 
            index[col]++;
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
    fastTranspose(sparse, trans);

    cout<<"\nFast Transpose of Sparse Matrix:\n";
    displaySparse(trans);

    return 0;
}
