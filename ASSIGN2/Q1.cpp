#include <iostream>
using namespace std;
struct Student {
    string name;
    int roll;
    string division;
    string year;
};
int linear_search(Student students[],int n,string name,int roll,string year,string division) {
    for(int i=0;i<n;i++) {
        if (students[i].name==name && students[i].roll==roll &&
            students[i].year==year && students[i].division==division) {
            return i;
        }
    }
    return -1;
}
int binary_search(Student students[],int n,string name,int roll,string year,string division) {
    int low=0,high=n-1;
    while(low<=high) {
        int mid=(low+high)/2;
        if (students[mid].roll==roll && students[mid].name==name && students[mid].year==year && students[mid].division==division) {
            return mid;
        }
        else if (students[mid].roll<roll) {
            low=mid+1;
        }
        else {
            high=mid-1;
        }
    }
    return -1;
}

int main() {
    Student students[]={
        {"ABC", 12, "X", "SY"},
        {"XYZ", 17, "X", "SY"},
        {"PQR", 22, "Y", "SY"},
        {"LMN", 31, "Z", "TY"},
        {"DEF", 45, "A", "BTech"}
    };
    int n=sizeof(students)/sizeof(students[0]);

    string targetName,targetYear,targetDiv;
    int targetRoll;

    cout<<"Enter student details to search:\n";
    cout<<"Name: ";
    cin>>targetName;
    cout<<"Roll No: ";
    cin>>targetRoll;
    cout<<"Year: ";
    cin>>targetYear;
    cout<<"Division: ";
    cin>>targetDiv;

    int x,y,ch;
    do{
        cout<<"\n1. Linear Search\n2. Binary Search\n3. Exit\n";
        cout<<"Enter the choice: ";
        cin>>ch;
        switch(ch) {
            case 1:
                x=linear_search(students,n,targetName,targetRoll,targetYear,targetDiv);
                if (x!=-1)
                    cout<<"\nStudent Data Found using Linear Search: O(n)"<<endl<<"Name: "<<students[x].name<<" Roll: "<<students[x].roll<<" Year: "<<students[x].year<<" Division: "<<students[x].division<<endl;
                else
                    cout<<"\nStudent Data not found using Linear Search.\n";
                break;
            case 2:
                y=binary_search(students,n,targetName,targetRoll,targetYear,targetDiv);
                if (y!=-1)
                    cout<<"\nStudent Data Found using Binary Search: O(log n)"<<endl<<"Name: "<<students[y].name<<" Roll: "<<students[y].roll<<" Year: "<<students[y].year<<" Division: "<<students[y].division;
                else
                    cout<<"\nStudent Data not found using Binary Search.\n";
                break;
            case 3:
                exit(0);
                break;
            default:
                cout<<"Invalid Choice. Select choice from menu.\n";
        }
    } while(ch!=3);
    return 0;
}
