#include <iostream>
#include <limits>
using namespace std;

// This function implements the Dice Game with safe input handling,
// streamlined replay logic, and improvements commented clearly.
void playDiceGame() {
    char playAgain = 'Y';

    while (playAgain == 'Y' || playAgain == 'y') {

        cout << "\n--- Dice Game ---\n\n";

        // Generate two random dice rolls (1–6)
        int die1 = rand() % 6 + 1;
        int die2 = rand() % 6 + 1;

        cout << "Rolling the dice...\n\n";
        cout << "Die 1: " << die1 << "\n";
        cout << "Die 2: " << die2 << "\n\n";

        if (die1 == die2) {
            cout << "They match! You win!\n";
        } else {
            cout << "They do not match. You lose.\n";
        }

        // FIX: Clean leftover newline before reading a char
        // This prevents automatic skipping of Y/N prompts caused by buffered '\n'

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "\nRoll again? (Y/N): ";

        // FIX: Loop until the user enters ONLY Y/y/N/n.
        // Prevents accidental exit from typing garbage like '$', 'hello', '12', etc.
        while (true) {
            cin >> playAgain;

            if (playAgain == 'Y' || playAgain == 'y' ||
                playAgain == 'N' || playAgain == 'n') {

                break; // Valid input -> exit validation loop
            }

            // Invalid input -> reprompt the user
            cout << "Please enter Y or N only: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // If player does NOT want to roll again
        if (playAgain == 'N' || playAgain == 'n') {

            // FIX: Return to menu message
            cout << "\nReturning to main menu...\n";
            return;
        }

        // If input was 'Y' or 'y', the loop restarts automatically.

    } // end while(playAgain)
}

// CHANGES MADE
// TODO: game just played out, without any user interaction, so add user interactions
// TODO: make more interactive 
// TODO: fix clear.cin, which makes a weird extra line that needs to be cleared by hitting enter 
// TODO: add instructions for game, from Assignment 03 files
// TODO: Add dice roll animation and ASCII dice art later.