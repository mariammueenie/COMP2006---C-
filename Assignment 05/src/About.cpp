#include <iostream>    // cin, cout
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
#include "About.h"
#include "ArcadeGlobals.h"
#include <ctime>

namespace arcade {
    using namespace std;
void showAbout() {

    string again = "Y";

    while (again == "Y") {

        cout << "\n=====================================\n";
        cout << "               ABOUT GAME\n";
        cout << "=====================================\n\n";

        // Greet player by name
        cout << "Hello, " << player.first << " " << player.last << "!\n";

        // Get time from device
        time_t now = time(nullptr);
        cout << "It is currently: " << ctime(&now) << "\n";
        
        // TODO: Insert game information
        cout << "Welcome to the Mini Arcade — Assignment 05 Edition!\n\n";

        cout << "This program demonstrates:\n";
        cout << " - Namespaces\n";
        cout << " - Header Files\n";
        cout << " - Structs (PlayerName)\n";
        cout << " - Input Validation Functions\n";
        cout << " - Vectors (Lottery Game)\n";
        cout << " - File Output (Lottery Ticket System)\n";
        cout << " - Multi-File Project Organization\n";
        cout << " - Bonus Gameplay (Rock-Paper-Scissors)\n\n";

        cout << "Games Included:\n";
        cout << " 1. Guessing Game (Numbers 1-100, 7 tries)\n";
        cout << " 2. Dice Game (Pick two values and match to win)\n";
        cout << " 3. Lottery Game (1-40, Bonus Tickets, Extra Lines)\n";
        cout << " 4. Guessing Name Game (Letter-matching mode)\n";
        cout << "    //TODO: Insert switch loop to get instructions for each game here";

        cout << "\nAdditional Features:\n";
        cout << " 5. Credits\n";
        cout << " 6. About / Help Page (this page)\n\n";

        cout << "Purpose of the Program:\n";
        cout << " To practice modular design, functions, vectors,\n";
        cout << " input validation, multi-file organization, and\n";
        cout << " the use of namespaces in a C++ project.\n\n";

        cout << "====================================\n";
        cout << "         End of About Page\n";
        cout << "====================================\n\n";
    
        
        again = getYesNo( "View the 'About' section again? (Y/N): ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (again == "N") {
            cout << "\nReturning to main menu...\n";
            return;
        }
    }}
} // namespace arcade