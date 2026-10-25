#ifndef UTILS_H
#define UTILS_H

#include <string> // Provides the message type used by the pause helper

void pressAnyKey(std::string message); // Retains the original helper name; waits for Enter
bool getValues(int &first, int &second); // Returns false if input ends before both operands are available
void displayResult(int first, int second, long long result); // Displays the operands and integer result
int getOptionFromUser(); // Retries invalid input and returns 5 when input ends

#endif
