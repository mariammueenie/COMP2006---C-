#include <iostream>
using namespace std;

// This function implements the Dice Game.
// Two dice are rolled. If they match, the player wins; otherwise, the player loses.
// A replay loop gives the player the option to roll again or return to the menu.
void playDiceGame() {
    char playAgain = 'Y';

    // Loop to allow the player to replay the dice game multiple times.
    while (playAgain == 'Y' || playAgain == 'y') {

        cout << "\n--- Dice Game ---\n\n";

        // Generate two random values between 1 and 6 to simulate dice.
        int die1 = rand() % 6 + 1;
        int die2 = rand() % 6 + 1;

        cout << "Rolling the dice...\n\n";
        cout << "Die 1: " << die1 << "\n";
        cout << "Die 2: " << die2 << "\n\n";

        // Matching dice represents a win, as per assignment rules.
        if (die1 == die2) {
            cout << "They match! You win!\n";
        } else {
            cout << "They do not match. You lose.\n";
        }

        // Replay prompt tailored to the dice game.
        cout << "\nWould you like to roll again? (Y/N): ";
        cin >> playAgain;

        if (playAgain == 'Y' || playAgain == 'y') {
            // Loop back and perform another dice roll.
            continue;
        }

        // If the player does not want to roll again, ask about returning to the main menu.
        char returnToMenu;
        cout << "Return to main menu? (Y/N): ";
        cin >> returnToMenu;

        // Returning from the function sends control back to the arcade menu.
        return;
    }
}

// WHY CHANGED 
// The dice game did not prompt the user to enter numerical values between 1-6
// Loop was not made well, lead to infinite loop 
// Bad input handling 