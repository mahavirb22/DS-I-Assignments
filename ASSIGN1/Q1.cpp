#include<iostream>
using namespace std;
int strLen(char str[]) {
    int len=0;
    while(str[len]!='\0') {
        len++;
    }
    return len;
}
void strCopy(char src[], char dest[]) {
    int i=0;
    while(src[i]!='\0') {
        dest[i]=src[i];
        i++;
    }
    dest[i]='\0'; 
}
void strRev(char str[]) {
    int i=0; 
    int j=strLen(str)-1;
    while(i<j) {
        char temp=str[i];
        str[i]=str[j];
        str[j]=temp;
        i++;
        j--;
    }
}
void strConcat(char str1[], char str2[]) {
    int len1=strLen(str1);
    int i=0;
    while(str2[i]!='\0') {
        str1[len1+i]=str2[i];
        i++;
    }
    str1[len1+i]='\0';
}

int main() {
    char str1[100],str2[100],copy[100];

    cout<<"Enter first string: ";
    cin>>str1;

    cout<<"Enter second string: ";
    cin>>str2;

    cout<<"\nLength of first string= "<<strLen(str1);

    strCopy(str1,copy);
    cout<<"\nCopy of first string: "<<copy;

    strRev(str1);
    cout<<"\nReverse of first string: "<<str1;

    strConcat(copy,str2);
    cout<<"\nConcatenation: "<<copy;
    return 0;
}
