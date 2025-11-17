// main_type.cpp - Mini Arcade with Type() function for text output.

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Central text output function.
// This function is used instead of cout for main messages,
// so that the display style can be changed in one place if needed.
void Type(const string& text) {
    cout << text;
}

// Prototypes
void playGuessingGame();
void playDiceGame();
void playLotteryGame();
void playNameGuessingGame();
void showCredits();

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

    srand(static_cast<unsigned int>(time(0)));

    do {
        Type("\n==============================\n");
        Type("         MINI ARCADE\n");
        Type("==============================\n");
        Type("1. Guessing Game (Numbers)\n");
        Type("2. Dice Game (Match to Win)\n");
        Type("3. Lottery Game (Vector Victory)\n");
        Type("4. Guessing Name Game\n");
        Type("5. Credits\n");
        Type("6. Exit\n");
        Type("Enter your choice (1-6): ");

        cin >> choice;

        if (choice < 1 || choice > 6) {
            Type("Invalid choice. Please select a number between 1 and 6.\n");
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
                playLotteryGame();
                break;
            case 4:
                playNameGuessingGame();
                break;
            case 5:
                showCredits();
                break;
            case 6:
                Type("Exiting the Mini Arcade. Goodbye!\n");
                break;
        }

    } while (choice != 6);

    return 0;
}

// Game 1 using Type()

void playGuessingGame() {
    char playAgain = 'Y';

    while (playAgain == 'Y' || playAgain == 'y') {
        Type("\n--- Guessing Game ---\n\n");

        int secretNumber;
        int guess;
        int attempts = 7;

        secretNumber = rand() % 100 + 1;

        Type("I am thinking of a number between 1 and 100.\n");
        cout << "You have " << attempts << " attempts.\n\n";

        bool guessed = false;

        for (int i = 1; i <= attempts; i++) {
            cout << "Attempt " << i << "/" << attempts << ": ";
            cin >> guess;

            if (guess < 1 || guess > 100) {
                Type("Please enter a number between 1 and 100.\n");
                i--;
                continue;
            }

            if (guess == secretNumber) {
                cout << "\nCorrect! The number was " << secretNumber << ".\n";
                guessed = true;
                break;
            } else if (guess < secretNumber) {
                Type("Too low. Try a higher number.\n\n");
            } else {
                Type("Too high. Try a lower number.\n\n");
            }
        }

        if (!guessed) {
            cout << "You are out of attempts. The number was " << secretNumber << ".\n";
        }

        Type("\nWould you like to play the Guessing Game again? (Y/N): ");
        cin >> playAgain;

        if (playAgain == 'Y' || playAgain == 'y') {
            continue;
        }

        char returnToMenu;
        Type("Return to main menu? (Y/N): ");
        cin >> returnToMenu;
        return;
    }
}

// Game 2 using Type()

void playDiceGame() {
    char playAgain = 'Y';

    while (playAgain == 'Y' || playAgain == 'y') {
        Type("\n--- Dice Game ---\n\n");

        int die1 = rand() % 6 + 1;
        int die2 = rand() % 6 + 1;

        Type("Rolling the dice...\n\n");
        cout << "Die 1: " << die1 << "\n";
        cout << "Die 2: " << die2 << "\n\n";

        if (die1 == die2) {
            Type("They match! You win!\n");
        } else {
            Type("They do not match. You lose.\n");
        }

        Type("\nWould you like to roll again? (Y/N): ");
        cin >> playAgain;

        if (playAgain == 'Y' || playAgain == 'y') {
            continue;
        }

        char returnToMenu;
        Type("Return to main menu? (Y/N): ");
        cin >> returnToMenu;
        return;
    }
}

// Lottery helpers with normal cout (they focus on data, not styling)

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

    Type("Would you like your ticket randomly generated? (Y/N): ");
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        ticket = generateUnique(6, 1, 49);
        Type("Your ticket was randomly generated.\n");
        return ticket;
    }

    Type("Enter 6 UNIQUE numbers between 1 and 49:\n");
    int num;

    while (static_cast<int>(ticket.size()) < 6) {
        cout << "Number " << ticket.size() + 1 << ": ";
        cin >> num;

        if (num < 1 || num > 49) {
            Type("Number must be between 1 and 49.\n");
        } else if (find(ticket.begin(), ticket.end(), num) != ticket.end()) {
            Type("Duplicate number detected. Please enter a unique number.\n");
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

// Game 3 using Type where it’s text-based

void playLotteryGame() {
    char playAgain = 'Y';

    while (playAgain == 'Y' || playAgain == 'y') {
        Type("\n--- Lottery Game: Vector Victory Edition ---\n\n");

        vector<int> ticket = getUserTicket();
        vector<int> bonusLine = generateRandomLine();
        vector<int> winning = generateUnique(6, 1, 49);

        int bonusNum = rand() % 49 + 1;
        while (find(winning.begin(), winning.end(), bonusNum) != winning.end()) {
            bonusNum = rand() % 49 + 1;
        }

        Type("\nYour Ticket: ");
        for (int n : ticket) cout << n << " ";
        Type("\nBonus Line: ");
        for (int n : bonusLine) cout << n << " ";
        Type("\nWinning Numbers: ");
        for (int n : winning) cout << n << " ";
        cout << "\nBonus Number: " << bonusNum << "\n\n";

        int resultTicket = compareLines(ticket, winning, bonusNum);
        int resultBonus  = compareLines(bonusLine, winning, bonusNum);

        cout << "Your ticket matched " << resultTicket << " numbers.\n";
        cout << "Prize: " << calculatePrize(resultTicket) << "\n\n";

        cout << "Bonus line matched " << resultBonus << " numbers.\n";
        cout << "Prize: " << calculatePrize(resultBonus) << "\n\n";

        writeTicketToFile(ticket, bonusLine, winning, bonusNum, resultTicket, resultBonus);

        Type("Results have been saved to lottery_ticket.txt.\n");

        Type("\nWould you like to buy another lottery ticket? (Y/N): ");
        cin >> playAgain;

        if (playAgain == 'Y' || playAgain == 'y') {
            continue;
        }

        char returnToMenu;
        Type("Return to main menu? (Y/N): ");
        cin >> returnToMenu;
        return;
    }
}

// Name helpers and game, using Type for messages

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

void playNameGuessingGame() {
    Type("\n=== Guessing Name: Figuring Out the Name Edition ===\n\n");

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
        Type("Choose an option:\n");
        Type("1. Random name\n");
        Type("2. Choose name length (3–10 letters)\n");
        Type("Enter choice: ");

        int choice;
        cin >> choice;

        string selectedName;

        if (choice == 1) {
            selectedName = names[rand() % names.size()];
        } else if (choice == 2) {
            int lengthChoice;
            Type("Enter desired name length (3–10): ");
            cin >> lengthChoice;

            vector<string> filtered;
            for (const string& n : names) {
                if (static_cast<int>(n.length()) == lengthChoice) {
                    filtered.push_back(n);
                }
            }

            if (filtered.empty()) {
                Type("No names of that length. Selecting random instead.\n");
                selectedName = names[rand() % names.size()];
            } else {
                selectedName = filtered[rand() % filtered.size()];
            }
        } else {
            Type("Invalid choice. Selecting random name.\n");
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
                Type("Not quite. Matching letters in correct positions:\n");
                cout << getMatchedLetters(guess, selectedName) << "\n";
            }

            Type("Would you like to try guessing this name again? (Y/N): ");
            cin >> tryAgain;
            cin.ignore();
        }

        Type("\nWould you like to play the Guessing Name game again? (Y/N): ");
        cin >> playAgain;

        if (playAgain == 'Y' || playAgain == 'y') {
            continue;
        }

        char returnToMenu;
        Type("Return to main menu? (Y/N): ");
        cin >> returnToMenu;
        return;
    }
}

// Credits using Type

void showCredits() {
    char viewAgain = 'Y';

    while (viewAgain == 'Y' || viewAgain == 'y') {
        Type("\n=====================================\n");
        Type("               CREDITS\n");
        Type("=====================================\n\n");

        Type("[ Mini Arcade - Version 4.1 ]\n\n");
        Type("Developed by: Group 9\n");
        Type("Lead Programmer: Mariam Mueen\n");
        Type("Programmer: Fayzabanu Diwan\n\n");
        Type("Thank you for playing the Mini Arcade!\n\n");

        Type("Would you like to view the credits again? (Y/N): ");
        cin >> viewAgain;

        if (viewAgain == 'Y' || viewAgain == 'y') {
            continue;
        }

        char returnToMenu;
        Type("Return to main menu? (Y/N): ");
        cin >> returnToMenu;
        return;
    }
}
