// main.cpp - Mini Arcade Assignment 4
// This program implements a Mini Arcade with four games and a credits screen.
// It demonstrates modular design using functions, vectors for lottery data,
// and simple file output for storing lottery results.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Function prototypes for all features.
void playGuessingGame();
void playDiceGame();
void playLotteryGame();
void playNameGuessingGame();
void showCredits();

// Helper function prototypes for the lottery and name games.
vector<int> generateUnique(int count, int minVal, int maxVal);
vector<int> getUserTicket();
vector<int> generateRandomLine();
int compareLines(const vector<int>& line, const vector<int>& winning, int bonusNum);
string calculatePrize(int matches);
void writeTicketToFile(const vector<int>& ticket,
                       const vector<int>& bonusLine,
                       const vector<int>& winning,
                       int bonusNum,
                       int resultTicket,
                       int resultBonus);

bool compareNames(const string& guess, const string& answer);
string getMatchedLetters(const string& guess, const string& answer);

int main() {
    int choice = 0;

    // Seed the random number generator once for the entire program.
    srand(static_cast<unsigned int>(time(0)));

    // Main arcade loop: keeps running until user chooses Exit from the menu.
    do {
        // Display menu options.
        cout << "\n==============================\n";
        cout << "         MINI ARCADE\n";
        cout << "==============================\n";
        cout << "1. Guessing Game (Numbers)\n";
        cout << "2. Dice Game (Match to Win)\n";
        cout << "3. Lottery Game (Vector Victory)\n";
        cout << "4. Guessing Name Game\n";
        cout << "5. Credits\n";
        cout << "6. Exit\n";
        cout << "Enter your choice (1-6): ";

        cin >> choice;

        // Validate menu choice is within expected range.
        if (choice < 1 || choice > 6) {
            cout << "Invalid choice. Please select a number between 1 and 6.\n";
            continue;
        }

        // Dispatch to the selected game or feature.
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
            case 6:
                cout << "Exiting the Mini Arcade. Goodbye!\n";
                break;
        }

        // After each game or credits, the loop repeats and shows the menu again.

    } while (choice != 6);

    return 0;
}

// =========================
// Game 1: Guessing Game
// =========================

void playGuessingGame() {
    char playAgain = 'Y';

    while (playAgain == 'Y' || playAgain == 'y') {
        cout << "\n--- Guessing Game ---\n\n";

        int secretNumber;
        int guess;
        int attempts = 7;

        secretNumber = rand() % 100 + 1;

        cout << "I am thinking of a number between 1 and 100.\n";
        cout << "You have " << attempts << " attempts.\n\n";

        bool guessed = false;

        for (int i = 1; i <= attempts; i++) {
            cout << "Attempt " << i << "/" << attempts << ": ";
            cin >> guess;

            if (guess < 1 || guess > 100) {
                cout << "Please enter a number between 1 and 100.\n";
                i--;
                continue;
            }

            if (guess == secretNumber) {
                cout << "\nCorrect! The number was " << secretNumber << ".\n";
                guessed = true;
                break;
            } else if (guess < secretNumber) {
                cout << "Too low. Try a higher number.\n\n";
            } else {
                cout << "Too high. Try a lower number.\n\n";
            }
        }

        if (!guessed) {
            cout << "You are out of attempts. The number was " << secretNumber << ".\n";
        }

        cout << "\nWould you like to play the Guessing Game again? (Y/N): ";
        cin >> playAgain;

        if (playAgain == 'Y' || playAgain == 'y') {
            continue;
        }

        char returnToMenu;
        cout << "Return to main menu? (Y/N): ";
        cin >> returnToMenu;
        return;
    }
}

// =========================
// Game 2: Dice Game
// =========================

void playDiceGame() {
    char playAgain = 'Y';

    while (playAgain == 'Y' || playAgain == 'y') {
        cout << "\n--- Dice Game ---\n\n";

        int die1 = rand() % 6 + 1;
        int die2 = rand() % 6 + 1;

        cout << "Rolling the dice...\n\n";
        cout << "Die 1: " << die1 << "\n";
        cout << "Die 2: " << die2 << "\n\n";

        if (die1 == die2) {
            cout << "They match! You win!\n";
        } else {
            cout << "They do not match. You lose.\n";
        }

        cout << "\nWould you like to roll again? (Y/N): ";
        cin >> playAgain;

        if (playAgain == 'Y' || playAgain == 'y') {
            continue;
        }

        char returnToMenu;
        cout << "Return to main menu? (Y/N): ";
        cin >> returnToMenu;
        return;
    }
}

// =========================
// Lottery Helpers
// =========================

vector<int> generateUnique(int count, int minVal, int maxVal) {
    vector<int> nums;
    while (static_cast<int>(nums.size()) < count) {
        int n = rand() % maxVal + minVal;
        if (find(nums.begin(), nums.end(), n) == nums.end()) {
            nums.push_back(n);
        }
    }
    return nums;
}

vector<int> getUserTicket() {
    vector<int> ticket;
    char choice;

    cout << "Would you like your ticket randomly generated? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        ticket = generateUnique(6, 1, 49);
        cout << "Your ticket was randomly generated.\n";
        return ticket;
    }

    cout << "Enter 6 UNIQUE numbers between 1 and 49:\n";
    int num;

    while (static_cast<int>(ticket.size()) < 6) {
        cout << "Number " << ticket.size() + 1 << ": ";
        cin >> num;

        if (num < 1 || num > 49) {
            cout << "Number must be between 1 and 49.\n";
        } else if (find(ticket.begin(), ticket.end(), num) != ticket.end()) {
            cout << "Duplicate number detected. Please enter a unique number.\n";
        } else {
            ticket.push_back(num);
        }
    }

    return ticket;
}

vector<int> generateRandomLine() {
    return generateUnique(6, 1, 49);
}

int compareLines(const vector<int>& line, const vector<int>& winning, int bonusNum) {
    int matches = 0;

    for (int n : line) {
        if (find(winning.begin(), winning.end(), n) != winning.end()) {
            matches++;
        }
    }

    if (find(line.begin(), line.end(), bonusNum) != line.end()) {
        matches++;
    }

    return matches;
}

string calculatePrize(int matches) {
    switch (matches) {
        case 6: return "$5,000,000";
        case 5: return "$250,000";
        case 4: return "$10,000";
        case 3: return "$1,000";
        default: return "Better luck next time!";
    }
}

void writeTicketToFile(const vector<int>& ticket,
                       const vector<int>& bonusLine,
                       const vector<int>& winning,
                       int bonusNum,
                       int resultTicket,
                       int resultBonus) {
    ofstream file("lottery_ticket.txt");

    file << "Your Ticket: ";
    for (int n : ticket) file << n << " ";
    file << "\nBonus Line: ";
    for (int n : bonusLine) file << n << " ";
    file << "\nWinning Numbers: ";
    for (int n : winning) file << n << " ";
    file << "\nBonus Number: " << bonusNum << "\n";

    file << "\nYour ticket matched " << resultTicket << " numbers.\n";
    file << "Prize: " << calculatePrize(resultTicket) << "\n";

    file << "\nBonus line matched " << resultBonus << " numbers.\n";
    file << "Prize: " << calculatePrize(resultBonus) << "\n";

    file.close();
}

// =========================
// Game 3: Lottery Game
// =========================

void playLotteryGame() {
    char playAgain = 'Y';

    while (playAgain == 'Y' || playAgain == 'y') {
        cout << "\n--- Lottery Game: Vector Victory Edition ---\n\n";

        vector<int> ticket = getUserTicket();
        vector<int> bonusLine = generateRandomLine();
        vector<int> winning = generateUnique(6, 1, 49);

        int bonusNum = rand() % 49 + 1;
        while (find(winning.begin(), winning.end(), bonusNum) != winning.end()) {
            bonusNum = rand() % 49 + 1;
        }

        int resultTicket = compareLines(ticket, winning, bonusNum);
        int resultBonus  = compareLines(bonusLine, winning, bonusNum);

        cout << "\nYour Ticket: ";
        for (int n : ticket) cout << n << " ";
        cout << "\nBonus Line: ";
        for (int n : bonusLine) cout << n << " ";
        cout << "\nWinning Numbers: ";
        for (int n : winning) cout << n << " ";
        cout << "\nBonus Number: " << bonusNum << "\n\n";

        cout << "Your ticket matched " << resultTicket << " numbers.\n";
        cout << "Prize: " << calculatePrize(resultTicket) << "\n\n";

        cout << "Bonus line matched " << resultBonus << " numbers.\n";
        cout << "Prize: " << calculatePrize(resultBonus) << "\n\n";

        writeTicketToFile(ticket, bonusLine, winning, bonusNum, resultTicket, resultBonus);

        cout << "Results have been saved to lottery_ticket.txt.\n";

        cout << "\nWould you like to buy another lottery ticket? (Y/N): ";
        cin >> playAgain;

        if (playAgain == 'Y' || playAgain == 'y') {
            continue;
        }

        char returnToMenu;
        cout << "Return to main menu? (Y/N): ";
        cin >> returnToMenu;
        return;
    }
}

// =========================
// Name Guess Helpers
// =========================

bool compareNames(const string& guess, const string& answer) {
    return guess == answer;
}

string getMatchedLetters(const string& guess, const string& answer) {
    string result = "";
    for (size_t i = 0; i < answer.length(); i++) {
        if (i < guess.length() && guess[i] == answer[i]) {
            result += guess[i];
        } else {
            result += '_';
        }
        if (i < answer.length() - 1) {
            result += ' ';
        }
    }
    return result;
}

// =========================
// Game 4: Guessing Name Game
// =========================

void playNameGuessingGame() {
    cout << "\n=== Guessing Name: Figuring Out the Name Edition ===\n\n";

    vector<string> names = {
        "Ali",
        "Mariam",
        "Fayzan",
        "Diwan",
        "Jessica",
        "Benjamin",
        "Alexander"
    };

    char playAgain = 'Y';

    while (playAgain == 'Y' || playAgain == 'y') {
        cout << "Choose an option:\n";
        cout << "1. Random name\n";
        cout << "2. Choose name length (3–10 letters)\n";
        cout << "Enter choice: ";

        int choice;
        cin >> choice;

        string selectedName;

        if (choice == 1) {
            selectedName = names[rand() % names.size()];
        } else if (choice == 2) {
            int lengthChoice;
            cout << "Enter desired name length (3–10): ";
            cin >> lengthChoice;

            vector<string> filtered;
            for (const string& n : names) {
                if (static_cast<int>(n.length()) == lengthChoice) {
                    filtered.push_back(n);
                }
            }

            if (filtered.empty()) {
                cout << "No names of that length. Selecting random instead.\n";
                selectedName = names[rand() % names.size()];
            } else {
                selectedName = filtered[rand() % filtered.size()];
            }
        } else {
            cout << "Invalid choice. Selecting random name.\n";
            selectedName = names[rand() % names.size()];
        }

        cin.ignore();

        bool guessedCorrectly = false;
        char tryAgain = 'Y';

        while (tryAgain == 'Y' || tryAgain == 'y') {
            cout << "\nGuess the name (" << selectedName.length() << " letters): ";
            string guess;
            getline(cin, guess);

            if (compareNames(guess, selectedName)) {
                cout << "\nCorrect! The name was: " << selectedName << "\n";
                guessedCorrectly = true;
                break;
            } else {
                cout << "Not quite. Matching letters in correct positions:\n";
                cout << getMatchedLetters(guess, selectedName) << "\n";
            }

            cout << "Would you like to try guessing this name again? (Y/N): ";
            cin >> tryAgain;
            cin.ignore();
        }

        cout << "\nWould you like to play the Guessing Name game again? (Y/N): ";
        cin >> playAgain;

        if (playAgain == 'Y' || playAgain == 'y') {
            continue;
        }

        char returnToMenu;
        cout << "Return to main menu? (Y/N): ";
        cin >> returnToMenu;
        return;
    }
}

// =========================
// Credits Screen
// =========================

void showCredits() {
    char viewAgain = 'Y';

    while (viewAgain == 'Y' || viewAgain == 'y') {
        cout << "\n=====================================\n";
        cout << "               CREDITS\n";
        cout << "=====================================\n\n";

        cout << "[ Mini Arcade - Version 4.1 ]\n\n";
        cout << "Developed by: Group 9\n";
        cout << "Lead Programmer: Mariam Mueen\n";
        cout << "Programmer: Fayzabanu Diwan\n\n";
        cout << "Thank you for playing the Mini Arcade!\n\n";

        cout << "Would you like to view the credits again? (Y/N): ";
        cin >> viewAgain;

        if (viewAgain == 'Y' || viewAgain == 'y') {
            continue;
        }

        char returnToMenu;
        cout << "Return to main menu? (Y/N): ";
        cin >> returnToMenu;
        return;
    }
}
