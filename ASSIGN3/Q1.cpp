/* Mahavir Manoj Bhandari */
#include<iostream>
#include<string>
using namespace std;

struct Node {
    int prn;
    string name;
    Node* next;

    Node(int p, string n) {
        prn = p;
        name = n;
        next = NULL;
    }
};

class Club {
    Node* head;

public:
    Club() { 
        head = NULL; 
    }

    void addPresident(int prn, string name) {
        Node* newNode = new Node(prn, name);
        newNode->next = head;
        head = newNode;
        cout<<"President added successfully.\n";
    }

    void addSecretary(int prn, string name) {
        Node* newNode = new Node(prn, name);
        if(!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while(temp->next != NULL){ 
            temp = temp->next;
        }
        temp->next = newNode;
        cout<<"Secretary added successfully.\n";
    }

    void addMember(int prn, string name) {
        if(!head) {
            cout<<"No President found. Add President first.\n";
            return;
        }
        Node* newNode = new Node(prn, name);
        Node* temp = head;

        if(head->next == NULL) {
            head->next = newNode;
            return;
        }

        while(temp->next->next != NULL) {
            temp = temp->next;
        }
        newNode->next = temp->next;
        temp->next = newNode;
        cout<<"Member added successfully.\n";
    }

    void deleteMember(int prn) {
        if(!head) {
            cout<<"Club list is empty.\n";
            return;
        }
        Node* temp = head;
        Node* prev = NULL;

        if(head->prn == prn) {
            head = head->next;
            delete temp;
            cout<<"President deleted successfully.\n";
            return;
        }

        while(temp->prn != prn) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
        cout<<"Member deleted successfully.\n";
        delete temp;
    }

    int countMembers() {
        int count = 0;
        Node* temp = head;
        while(temp != NULL) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void display() {
        if (head == NULL) {
            cout<<"No members in the club.\n";
            return;
        }
        cout<<"\nClub Members:\n";
        Node* temp = head;
        int i = 1;
        while(temp != NULL) {
            cout<<i++<< ". PRN: " << temp->prn << ", Name: " << temp->name;
            if (temp == head)
                cout << "(Pre)";
            else if (temp->next == NULL)
                cout << "(Sec)";
            cout<<"\n";
            temp = temp->next;
        }
    }

    void reverse() {
        Node* prev = NULL;
        Node* temp = head;
        Node* next = NULL;
        while(temp != NULL) {
            next = temp->next;
            temp->next = prev;
            prev = temp;
            temp = next;
        }
        head = prev;
        cout<<"Club list reversed.\n";
    }

    void search(int prn) {
        Node* temp = head;
        while(temp != NULL) {
            if(temp->prn == prn) {
                cout<<"Member found: "<<temp->name<<" PRN: "<<prn<<" \n";
                return;
            }
            temp = temp->next;
        }
        cout<<"Member not found.\n";
    }

    void sortByPRN() {
        if(head == NULL || head->next == NULL) return;

        for(Node* i = head; i != NULL; i = i->next) {
            for(Node* j = i->next; j != NULL; j = j->next) {
                if (i->prn > j->prn) {
                    swap(i->prn, j->prn);
                    swap(i->name, j->name);
                }
            }
        }
        cout<<"Club members sorted by PRN.\n";
    }
};

int main() {
    Club div;
    int choice,prn,div1_n,div2_n,i;
    string name;

    Node* head1 = NULL;
    Node* head2 = NULL;
    Node* temp;
    Node* t;

    do {
        cout << "\n--- Vertex Club Menu ---\n";
        cout << "1. Add President\n2. Add Secretary\n3. Add Member\n4. Delete Member\n5. Display Members\n";
        cout << "6. Count Members\n7. Concatenate Division Lists\n8. Reverse List\n9. Search by PRN\n10. Sort by PRN\n0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter PRN and Name: ";
                cin >> prn >> name;
                div.addPresident(prn, name);
                break;

            case 2:
                cout << "Enter PRN and Name: ";
                cin >> prn >> name;
                div.addSecretary(prn, name);
                break;

            case 3:
                cout << "Enter PRN and Name: ";
                cin >> prn >> name;
                div.addMember(prn, name);
                break;

            case 4:
                cout << "Enter PRN to delete: ";
                cin >> prn;
                div.deleteMember(prn);
                break;

            case 5:
                div.display();
                break;

            case 6:
                cout<<"Total members: "<<div.countMembers()<<endl;
                break;

            case 7:
                cout<<"Enter the total number of members in div 1 list: ";
                cin>>div1_n;
                cout<<"Enter the details div 1\n";
                for(int i=0;i<div1_n;i++) {
                    cout<<"Enter PRN and Name: ";
                    cin>>prn>>name;
                    Node* newNode = new Node(prn,name);
                    if(head1 == NULL) {
                        head1 = newNode;
                    }
                    else {
                        Node* temp = head1;
                        while(temp->next != NULL) {
                            temp = temp->next;
                        }
                        temp->next = newNode;
                    }
                }

                cout<<"Enter the total number of members in div 2 list: ";
                cin>>div2_n;
                cout<<"Enter the details div 2\n";
                for(int i=0;i<div2_n;i++) {
                    cout<<"Enter PRN and Name: ";
                    cin>>prn>>name;
                    Node* newNode = new Node(prn,name);
                    if(head2 == NULL) {
                        head2 = newNode;
                    }
                    else {
                        temp = head2;
                        while(temp->next != NULL) {
                            temp = temp->next;
                        }
                        temp->next = newNode;
                    }
                }

                if(head1 == NULL)
                    head1 = head2;
                else {
                    temp = head1;
                    while (temp->next != NULL) {
                        temp = temp->next;
                    }
                    temp->next = head2;
                }

                cout<<"\nAfter concatenation, the combined list is:\n";
                t = head1;
                i = 1;
                while(t != NULL) {
                    cout<<i++<<". PRN: "<<t->prn<<", Name: "<<t->name<<endl;
                    t = t->next;
                }
                break;

            case 8:
                div.reverse();
                break;

            case 9:
                cout<<"Enter PRN to search: ";
                cin>>prn;
                div.search(prn);
                break;

            case 10:
                div.sortByPRN();
                break;

            case 0:
                cout<<"Exiting...\n";
                break;

            default:
                cout<<"Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}
