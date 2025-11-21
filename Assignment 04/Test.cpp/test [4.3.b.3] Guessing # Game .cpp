#include <iostream>
#include <limits>
#include <string>
#include <sstream>
using namespace std;

/*
===========================================================
 STRICT SINGLE-INTEGER INPUT SYSTEM (Matches Main Menu)
 ----------------------------------------------------------
 Fix:
- Read entire input line using getline()
- Trim whitespace
- Ensure EVERY character is a digit 0–9
- Convert using stoi()
- REFERENCE: https://cplusplus.com/reference/string/stoi/
- Range-check (1–100)
- Accept ONLY ONE valid integer per line
===========================================================
*/

// ------------------------------------------------------------
// EXACTLY the same integer validation logic as menu
// ------------------------------------------------------------
int getStrictInteger(const string& prompt, int minV, int maxV)
{
    while (true)
    {
        cout << prompt;

        string line;
        getline(cin, line);

        // Trim whitespace
        while (!line.empty() && isspace(line.front()))
            line.erase(0, 1);
        while (!line.empty() && isspace(line.back()))
            line.pop_back();

        if (line.empty()) {
            cout << "Invalid input. Please enter ONE whole number.\n"; // if user enters multiple values, even if values are valid
            continue;
        }

        // Ensure every character is a digit
        // REFERENCE: https://cplusplus.com/reference/cctype/isdigit/
        // REFERENCE: https://en.cppreference.com/w/cpp/language/range-for.html
        // REFERENCE: https://www.learncpp.com/cpp-tutorial/logical-operators/
        // REFERENCE: https://cplusplus.com/doc/tutorial/variables/

        bool bad = false;
        for (char c : line) {
            if (!isdigit(c)) {
                bad = true;
                break;
            }
        }
        if (bad) {
            cout << "Invalid input. ONLY digits 0-9 allowed.\n";
            continue;
        }

        int value = stoi(line);

        if (value < minV || value > maxV) {
            cout << "Number must be between " << minV << " and " << maxV << ".\n";
            continue;
        }

        return value;
    }
}

// ============================================================
// Guessing Game
// ============================================================
void playGuessingGame() {
    char playAgain = 'Y';

    while (playAgain == 'Y' || playAgain == 'y') {

        cout << "\n--- # Guessing Game ---\n\n";

        int secretNumber = rand() % 100 + 1;
        int guess;
        int attempts = 7;
        bool guessed = false;

        cout << "Hello, "<< player.first << ". I am thinking of a whole number between 1 and 100.\n";
        cout << "Can you guess what it is?\n";
        cout << "You have " << attempts << " attempts.\n\n";

        // Clear leftover newline before using getline()
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // -------------------------------------------
        // Stores all previous guesses as a single string
        // Will use vector or array in assignment 5, but keeping it simple here :)
        // -------------------------------------------
        string previousGuesses = "";

        for (int i = 1; i <= attempts; i++) {

            // ==========================================================
            // using getStrictInteger() instead of cin >> guess
            // for better input validation
            // same behavior as main menu input validation.
            // ==========================================================
            guess = getStrictInteger(
                "Attempt " + to_string(i) + "/" + to_string(attempts) + ": ",
                1, 100
            );

            // ==========================================================
            // DUPLICATE GUESS CHECK
            // ----------------------------------------------------------
            // stored guesses in a single string, with spaces between values
            // If the value "42 " already exists, the guess is repeated.
            // Attempts DO NOT decrease for repeated guesses.
            // ==========================================================
            string guessToken = to_string(guess) + " ";

            if (previousGuesses.find(guessToken) != string::npos) {
                cout << "Careful, You already guessed " << guess
                     << "! Try a different number.\n\n";
                i--;        // do not penalize the player
                continue;   // ask for a new guess
            }

            // First-time guess -> record it
            previousGuesses += guessToken;

            // If correct guess
            if (guess == secretNumber) {
                cout << "\nCorrect! The number was " << secretNumber << ".\n";
                guessed = true;
                break;
            }
            // If guess too low
            else if (guess < secretNumber) {
                cout << "Too low.\n";
            }
            // If guess too high
            else {
                cout << "Too high.\n";
            }

            // ---------------------------------------------
            // Show "Try again" ONLY if there are attempts left
            // ---------------------------------------------
            if (i < attempts) {
                cout << "Try again!\n\n";
            }
        }

        if (!guessed) {
            cout << "You are out of attempts. The number was "
                 << secretNumber << ".\n";
        }

        // ==========================================================
        // Replay prompt (same Y/N validation as menu)
        // ==========================================================
        cout << "\nPlay again? (Y/N): ";

        while (true) {
            cin >> playAgain;

            if (playAgain == 'Y' || playAgain == 'y' ||
                playAgain == 'N' || playAgain == 'n') {
                break; 
            }

            cout << "Please enter Y or N only: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (playAgain == 'N' || playAgain == 'n') {
            cout << "\nReturning to main menu...\n";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


