#include <iostream>
#include <vector>
#include <string>
using namespace std;

// This helper compares the player's guess with the actual name.
// It returns true if the strings are exactly equal.
bool compareNames(const string& guess, const string& answer) {
    return guess == answer;
}

// This helper builds a string showing which letters in the guess
// match the correct name in the same positions.
// Correct letters are shown, and incorrect positions are replaced with '_'.
string getMatchedLetters(const string& guess, const string& answer) {
    string result = "";

    for (size_t i = 0; i < answer.length(); i++) {
        if (i < guess.length() && guess[i] == answer[i]) {
            result += guess[i];
        } else {
            result += '_';
        }

        // Add a space between characters for readability.
        if (i < answer.length() - 1) {
            result += ' ';
        }
    }

    return result;
}

// This function implements the Guessing Name game.
// The player either gets a random name or selects a desired length range,
// then repeatedly guesses the name, receiving feedback on matched letters.
// A replay loop allows them to play again or return to the menu.
void playNameGuessingGame() {
    cout << "\n=== Guessing Name: Figuring Out the Name Edition ===\n\n";

    // Predefined names of varying lengths (3–10 letters) as required.
    vector<string> names = {
        "Ali",      // 3 letters
        "Mariam",   // 6 letters
        "Fayzan",   // 6 letters
        "Diwan",    // 5 letters
        "Jessica",  // 7 letters
        "Benjamin", // 8 letters
        "Alexander" // 9 letters
    };

    char playAgain = 'Y';

    // Outer loop allows the entire game to be replayed with potentially new names.
    while (playAgain == 'Y' || playAgain == 'y') {

        // Prompt the user for how the name should be chosen.
        cout << "Choose an option:\n";
        cout << "1. Random name\n";
        cout << "2. Choose name length (3–10 letters)\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        string selectedName;

        if (choice == 1) {
            // Select a random name from the vector.
            selectedName = names[rand() % names.size()];
        } else if (choice == 2) {
            // Allow the user to request a specific name length.
            int lengthChoice;
            cout << "Enter desired name length (3–10): ";
            cin >> lengthChoice;

            vector<string> filtered;

            // Filter the vector to only names of the requested length.
            for (const string& n : names) {
                if (static_cast<int>(n.length()) == lengthChoice) {
                    filtered.push_back(n);
                }
            }

            // If no names match that length, fall back to a random choice.
            if (filtered.empty()) {
                cout << "No names of that length. Selecting random instead.\n";
                selectedName = names[rand() % names.size()];
            } else {
                selectedName = filtered[rand() % filtered.size()];
            }
        } else {
            // Invalid menu choice defaults to a random name.
            cout << "Invalid choice. Selecting random name.\n";
            selectedName = names[rand() % names.size()];
        }

        // Clear the input buffer before reading full-line guesses.
        cin.ignore();

        bool guessedCorrectly = false;
        char tryAgain = 'Y';

        // This inner loop lets the player guess multiple times for the same name.
        while (tryAgain == 'Y' || tryAgain == 'y') {
            cout << "\nGuess the name (" << selectedName.length() << " letters): ";
            string guess;
            getline(cin, guess);

            if (compareNames(guess, selectedName)) {
                // Player guessed the name correctly.
                cout << "\nCorrect! The name was: " << selectedName << "\n";
                guessedCorrectly = true;
                break; // Exit the guessing loop for this round.
            } else {
                // Show feedback of matched letters in correct positions.
                cout << "Not quite. Matching letters in correct positions:\n";
                cout << getMatchedLetters(guess, selectedName) << "\n";
            }

            // Ask if the player wants to guess again for the same name.
            cout << "Would you like to try guessing this name again? (Y/N): ";
            cin >> tryAgain;
            cin.ignore();
        }

        // Once guessing for this name is finished (correct or not), ask about replaying the whole game.
        cout << "\nWould you like to play the Guessing Name game again? (Y/N): ";
        cin >> playAgain;

        if (playAgain == 'Y' || playAgain == 'y') {
            // Loop back to pick another name and continue the game.
            continue;
        }

        // If not replaying, offer to return to the main menu.
        char returnToMenu;
        cout << "Return to main menu? (Y/N): ";
        cin >> returnToMenu;

        // Returning from this function sends control back to the main arcade menu.
        return;
    }
}
