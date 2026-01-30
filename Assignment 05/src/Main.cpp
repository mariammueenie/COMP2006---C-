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
using namespace std;

// Run game in Developer Command Prompt for VS 2022
// cd into src file 
// then run: cl /EHsc /std:c++17 *.cpp /Fe:ArcadeGame.exe
// then run: ArcadeGame.exe

// ============================
// Game Header Files
// ============================
#include "ArcadeGlobals.h"
#include "GuessingGame.h"
#include "DiceGame.h"
#include "LotteryGame.h"
#include "NameGame.h"
#include "Credits.h"
#include "About.h"

// Access arcade namespace globally
using namespace arcade;

// ============================
// MAIN ARCADE PROGRAM
// ============================
int main() {
    
    cout << "\nWelcome to the Mini Arcade!\n";
    cout << "Press ENTER to get started...";
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    // ================================
    // GET PLAYER NAME AT PROGRAM START
    // ================================
    player = getPlayerName();   // Stores into global arcade::player

    int choice = 0;

    // Seed RNG once for all games
    srand(static_cast<unsigned int>(time(0)));

    // ================================
    // MAIN MENU LOOP
    // ================================
    do {
        cout << "\n==============================\n";
        cout << "         MINI ARCADE\n";
        cout << "==============================\n";

        cout << "Player: " << player.first << " " << player.last << "\n\n";

        cout << "1. Guessing Game (Numbers)\n";
        cout << "2. Dice Game (Match to Win)\n";
        cout << "3. Lottery Game (Vector Victory)\n";
        cout << "4. Name Guessing Game\n";
        cout << "5. Credits\n";
        cout << "6. About\n";
        cout << "7. Exit\n";

        // Strict validated input (string → trimmed → digit-check → stoi)
        string line;
        cout << "Enter your choice (1-7): ";
        getline(cin, line);

        // Trim leading spaces
        while (!line.empty() && isspace(static_cast<unsigned char>(line.front())))
            line.erase(0, 1);

        // Trim trailing spaces
        while (!line.empty() && isspace(static_cast<unsigned char>(line.back())))
            line.pop_back();

        // Check empty input
        if (line.empty()) {
            cout << "Invalid input. Please enter ONE digit.\n";
            continue;
        }

        // Verify all characters are digits
        bool badInput = false;
        for (char c : line) {
            if (!isdigit(static_cast<unsigned char>(c))) {
                badInput = true;
                break;
            }
        }

        if (badInput) {
            cout << "Invalid input. Please enter numbers only.\n";
            continue;
        }

        // Convert to integer
        choice = stoi(line);

        if (choice < 1 || choice > 7) {
            cout << "Choice must be between 1 and 7.\n";
            continue;
        }

        // ============================
        // MENU SELECTION HANDLING
        // ============================
        switch (choice) {
            case 1:
                playGuessingGame();
                break;

            case 2:
                playDiceGame();
                break;

            case 3:
                // CORRECT SIGNATURE: playLotteryGame(const PlayerName&)
                playLotteryGame(player);
                break;

            case 4:
                playNameGuessingGame();
                break;

            case 5:
                showCredits();
                break;

            case 6:
                showAbout();
                break;

            case 7: {
                string ans = getYesNo("Are you sure you want to exit? (Y/N): ");
                if (ans == "Y") {
                    cout << "Exiting the Mini Arcade. Goodbye!\n";
                } else {
                    choice = 0; // resets so loop continues
                }
                break;
            }
        }

    } while (choice != 7);

    return 0;
}
// End of main.cpp