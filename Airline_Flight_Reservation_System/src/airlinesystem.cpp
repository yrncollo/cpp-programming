#include <iostream>
#include <string>
using namespace std;

const int TOTAL_SEATS = 100;

class Flight {
public:
    Flight() : reservedSeats(0), cancelledTickets(0) {
        for (int i = 0; i < TOTAL_SEATS; ++i) {
            seats[i] = 0; // Initialize all seats to unbooked
        }
        start = nullptr;
    }

    void bookTicket();
    void cancelTicket();
    void changeReservation();
    void passengerDetails();
    void getBookingDetails();

private:
    struct Passenger {
        string fname;
        string lname;
        string ID;
        string phoneNumber;
        string foodMenu;
        int seatNumber;
        int reservationNumber;
        Passenger* next;
    };

    Passenger* start;
    int seats[TOTAL_SEATS];
    int reservedSeats;
    int cancelledTickets;

    bool isSeatAvailable(int seatNumber);
    void displayAvailableSeats();
    void addPassenger(Passenger* newPassenger);
};

bool Flight::isSeatAvailable(int seatNumber) {
    return seatNumber > 0 && seatNumber <= TOTAL_SEATS && seats[seatNumber - 1] == 0;
}

void Flight::displayAvailableSeats() {
    cout << "Available seats: ";
    for (int i = 0; i < TOTAL_SEATS; ++i) {
        if (seats[i] == 0) {
            cout << (i + 1) << " ";
        }
    }
    cout << endl;
}

void Flight::addPassenger(Passenger* newPassenger) {
    if (!start) {
        start = newPassenger;
    } else {
        Passenger* temp = start;
        while (temp->next) {
            temp = temp->next;
        }
        temp->next = newPassenger;
    }
}

void Flight::bookTicket() {
    Passenger* newPassenger = new Passenger();
    cout << "Enter your first name: ";
    cin >> newPassenger->fname;
    cout << "Enter your last name: ";
    cin >> newPassenger->lname;
    cout << "Enter your ID: ";
    cin >> newPassenger->ID;
    cout << "Enter your phone number: ";
    cin >> newPassenger->phoneNumber;

    int seatNumber;
    do {
        displayAvailableSeats();
        cout << "Enter the seat number: ";
        cin >> seatNumber;
    } while (!isSeatAvailable(seatNumber));

    seats[seatNumber - 1] = -1; // Mark seat as booked
    newPassenger->seatNumber = seatNumber;

    cout << "Enter your food choice preference (1. Veg, 2. Non-Veg, 3. No Food): ";
    int choice;
    cin >> choice;
    switch (choice) {
    case 1: newPassenger->foodMenu = "Veg"; break;
    case 2: newPassenger->foodMenu = "Non-Veg"; break;
    case 3: newPassenger->foodMenu = "No Food"; break;
    default: newPassenger->foodMenu = "No Food"; break;
    }

    newPassenger->next = nullptr;
    newPassenger->reservationNumber = ++reservedSeats;
    cout << "Your reservation number is: " << reservedSeats << endl;

    addPassenger(newPassenger);
}

void Flight::cancelTicket() {
    cout << "Enter your reservation number: ";
    int reservationNumber;
    cin >> reservationNumber;

    Passenger* prev = nullptr;
    Passenger* current = start;

    while (current) {
        if (current->reservationNumber == reservationNumber) {
            if (prev) {
                prev->next = current->next;
            } else {
                start = current->next;
            }

            seats[current->seatNumber - 1] = 0; // Mark seat as available
            delete current;
            ++cancelledTickets;
            cout << "Ticket cancelled successfully." << endl;
            return;
        }
        prev = current;
        current = current->next;
    }

    cout << "Reservation number not found." << endl;
}

void Flight::changeReservation() {
    cout << "Enter your current seat number: ";
    int currentSeatNumber;
    cin >> currentSeatNumber;

    if (!isSeatAvailable(currentSeatNumber)) {
        Passenger* current = start;
        while (current) {
            if (current->seatNumber == currentSeatNumber) {
                int newSeatNumber;
                do {
                    displayAvailableSeats();
                    cout << "Enter the new seat number: ";
                    cin >> newSeatNumber;
                } while (!isSeatAvailable(newSeatNumber));

                seats[current->seatNumber - 1] = 0; // Mark old seat as available
                seats[newSeatNumber - 1] = -1; // Mark new seat as booked
                current->seatNumber = newSeatNumber;
                cout << "Seat changed successfully." << endl;
                return;
            }
            current = current->next;
        }
    }

    cout << "Current seat number is invalid or not booked." << endl;
}

void Flight::passengerDetails() {
    cout << "Enter your reservation number: ";
    int reservationNumber;
    cin >> reservationNumber;

    Passenger* current = start;
    while (current) {
        if (current->reservationNumber == reservationNumber) {
            cout << "Reservation Number: " << current->reservationNumber << endl;
            cout << "Name: " << current->fname << " " << current->lname << endl;
            cout << "ID: " << current->ID << endl;
            cout << "Phone Number: " << current->phoneNumber << endl;
            cout << "Seat Number: " << current->seatNumber << endl;
            cout << "Food Menu: " << current->foodMenu << endl;
            return;
        }
        current = current->next;
    }

    cout << "Reservation number not found." << endl;
}

void Flight::getBookingDetails() {
    cout << "All Booking Details:" << endl;
    Passenger* current = start;
    while (current) {
        cout << "Reservation Number: " << current->reservationNumber << endl;
        cout << "Name: " << current->fname << " " << current->lname << endl;
        cout << "ID: " << current->ID << endl;
        cout << "Phone Number: " << current->phoneNumber << endl;
        cout << "Seat Number: " << current->seatNumber << endl;
        cout << "Food Menu: " << current->foodMenu << endl;
        current = current->next;
    }
}

void displayMenu() {
    cout << "\t\t|------------------------------------------------------------------|" << "\n";
    cout << "\t\t|                                                                  |" << "\n"; 
    cout << "\t\t|     WELCOME TO YRNCOLLO AIRLINE FLIGHT RESERVATION SYSTEM        |" << "\n";
    cout << "\t\t|                                                                  |" << "\n"; 
    cout << "\t\t|------------------------------------------------------------------|" << "\n";
    cout << "\t\t|          Choose your option:                                     |" << "\n"; 
    cout << "\t\t|------------------------------------------------------------------|" << "\n";
    cout << "\t\t|                                                                  |" << "\n";  
    cout << "\t\t|          1) BOOK TICKET                                          |" << "\n"; 
    cout << "\t\t|                                                                  |" << "\n"; 
    cout << "\t\t|          2) CANCEL TICKET                                        |" << "\n"; 
    cout << "\t\t|                                                                  |" << "\n";
    cout << "\t\t|          3) CHANGE RESERVATION                                   |" << "\n"; 
    cout << "\t\t|                                                                  |" << "\n";
    cout << "\t\t|          4) PASSENGER DETAILS                                    |" << "\n"; 
    cout << "\t\t|                                                                  |" << "\n";
    cout << "\t\t|          5) GET BOOKING DETAILS                                  |" << "\n"; 
    cout << "\t\t|                                                                  |" << "\n";
    cout << "\t\t|          6) EXIT                                                 |" << "\n"; 
    cout << "\t\t|------------------------------------------------------------------|" << "\n";
}

int main() {
    Flight flight;
    int choice;

    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            system("CLS");
            flight.bookTicket();
            break;
        case 2:
            system("CLS");
            flight.cancelTicket();
            break;
        case 3:
            system("CLS");
            flight.changeReservation();
            break;
        case 4:
            system("CLS");
            flight.passengerDetails();
            break;
        case 5:
            system("CLS");
            flight.getBookingDetails();
            break;
        case 6:
            system("CLS");
            cout << "Thank you for using YRNCOLLO Airline Flight Reservation System." << endl;
            break;
        default:
            system("CLS");
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}
