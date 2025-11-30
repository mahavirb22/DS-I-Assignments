#include<iostream>
using namespace std;

struct Node {
    int start; 
    int end;   
    Node* next;

    Node(int s, int e)  {
        start = s;
        end = e;
        next = nullptr;
    }
};

class AppointmentList {
    Node* head;
    int dayStart, dayEnd, minDur, maxDur;

public:
    AppointmentList(int ds, int de, int minD, int maxD) {
        head = nullptr;
        dayStart = ds;
        dayEnd = de;
        minDur = minD;
        maxDur = maxD;
    }

    void printTime(int t) {
        int h = t / 60;
        int m = t % 60;
        cout<<h<<" : "<<m;
    }

    void displayAppointments() {
        if(!head) {
            cout<<"\nNo appointments booked.\n";
            return;
        }
        cout<<"\n--- Booked Appointments ---\n";
        Node* temp = head;
        while(temp) {
            printTime(temp->start);
            cout<<" - ";
            printTime(temp->end);
            cout<<endl;
            temp = temp->next;
        }
    }

    void displayAvailableSlots() {
        cout<<"\n--- Available Time Slots ---\n";
        if(!head) {
            printTime(dayStart);
            cout<<" - ";
            printTime(dayEnd);
            cout<<endl;
            return;
        }
        Node* temp = head;
        int prevEnd = dayStart;

        while(temp) {
            if(temp->start > prevEnd) {
                printTime(prevEnd);
                cout<<" - ";
                printTime(temp->start);
                cout<<endl;
            }
            prevEnd = temp->end;
            temp = temp->next;
        }

        if(prevEnd < dayEnd) {
            printTime(prevEnd);
            cout<<" - ";
            printTime(dayEnd);
            cout<<endl;
        }
    }

    bool isAvailable(int s, int e) {
        if(s < dayStart || e > dayEnd || s >= e)
            return false;

        Node* temp = head;
        while(temp) {
            if(!(e <= temp->start || s >= temp->end))
                return false; 
            temp = temp->next;
        }
        return true;
    }

    void bookAppointment() {
        int sh, sm, eh, em;
        cout<<"Enter start time (HH MM): ";
        cin>>sh>>sm;
        cout<<"Enter end time (HH MM): ";
        cin>>eh>>em;

        int start = sh * 60 + sm;
        int end = eh * 60 + em;
        int duration = end - start;

        if(duration < minDur || duration > maxDur) {
            cout<<"Duration must be between "<<minDur<<" and "<<maxDur<<" minutes or time must be in 24 hours.\n";
            return;
        }

        if(!isAvailable(start, end)) {
            cout<<"Time slot not available or already booked.\n";
            return;
        }

        Node* newNode = new Node(start, end);

        if(!head || start < head->start) {
            newNode->next = head;
            head = newNode;
        }
        else {
            Node* temp = head;
            while (temp->next && temp->next->start < start)
                temp = temp->next;
            newNode->next = temp->next;
            temp->next = newNode;
        }

        cout<<"Appointment booked successfully!\n";
    }

    void cancelAppointment() {
        if(!head) {
            cout<<"No appointments to cancel.\n";
            return;
        }

        int h, m;
        cout<<"Enter start time (HH MM) of appointment to cancel: ";
        cin>>h>>m;
        int t = h * 60 + m;

        Node* temp = head;
        Node* prev = nullptr;

        while(temp && temp->start != t) {
            prev = temp;
            temp = temp->next;
        }

        if(!temp) {
            cout<<"Appointment not found.\n";
            return;
        }

        if(!prev)
            head = temp->next;
        else
            prev->next = temp->next;

        delete temp;
        cout<<"Appointment cancelled.\n";
    }

    void sortByData() {
        if(!head) return;
        for(Node* i = head; i; i = i->next)
            for(Node* j = i->next; j; j = j->next)
                if(i->start > j->start) {
                    swap(i->start, j->start);
                    swap(i->end, j->end);
                }
        cout<<"Sorted by swapping data values.\n";
    }

    void sortByPointer() {
        if(!head || !head->next) 
            return;

        Node* sorted = nullptr;

        while(head) {
            Node* curr = head;
            head = head->next;

            if(!sorted || curr->start < sorted->start) {
                curr->next = sorted;
                sorted = curr;
            } 
            else {
                Node* temp = sorted;
                while (temp->next && temp->next->start < curr->start)
                    temp = temp->next;
                curr->next = temp->next;
                temp->next = curr;
            }
        }
        head = sorted;
        cout<<"Sorted by pointer manipulation.\n";
    }
};

int main() {
    AppointmentList scheduler(9 * 60, 17 * 60, 30, 90);

    int ch;
    do{
        cout<<"\n\n=== Appointment Scheduler ===\n";
        cout<<"1. Display Available Slots\n";
        cout<<"2. Book Appointment\n";
        cout<<"3. Cancel Appointment\n";
        cout<<"4. Sort by Data\n";
        cout<<"5. Sort by Pointers\n";
        cout<<"6. Display All Appointments\n";
        cout<<"7. Exit\n";
        cout<<"Enter choice: ";
        cin>>ch;
        switch(ch) {
            case 1:
                scheduler.displayAvailableSlots();
                break;
            case 2:
                scheduler.bookAppointment();
                break;
            case 3: 
                scheduler.cancelAppointment(); 
                break;
            case 4: 
                scheduler.sortByData(); 
                break;
            case 5: 
                scheduler.sortByPointer(); 
                break;
            case 6: 
                scheduler.displayAppointments(); 
                break;
            case 7: 
                exit(0); 
                break;
            default:
                cout<<"Invalid Choice. Select choice from menu.\n";
        }
    } while(ch!=7);
}
