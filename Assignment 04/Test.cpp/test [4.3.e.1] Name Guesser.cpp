#include <iostream>
#include <string>
#include <limits>
#include <cctype>   // for tolower
using namespace std;

/*
===========================================================
 Case-insensitive string comparison
 Why needed?
 - The assignment requires guessing names like "Mariam",
   "Jessica", etc.
 - Without case-insensitivity, "mariam" ≠ "Mariam",
   which is frustrating for players (personally tested :/ )
 - This helper function allows "Mariam", "mariam", "MARIAM",
   "MaRiAm", etc. to all be accepted as correct.
 Reference:
   LearnCPP – "Comparing strings case-insensitively"
   https://www.learncpp.com/cpp-tutorial/string-comparison/
===========================================================
*/
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

// Hardcoded names (3–10 letters)
string getNameByIndex(int index) {
    switch (index) {
        case 1: return "Ali";        // 3
        case 2: return "Diwan";      // 5
        case 3: return "Mariam";     // 6
        case 4: return "Fayzan";     // 6
        case 5: return "Jessica";    // 7
        case 6: return "Benjamin";   // 8
        case 7: return "Alexander";  // 9
        default: return "Mariam";
    }
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
    int index = rand() % 7 + 1;
    return getNameByIndex(index);
}

// Random name of specific length
string getRandomNameByLength(int lengthChoice) {
    int matchCount = 0;

    for (int i = 1; i <= 7; i++)
        if ((int)getNameByIndex(i).length() == lengthChoice)
            matchCount++;

    if (matchCount == 0)
        return getRandomName();

    int target = rand() % matchCount + 1;
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
    char playAnother = 'Y';

    cout << "\n=== Guessing Name: Figuring Out the Name Edition ===\n\n";

    while (playAnother == 'Y' || playAnother == 'y') {

        int mode = 0;

        while (true) {
            cout << "Choose an option:\n";
            cout << "1. Random name\n";
            cout << "2. Choose name length (3–10 letters)\n";
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

        int lengthChoice = 0;
        string secret;

        if (mode == 1) {
            secret = getRandomName();
        } else {
            while (true) {
                cout << "Enter desired name length (3–10): ";
                if (!(cin >> lengthChoice)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Enter a WHOLE number 3–10.\n";
                    continue;
                }

                if (lengthChoice < 3 || lengthChoice > 10) {
                    cout << "Length must be between 3 and 10.\n";
                } else {
                    break;
                }
            }
            secret = getRandomNameByLength(lengthChoice);
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        bool guessed = false;
        char trySame = 'Y';

        while (!guessed && (trySame == 'Y' || trySame == 'y')) {
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

            cout << "Try this same name again? (Y/N): ";
            while (true) {
                cin >> trySame;
                if (trySame == 'Y' || trySame == 'y' ||
                    trySame == 'N' || trySame == 'n')
                    break;

                cout << "Enter Y or N only: ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (!guessed) {
            cout << "Returning to menu...\n";
            return;
        }

        cout << "\nPlay again with a NEW name? (Y/N): ";
        while (true) {
            cin >> playAnother;
            if (playAnother == 'Y' || playAnother == 'y' ||
                playAnother == 'N' || playAnother == 'n')
                break;

            cout << "Enter Y or N only: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
