#include <iostream>
using namespace std;

// This function implements the number guessing game.
// The player has 7 attempts to guess a secret number from 1 to 100.
// A replay loop allows the player to play again or return to the main menu.
void playGuessingGame() {
    char playAgain = 'Y';

    // This loop allows the entire game to be replayed multiple times.
    // It runs as long as the player responds 'Y' or 'y' to the replay prompt.
    while (playAgain == 'Y' || playAgain == 'y') {

        cout << "\n--- Guessing Game ---\n\n";

        int secretNumber;
        int guess;
        int attempts = 7;

        // Generate a random secret number between 1 and 100.
        // srand should be called once in main, but rand() can be used here.
        secretNumber = rand() % 100 + 1;

        cout << "I am thinking of a number between 1 and 100.\n";
        cout << "You have " << attempts << " attempts.\n\n";

        bool guessed = false;

        // This loop represents the limited number of attempts.
        // Each iteration gives the player one guess.
        for (int i = 1; i <= attempts; i++) {
            cout << "Attempt " << i << "/" << attempts << ": ";
            cin >> guess;

            // Input validation ensures the guess is within the allowed range.
            if (guess < 1 || guess > 100) {
                cout << "Please enter a number between 1 and 100.\n";
                // The attempt is not counted as "used" if out of range.
                i--;
                continue;
            }

            if (guess == secretNumber) {
                cout << "\nCorrect! The number was " << secretNumber << ".\n";
                guessed = true;
                break; // Exit the attempt loop because the player won.
            } else if (guess < secretNumber) {
                cout << "Too low. Try a higher number.\n\n";
            } else {
                cout << "Too high. Try a lower number.\n\n";
            }
        }

        // If the player did not guess correctly within the attempts, reveal the number.
        if (!guessed) {
            cout << "You are out of attempts. The number was " << secretNumber << ".\n";
        }

        // Replay prompt specific to this game.
        cout << "\nWould you like to play the Guessing Game again? (Y/N): ";
        cin >> playAgain;

        if (playAgain == 'Y' || playAgain == 'y') {
            // Continue at the top of the while loop and start a new game.
            continue;
        }

        // If the player does not want to replay, ask about returning to the main menu.
        char returnToMenu;
        cout << "Return to main menu? (Y/N): ";
        cin >> returnToMenu;

        // Returning from the function sends control back to the main menu loop.
        return;
    }
}
