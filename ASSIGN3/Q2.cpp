/* Mahavir Manoj Bhandari */
#include <iostream>
using namespace std;

struct Seat {
    int seatNum;
    bool booked;         
    Seat* next;
    Seat* prev;
};

class Galaxy {
    Seat* head = NULL;
    Seat* prev = NULL;
    public:
    Galaxy() {
        for(int i=1; i<=8; i++) {
            for(int j=1;j<=8;j++) {
                Seat* newSeat = new Seat();
                newSeat->seatNum = j;
                newSeat->booked = false;
                newSeat->next = NULL;
                newSeat->prev = NULL;
                if(head == NULL) {
                    head = newSeat;
                    prev = newSeat;
                }
                else {
                    prev->next = newSeat;
                    newSeat->prev = prev;
                    prev = newSeat;
                }
            }
        }
    }
    void displaySeats() {
        Seat* temp = head;
        for(int i=1;i<=8;i++) {
            cout<<"Row "<<i<<": ";
            for(int j=1;j<=8;j++) {
                if(temp->booked) {
                    cout<<"[ X ]";
                }
                else {
                    cout<<"[ Y ]";
                }
                temp = temp->next;
            }
            cout<<endl;
        }
    }
    void bookSeat(int row, int seat) {
        if(row < 1 || row > 8 || seat < 1 || seat > 8) {
            cout<<"Invalid row or seat number. Please enter values between 1 and 8.\n";
            return;
        }
        int index = (row - 1) * 8 + (seat - 1);
        Seat* temp = head;
        for(int i=0;i<index;i++) {
            temp = temp->next;
        }
        if(temp->booked) {
            cout<<"Seat is already booked. Choose another seat.\n";
        } 
        else {
            temp->booked = true;
            cout<<"Seat "<<seat<<" from row "<<row<<" is booked successfully.\n";
        }
    }

    void cancelSeat(int row,int seat) {
        if(row < 1 || row > 8 || seat < 1 || seat > 8) {
            cout<<"Invalid row or seat number. Please enter values between 1 and 8.\n";
            return;
        }
        int index = (row - 1) * 8 + (seat - 1);
        Seat* temp = head;
        for(int i=0;i<index;i++) {
            temp = temp->next;
        }
        if(!temp->booked) {
            cout<<"Seat is not yet booked. Do you want to book it? (y/n)\n";
            char ch;
            cin>>ch;
            if(ch=='y') {
                temp->booked = true;
                cout<<"Seat "<<seat<<" from row "<<row<<" is booked successfully.";
            }
        }
        else {
            temp->booked = false;
            cout<<"Seat "<<seat<<" from row "<<row<<" is cancelled successfully.";
        }
        cout<<endl;
    }
};

int main() {
    Galaxy g;
    int ch,row,seat;

    do {
        cout<<"\n\tGalaxy Multiplex Ticket System\t\n";
        cout<<"1. Display all seats\n";
        cout<<"2. Book a seat\n";
        cout<<"3. Cancel a seat\n";
        cout<<"4. Exit\n";
        cout<<"Enter your choice: ";
        cin>>ch;

        switch (ch) {
        case 1:
            g.displaySeats();
            break;
        case 2:
            cout<<"Enter Row (1 to 8): ";
            cin>>row;
            cout<<"Enter Seat (1 to 8): ";
            cin>>seat;
            g.bookSeat(row,seat);
            break;
        case 3:
            cout<<"Enter Row (1 to 8): ";
            cin>>row;
            cout<<"Enter Seat (1 to 8): ";
            cin>>seat;
            g.cancelSeat(row,seat);
            break;
        case 4:
            cout<<"Exiting..\n";
            break;
        default:
            cout<<"Invalid choice! Try again.\n";
        }
    } while(ch!= 4);

    return 0;
}
