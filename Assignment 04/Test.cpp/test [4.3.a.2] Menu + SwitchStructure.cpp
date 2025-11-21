#include <iostream>
#include <cstdlib>      // for rand(), srand()
#include <ctime>        // for time()
#include <limits>       // for numeric_limits for safe input cleanup
#include <string>       // *** ADDED for name handling ***
using namespace std;

// ============================
// *** ADDED: PlayerName struct
// ============================
struct PlayerName {
    string first;
    string last;
};

// ============================
// *** ADDED: getPlayerName()
// ============================
PlayerName getPlayerName() {
    PlayerName p;
    string input;

    // Helper lambda to trim whitespace
    auto trim = [&](string s) {
        size_t start = s.find_first_not_of(" \t\r\n");
        size_t end   = s.find_last_not_of(" \t\r\n");
        if (start == string::npos) return string(""); 
        return s.substr(start, end - start + 1);
    };

    cin.ignore(numeric_limits<streamsize>::max(), '\n');  
    // ^^^ IMPORTANT: clears leftover newline from previous cin >> so getline() works properly

    // FIRST NAME
    while (true) {
        cout << "Enter your FIRST name: ";
        getline(cin, input);

        input = trim(input);
        if (!input.empty()) {
            p.first = input;
            break;
        }
        cout << "Invalid. Name cannot be empty.\n";
    }

    // LAST NAME
    while (true) {
        cout << "Enter your LAST name: ";
        getline(cin, input);

        input = trim(input);
        if (!input.empty()) {
            p.last = input;
            break;
        }
        cout << "Invalid. Name cannot be empty.\n";
    }

    return p;
}

// Function prototypes for all major features
void playGuessingGame();
void playDiceGame();
void playLotteryGame();
void playNameGuessingGame();
void showCredits();

int main() {

    // =====================================
    // *** ADDED: Get player name at startup
    // =====================================
    cout << "\nWelcome to the Mini Arcade!\n";
    PlayerName player = getPlayerName();

    int choice = 0;

    // Seed timer once for entire program
    srand(static_cast<unsigned int>(time(0)));

    do {
        // Display menu
        cout << "\n==============================\n";
        cout << "         MINI ARCADE\n";
        cout << "==============================\n";

        // =====================================
        // *** ADDED: Greet player in the menu
        // =====================================
        cout << "Player: " << player.first << " " << player.last << "\n\n";

        cout << "1. Guessing Game (Numbers)\n";
        cout << "2. Dice Game (Match to Win)\n";
        cout << "3. Lottery Game (Vector Victory)\n";
        cout << "4. Guessing Name Game\n";
        cout << "5. Credits\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";

        cin >> choice;

        // safe input validation
        if (!cin) {
            cin.clear(); 
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 6.\n";
            continue;
        }

        if (choice < 1 || choice > 6) {
            cout << "Invalid choice. Please select a number between 1 and 6.\n";
            continue;
        }

        switch (choice) {
            case 1:
                playGuessingGame();
                break;

            case 2:
                playDiceGame();
                break;

            case 3:
                // =============================================
                // *** IF NEEDED: pass player name to lottery ***
                // playLotteryGame(player.first, player.last);
                // (For now leaving original call so your structure remains unchanged)
                // =============================================
                // playLotteryGame();
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

                if (confirm == 'y' || confirm == 'Y') { 
                    cout << "Exiting the Mini Arcade. Goodbye!\n";
                } else {
                    choice = 0;
                }
                break;
            }
        }

    } while (choice != 6);

    return 0;
}
