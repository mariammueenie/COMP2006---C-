#include <iostream>
#include <limits>
using namespace std;

// This function implements the number guessing game.
// Improvements based on prev version failures (with comments explaining each change)
void playGuessingGame() {
    char playAgain = 'Y';

    while (playAgain == 'Y' || playAgain == 'y') {

        cout << "\n--- Guessing Game ---\n\n";

        int secretNumber;
        int guess;
        int attempts = 7;

        // Generate random number
        secretNumber = rand() % 100 + 1;

        cout << "I am thinking of a number between 1 and 100.\n";
        cout << "You have " << attempts << " attempts.\n\n";

        bool guessed = false;

        for (int i = 1; i <= attempts; i++) {

            cout << "Attempt " << i << "/" << attempts << ": ";

            // FIX: Prevent cin failure when user types letters, symbols, ETC
            // This loops until a valid integer is entered
            while (!(cin >> guess)) {
                cin.clear(); // reset fail state
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush garbage
                cout << "Invalid input. Please enter a WHOLE NUMBER between 1 and 100: ";
            }

            // Range validation (non-penalty)
            if (guess < 1 || guess > 100) {
                cout << "Please enter a number between 1 and 100.\n";
                i--;
                continue;
            }

            if (guess == secretNumber) {
                cout << "\nCorrect! The number was " << secretNumber << ".\n";
                guessed = true;
                break;
            } else if (guess < secretNumber) {
                cout << "Too low. Try a higher number.\n\n";
            } else {
                cout << "Too high. Try a lower number.\n\n";
            }
        }

        if (!guessed) {
            cout << "You are out of attempts. The number was " << secretNumber << ".\n";
        }

        // FIX: streamlined replay logic: ONLY one question
        // Also prevents accidental exits by rejecting garbage input
        // Flushes leftover newline characters before reading char input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover input

        cout << "\nPlay again? (Y/N): ";

        while (true) {
            cin >> playAgain;

            // Prevents accidental exits from garbage like "$", "h", "abc", etc.
            if (playAgain == 'Y' || playAgain == 'y' ||
                playAgain == 'N' || playAgain == 'n') {

                break; // valid input -> exit validation loop
            }

            // invalid input -> prompt again
            cout << "Please enter Y or N only: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (playAgain == 'N' || playAgain == 'n') {
            // FIX: Message when returning to main menu
            cout << "\nReturning to main menu...\n";
            return;
        }

    } // end replay loop
}

// CHANGES TO MAKE
    // TODO: Prevent cin failure when user types letters, symbols, ETC
    // TODO: Range validation (non-penalty) for guesses outside 1-100
    // TODO: Prevent accidental exits by rejecting garbage input
