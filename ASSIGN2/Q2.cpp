#include <iostream>
using namespace std;

struct Student {
    string student_name;
    int student_roll_no;
    int total_marks;
}; 
// Bubble Sort
void bubble_sort(Student arr[],int n,int &bswapCount) {
    bswapCount=0;
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            if (arr[j].student_roll_no > arr[j + 1].student_roll_no) {
                swap(arr[j],arr[j + 1]);
                bswapCount++;
            }
        }
    }
}
//partition function for Quick Sort
int partition(Student arr[],int low,int high,int &qswapCount) {
    int pivot=arr[low].student_roll_no;
    int i=low;
    int j=high;
    while(i<j) {
        while(arr[i].student_roll_no<=pivot && i<=high-1) {
            i++;
        }
        while(arr[j].student_roll_no>pivot && j>=low+1) {
            j--;
        }
        if(i<j) {
            swap(arr[i].student_roll_no,arr[j].student_roll_no);
            qswapCount++;
        }
    }
    swap(arr[low].student_roll_no,arr[j].student_roll_no);
    qswapCount++;
    return j;
}
// Quick Sort
void quick_sort(Student arr[],int low,int high,int &qswapCount) {
    if(low<high) {
        int parIndex=partition(arr,low,high,qswapCount);
        quick_sort(arr,low,parIndex-1,qswapCount);
        quick_sort(arr,parIndex+1,high,qswapCount);
    }
}

int main() {
    int n,ch;
    cout<<"Enter number of students: ";
    cin>>n;

    Student arr[n];

    for (int i=0;i<n;i++) {
        cout<<"Enter name, rollno, total marks for student "<<i+1<<": ";
        cin>>arr[i].student_name>>arr[i].student_roll_no>>arr[i].total_marks;
    }
    int bswapCount=0,qswapCount=0;
    do {
        cout<<"\nSorting Methods\n";
        cout<<"1. Bubble Sort\n2. Quick Sort\n3. Exit\n";
        cout<<"Enter the choice: ";
        cin>>ch;
        switch(ch) {
            case 1:
                bubble_sort(arr,n,bswapCount);

                cout<<"\nStudents sorted by Roll No (Bubble Sort):\n";
                cout<<"Roll No    Student Name     Total Marks\n";
                for(int i=0;i<n;i++) {
                    cout<<arr[i].student_roll_no<<"               "
                        <<arr[i].student_name<<"               "
                        <<arr[i].total_marks<<endl;
                }

                cout<<"\nTotal swaps performed: "<<bswapCount<<endl;
                break;
            case 2:
                quick_sort(arr,0,n - 1,qswapCount);

                cout<<"\nStudents sorted by Roll No (Quick Sort):\n";
                cout<<"Roll No      Student Name        Total Marks\n";
                for(int i=0;i<n;i++) {
                    cout<<arr[i].student_roll_no<<"               "
                        <<arr[i].student_name<<"               "
                        <<arr[i].total_marks<<endl;
                }

                cout<<"\nTotal swaps performed: "<<qswapCount<<endl;
                break;
            case 3:
                cout<<"Exiting the program.\n";
                exit(0);
                break;
            default:
                cout<<"Invalid choice!\n";
        }
    } while(ch!=3);

    return 0;
}
