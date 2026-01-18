#include <iostream>
#include "utils.h"

using namespace std;

void clearScreen() {
    cout << "\x1b[2J\x1b[H";
    cout.flush();
}

void waitForEnter() {
    cout << "\nPress [Enter] to return to menu...";
    cin.ignore(1000, '\n');
    cin.get();
}