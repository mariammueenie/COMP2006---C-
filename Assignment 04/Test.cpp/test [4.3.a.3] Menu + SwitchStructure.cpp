#include <iostream>
#include <cstdlib>      // rand(), srand()
#include <ctime>        // time()
#include <limits>       // numeric_limits
#include <string>       // string
using namespace std;

// ============================
// PlayerName struct
// ============================
struct PlayerName {
    string first;
    string last;
};

// ============================
// SIMPLE NAME VALIDATION
// ============================

// FIRST NAME: letters + hyphen only
bool validFirstName(const string& s) {
    if (s.empty()) return false;

    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];
        if (!isalpha(c) && c != '-') {
            return false;
        }
    }
    return true;
}

// LAST NAME: letters + apostrophe only
bool validLastName(const string& s) {
    if (s.empty()) return false;

    for (size_t i = 0; i < s.length(); i++) {
        char c = s[i];
        if (!isalpha(c) && c != '\'') {
            return false;
        }
    }
    return true;
}

// ============================
// getPlayerName()
// ============================
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
        while (!input.empty() && isspace(input.front()))
            input.erase(0, 1);
        while (!input.empty() && isspace(input.back()))
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

        while (!input.empty() && isspace(input.front()))
            input.erase(0, 1);
        while (!input.empty() && isspace(input.back()))
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
// Function prototypes
// =========================================================
void playGuessingGame();
void playDiceGame();
void playLotteryGame();
void playNameGuessingGame();
void showCredits();

// =========================================================
// main()
// =========================================================
int main() {

    cout << "\nWelcome to the Mini Arcade!\n";
    PlayerName player = getPlayerName();

    int choice = 0;
    srand(static_cast<unsigned int>(time(0)));

    do {
        cout << "\n==============================\n";
        cout << "         MINI ARCADE\n";
        cout << "==============================\n";

        cout << "Player: " << player.first << " " << player.last << "\n\n";

        cout << "1. Guessing Game (Numbers)\n";
        cout << "2. Dice Game (Match to Win)\n";
        cout << "3. Lottery Game (Vector Victory)\n";
        cout << "4. Guessing Name Game\n";
        cout << "5. Credits\n";
        cout << "6. Exit\n";

        // =========================================================
        // NEW INPUT SYSTEM:
        // Accept ONLY *one* integer on the line.
        //
        // WHY THIS FIX IS NECESSARY:
        // If the user enters "1 2", normal cin >> choice
        //  reads "1"
        //  leaves "2" in the buffer
        //  next game reads "2" automatically
        //
        // REFERENCES:
        // LearnCPP — Safe input using getline()
        // https://www.learncpp.com/cpp-tutorial/input-validation/
        //
        // LearnCPP — Why cin >> leaves leftover characters
        // https://www.learncpp.com/cpp-tutorial/input-with-istream/
        //
        // StackOverflow — leftover buffer problem ("1 2" issue)
        // https://stackoverflow.com/questions/17335816/
        // =========================================================

        string line;
        cout << "Enter your choice (1-6): ";
        getline(cin, line);

        // Trim whitespace
        while (!line.empty() && isspace(line.front()))
            line.erase(0, 1);
        while (!line.empty() && isspace(line.back()))
            line.pop_back();

        bool badInput = false;

        if (line.empty()) {
            badInput = true;
        } else {
            // Allow ONLY digits (no spaces, no letters)
            for (size_t i = 0; i < line.length(); i++) {
                if (!isdigit(line[i])) {
                    badInput = true;
                    break;
                }
            }
        }

        if (badInput) {
            cout << "Invalid input. Please enter ONE single integer only.\n";
            continue;
        }

        // Convert safely
        choice = stoi(line);

        if (choice < 1 || choice > 6) {
            cout << "Invalid choice. Please select a number between 1 and 6.\n";
            continue;
        }

        // =========================================================

        switch (choice) {
            case 1:
                playGuessingGame();
                break;

            case 2:
                playDiceGame();
                break;

            case 3:
                playLotteryGame();
                break;

            case 4:
                playNameGuessingGame();
                break;

            case 5:
                showCredits();
                break;

            case 6: {
                char confirm;
                cout << "Are you sure you want to exit? (y/n): ";
                cin >> confirm;

                if (confirm == 'y' || confirm == 'Y')
                    cout << "Exiting the Mini Arcade. Goodbye!\n";
                else
                    choice = 0; // cancel exit

                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
        }

    } while (choice != 6);

    return 0;
}
