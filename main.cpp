#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

// ============================================================
// CONSTANTS
// ============================================================

const string ADMIN_USERNAME = "admin";
const string ADMIN_PASSWORD = "admin123";

const double SLEEPER_MULTIPLIER = 1.0;
const double AC3_MULTIPLIER = 1.5;
const double AC2_MULTIPLIER = 2.0;
const double AC1_MULTIPLIER = 3.0;


// ============================================================
// INPUT HELPER
// ============================================================

int getIntegerInput(const string& message) {

    int value;

    while (true) {

        cout << message;

        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Please enter a number.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


// ============================================================
// USER - ABSTRACT BASE CLASS
// ============================================================

class User {

protected:
    string name;

public:

    User() {}

    User(string userName) {
        name = userName;
    }

    string getName() const {
        return name;
    }

    virtual void displayRole() const = 0;

    virtual ~User() {}
};


// ============================================================
// PASSENGER
// ============================================================

class Passenger : public User {

private:
    int age;
    string gender;

public:

    Passenger() : User(), age(0), gender("") {}

    Passenger(string userName, int userAge, string userGender)
        : User(userName), age(userAge), gender(userGender) {}

    int getAge() const {
        return age;
    }

    string getGender() const {
        return gender;
    }

    void displayRole() const override {
        cout << "Role: Passenger\n";
    }
};


// ============================================================
// ADMIN
// ============================================================

class Admin : public User {

private:
    string password;

public:

    Admin() : User(), password("") {}

    Admin(string userName, string userPassword)
        : User(userName), password(userPassword) {}

    bool login(const string& enteredUsername,
               const string& enteredPassword) const {

        return enteredUsername == name &&
               enteredPassword == password;
    }

    void displayRole() const override {
        cout << "Role: Administrator\n";
    }
};


// ============================================================
// TRAIN
// ============================================================

class Train {

private:
    int trainNumber;
    string trainName;
    string source;
    string destination;

    int totalSeats;
    double baseFare;

    vector<bool> bookedSeats;

public:

    Train(int number,
          string name,
          string src,
          string dest,
          int seats,
          double fare)
        : trainNumber(number),
          trainName(name),
          source(src),
          destination(dest),
          totalSeats(seats),
          baseFare(fare),
          bookedSeats(seats + 1, false) {}

    int getTrainNumber() const {
        return trainNumber;
    }

    string getTrainName() const {
        return trainName;
    }

    string getSource() const {
        return source;
    }

    string getDestination() const {
        return destination;
    }

    int getTotalSeats() const {
        return totalSeats;
    }

    double getBaseFare() const {
        return baseFare;
    }

    int getAvailableSeats() const {

        int count = 0;

        for (int i = 1; i <= totalSeats; i++) {

            if (!bookedSeats[i]) {
                count++;
            }
        }

        return count;
    }

    int bookSeat() {

        for (int i = 1; i <= totalSeats; i++) {

            if (!bookedSeats[i]) {

                bookedSeats[i] = true;
                return i;
            }
        }

        return -1;
    }

    bool cancelSeat(int seatNumber) {

        if (seatNumber < 1 || seatNumber > totalSeats) {
            return false;
        }

        if (!bookedSeats[seatNumber]) {
            return false;
        }

        bookedSeats[seatNumber] = false;

        return true;
    }

    void updateTrain(string newName,
                     string newSource,
                     string newDestination,
                     double newFare) {

        trainName = newName;
        source = newSource;
        destination = newDestination;
        baseFare = newFare;
    }

    void displayTrain() const {

        cout << left
             << setw(10) << trainNumber
             << setw(25) << trainName
             << setw(18) << source
             << setw(18) << destination
             << setw(12) << totalSeats
             << setw(15) << getAvailableSeats()
             << setw(10) << fixed << setprecision(2) << baseFare
             << '\n';
    }
};


// ============================================================
// TICKET
// ============================================================

class Ticket {

private:

    long long pnr;

    Passenger passenger;

    int trainNumber;
    string trainName;

    int seatNumber;

    string travelClass;

    double fare;

    bool cancelled;

public:

    Ticket(long long ticketPNR,
           Passenger passengerInfo,
           int number,
           string name,
           int seat,
           string className,
           double ticketFare)
        : pnr(ticketPNR),
          passenger(passengerInfo),
          trainNumber(number),
          trainName(name),
          seatNumber(seat),
          travelClass(className),
          fare(ticketFare),
          cancelled(false) {}

    long long getPNR() const {
        return pnr;
    }

    Passenger getPassenger() const {
        return passenger;
    }

    int getTrainNumber() const {
        return trainNumber;
    }

    int getSeatNumber() const {
        return seatNumber;
    }

    bool isCancelled() const {
        return cancelled;
    }

    void cancel() {
        cancelled = true;
    }

    void displayTicket() const {

        cout << "\n========================================\n";
        cout << "              TICKET DETAILS\n";
        cout << "========================================\n";

        cout << "PNR           : " << pnr << '\n';
        cout << "Passenger     : " << passenger.getName() << '\n';
        cout << "Age           : " << passenger.getAge() << '\n';
        cout << "Gender        : " << passenger.getGender() << '\n';

        cout << "Train Number  : " << trainNumber << '\n';
        cout << "Train Name    : " << trainName << '\n';

        cout << "Seat Number   : " << seatNumber << '\n';
        cout << "Class         : " << travelClass << '\n';

        cout << "Fare          : Rs. "
             << fixed << setprecision(2) << fare << '\n';

        cout << "Status        : "
             << (cancelled ? "CANCELLED" : "CONFIRMED")
             << '\n';

        cout << "========================================\n";
    }
};


// ============================================================
// RAILWAY SYSTEM
// ============================================================

class RailwaySystem {

private:

    vector<Train> trains;
    vector<Ticket> tickets;

    long long nextPNR = 1000000001;


    // --------------------------------------------------------
    // Find Train
    // --------------------------------------------------------

    Train* findTrain(int trainNumber) {

        for (auto& train : trains) {

            if (train.getTrainNumber() == trainNumber) {
                return &train;
            }
        }

        return nullptr;
    }


    // --------------------------------------------------------
    // Find Ticket
    // --------------------------------------------------------

    Ticket* findTicket(long long pnr) {

        for (auto& ticket : tickets) {

            if (ticket.getPNR() == pnr) {
                return &ticket;
            }
        }

        return nullptr;
    }


    // --------------------------------------------------------
    // Calculate Fare
    // --------------------------------------------------------

    double calculateFare(double baseFare, int classChoice) {

        switch (classChoice) {

            case 1:
                return baseFare * SLEEPER_MULTIPLIER;

            case 2:
                return baseFare * AC3_MULTIPLIER;

            case 3:
                return baseFare * AC2_MULTIPLIER;

            case 4:
                return baseFare * AC1_MULTIPLIER;

            default:
                return -1;
        }
    }


    // --------------------------------------------------------
    // Get Class Name
    // --------------------------------------------------------

    string getClassName(int classChoice) {

        switch (classChoice) {

            case 1:
                return "Sleeper";

            case 2:
                return "AC 3 Tier";

            case 3:
                return "AC 2 Tier";

            case 4:
                return "AC 1 Tier";

            default:
                return "Unknown";
        }
    }


public:

    // ========================================================
    // CONSTRUCTOR
    // ========================================================

    RailwaySystem() {

        trains.emplace_back(
            12845,
            "BBS SMVB Express",
            "Bhubaneswar",
            "Bangalore",
            50,
            850
        );

        trains.emplace_back(
            18463,
            "Prashanti Express",
            "Bhubaneswar",
            "Bangalore",
            40,
            780
        );

        trains.emplace_back(
            12801,
            "Purushottam Express",
            "Bhubaneswar",
            "New Delhi",
            60,
            920
        );

        trains.emplace_back(
            22823,
            "Rajdhani Express",
            "Bhubaneswar",
            "New Delhi",
            30,
            1450
        );
    }


    // ========================================================
    // DISPLAY ALL TRAINS
    // ========================================================

    void displayAllTrains() const {

        if (trains.empty()) {

            cout << "\nNo trains available.\n";
            return;
        }

        cout << "\n";
        cout << left
             << setw(10) << "Number"
             << setw(25) << "Train Name"
             << setw(18) << "Source"
             << setw(18) << "Destination"
             << setw(12) << "Total"
             << setw(15) << "Available"
             << setw(10) << "Fare"
             << '\n';

        cout << string(108, '-') << '\n';

        for (const auto& train : trains) {
            train.displayTrain();
        }
    }


    // ========================================================
    // SEARCH TRAIN
    // ========================================================

    void searchTrain() {

        string source;
        string destination;

        cout << "\nEnter source: ";
        getline(cin, source);

        cout << "Enter destination: ";
        getline(cin, destination);

        bool found = false;

        cout << "\nSearch Results:\n";

        cout << left
             << setw(10) << "Number"
             << setw(25) << "Train Name"
             << setw(18) << "Source"
             << setw(18) << "Destination"
             << setw(12) << "Total"
             << setw(15) << "Available"
             << setw(10) << "Fare"
             << '\n';

        cout << string(108, '-') << '\n';

        for (const auto& train : trains) {

            if (train.getSource() == source &&
                train.getDestination() == destination) {

                train.displayTrain();
                found = true;
            }
        }

        if (!found) {
            cout << "No matching trains found.\n";
        }
    }


    // ========================================================
    // BOOK TICKET
    // ========================================================

    void bookTicket() {

        int trainNumber =
            getIntegerInput("\nEnter train number: ");

        Train* train = findTrain(trainNumber);

        if (train == nullptr) {

            cout << "Train not found.\n";
            return;
        }

        if (train->getAvailableSeats() == 0) {

            cout << "Sorry, no seats available on this train.\n";
            return;
        }


        // Passenger details

        string name;

        cout << "Enter passenger name: ";
        getline(cin, name);

        int age;

        while (true) {

            age = getIntegerInput("Enter age: ");

            if (age >= 1 && age <= 120) {
                break;
            }

            cout << "Age must be between 1 and 120.\n";
        }


        string gender;

        cout << "Enter gender: ";
        getline(cin, gender);


        Passenger passenger(name, age, gender);


        // Class selection

        cout << "\nSelect Class:\n";
        cout << "1. Sleeper       (1x fare)\n";
        cout << "2. AC 3 Tier     (1.5x fare)\n";
        cout << "3. AC 2 Tier     (2x fare)\n";
        cout << "4. AC 1 Tier     (3x fare)\n";

        int classChoice;

        while (true) {

            classChoice =
                getIntegerInput("Enter class choice: ");

            if (classChoice >= 1 &&
                classChoice <= 4) {

                break;
            }

            cout << "Invalid class choice.\n";
        }


        double fare =
            calculateFare(
                train->getBaseFare(),
                classChoice
            );

        string className =
            getClassName(classChoice);


        // Book seat

        int seatNumber = train->bookSeat();

        if (seatNumber == -1) {

            cout << "Sorry, no seats available.\n";
            return;
        }


        // Create ticket

        long long pnr = nextPNR++;

        Ticket ticket(
            pnr,
            passenger,
            train->getTrainNumber(),
            train->getTrainName(),
            seatNumber,
            className,
            fare
        );

        tickets.push_back(ticket);


        cout << "\nTicket booked successfully!\n";
        cout << "Your PNR is: " << pnr << '\n';
        cout << "Your seat number is: "
             << seatNumber << '\n';

        cout << "Fare: Rs. "
             << fixed << setprecision(2)
             << fare << '\n';
    }


    // ========================================================
    // VIEW TICKET
    // ========================================================

    void viewTicket() {

        long long pnr =
            getIntegerInput("\nEnter PNR: ");

        Ticket* ticket = findTicket(pnr);

        if (ticket == nullptr) {

            cout << "Ticket not found.\n";
            return;
        }

        ticket->displayTicket();
    }


    // ========================================================
    // CANCEL TICKET
    // ========================================================

    void cancelTicket() {

        long long pnr =
            getIntegerInput("\nEnter PNR: ");

        Ticket* ticket = findTicket(pnr);

        if (ticket == nullptr) {

            cout << "Ticket not found.\n";
            return;
        }

        if (ticket->isCancelled()) {

            cout << "This ticket is already cancelled.\n";
            return;
        }


        Train* train =
            findTrain(ticket->getTrainNumber());

        if (train == nullptr) {

            cout << "Associated train not found.\n";
            return;
        }


        bool cancelled =
            train->cancelSeat(
                ticket->getSeatNumber()
            );

        if (!cancelled) {

            cout << "Unable to cancel the seat.\n";
            return;
        }

        ticket->cancel();

        cout << "Ticket cancelled successfully.\n";
    }


    // ========================================================
    // BOOKING HISTORY
    // ========================================================

    void bookingHistory() {

        string name;

        cout << "\nEnter passenger name: ";
        getline(cin, name);

        bool found = false;

        cout << "\nBooking History:\n";

        for (const auto& ticket : tickets) {

            if (ticket.getPassenger().getName() == name) {

                ticket.displayTicket();

                found = true;
            }
        }

        if (!found) {

            cout << "No booking history found "
                 << "for this passenger.\n";
        }
    }


    // ========================================================
    // ADD TRAIN - ADMIN
    // ========================================================

    void addTrain() {

        int trainNumber =
            getIntegerInput("\nEnter train number: ");

        if (findTrain(trainNumber) != nullptr) {

            cout << "A train with this number "
                 << "already exists.\n";

            return;
        }


        string trainName;
        string source;
        string destination;

        cout << "Enter train name: ";
        getline(cin, trainName);

        cout << "Enter source: ";
        getline(cin, source);

        cout << "Enter destination: ";
        getline(cin, destination);


        int totalSeats;

        while (true) {

            totalSeats =
                getIntegerInput("Enter total seats: ");

            if (totalSeats > 0) {
                break;
            }

            cout << "Seats must be greater than 0.\n";
        }


        double baseFare;

        while (true) {

            cout << "Enter base fare: ";

            if (cin >> baseFare) {

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                if (baseFare > 0) {
                    break;
                }
            }

            cout << "Please enter a valid positive fare.\n";

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );
        }


        trains.emplace_back(
            trainNumber,
            trainName,
            source,
            destination,
            totalSeats,
            baseFare
        );

        cout << "Train added successfully.\n";
    }


    // ========================================================
    // REMOVE TRAIN - ADMIN
    // ========================================================

    void removeTrain() {

        int trainNumber =
            getIntegerInput("\nEnter train number to remove: ");

        for (auto it = trains.begin();
             it != trains.end();
             ++it) {

            if (it->getTrainNumber() == trainNumber) {

                if (it->getAvailableSeats() !=
                    it->getTotalSeats()) {

                    cout << "Cannot remove train because "
                         << "tickets are already booked.\n";

                    return;
                }

                trains.erase(it);

                cout << "Train removed successfully.\n";

                return;
            }
        }

        cout << "Train not found.\n";
    }


    // ========================================================
    // UPDATE TRAIN - ADMIN
    // ========================================================

    void updateTrain() {

        int trainNumber =
            getIntegerInput("\nEnter train number to update: ");

        Train* train = findTrain(trainNumber);

        if (train == nullptr) {

            cout << "Train not found.\n";
            return;
        }


        string newName;
        string newSource;
        string newDestination;

        cout << "Enter new train name: ";
        getline(cin, newName);

        cout << "Enter new source: ";
        getline(cin, newSource);

        cout << "Enter new destination: ";
        getline(cin, newDestination);


        double newFare;

        while (true) {

            cout << "Enter new base fare: ";

            if (cin >> newFare) {

                cin.ignore(
                    numeric_limits<streamsize>::max(),
                    '\n'
                );

                if (newFare > 0) {
                    break;
                }
            }

            cout << "Please enter a valid positive fare.\n";

            cin.clear();

            cin.ignore(
                numeric_limits<streamsize>::max(),
                '\n'
            );
        }


        train->updateTrain(
            newName,
            newSource,
            newDestination,
            newFare
        );

        cout << "Train updated successfully.\n";
    }


    // ========================================================
    // PASSENGER MENU
    // ========================================================

    void passengerMenu() {

        while (true) {

            cout << "\n========================================\n";
            cout << "          PASSENGER MENU\n";
            cout << "========================================\n";

            cout << "1. View All Trains\n";
            cout << "2. Search Train\n";
            cout << "3. Book Ticket\n";
            cout << "4. View Ticket\n";
            cout << "5. Cancel Ticket\n";
            cout << "6. Booking History\n";
            cout << "7. Back\n";

            int choice =
                getIntegerInput("Enter choice: ");

            switch (choice) {

                case 1:
                    displayAllTrains();
                    break;

                case 2:
                    searchTrain();
                    break;

                case 3:
                    bookTicket();
                    break;

                case 4:
                    viewTicket();
                    break;

                case 5:
                    cancelTicket();
                    break;

                case 6:
                    bookingHistory();
                    break;

                case 7:
                    return;

                default:
                    cout << "Invalid choice.\n";
            }
        }
    }


    // ========================================================
    // ADMIN MENU
    // ========================================================

    void adminMenu() {

        while (true) {

            cout << "\n========================================\n";
            cout << "            ADMIN MENU\n";
            cout << "========================================\n";

            cout << "1. Add Train\n";
            cout << "2. Remove Train\n";
            cout << "3. Update Train\n";
            cout << "4. View All Trains\n";
            cout << "5. Back\n";

            int choice =
                getIntegerInput("Enter choice: ");

            switch (choice) {

                case 1:
                    addTrain();
                    break;

                case 2:
                    removeTrain();
                    break;

                case 3:
                    updateTrain();
                    break;

                case 4:
                    displayAllTrains();
                    break;

                case 5:
                    return;

                default:
                    cout << "Invalid choice.\n";
            }
        }
    }


    // ========================================================
    // ADMIN LOGIN
    // ========================================================

    void adminLogin() {

        string username;
        string password;

        cout << "\n========================================\n";
        cout << "             ADMIN LOGIN\n";
        cout << "========================================\n";

        cout << "Username: ";
        getline(cin, username);

        cout << "Password: ";
        getline(cin, password);


        Admin admin(
            ADMIN_USERNAME,
            ADMIN_PASSWORD
        );


        if (admin.login(username, password)) {

            cout << "\nLogin successful!\n";

            admin.displayRole();

            adminMenu();

        } else {

            cout << "\nInvalid username or password.\n";
        }
    }


    // ========================================================
    // MAIN MENU
    // ========================================================

    void run() {

        while (true) {

            cout << "\n========================================\n";
            cout << "       RAILWAY MANAGEMENT SYSTEM\n";
            cout << "========================================\n";

            cout << "1. Passenger\n";
            cout << "2. Admin\n";
            cout << "3. Exit\n";

            int choice =
                getIntegerInput("Enter choice: ");


            switch (choice) {

                case 1:
                    passengerMenu();
                    break;

                case 2:
                    adminLogin();
                    break;

                case 3:

                    cout << "\nThank you for using "
                         << "Railway Management System!\n";

                    return;

                default:

                    cout << "Invalid choice. "
                         << "Please try again.\n";
            }
        }
    }
};


// ============================================================
// MAIN
// ============================================================

int main() {

    RailwaySystem railwaySystem;

    railwaySystem.run();

    return 0;
}