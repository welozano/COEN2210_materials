/*
 * Course: COEN 2210 - Introduction to Programming
 * Sample: Basic Integer Calculator
 * Description: Portable adaptation of the original Visual Studio sample.
 */
#include <iostream> // Provides terminal output
#include "utils.h" // Declares input and display helpers
#include "mathOps.h" // Declares arithmetic operations

using namespace std;

int main() {
    int option;
    int first;
    int second;
    bool done = false; // Controls the menu loop

    while (!done) {
        cout << "\nSIMPLE INTEGER CALCULATOR\n";
        cout << "--------------------------\n";
        cout << "1. Addition\n2. Subtraction\n3. Multiplication\n";
        cout << "4. Division\n5. Exit application\n";
        cout << "--------------------------\nEnter option number: ";
        option = getOptionFromUser(); // Reads one complete integer response

        switch (option) {
            case 1:
                if (getValues(first, second)) { // Continues only after both operands are available
                    computeAdd(first, second);
                }
                break;
            case 2:
                if (getValues(first, second)) {
                    computeSub(first, second);
                }
                break;
            case 3:
                if (getValues(first, second)) {
                    computeMul(first, second);
                }
                break;
            case 4:
                if (getValues(first, second)) {
                    computeDiv(first, second);
                }
                break;
            case 5:
                done = true;
                break;
            default:
                pressAnyKey("Invalid option!"); // Pauses after an invalid menu selection
                break;
        }
    }

    cout << "Goodbye!" << endl;
    return 0;
}
