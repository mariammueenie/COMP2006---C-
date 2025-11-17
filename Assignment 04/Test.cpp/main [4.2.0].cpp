#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include <cctype>
#include <vector>
#include <fstream>
#include <iomanip>

using namespace std;

/* ---------------------------------------------------------
   🔒 UNIVERSAL SAFE INPUT FUNCTIONS  
--------------------------------------------------------- */

// Reads ONE integer only (no extra characters allowed)
bool get_single_int(int& out, int min, int max) {
    string input;
    getline(cin, input);

    // Trim spaces
    while (!input.empty() && isspace(input.front())) input.erase(input.begin());
    while (!input.empty() && isspace(input.back())) input.pop_back();

    // EMPTY?
    if (input.empty()) return false;

    // Check every character
    for (char c : input) {
        if (!isdigit(c)) return false; // ONLY digits allowed
    }

    // Convert
    try {
        out = stoi(input);
    }
    catch (...) { return false; }

    // Range check
    if (out < min || out > max) return false;

    return true;
}

// Reads ONE word name, ONLY letters + a few spaces
bool get_valid_name(string& out) {
    string input;
    getline(cin, input);

    // Trim spaces
    while (!input.empty() && isspace(input.front())) input.erase(input.begin());
    while (!input.empty() && isspace(input.back())) input.pop_back();

    if (input.empty()) return false;

    int spaceCount = 0;

    for (char c : input) {
        if (isalpha(c)) continue;

        if (isspace(c)) {
            spaceCount++;
            if (spaceCount > 2) return false; // allow 1–2 internal spaces
            continue;
        }

        return false; // reject digits and punctuation
    }

    out = input;
    return true;
}

/* ---------------------------------------------------------
   🎮 MAIN PROGRAM
--------------------------------------------------------- */

int main() {
    srand(static_cast<unsigned int>(time(0)));

    string firstName, lastName;

    cout << "Welcome to The Mini Arcade!!\n\n";

    /* ---------------- FIRST NAME ---------------- */
    cout << "Please enter your first name:\n\n";
    while (!get_valid_name(firstName)) {
        cout << "Invalid first name. Only letters and a few spaces allowed. Try again:\n\n";
    }

    cout << "\n";

    /* ---------------- LAST NAME ---------------- */
    cout << "Please enter your last name:\n\n";
    while (!get_valid_name(lastName)) {
        cout << "Invalid last name. Only letters and a few spaces allowed. Try again:\n\n";
    }

    cout << "\n";
    cout << "Hello, " << firstName << " " << lastName << "! Let's play a game.\n\n";

    int gameChoice = 0;

    /* ================= MENU LOOP ================= */
    do {
        cout << "================================\n";
        cout << "           GAME MENU            \n";
        cout << "================================\n";
        cout << "1. Guessing Game\n";
        cout << "2. Roll the Dice\n";
        cout << "3. Lottery\n";
        cout << "4. Credits\n";
        cout << "5. Exit\n";
        cout << "================================\n";
        cout << "Please enter the number of the game you would like to play:\n\n";

        while (!get_single_int(gameChoice, 1, 5)) {
            cout << "Invalid input. Enter a whole number (1–5):\n\n";
        }

        cout << "\n";

        /* ================= SWITCH ================= */
        switch (gameChoice) {

/* ---------------------------------------------------------
   🎯 GAME 1 — GUESSING GAME
--------------------------------------------------------- */
            case 1: {
                cout << "Hello, " << firstName << "! Welcome to the Guessing Game!\n\n";
                cout << "Guess a number between 1 and 100. You get 3 attempts.\n\n";

                char playAgain;

                do {
                    int limit = 3;
                    int count = 0;
                    int secret = (rand() % 100) + 1;

                    while (count < limit) {
                        cout << "Enter your guess:\n";

                        int guess;
                        while (!get_single_int(guess, 1, 100)) {
                            cout << "Invalid input. Enter ONE whole number (1–100):\n";
                        }

                        count++;
                        cout << "Attempt " << count << " of " << limit << "\n\n";

                        if (guess < secret)
                            cout << "Too low!\n\n";
                        else if (guess > secret)
                            cout << "Too high!\n\n";
                        else {
                            cout << "Congratulations, " << firstName << "! You guessed it!\n\n";
                            break;
                        }

                        if (count == limit) {
                            cout << "Out of attempts! Correct number was " << secret << ".\n\n";
                        }
                    }

                    cout << "Play again? (y/n): ";
                    cin >> playAgain;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                } while (tolower(playAgain) == 'y');

                cout << "Returning to main menu...\n\n";
                break;
            }

/* ---------------------------------------------------------
   🎲 GAME 2 — ROLL THE DICE
--------------------------------------------------------- */
            case 2: {
                char playAgain;
                do {
                    cout << "Hello, " << firstName << "! Let's play Roll the Dice!\n\n";

                    int firstRoll, secondRoll;

                    cout << "Enter your first number (1–6):\n";
                    while (!get_single_int(firstRoll, 1, 6)) {
                        cout << "Invalid input. Enter ONE whole number (1–6):\n";
                    }

                    cout << "Enter your second number (1–6):\n";
                    while (!get_single_int(secondRoll, 1, 6)) {
                        cout << "Invalid input. Enter ONE whole number (1–6):\n";
                    }

                    int c1 = (rand() % 6) + 1;
                    int c2 = (rand() % 6) + 1;

                    cout << "\nYou chose: " << firstRoll << " " << secondRoll << "\n";
                    cout << "Computer rolled: " << c1 << " " << c2 << "\n\n";

                    if (firstRoll == c1 && secondRoll == c2)
                        cout << "YOU WIN!\n\n";
                    else
                        cout << "You lose.\n\n";

                    cout << "Play again? (y/n): ";
                    cin >> playAgain;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                } while (tolower(playAgain) == 'y');

                cout << "Returning to main menu...\n";
                break;
            }

/* ---------------------------------------------------------
   🎰 GAME 3 — LOTTERY (FIXED + SECURE)
--------------------------------------------------------- */
            case 3: {
                cout << "Hello, " << firstName << "! Welcome to the Lottery!\n";

                char playAgain = 'y';

                do {
                    vector<int> userNums;
                    vector<int> autoNums;
                    vector<int> winningNums;

                    cout << "\nEnter 7 UNIQUE numbers between 1 and 49:\n\n";

                    // USER INPUT LOOP
                    while (userNums.size() < 7) {
                        cout << "Enter number " << userNums.size() + 1 << ":\n";

                        int n;
                        if (!get_single_int(n, 1, 49)) {
                            cout << "Invalid input. Enter EXACTLY ONE number (1–49).\n\n";
                            continue;
                        }

                        bool dup=false;
                        for(int x:userNums) if(x==n) dup=true;

                        if (dup) {
                            cout << "Duplicate. Enter another number.\n\n";
                            continue;
                        }

                        userNums.push_back(n);
                    }

                    // Auto-generated unique numbers
                    while(autoNums.size()<7) {
                        int r=(rand()%49)+1;
                        bool exists=false;
                        for(int x:autoNums) if(x==r) exists=true;
                        if(!exists) autoNums.push_back(r);
                    }

                    // Winning numbers
                    while(winningNums.size()<7) {
                        int r=(rand()%49)+1;
                        bool exists=false;
                        for(int x:winningNums) if(x==r) exists=true;
                        if(!exists) winningNums.push_back(r);
                    }

                    auto countMatches = [](const vector<int>& a,const vector<int>& b){
                        int m=0;
                        for(int x:a) for(int y:b) if(x==y) m++;
                        return m;
                    };

                    int matchUser = countMatches(userNums, winningNums);
                    int matchAuto = countMatches(autoNums, winningNums);

                    auto prizeFor=[](int m){
                        switch(m){
                            case 6: return 5000000.0;
                            case 5: return 250000.0;
                            case 4: return 10000.0;
                            case 3: return 1000.0;
                            default: return 0.0;
                        }
                    };

                    double prizeUser = prizeFor(matchUser);
                    double prizeAuto = prizeFor(matchAuto);

                    cout << "\n==============================\n";
                    cout << "YOUR LOTTERY TICKET\n";
                    cout << "==============================\n";

                    cout << "Line 1: ";
                    for(int n:userNums) cout<<n<<" ";
                    cout << "\nLine 2: ";
                    for(int n:autoNums) cout<<n<<" ";
                    cout << "\nWinning Numbers: ";
                    for(int n:winningNums) cout<<n<<" ";
                    cout << "\n";

                    cout << "Matches (You): " << matchUser 
                         << " → " << (prizeUser>0 ? "$"+to_string((int)prizeUser) : "No prize") << "\n";

                    cout << "Matches (Computer): " << matchAuto
                         << " → " << (prizeAuto>0 ? "$"+to_string((int)prizeAuto) : "No prize") << "\n\n";

                    cout << "Play Lottery again? (y/n): ";
                    cin >> playAgain;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');

                } while (tolower(playAgain)=='y');

                cout << "Returning to main menu...\n";
                break;
            }

/* ---------------------------------------------------------
   🎤 CREDITS
--------------------------------------------------------- */
            case 4:
                cout << "CREDITS\n\n";
                cout << "Created by:\n";
                cout << "Mariam Mueen\n";
                cout << "Fayzabanu Diwan\n";
                cout << "Group 9\n";
                break;

/* ---------------------------------------------------------
   🚪 EXIT
--------------------------------------------------------- */
            case 5:
                cout << "Thank you for playing, " << firstName << "!\n";
                break;
        }

    } while (gameChoice != 5);

    return 0;
}
