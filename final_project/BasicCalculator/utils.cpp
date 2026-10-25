#include <iostream> // Provides terminal input and output
#include <limits> // Provides streamsize limits for discarding invalid input
#include <string> // Provides complete-line input
#include "utils.h" // Checks the helper definitions against their declarations

using namespace std;

// Reads one integer per line and rejects extra non-whitespace characters.
bool readInteger(int &value) {
    string remainder;
    while (true) {
        if (!(cin >> value)) {
            if (cin.eof()) {
                return false; // Lets the caller finish when terminal input ends
            }
            cin.clear(); // Restores input after a nonnumeric or out-of-range response
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            getline(cin, remainder); // Consumes the rest of the response, including its newline
            if (remainder.find_first_not_of(" \t\r") == string::npos) {
                return true;
            }
        }
        cout << "Invalid input. Enter one whole number: ";
    }
}

void pressAnyKey(string message) {
    string ignoredLine;
    cout << '\n' << message << "\n<Press Enter to continue>" << endl;
    getline(cin, ignoredLine); // Uses portable terminal input instead of Windows-only _getch
}

bool getValues(int &first, int &second) {
    cout << "\nENTERING OPERANDS\n------------------------------\n";
    cout << "Enter first operand: ";
    if (!readInteger(first)) {
        return false;
    }
    cout << "Enter second operand: ";
    return readInteger(second); // Updates the caller's operand through a reference
}

void displayResult(int first, int second, long long result) {
    cout << "First operand is " << first << endl;
    cout << "Second operand is " << second << endl;
    cout << "The result is " << result << endl;
}

int getOptionFromUser() {
    int option;
    if (!readInteger(option)) {
        return 5; // Treats end-of-input as a request to exit
    }
    return option;
}
