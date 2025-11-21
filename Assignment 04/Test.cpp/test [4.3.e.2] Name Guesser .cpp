#include <iostream>
#include <string>
#include <limits>
#include <cctype>   // for tolower
using namespace std;

/* =========================================================
   Name Guessing Game
   ========================================================= */

bool equalsIgnoreCase(const string& a, const string& b)
{
    if (a.length() != b.length())
        return false;

    for (size_t i = 0; i < a.length(); i++) {
        if (tolower(static_cast<unsigned char>(a[i])) !=
            tolower(static_cast<unsigned char>(b[i]))) {
            return false;
        }
    }
    return true;
}

string getNameByIndex(int index) {
    switch (index) {
        case 1: return "Ali";
        case 2: return "Diwan";
        case 3: return "Mariam";
        case 4: return "Fayzan";
        case 5: return "Jessica";
        case 6: return "Benjamin";
        case 7: return "Alexander";
    }
    return "Mariam";
}

// Exact comparison, ignoring case
bool compareNames(const string& guess, const string& answer) {
    return equalsIgnoreCase(guess, answer);
}

// Build hint string
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

// Random name of any length
string getRandomName() {
    int i = rand() % 7 + 1;
    return getNameByIndex(i);
}

// Random name of specific length
string getRandomNameByLength(int lengthChoice) {
    int count = 0;

    for (int i = 1; i <= 7; i++)
        if ((int)getNameByIndex(i).length() == lengthChoice)
            count++;

    if (count == 0)
        return getRandomName();

    int target = rand() % count + 1;
    int seen = 0;

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

            if (!(cin >> mode)) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid input. Enter 1 or 2.\n";
                continue;
            }

            if (mode == 1 || mode == 2)
                break;

            cout << "Invalid choice. Enter 1 or 2.\n";
        }

        int length = 0;
        string secret;

        if (mode == 1) {
            secret = getRandomName();
        } else {
            while (true) {
                cout << "Enter desired name length (3-10): ";
                if (!(cin >> length)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Enter a WHOLE number 3–10.\n";
                    continue;
                }
                if (length < 3 || length > 10) {
                    cout << "Length must be between 3 and 10.\n";
                } else break;
            }
            secret = getRandomNameByLength(length);
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool guessed = false;

        while (!guessed) {

            cout << "\nGuess the name (" << secret.length() << " letters): ";
            string guess;
            getline(cin, guess);

            if (compareNames(guess, secret)) {
                cout << "\nCorrect! The name was: " << secret << "\n";
                guessed = true;
                break;
            }

            cout << "Matching letters:\n";
            cout << getMatchedLetters(guess, secret) << "\n";

            string trySame = getYesNo("Try this same name again? (Y/N): ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

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

// CHANGES TO MAKE
// name guessing game 
    // when choosing name length, the loop takes you straight to the end of the game
    // when you hit enter 
    // when entering letters, it lets you enter letters and numbers, and just takes the correct letters, rather
    // than working like hangman
    // asks you if you want to try playing the same game again, even when you guessed the name correctly