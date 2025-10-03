#include <iostream>
#include <limits>
#include <ctime>    // time()
#include <cctype>   // tolower()
#include <cstdlib>  // rand(), srand()

using namespace std;

int main() {
    // seed the random number generator
    srand(static_cast<unsigned int>(time(0)));

    // ask for a name so the greeting works
    string firstName;
    cout << "Welcome to Roll the Dice!\n";
    cout << "Enter your first name: ";
    cin >> firstName;
    cout << "\n";

    // game loop
    char playAgain;
    //
    do {
        // explain the game
        cout << "Hello, " << firstName << "Lets play Roll the Dice!\n";
        cout << "Enter two numbers (1-6). If BOTH match the computer's roll (in order), you win!\n\n";

        // get two numbers from user
        int firstRoll, secondRoll;

        // validation
        while (true) {
            cout << "Enter your first number (1-6): ";
            if (!(cin >> firstRoll)) {
                cout << "Not a number. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (firstRoll < 1 || firstRoll > 6) {
                cout << "Out of range. Try again.\n";
                continue;
            }
            break;
        }

        // validation
        while (true) {
            cout << "Enter your second number (1-6): ";
            if (!(cin >> secondRoll)) {
                cout << "Not a number. Try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            if (secondRoll < 1 || secondRoll > 6) {
                cout << "Out of range. Try again.\n";
                continue;
            }
            break;
        }

        // computer rolls
        int comp1 = (rand() % 6) + 1;
        int comp2 = (rand() % 6) + 1;

        // print results
        cout << "You chose: " << firstRoll << " " << secondRoll << "\n\n";
        cout << "Computer rolled: " << comp1 << " " << comp2 << "\n\n";

        // determine if user won
        if (firstRoll == comp1 && secondRoll == comp2) {
            cout << "Both numbers match — YOU WIN!\n\n";
        } else {
            cout << "At least one number didn't match — you lose.\n\n";
        }

        // ask to play again
        cout << "Play again? (y/n): ";
        cin >> playAgain;
        cout << "\n";

    } while (tolower(playAgain) == 'y'); // end of game loop
}
