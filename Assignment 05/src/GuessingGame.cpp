#include <iostream>
#include <cstdlib>      // rand(), srand()
#include <ctime>        // time()
#include <limits>       // numeric_limits
#include <string>       // string
#include <sstream>      // stringstream / stoi references (future-safe)
#include <vector>       // ONLY for lottery game (allowed there)
#include <iomanip>      // for setw, left, right (Murach-style formatting)
#include <algorithm>    // sort, find
#include <fstream>      // file output in lottery game
#include <cctype>       // isalpha, isspace, tolower, isdigit
#include <thread>       // for dice rolling effect (sleep)
#include <chrono>       // for milliseconds (sleep)

// Headers
#include "../include/GuessingGame.h"
#include "../include/ArcadeGlobals.h"

namespace arcade {


// =========================================================
// Guessing Game
// =========================================================

    void playGuessingGame() {
        string playAgain = "Y";

        // Loop continues while player answer continues to be 'Yes'
        while (playAgain == "Y") {

            cout << "\n--- # Guessing Game ---\n\n";

            int secretNumber = rand() % 100 + 1;
            int guess;
            int attempts = 7;
            // Loop starts with assumption that player does not know random number
            // Therefore guess = false
            // Once player guesses some value, it is compared to intSecretNumber 
            // If int guess = int secret number, the loop ends early, and player wins!
            // If not, loop continues to end. 
            // If int attempts reaches 7, and int guess does NOT equal int secretNumber,
            //   then bool guessed = false, and loop ends, telling player they lost. 
            bool guessed = false;

            cout << "Hello, " << player.first
                << ". I am thinking of a whole number between 1 and 100.\n";
            cout << "Can you guess what it is?\n";
            cout << "You have " << attempts << " attempts.\n\n";

        
            // To track previous guesses
            // Comma used to separate strings to avoid partial matches
            string previousGuesses = ",";

            for (int i = 1; i <= attempts; i++) {

                guess = getStrictInteger(
                    "Attempt " + to_string(i) + "/" + to_string(attempts) + ": ",
                    1, 100
                );

                // Read string to check for previous guesses 
                // Initially separated with only spaces initially to avoid partial matches 
                // Realized that better separator is comma + space
                // Store guesses with comma's to avoid partial match issues 
                string guessToken = "," + to_string(guess) + ",";

                if (previousGuesses.find(guessToken) != string::npos) {
                    cout << "You already guessed " << guess
                        << "! Try a different number.\n\n";
                    i--;
                    continue;
                }

                // Append to previous guesses
                previousGuesses += guessToken;

                if (guess == secretNumber) {
                    cout << "\nCorrect! The number was " << secretNumber << ".\n";
                    guessed = true;
                    break;
                }
                else if (guess < secretNumber) {
                    cout << "Too low.\n";
                }
                else {
                    cout << "Too high.\n";
                }
                // Added: Hint if user is within of the secret number
                if (abs(secretNumber - guess) <= 5) {
                    cout << "🔥 You are VERY close!\n";
                }
                if (i < attempts) {
                    cout << "Try again!\n\n";
                }
            }

            // If int secretNumber is not guessed:
            if (!guessed) {
                cout << "You are out of attempts. The number was "
                    << secretNumber << ".\n";
            }

            playAgain = getYesNo("\nPlay again? (Y/N): ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (playAgain == "N") {
                cout << "\nReturning to main menu...\n";
                return;
            }
        }
    }
} // namespace arcade