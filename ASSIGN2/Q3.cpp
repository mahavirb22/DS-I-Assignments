#include <iostream>
using namespace std;
// Partition function for Quick Sort
int partition(int arr[],int low,int high) {
    int pivot=arr[low];
    int i=low;
    int j=high;
    while(i<j) {
        while(arr[i]<=pivot && i<=high-1) {
            i++;
        }
        while(arr[j]>pivot && j>=low+1) {
            j--;
        }
        if(i<j) swap(arr[i],arr[j]);
    }
    swap(arr[low],arr[j]);
    return j;
}
// Quick Sort
void quick_sort(int arr[],int low,int high) {
    if(low<high) {
        int parIndex=partition(arr,low,high);
        quick_sort(arr,low,parIndex-1);
        quick_sort(arr,parIndex+1,high);
    }
}
// Function to find min and max using Divide and Conquer
void minmax(int arr[],int low,int high,int &minVal,int &maxVal) {
    if(low==high) {
        if(arr[low]<minVal)
            minVal=arr[low];
        if(arr[high]>maxVal)
            maxVal=arr[high];
        return;
    }

    if(high==low+1) {
        if(arr[low]<arr[high]) {
            if(arr[low]<minVal)
                minVal=arr[low];
            if(arr[high]>maxVal)
                maxVal=arr[high];
        }
        else {
            if(arr[high]<minVal)
                minVal=arr[high];
            if(arr[low]>maxVal)
                maxVal=arr[high];
        }
        return;
    }

    int mid=(low+high)/2;
    minmax(arr,low,mid,minVal,maxVal);
    minmax(arr,mid+1,high,minVal,maxVal);
}

int main() {
    int n;
    cout<<"Enter number of students: ";
    cin>>n;

    int arr[n];

    for (int i = 0; i < n; i++) {
        cout<<"Enter marks: ";
        cin>>arr[i];
    }

    quick_sort(arr,0,n - 1);

    cout<<"\nStudents sorted by Marks: \n";
    for (int i = 0; i < n; i++) {
        cout << arr[i]<<endl;
    }

    int minVal=arr[0];
    int maxVal=arr[0];

    minmax(arr,0,n-1,minVal,maxVal);

    cout<<"\nMinimum marks: "<<minVal<<endl;
    cout<<"Maximum marks: "<<maxVal<<endl;

    return 0;
}
