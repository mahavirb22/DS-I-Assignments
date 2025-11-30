#include<iostream>
using namespace std;
struct Employee {
    float height;
    float weight;
    float avg;
};
// Function to calculate average of height and weight
void calculate_avg(Employee arr[], int n) {
    for(int i=0; i<n; i++) {
        arr[i].avg = (arr[i].height + arr[i].weight) / 2;
    } 
}
// Selection Sort
void selection_sort(Employee arr[], int n) {
    for(int i=0; i<n-1; i++) {
        int min=i;
        for(int j=i+1; j<n; j++) {
            if(arr[j].avg<arr[min].avg) {
                min=j;
            }
        }
        swap(arr[min].avg,arr[i].avg);
    }
}
// Merge function for Merge Sort
void merge(Employee arr[], int low, int mid, int high) {
    Employee temp[100];  // Temporary array to store merged data
    int left = low;
    int right = mid + 1;
    int k = 0;

    while(left <= mid && right <= high) {
        if(arr[left].avg <= arr[right].avg) {
            temp[k++] = arr[left++];
        } else {
            temp[k++] = arr[right++];
        }
    }

    while(left <= mid) temp[k++] = arr[left++];
    while(right <= high) temp[k++] = arr[right++];
 
    for(int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }
}
// Merge Sort
void merge_sort(Employee arr[], int low, int high) {
    if(low >= high) return;

    int mid = (low + high) / 2;
    merge_sort(arr, low, mid);
    merge_sort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

int main() {
    int n;
    cout << "Enter the number of employees: ";
    cin >> n;

    Employee emp[n];
    for(int i=0; i<n; i++) {
        cout << "Enter height and weight of employee " << i+1 << ": ";
        cin >> emp[i].height >> emp[i].weight;
    }

    calculate_avg(emp, n);

    int choice;
    cout << "\nChoose sorting method:\n1. Selection Sort\n2. Merge Sort\nEnter choice: ";
    cin >> choice;

    switch(choice) {
        case 1:
            selection_sort(emp, n);
            cout << "\nSorted using Selection Sort.\n";
            break;
        case 2:
            merge_sort(emp, 0, n-1);
            cout << "\nSorted using Merge Sort.\n";
            break;
        default:
            cout << "Invalid choice! Showing unsorted list.\n";
    }

    cout << "\nEmployee details:\n";
    cout << "Height     Weight     Average\n";
    for(int i=0; i<n; i++) {
        cout << emp[i].height << "          " << emp[i].weight << "         " << emp[i].avg << endl;
    }

    return 0;
}
