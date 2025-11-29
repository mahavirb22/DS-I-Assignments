#include <iostream>
using namespace std;
struct Student {
    int student_roll_no;
    int total_marks;
};
void bubble_sort(Student arr[],int n) {
    for(int i=0;i<n-1;i++) {
        for(int j=0;j<n-i-1;j++) {
            if(arr[j].total_marks<arr[j+1].total_marks) {
                swap(arr[j],arr[j+1]);
            }
        }
    }
}
int main() {
    int n;
    cout<<"Enter number of students: ";
    cin>>n;
    Student arr[n];
    for(int i=0;i<n;i++) {
        cout<<"Enter totalmarks for student "<<i+1<<": ";
        cin>>arr[i].total_marks;
    }
    bubble_sort(arr,n);
    for(int i=0;i<n;i++) {
        arr[i].student_roll_no=i+1;
    }
    cout<<"\nStudents details: \n";
    cout<<"Roll no.     Marks\n";
    for(int i=0;i<n;i++) {
        cout<<" "<<arr[i].student_roll_no<<"            "<<arr[i].total_marks<<endl;
    }
    return 0;
}
