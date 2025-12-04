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
#include "../include/About.h"
#include "../include/ArcadeGlobals.h"
#include <ctime>

namespace arcade {

void showAbout() {

    string again = "Y";

    while (again == "Y") {

        cout << "\n=====================================\n";
        cout << "               ABOUT GAME\n";
        cout << "=====================================\n\n";

        cout << "INSERT INFO ABOUT GAME TMRW\n\n"
        // TODO: Insert game information
        time_t now = time(nullptr);
        cout << "Mini Arcade - Assignment 5 Edition\n";
        cout << "Date/time: " << ctime(&now);
        cout << "Features:\n";
        cout << "- Namespaces and header files\n";
        cout << "- Improved input validation\n";
        cout << "- Updated Lottery rules (1–40, bonus, extra lines)\n";
        cout << "- Rock Paper Scissors gamble option\n";
        cout << "- Multiple games in one program\n";
        
        again = getYesNo( "View the 'About' section again? (Y/N): ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (again == "N") {
            cout << "\nReturning to main menu...\n";
            return;
        }
    }

}
} // namespace arcade