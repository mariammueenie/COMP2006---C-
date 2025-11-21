#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
using namespace std;

// Helper function to generate a line of unique random numbers
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

// Player ticket input, with SAFETY UPGRADES applied
vector<int> getUserTicket() {
    vector<int> ticket;
    char choice;

    // FIX: Clear leftover newline before reading char input
    // Prevents skipped prompts when previous input left '\n'
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Would you like your ticket randomly generated? (Y/N): ";


    // FIX: Full safe Y/N validation
    // Prevents accidental skipping/exiting on garbage input
    while (true) {
        cin >> choice;

        if (choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n') {
            break;
        }

        cout << "Please enter Y or N only: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    if (choice == 'Y' || choice == 'y') {
        ticket = generateUnique(6, 1, 49);
        cout << "Your ticket was randomly generated.\n";
        return ticket;
    }

    cout << "Enter 6 UNIQUE numbers between 1 and 49:\n";

    // FIX: Strong numeric input validation for manual ticket entry
    // Handles letters, symbols, decimals, blank input, etc.
    int num;
    while (static_cast<int>(ticket.size()) < 6) {
        cout << "Number " << ticket.size() + 1 << ": ";

        while (!(cin >> num)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter a WHOLE NUMBER between 1 and 49: ";
        }

        if (num < 1 || num > 49) {
            cout << "Number must be between 1 and 49.\n";
        }
        else if (find(ticket.begin(), ticket.end(), num) != ticket.end()) {
            cout << "Duplicate number detected. Please enter a unique number.\n";
        }
        else {
            ticket.push_back(num);
        }
    }

    return ticket;
}

// Bonus line generator
vector<int> generateRandomLine() {
    return generateUnique(6, 1, 49);
}

// Compare line against winning numbers, WITH UPDATED BONUS HANDLING
int compareLines(const vector<int>& line, const vector<int>& winning, int bonusNum) {
    int matches = 0;

    for (int n : line) {
        if (find(winning.begin(), winning.end(), n) != winning.end()) {
            matches++;
        }
    }

    // FIX: Bonus number is treated ONLY as a bonus
    // Not as a regular match. Not added to match count

    return matches;
}

// Bonus handling (bonus match calculated separately)
bool hasBonus(const vector<int>& line, int bonusNum) {
    return find(line.begin(), line.end(), bonusNum) != line.end();
}

string calculatePrize(int matches, bool bonusHit) {
    // FIX: Bonus used to affect prize only when matches == 5
    // Emulates MEGA Millions / Lotto Max style bonus rule

    if (matches == 6) return "$5,000,000";
    if (matches == 5 && bonusHit) return "$250,000";    // Bonus makes 5+bonus win
    if (matches == 5) return "$50,000";                 // Without bonus
    if (matches == 4) return "$10,000";
    if (matches == 3) return "$1,000";
    return "Better luck next time!";
}

void writeTicketToFile(
    const vector<int>& ticket,
    const vector<int>& bonusLine,
    const vector<int>& winning,
    int bonusNum,
    int resultTicket,
    bool bonusHitTicket,
    int resultBonus,
    bool bonusHitBonus)
{
    ofstream file("lottery_ticket.txt");

    file << "Your Ticket: ";
    for (int n : ticket) file << n << " ";
    file << "\nBonus Line: ";
    for (int n : bonusLine) file << n << " ";
    file << "\nWinning Numbers: ";
    for (int n : winning) file << n << " ";
    file << "\nBonus Number: " << bonusNum << "\n";

    file << "\nYour ticket matched " << resultTicket << " numbers.\n";
    file << "Prize: " << calculatePrize(resultTicket, bonusHitTicket) << "\n";

    file << "\nBonus line matched " << resultBonus << " numbers.\n";
    file << "Prize: " << calculatePrize(resultBonus, bonusHitBonus) << "\n";
}

void playLotteryGame() {
    char playAgain = 'Y';

    while (playAgain == 'Y' || playAgain == 'y') {

        cout << "\n--- Lottery Game: Vector Victory Edition ---\n\n";

        vector<int> ticket = getUserTicket();
        vector<int> bonusLine = generateRandomLine();
        vector<int> winning = generateUnique(6, 1, 49);

        // Generate bonus number not included in winning numbers
        int bonusNum = rand() % 49 + 1;
        while (find(winning.begin(), winning.end(), bonusNum) != winning.end()) {
            bonusNum = rand() % 49 + 1;
        }

        // Compare matches WITHOUT counting bonus
        int resultTicket = compareLines(ticket, winning, bonusNum);
        int resultBonus  = compareLines(bonusLine, winning, bonusNum);

        // Bonus effects applied separately
        bool bonusHitTicket = hasBonus(ticket, bonusNum);
        bool bonusHitBonus  = hasBonus(bonusLine, bonusNum);

        // =============================================
        // FIX: Sort all number lists before displaying
        // Improves readability
        sort(ticket.begin(), ticket.end());
        sort(bonusLine.begin(), bonusLine.end());
        sort(winning.begin(), winning.end());

        cout << "\nYour Ticket: ";
        for (int n : ticket) cout << n << " ";
        cout << "\nBonus Line: ";
        for (int n : bonusLine) cout << n << " ";
        cout << "\nWinning Numbers: ";
        for (int n : winning) cout << n << " ";
        cout << "\nBonus Number: " << bonusNum << "\n\n";

        cout << "Your ticket matched " << resultTicket << " numbers.\n";
        cout << "Prize: " << calculatePrize(resultTicket, bonusHitTicket) << "\n\n";

        cout << "Bonus line matched " << resultBonus << " numbers.\n";
        cout << "Prize: " << calculatePrize(resultBonus, bonusHitBonus) << "\n\n";

        writeTicketToFile(ticket, 
            bonusLine, winning, bonusNum,
            resultTicket, bonusHitTicket,
            resultBonus, bonusHitBonus);
        cout << "Results have been saved to lottery_ticket.txt.\n";

        // FIX: Streamlined replay logic (ONLY ONE Y/N)
        cout << "\nBuy another lottery ticket? (Y/N): ";

        // FIX: Safe Y/N validation
        // Prevents accidental exit from garbage input.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (true) {
            cin >> playAgain;
            if (playAgain == 'Y' || playAgain == 'y' ||
                playAgain == 'N' || playAgain == 'n') {
                break;
            }
            cout << "Please enter Y or N only: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (playAgain == 'N' || playAgain == 'n') {
            cout << "\nReturning to main menu...\n";
            return;
        }
    }
}

// CHANGES TO MAKE
// TODO: more validation fixes 
// TODO: make output of results prettier 
// TODO: need to comment code better 
// TODO: test everything again 0_0
// TODO: output file function needs to be fixed, and name variable needs to be global to work here!!