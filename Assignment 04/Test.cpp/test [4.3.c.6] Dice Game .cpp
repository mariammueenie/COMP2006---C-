#include <iostream>
#include <limits>
#include <string>   // string, getline, stoi
#include <cctype>   // isspace, isdigit
#include <cstdlib>  // rand()
using namespace std;

// This function implements the Dice Game with safe input handling,
// streamlined replay logic, and improvements commented clearly.

// Dice Game
// Fix: Changed logic of game to more accurately reflect Assignment 04

// Forward declaration so the compiler knows this helper exists somewhere:
string getYesNo(const string& prompt);

void playDiceGame() {
    string playAgain = "Y";

    while (playAgain == "Y") {

        cout << "\n--- Dice Game ---\n\n";
        cout << "Welcome to the Dice Game!\n";
        cout << "You will choose TWO numbers from 1–6.\n";
        cout << "Then press ENTER to roll each die.\n";
        cout << "WIN = both dice match your two chosen numbers.\n\n";

        int guess1 = 0;
        int guess2 = 0;

        // SAFE INPUT for both guesses (same logic style as Guessing Game)
        // Strict: one integer only, no spaces, no letters, 1–6 only

        // First guess
        while (true) {
            string line;
            cout << "Enter your FIRST number (1-6): ";
            getline(cin, line);

            // Trim whitespace
            while (!line.empty() && isspace(static_cast<unsigned char>(line.front())))
                line.erase(0, 1);
            while (!line.empty() && isspace(static_cast<unsigned char>(line.back())))
                line.pop_back();

            bool badInput = false;

            if (line.empty()) {
                badInput = true;
            } else {
                // Allow ONLY digits (no spaces, no letters)
                for (size_t i = 0; i < line.length(); i++) {
                    if (!isdigit(static_cast<unsigned char>(line[i]))) {
                        badInput = true;
                        break;
                    }
                }
            }

            if (badInput) {
                cout << "Invalid input. Please enter ONE single integer only.\n";
                continue;
            }

            // Convert safely
            int value = stoi(line);

            if (value < 1 || value > 6) {
                cout << "Invalid choice. Please select a number between 1 and 6.\n";
                continue;
            }

            guess1 = value;
            break;
        }

        // ---- Second guess ----
        while (true) {
            string line;
            cout << "Enter your SECOND number (1-6): ";
            getline(cin, line);

            // Trim whitespace
            while (!line.empty() && isspace(static_cast<unsigned char>(line.front())))
                line.erase(0, 1);
            while (!line.empty() && isspace(static_cast<unsigned char>(line.back())))
                line.pop_back();

            bool badInput = false;

            if (line.empty()) {
                badInput = true;
            } else {
                // Allow ONLY digits (no spaces, no letters)
                for (size_t i = 0; i < line.length(); i++) {
                    if (!isdigit(static_cast<unsigned char>(line[i]))) {
                        badInput = true;
                        break;
                    }
                }
            }

            if (badInput) {
                cout << "Invalid input. Please enter ONE single integer only.\n";
                continue;
            }

            // Convert safely
            int value = stoi(line);

            if (value < 1 || value > 6) {
                cout << "Invalid choice. Please select a number between 1 and 6.\n";
                continue;
            }

            guess2 = value;
            break;
        }

        // ENTER TO ROLL
        // (No cin.ignore here: we used getline above, so buffer is clean)
        cout << "\nPress ENTER to roll the dice...";
        cin.get();

        cout << "Rolling Die 1... press ENTER...";
        cin.get();

        int die1 = (rand() % 6) + 1;
        cout << "Die 1 rolled: " << die1 << "\n";

        cout << "Rolling Die 2... press ENTER...";
        cin.get();

        int die2 = (rand() % 6) + 1;
        cout << "Die 2 rolled: " << die2 << "\n\n";

        // WIN CONDITION
        // Order does NOT matter:
        //  - guess1/guess2 vs die1/die2 in any order
        bool win =
            ((die1 == guess1 && die2 == guess2) ||
             (die1 == guess2 && die2 == guess1));

        if (win) {
            cout << "YOU WIN! Both dice matched your numbers!\n";
        } else {
            cout << "You lose. Better luck next time!\n";
        }

        // PLAY AGAIN?
        playAgain = getYesNo("\nPlay again? (Y/N): ");

        if (playAgain == "N") {
            cout << "\nReturning to main menu...\n";
            return;
        }
    }
}