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
#include "DiceGame.h"
#include "ArcadeGlobals.h"

namespace arcade {
    using namespace std;

/* =========================================================
   Dice Game
   ========================================================= */
    // REDUNDANT
    // TODO: Remove if confirmed unused
    // Forward declaration for your existing helper
    // Purpose is to 'tell' compiler, trust me bro the function I referenced
    //   is coming soon, just keep reading, don't throw an error plz
    // Specifically for the Yes/No function in the game loop
    // Solved error :)
    // REFERENCE: https://www.geeksforgeeks.org/cpp/what-are-forward-declarations-in-c/
    // REFERENCE: https://favtutor.com/blogs/forward-declaration-cpp
    // string getYesNo(const string& prompt);

    // ======================================================
    // NEW FUNCTION ADDED: ASCII Dice Printer
    // REFERENCE for ASCII dice style:
    // https://ascii.co.uk/art/dice
    // https://www.asciiart.eu/miscellaneous/dice
    // ======================================================
    void printDice(int value) {
        switch (value) {
            case 1:
                // dice rolls 1
                cout << " -----\n"
                        "|     |\n"
                        "|  *  |\n"
                        "|     |\n"
                        " -----\n";
                break;
            case 2:
                // dice rolls 2
                cout << " -----\n"
                        "|*    |\n"
                        "|     |\n"
                        "|    *|\n"
                        " -----\n";
                break;
            case 3:
                // dice rolls 3
                cout << " -----\n"
                        "|*    |\n"
                        "|  *  |\n"
                        "|    *|\n"
                        " -----\n";
                break;
            case 4:
                // dice rolls 4
                cout << " -----\n"
                        "|*   *|\n"
                        "|     |\n"
                        "|*   *|\n"
                        " -----\n";
                break;
            case 5:
                // dice rolls 5
                cout << " -----\n"
                        "|*   *|\n"
                        "|  *  |\n"
                        "|*   *|\n"
                        " -----\n";
                break;
            case 6:
                // dice rolls 6
                cout << " -----\n"
                        "|*   *|\n"
                        "|*   *|\n"
                        "|*   *|\n"
                        " -----\n";
                break;
        }
    }

    // ======================================================
    // NEW FUNCTION ADDED: Fake Rolling Effect
    // Reference for console loading animation concept:
    // https://stackoverflow.com/questions/14513676/
    // ======================================================
    void rollingEffect() {
        cout << "Rolling";
        // print 3 dots, one at a time, 0.3 seconds between each print
        for (int i = 0; i < 3; i++) {
            this_thread::sleep_for(chrono::milliseconds(300));   // small pause
            cout << ".";
        }
        cout << "\n";
    }

    // ======================================================
    // MAIN GAME
    // ======================================================
    void playDiceGame() {
        string playAgain = "Y";

        // Loop continues while playAgain is 'Yes'
        while (playAgain == "Y") {

            cout << "\n--- Dice Game ---\n\n";
            cout << "Welcome to the Dice Game!\n";
            cout << "You will choose TWO numbers from 1-6.\n";
            cout << "Then press ENTER to roll each die.\n";
            cout << "WIN = both dice match your two chosen numbers.\n\n";

            // Initialize guesses
            int guess1 = 0;
            int guess2 = 0;

            // ===========================================================
            // STRICT INPUT VALIDATION
            // ===========================================================

            // FIRST USER INPUT
            while (true) {
                string line;
                cout << "Enter your FIRST number (1-6): ";
                getline(cin, line);

                // trim whitespace
                while (!line.empty() && isspace((unsigned char)line.front())) line.erase(0, 1);
                while (!line.empty() && isspace((unsigned char)line.back())) line.pop_back();

                // Assume input is bad, until proven otherwise 
                bool badInput = false;

                // If line empty, badInput=true
                if (line.empty()) badInput = true;
                else {
                    // If input is digit, with some addition, input is bad (prevents multiple valid inputs)
                    for (char c : line)
                        if (!isdigit((unsigned char)c)) badInput = true;
                }

                // If input is bad, request another
                if (badInput) {
                    cout << "Invalid input. Please enter ONE single integer only.\n";
                    continue;
                }

                // Convert string to int, to allow for range check
                int value = stoi(line);

                // Range check
                if (value < 1 || value > 6) {
                    cout << "Invalid choice. Please select a number between 1 and 6.\n";
                    continue;
                }

                guess1 = value;
                break;
            }

            // SECOND USER INPUT
            while (true) {
                string line;
                cout << "Enter your SECOND number (1-6): ";
                getline(cin, line);

                // trim whitespace
                while (!line.empty() && isspace((unsigned char)line.front())) line.erase(0, 1);
                while (!line.empty() && isspace((unsigned char)line.back())) line.pop_back();


                bool badInput = false;

                // Check input for non-numerical values
                if (line.empty()) badInput = true;
                else {
                    for (char c : line)
                        if (!isdigit((unsigned char)c)) badInput = true;
                }

                // If input is bad, prompt for new
                if (badInput) {
                    cout << "Invalid input. Please enter ONE single integer only.\n";
                    continue;
                }

                // String to int
                int value = stoi(line);

                // Range check
                if (value < 1 || value > 6) {
                    cout << "Invalid choice. Please select a number between 1 and 6.\n";
                    continue;
                }

                guess2 = value;
                break;
            }

            // ===========================================================
            // DICE ROLLING WITH NEW ANIMATION + MUST CLICK ENTER-TO-REVEAL
            // Additional interactivity
            // ===========================================================

            cout << "\nPress ENTER to roll the dice...";
            cin.get();

            // DICE 1
            int die1 = (rand() % 6) + 1;

            cout << "\nRolling Die 1... Press ENTER to roll!";
            cin.get();

            rollingEffect();       // NEW: fake roll animation
            printDice(die1);       // NEW: ASCII reveal
            cout << "Die 1 rolled: " << die1 << "\n\n";

            // DICE 2
            int die2 = (rand() % 6) + 1;

            cout << "Rolling Die 2... Press ENTER to roll!";
            cin.get();

            rollingEffect();       // NEW: fake roll animation
            printDice(die2);       // NEW: ASCII reveal
            cout << "Die 2 rolled: " << die2 << "\n\n";

            // ===========================================================
            // WIN CONDITION
            // ===========================================================
            bool win =
                // Order does not matter, so check both possibilities
                ((die1 == guess1 && die2 == guess2) ||
                (die1 == guess2 && die2 == guess1));

            if (win) {
                cout << "YOU WIN! Both dice matched your numbers!\n";
            } else {
                cout << "You lose. Better luck next time!\n";
            }

            // ===========================================================
            // PLAY AGAIN?
            // ===========================================================
            playAgain = getYesNo("\nPlay again? (Y/N): ");

            if (playAgain == "N") {
                cout << "\nReturning to main menu...\n";
                return;
            }
        }
    }
} // namespace arcade