#include <iostream>
#include <cstdlib>      // rand(), srand()
#include <ctime>        // time()
#include <limits>       // numeric_limits
#include <string>       // string
#include <sstream>      // stringstream / stoi references (future-safe)
#include <vector>       // ONLY for lottery game (allowed there)
#include <iomanip>      // for setw, left, right (Murach-style formatting)
#include <algorithm>    // sort, find
#include <fstream>      // file output in lottery game
#include <cctype>       // isalpha, isspace, tolower, isdigit
#include <thread>       // for dice rolling effect (sleep)
#include <chrono>       // for milliseconds (sleep)

// Headers
#include "Credits.h"
#include "ArcadeGlobals.h"
namespace arcade {
    using namespace std;

/* =========================================================
   Credits
   ========================================================= */
void showCredits() {

    string again = "Y";

    while (again == "Y") {

        cout << "\n=====================================\n";
        cout << "               CREDITS\n";
        cout << "=====================================\n\n";

        cout << "[ Mini Arcade ]\n";
        cout << " > Version: 5.0 - Assignment 5 Update\n";
        cout << " > This program uses namespaces and headers (Murach Chapter 9).\n\n";

        cout << "Developed for:\n";
        cout << " > COMP 2006 - C++ Programming\n";
        cout << " > Georgian College\n";
        cout << " > Instructor: Professor Maziar Shajari\n\n";

        cout << "Developed by: Group 9\n";
        cout << " > Programmer: Mariam Mueen\n";
        cout << " > Programmer: Fayzabanu Diwan\n\n";

        cout << "Special Thanks / References:\n";
        cout << " > Murach's C++ Programming, 2nd Edition\n";
        cout << " > Instructor class notes on namespaces, validation, and functions\n";
        cout << " > Standard C++ documentation for getline, stoi, vectors, and time.\n\n";

        cout << "Thank you for playing the Mini Arcade!\n\n";

        again = getYesNo("View the credits again? (Y/N): ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (again == "N") {
            cout << "\nReturning to main menu...\n";
            return;
        }
    }
}
} // namespace arcade