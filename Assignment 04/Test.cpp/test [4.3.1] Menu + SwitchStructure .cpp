#include <iostream>
using namespace std;

// function prototypes for all major features
void playGuessingGame();
void playDiceGame();
void playLotteryGame();
void playNameGuessingGame();
void showCredits();

int main() {
    int choice = 0;

    // Seed the random number generator once for the entire program.
    // This ensures that all random behavior in the games is different each run.
    srand(static_cast<unsigned int>(time(0)));

    // This loop keeps the arcade running until the user chooses to exit.
    // It satisfies the requirement to keep the program active using a loop.
    do {
        // Display the main menu options to the user.
        cout << "\n==============================\n";
        cout << "         MINI ARCADE\n";
        cout << "==============================\n";
        cout << "1. Guessing Game (Numbers)\n";
        cout << "2. Dice Game (Match to Win)\n";
        cout << "3. Lottery Game (Vector Victory)\n";
        cout << "4. Guessing Name Game\n";
        cout << "5. Credits\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";

        cin >> choice;

        // Basic input validation for menu choice.
        // This checks that the selected option is within the allowed range.
        if (choice < 1 || choice > 6) {
            cout << "Invalid choice. Please select a number between 1 and 6.\n";
            continue; // Restart the loop and show the menu again.
        }

        // The switch statement directs the user to the chosen game or feature.
        // Each case calls a function that handles that part of the arcade.
        switch (choice) {
            case 1:
                // Launches the number Guessing Game.
                playGuessingGame();
                break;
            case 2:
                // Launches the Dice Game where matching dice means a win.
                playDiceGame();
                break;
            case 3:
                // Launches the Lottery Game, which uses vectors and file output.
                playLotteryGame();
                break;
            case 4:
                // Launches the Guessing Name game.
                playNameGuessingGame();
                break;
            case 5:
                // Displays the Credits screen with replay support.
                showCredits();
                break;
            case 6:
                // Clean exit option. The loop will end after this.
                cout << "Exiting the Mini Arcade. Goodbye!\n";
                break;
        }

        // After a game or credits, control returns here and the menu is shown again.
        // This continues until the user chooses option 6 (Exit).

    } while (choice != 6); // Loop condition keeps the arcade active.

    return 0;
}
