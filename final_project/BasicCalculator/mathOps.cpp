#include <iostream> // Provides operation headings
#include "mathOps.h" // Checks the operation definitions against their declarations
#include "utils.h" // Provides shared result display and pause helpers

using namespace std;

void computeAdd(int first, int second) {
    cout << "\nADDITION\n----------------------\n";
    displayResult(first, second, static_cast<long long>(first) + second); // Widens before arithmetic to preserve large results
    pressAnyKey("Done!");
}

void computeSub(int first, int second) {
    cout << "\nSUBTRACTION\n----------------------\n";
    displayResult(first, second, static_cast<long long>(first) - second);
    pressAnyKey("Done!");
}

void computeMul(int first, int second) {
    cout << "\nMULTIPLICATION\n----------------------\n";
    displayResult(first, second, static_cast<long long>(first) * second);
    pressAnyKey("Done!");
}

void computeDiv(int first, int second) {
    cout << "\nDIVISION\n----------------------\n";
    if (second == 0) { // Prevents division by zero
        pressAnyKey("The second operand cannot be zero.");
    } else {
        displayResult(first, second, static_cast<long long>(first) / second); // Keeps the original integer-division behavior
        pressAnyKey("Done!");
    }
}
