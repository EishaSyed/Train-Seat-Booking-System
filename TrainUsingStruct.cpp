#include <iostream>
using namespace std;

// Seat structure
struct Seat {
    int status; // 0 = Available, 1 = Booked, 2 = Not Available
};

Seat* train[3][7][4]; // 3 bogies, 7 rows, 4 columns

// Initialize train seat layout
void initializeTrain() {
    int initialStatus[3][7][4] = {
        {
            {0, 0, 0, 0},
            {0, 1, 1, 0},
            {0, 0, 0, 1},
            {0, 2, 2, 0},
            {2, 1, 0, 0},
            {0, 0, 0, 2},
            {1, 1, 1, 1}
        },
        {
            {0, 0, 0, 0},
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 2, 0, 0},
            {1, 0, 0, 1},
            {0, 0, 1, 1},
            {0, 0, 2, 2}
        },
        {
            {1, 0, 0, 1},
            {0, 0, 0, 0},
            {2, 2, 2, 2},
            {0, 0, 0, 0},
            {1, 1, 0, 0},
            {0, 0, 0, 0},
            {1, 0, 1, 0}
        }
    };

    for (int b = 0; b < 3; ++b)
        for (int r = 0; r < 7; ++r)
            for (int c = 0; c < 4; ++c) {
                train[b][r][c] = new Seat;
                train[b][r][c]->status = initialStatus[b][r][c];
            }
}

// Display menu
void showMenu() {
    cout << "\n===== Train Seat Booking Menu =====" << endl;
    cout << "1. Book a Seat" << endl;
    cout << "2. View Seat Layout" << endl;
    cout << "3. Exit" << endl;
    cout << "===================================" << endl;
}

// Show full seating layout
void showSeats() {
    cout << "\nSeat Layout:\n";
    cout << "0 = Available, 1 = Booked, 2 = Not Available\n\n";

    for (int b = 0; b < 3; ++b) {
        cout << "Bogie " << b + 1 << ":\n";
        for (int r = 0; r < 7; ++r) {
            cout << "Row " << r + 1 << ": ";
            for (int c = 0; c < 4; ++c) {
                if (c == 2) cout << "  "; // space for aisle
                cout << train[b][r][c]->status << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
}

// Ask user if they want to view seat layout
bool promptViewLayout() {
    char choice;
    cout << "Would you like to view the seat layout? (y/n): ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        showSeats();
        return true;
    }
    return false;
}

// Book a seat
void bookSeat() {
    int b, r, c;
    cout << "Enter bogie (1-3): ";
    cin >> b;
    cout << "Enter row (1-7): ";
    cin >> r;
    cout << "Enter column (1-4): ";
    cin >> c;

    b--; r--; c--;

    if (b < 0 || b >= 3 || r < 0 || r >= 7 || c < 0 || c >= 4) {
        cout << "Invalid seat location." << endl;
        return;
    }

    if (train[b][r][c]->status == 1) {
        cout << "Seat is already booked." << endl;
        if (promptViewLayout()) {
            bookSeat(); // retry
        }
    } else if (train[b][r][c]->status == 2) {
        cout << "Seat is not available." << endl;
        if (promptViewLayout()) {
            bookSeat(); // retry
        }
    } else if (train[b][r][c]->status == 0) {
        train[b][r][c]->status = 1;
        cout << "Seat booked successfully in Bogie " << b + 1
             << ", Row " << r + 1 << ", Column " << c + 1 << "." << endl;
    } else {
        cout << "Unknown seat status." << endl;
    }
}

// Clean up memory
void cleanupTrain() {
    for (int b = 0; b < 3; ++b)
        for (int r = 0; r < 7; ++r)
            for (int c = 0; c < 4; ++c)
                delete train[b][r][c];
}

int main() {
    initializeTrain();

    int choice;
    do {
        showMenu();
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bookSeat();
                break;
            case 2:
                showSeats();
                break;
            case 3:
                cout << "Exiting the system. Have a safe journey!" << endl;
                break;
            default:
                cout << "Invalid option. Try again." << endl;
        }
    } while (choice != 3);

    cleanupTrain();
    return 0;
}
