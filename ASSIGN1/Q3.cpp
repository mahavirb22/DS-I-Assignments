#include <iostream>
#include <chrono>
#include <cstdlib>
using namespace std;
using namespace chrono;

void row_major(int a[500][500], int b[500][500], int c[500][500], int n) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            int sum = 0;
            for(int k = 0; k < n; k++) {
                sum += a[i][k] * b[k][j]; 
            }
            c[i][j] = sum;
        }
    }
}

void column_major(int a[500][500], int b[500][500], int c[500][500], int n) {
    for(int j = 0; j < n; j++) {       
        for(int i = 0; i < n; i++) {
            int sum = 0;
            for(int k = 0; k < n; k++) {
                sum += a[i][k] * b[k][j];  
            }
            c[i][j] = sum;
        }
    }
}

int main() {
    int n;
    cout << "Enter matrix size (e.g., 100-500 for visible difference): ";
    cin >> n;
    
    static int a[500][500], b[500][500], c1[500][500], c2[500][500];
    
    srand(42);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
        }
    }
    
    auto start = high_resolution_clock::now();
    row_major(a, b, c1, n);
    auto end = high_resolution_clock::now();
    auto row_time = duration_cast<milliseconds>(end - start).count();
    
    start = high_resolution_clock::now();
    column_major(a, b, c2, n);
    end = high_resolution_clock::now();
    auto col_time = duration_cast<milliseconds>(end - start).count();
    
    cout << "\n=== Performance Analysis ===" << endl;
    cout << "Row-major time:    " << row_time << " ms" << endl;
    cout << "Column-major time: " << col_time << " ms" << endl;
    cout << "Speedup: " << (double)col_time / row_time << "x faster" << endl;
    
    return 0;
}