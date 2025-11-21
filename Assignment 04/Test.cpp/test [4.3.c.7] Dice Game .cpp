#include <iostream>
#include <limits>
#include <string>   // string, getline, stoi
#include <cctype>   // isspace, isdigit
#include <cstdlib>  // rand()
#include <thread>   // NEW: for dice rolling effect (sleep)
#include <chrono>   // NEW: for milliseconds (sleep)
using namespace std;

// Forward declaration for your existing helper
string getYesNo(const string& prompt);

// ======================================================
// NEW FUNCTION ADDED: ASCII Dice Printer
// REFERENCE for ASCII dice style:
// https://ascii.co.uk/art/dice
// https://www.asciiart.eu/miscellaneous/dice
// ======================================================
void printDice(int value) {
    switch (value) {
        case 1:
            cout << " -----\n"
                    "|     |\n"
                    "|  *  |\n"
                    "|     |\n"
                    " -----\n";
            break;
        case 2:
            cout << " -----\n"
                    "|*    |\n"
                    "|     |\n"
                    "|    *|\n"
                    " -----\n";
            break;
        case 3:
            cout << " -----\n"
                    "|*    |\n"
                    "|  *  |\n"
                    "|    *|\n"
                    " -----\n";
            break;
        case 4:
            cout << " -----\n"
                    "|*   *|\n"
                    "|     |\n"
                    "|*   *|\n"
                    " -----\n";
            break;
        case 5:
            cout << " -----\n"
                    "|*   *|\n"
                    "|  *  |\n"
                    "|*   *|\n"
                    " -----\n";
            break;
        case 6:
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

    while (playAgain == "Y") {

        cout << "\n--- Dice Game ---\n\n";
        cout << "Welcome to the Dice Game!\n";
        cout << "You will choose TWO numbers from 1-6.\n";
        cout << "Then press ENTER to roll each die.\n";
        cout << "WIN = both dice match your two chosen numbers.\n\n";

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

            bool badInput = false;

            if (line.empty()) badInput = true;
            else {
                for (char c : line)
                    if (!isdigit((unsigned char)c)) badInput = true;
            }

            if (badInput) {
                cout << "Invalid input. Please enter ONE single integer only.\n";
                continue;
            }

            int value = stoi(line);

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

            if (line.empty()) badInput = true;
            else {
                for (char c : line)
                    if (!isdigit((unsigned char)c)) badInput = true;
            }

            if (badInput) {
                cout << "Invalid input. Please enter ONE single integer only.\n";
                continue;
            }

            int value = stoi(line);

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
        // WIN CONDITION (unchanged)
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
