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
#include "../include/NameGame.h"
#include "../include/ArcadeGlobals.h"

//todo: replace raw cin>> with below
// mode = getStrictInteger("Enter choice (1 or 2): ", 1, 2);


namespace arcade {


/* =========================================================
   Name Guessing Game
   ========================================================= */

    // Checks if user input (guess) is the same as Name (answer)
    bool equalsIgnoreCase(const string& a, const string& b) // No case-sensitivity in comparison
    {
        if (a.length() != b.length()) // If string lengths are not same, names are not same automatically
            return false; // exit loop

        for (size_t i = 0; i < a.length(); i++) {
            if (tolower(static_cast<unsigned char>(a[i])) != // make both string fully lowercase
                tolower(static_cast<unsigned char>(b[i]))) { // check if full match
                return false; // If no match, exit
            }
        }
        return true; // If match, win!
    }

    // Retrieve name (answer)
    string getNameByIndex(int index) {
        switch (index) {
            case 1: return "Ali";         // TODO: ADD LENGTH 4 
            case 2: return "Diwan";       
            case 3: return "Mariam";
            case 4: return "Fayzan";
            case 5: return "Jessica";
            case 6: return "Benjamin";
            case 7: return "Alexander";
        }
        return "Mariam";
    }

    bool compareNames(const string& guess, const string& answer) {
        return equalsIgnoreCase(guess, answer);
    }

    string getMatchedLetters(const string& guess, const string& answer) {
        string result;

        for (size_t i = 0; i < answer.length(); i++) {
            if (i < guess.length() &&
                tolower(static_cast<unsigned char>(guess[i])) ==
                tolower(static_cast<unsigned char>(answer[i]))) {
                result += answer[i];
            } else {
                result += '_';
            }

            if (i < answer.length() - 1)
                result += ' ';
        }

        return result;
    }

    // choose random name length
    string getRandomName() {
        int i = rand() % 7 + 1;
        return getNameByIndex(i);
    }

    // If user asks for name of certain length
    // Read various switch cases, choose based on length of string
    string getRandomNameByLength(int lengthChoice) {
        int count = 0; // initialize 

        for (int i = 1; i <= 7; i++) // when user asks for name from 1-7 letters long
            if ((int)getNameByIndex(i).length() == lengthChoice)
                count++;

        if (count == 0)
            return getRandomName();

        int target = rand() % count + 1;
        int seen = 0;

        // read length of name
        for (int i = 1; i <= 7; i++) {
            string n = getNameByIndex(i);
            if ((int)n.length() == lengthChoice) {
                seen++;
                if (seen == target)
                    return n;
            }
        }

        return getRandomName();
    }

    // MAIN GAME LOOP
    void playNameGuessingGame() {

        string playAnother = "Y";

        cout << "\n=== Guessing Name: Figuring Out the Name Edition ===\n\n";

        while (playAnother == "Y") {

            int mode = 0;

            while (true) {
                cout << "Choose an option:\n";
                cout << "1. Random name\n";
                cout << "2. Choose name length (3-10 letters)\n";
                cout << "Enter choice (1 or 2): ";

                // If user does not enter valid choice
                if (!(cin >> mode)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Enter 1 or 2.\n";
                    continue;
                }

                // If user enters valid choice
                if (mode == 1 || mode == 2)
                    break;

                cout << "Invalid choice. Enter 1 or 2.\n";
            }

            int length = 0;
            string secret;

            // If user wants to choose the length of the name they guess
            if (mode == 1) {
                secret = getRandomName();
            } else {
                while (true) {
                    cout << "Enter desired name length (3-10): ";
                    // check if input is number
                    if (!(cin >> length)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Enter a WHOLE number 3-10.\n";
                        continue;
                    }
                    // if input is number, range check
                    if (length < 3 || length > 10) {
                        cout << "Length must be between 3 and 10 letters.\n";
                    } else break;
                }
                secret = getRandomNameByLength(length);
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Initialize guess
            bool guessed = false;

            while (!guessed) {

                cout << "\nGuess the name (" << secret.length() << " letters): ";
                string guess;
                // get user guess
                getline(cin, guess);

                // if user guess is correct
                if (compareNames(guess, secret)) {
                    cout << "\nCorrect! The name was: " << secret << "\n";
                    guessed = true;
                    break;
                }

                cout << "Matching letters:\n";
                // if some letters are correct, display them
                cout << getMatchedLetters(guess, secret) << "\n";

                // encourage user to continue, ask if they keep going
                // if yes continue
                string trySame = getYesNo("Not quite... keep trying? (Y/N): ");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // if no, break loop
                if (trySame == "N") break;
            }

            playAnother = getYesNo("\nPlay again with a NEW name? (Y/N): ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (playAnother == "N") {
                cout << "Returning to menu...\n";
                return;
            }
        }
    }
} // namespace arcade