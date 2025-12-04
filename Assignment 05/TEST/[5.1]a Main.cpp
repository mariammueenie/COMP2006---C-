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
using namespace std;

// FAIR WARNING: Commented the heck out of this code, mostly for my own understanding
// You know u understand something if u can explain it, or something lol 

// ============================
// PlayerName struct
// ============================
    struct PlayerName {
        string first;
        string last;
    };
    // Global player object so any game can access player.first / player.last
    // And so that games don't break
    PlayerName player;

// =========================================================
// YES/NO strictly-controlled validator (only Y/N/YES/NO)
// Since used in multiple games, defined here globally
// Muuuch easier than checking inline every time lmao
// =========================================================
    string getYesNo(const string& prompt) {
        cout << prompt;

        string input;
        while (true) {
            cin >> input;

            // lowercase whole string
            for (char &c : input) {
                c = tolower(static_cast<unsigned char>(c));
            }
            if (input == "y" || input == "yes") {
                return "Y";
            }
            if (input == "n" || input == "no") {
                return "N";
            }

            cout << "Please enter Y, N, YES, or NO only: ";
            cin.clear();
        }
    }

// =========================================================
// Function declarations
// =========================================================
    PlayerName getPlayerName();
    int getStrictInteger(const string& prompt, int minV, int maxV);
    void playGuessingGame();
    void playDiceGame();
    void playLotteryGame();
    void playNameGuessingGame();
    void showCredits();
    void showAbout();

// =========================================================
// main() Game / Menu Loop
// =========================================================
    int main() {

        cout << "\nWelcome to the Mini Arcade!\n";
        cout << "Please hit enter to get started...\n";
        player = getPlayerName();    // assign to the global player

        int choice = 0;
        // seed timer once for entire program
        srand(static_cast<unsigned int>(time(0)));

        do {
            // Display main menu
            cout << "\n==============================\n";
            cout << "         MINI ARCADE\n";
            cout << "==============================\n";

            cout << "Player: " << player.first << " " << player.last << "\n\n";

            cout << "1. Guessing Game (Numbers)\n";
            cout << "2. Dice Game (Match to Win)\n";
            cout << "3. Lottery Game (Vector Victory)\n";
            cout << "4. Guessing Name Game\n";
            cout << "5. Credits\n";
            cout << "6. About\n"
            cout << "7. Exit\n";

            // strict menu input system
            // Does 4 things 
            // 1. Read whole input as a string 
            // 2. Trim whitespace 
            // 3. Check that string contains ONLY digits 
            // 4. Convert string to integer and check range
            string line; // treated as string so that ANYTHING user types can be caught/validated
            cout << "Enter your choice (1-7): ";
            // prevents issues with leftover newlines
            // better than cin.ignore() alone
            // better than cin >> choice
            getline(cin, line);

            // trim leading spaces
            while (!line.empty() && isspace(line.front()))
                line.erase(0, 1);
            // trim trailing spaces
            while (!line.empty() && isspace(line.back()))
                line.pop_back();

            bool badInput = false;

            // checks if line is empty
            if (line.empty()) {
                badInput = true;
            } else {
                // checks if all characters are digits
                for (size_t i = 0; i < line.length(); i++) {
                    // REFERENCE: MURACH'S C++ PROGRAMMING, 2nd Edition
                    //            CHAPTER 6 SLIDES: 
                    //            How to Work with Data Types, Strings, and Vectors
                    if (!isdigit(static_cast<unsigned char>(line[i]))) {
                        badInput = true;
                        break;
                    }
                }
            }

            // If invalid input, prompted again
            if (badInput) {
                cout << "Invalid input. Please enter ONE single integer only.\n";
                continue;
            }

            // convert to integer
            // REFERENCE: https://en.cppreference.com/w/cpp/string/basic_string/stol
            // REFERENCE: https://cplusplus.com/reference/string/stoi/
            choice = stoi(line);

            // range check
            if (choice < 1 || choice > 7) {
                cout << "Invalid choice. Please select a number between 1 and 7.\n";
                continue;
            }
            // Main Menu Choice Handling
            switch (choice) {
                case 1: playGuessingGame(); break;
                case 2: playDiceGame(); break;
                case 3: playLotteryGame(); break;
                case 4: playNameGuessingGame(); break;
                case 5: showCredits(); break;
                case 6: showAbout(); break; // About section added
                case 7: {
                    string ans = getYesNo("Are you sure you want to exit? (Y/N): ");
                    if (ans == "Y") {
                        cout << "Exiting the Mini Arcade. Goodbye!\n";
                    } else {
                        choice = 0;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
            }
        } while (choice != 7); // Press 6 to exit
    return 0;
    }

// =========================================================
// NAME INPUT + VALIDATION
// Has 3 parts:
//    validFirstName() -> First name: letters + hyphen
//    validLastName()  -> Last name:  letters + apostrophe
//    getPlayerName()  -> Loops until valid
// ==========================================================

    // Validates first name (letters + hyphen only)
    // For names like "Mary-Jane" or "Micheal-Paul"
    // Uses static_cast<unsigned char> to avoid potential issues with negative char values
    // Uses !isalpha() to check for non-letter characters
    bool validFirstName(const string& s) {
        if (s.empty()) return false;

        for (size_t i = 0; i < s.length(); i++) {
            char c = s[i];
            if (!isalpha(static_cast<unsigned char>(c)) && c != '-') {
                return false;
            }
        }
        return true;
    }

    // Validates last name (letters + apostrophe only)
    // For names like "O'Connor" or "D'Angelo"
    //
    bool validLastName(const string& s) {
        if (s.empty()) return false;

        for (size_t i = 0; i < s.length(); i++) {
            char c = s[i];
            if (!isalpha(static_cast<unsigned char>(c)) && c != '\'') {
                return false;
            }
        }
        return true;
    }

    // 1. Prompts user for first name, keeps prompting until getFirstName() requirements satisfied 
    // 2. Prompts user for last name, keeps prompting until getLastName() requirements satisfied
    // 3. Returns PlayerName struct with valid names
    PlayerName getPlayerName() {
        PlayerName p;
        string input;

        // Clear leftover newline before getline()
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // FIRST NAME
            while (true) {
                cout << "Enter your FIRST name (letters and '-' only): ";
                getline(cin, input);

                // Trim start/end whitespace
                while (!input.empty() && isspace(static_cast<unsigned char>(input.front())))
                    input.erase(0, 1);
                while (!input.empty() && isspace(static_cast<unsigned char>(input.back())))
                    input.pop_back();

                if (validFirstName(input)) {
                    p.first = input;
                    break;
                }
                cout << "Invalid. First name must contain only letters and hyphens.\n";
            }

        // LAST NAME
            while (true) {
                cout << "Enter your LAST name (letters and '\'' only): ";
                getline(cin, input);

                while (!input.empty() && isspace(static_cast<unsigned char>(input.front())))
                    input.erase(0, 1);
                while (!input.empty() && isspace(static_cast<unsigned char>(input.back())))
                    input.pop_back();

                if (validLastName(input)) {
                    p.last = input;
                    break;
                }
                cout << "Invalid. Last name must contain only letters and apostrophes.\n";
            }

            return p;
        }

// =========================================================
// STRICT INTEGER INPUT FUNCTION
// Function that strictly validates integer input within a specified range.
// Nice and can be used in multiple games

// getline()
//    REFERENCE: https://en.cppreference.com/w/cpp/string/basic_string/getline
//    REFERENCE: https://en.cppreference.com/w/cpp/io/basic_istream/ignore
//    REFERENCE: 
// isspace(), isdigit(), isalpha()
//    REFERENCE: MURACHS C++ PROGRAMMING, 2nd Edition
//            CHAPTER 6 SLIDES: How to Work with Data Types, Strings, and Vectors
// trim w/ isspace() isdigit()
//    REFERENCE: https://en.cppreference.com/w/cpp/string/byte/isspace
//    REFERENCE: https://en.cppreference.com/w/cpp/string/byte/isdigit
// line.erase
//    REFERENCE: https://en.cppreference.com/w/cpp/string/basic_string/erase
// stoi()
//    REFERENCE: https://cplusplus.com/reference/string/stoi/
//               https://en.cppreference.com/w/cpp/string/basic_string/stol
// range check, minV, maxV
// -> Used minV and maxV to make function reusable in multiple games
//     ngl the idea was suggested by ChatGPT but I coded it myself
//     cuz I was thinking about how to do it anyway, and I was like umm
//     surely there is an easier way to do this than repeating the same code 
//     for each game but I wasn't sure how to do it
// guarantees ONE valid integer per line
// ============================================================

    int getStrictInteger(const string& prompt, int minV, int maxV)
    {
        while (true)
        {
            cout << prompt;
            string line;
            getline(cin, line);

            // Trim whitespace
            while (!line.empty() && isspace(static_cast<unsigned char>(line.front())))
                line.erase(0, 1);
            while (!line.empty() && isspace(static_cast<unsigned char>(line.back())))
                line.pop_back();

            if (line.empty()) {
                cout << "Invalid input. Please enter ONE whole number.\n";
                continue;
            }

            // Initializes bool bad to false (ie: Assume input is valid, unless proven to be bad)
            bool bad = false;
            for (char c : line) { // iterate through each character within input 
                if (!isdigit(static_cast<unsigned char>(c))) { // Check if c is NOT a digit
                    bad = true; // If non-digit character is found, set bool to true (ie: input IS bad)
                    break; // exit loop, since we now know input is bad
                }
            }
            if (bad) {
                cout << "Invalid input. Please enter an integer in the accepted range.\n";
                continue;
            }

            // converts string to int
            int value = stoi(line);

            // If value is singular integer, but too big/small
            if (value < minV || value > maxV) {
                cout << "Number must be between " << minV << " and " << maxV << ".\n";
                continue;
            }

            return value;
        }
    }