#include <iostream>
#include <limits>
using namespace std;

// This function implements the Dice Game with safe input handling,
// streamlined replay logic, and improvements commented clearly

// Dice Game
// Fix: Changed logic of game to more accurately reflect Assignment 04

/*
============================================================
 Dice Game - Updated using Guessing Game input validation
 With ENTER-to-roll interactivity
============================================================
*/

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

        // ===========================================================
        // SAFE INPUT for both guesses (same logic as Guessing Game)
        // ===========================================================

        while (true) {
            cout << "Enter your first number (1-6): ";
            cin >> guess1;

            if (cin.fail() || guess1 < 1 || guess1 > 6) {
                cout << "Invalid input. Enter a valid number between 1 and 6.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else break;
        }

        while (true) {
            cout << "Enter your second number (1-6): ";
            cin >> guess2;

            if (cin.fail() || guess2 < 1 || guess2 > 6) {
                cout << "Invalid input. Enter a valid number between 1 and 6.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else break;
        }

        // clear leftover newline before ENTER prompt
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // ===========================================================
        // ENTER TO ROLL
        // ===========================================================
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

        // ===========================================================
        // WIN CONDITION
        // Order does NOT matter:
        //  - guess1/guess2 vs die1/die2 in any order
        // ===========================================================
        bool win =
            ((die1 == guess1 && die2 == guess2) ||
             (die1 == guess2 && die2 == guess1));

        if (win) {
            cout <<  "YOU WIN! Both dice matched your numbers!\n";
        } else {
            cout << " You lose. Better luck next time!\n";
        }

        // ===========================================================
        // PLAY AGAIN?
        // ===========================================================
        playAgain = getYesNo("\nPlay again? (Y/N): ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (playAgain == "N") {
            cout << "\nReturning to main menu...\n";
            return;
        }
    }
}

// CHANGES TO MAKE 
// TODO: Different way of comparing results... i don't like this one
// TODO: Ensure that only 1 input will be accepted for guesses,
// TODO: and that multiple inputs are rejected
// TODO: