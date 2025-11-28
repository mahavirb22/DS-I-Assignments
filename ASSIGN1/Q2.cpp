#include<iostream>
using namespace std;

bool isMagicMatrix(int arr[50][50],int n) {
    int msum=0;
    for(int i=0;i<n;i++) {
        msum+=arr[0][i];
    }
    int dsum1=0,dsum2=0;
    for(int i=0;i<n;i++) {
        int rsum=0,csum=0;
        for(int j=0;j<n;j++) {
            rsum+=arr[i][j];
            csum+=arr[j][i];
        }
        if(rsum!=msum || csum!=msum) {
            return false;
        }
        dsum1+=arr[i][i];
        dsum2+=arr[i][n-i-1];
    }
    if(dsum1!=msum || dsum2!=msum) {
        return false;
    }
    cout<<"Magic sum: "<<msum<<endl;
    return true;
}

int main() {
    int n;
    cout<<"Enter the value of n: ";
    cin>>n;
    int arr[50][50];
    int msum=0;
    for(int i=0;i<n;i++) {
        for(int j=0;j<n;j++) {
            cout<<"Enter the element at position "<<i<<","<<j<<": ";
            cin>>arr[i][j];
        }
    }
    if(isMagicMatrix(arr,n)) {
        cout<<"It is the magic matrix";
    }
    else {
        cout<<"It is not the magic matrix";
    }
    return 0;
}