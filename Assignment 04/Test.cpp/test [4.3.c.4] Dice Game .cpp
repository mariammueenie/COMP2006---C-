#include <iostream>
#include <limits>
using namespace std;

// This function implements the Dice Game with safe input handling,
// streamlined replay logic, and improvements commented clearly

// Dice Game
// Fix: Changed logic of game to more accurately reflect Assignment 04


void playDiceGame() {
    string playAgain = "Y";

    // Main game loop for Dice Game
    while (playAgain == "Y") {

        cout << "\n--- Dice Game ---\n\n";
        cout << "Welcome to the Dice Game!\n";
        cout << "Choose TWO numbers between 1 and 6.\n";
        cout << "Then press ENTER to roll each die.\n";
        cout << "You WIN only if BOTH dice match your TWO numbers.\n\n";

        int guess1 = 0;
        int guess2 = 0;

        // ============================================
        // Prompt for first number (1–6)
        // ============================================
        while (true) {
            cout << "Enter your first number (1-6): ";
            cin >> guess1;

            if (cin.fail() || guess1 < 1 || guess1 > 6) {
                cout << "Invalid. Enter a number from 1 to 6.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else break;
        }

        // ============================================
        // Prompt for second number (1–6)
        // ============================================
        while (true) {
            cout << "Enter your second number (1-6): ";
            cin >> guess2;

            if (cin.fail() || guess2 < 1 || guess2 > 6) {
                cout << "Invalid. Enter a number from 1 to 6.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            } else break;
        }

        // Clear input leftover before pressing ENTER
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // ============================================
        // Dice rolling with ENTER pauses
        // ============================================
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

        // ============================================
        // Winning condition
        // Player wins if both dice match the two guesses
        // (Order does NOT matter)
        // ============================================
        bool match =
            ((die1 == guess1 && die2 == guess2) ||
             (die1 == guess2 && die2 == guess1));

        if (match) {
            cout << "🎉 YOU WIN!!! Both dice matched your numbers!\n";
        } else {
            cout << "❌ Sorry, you lose. Better luck next time!\n";
        }

        // ============================================
        // Replay prompt
        // ============================================
        cout << "\nPlay again? (Y/N): ";
        cin >> playAgain;

        // Input cleanup
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        playAgain = toupper(playAgain[0]);
    }
}