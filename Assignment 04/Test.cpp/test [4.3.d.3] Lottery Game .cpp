#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
#include <ctime>     // Added for timestamp
using namespace std;

// Helper to convert names into clean filename format
// "Mariam", "Mueen" -> "lotto_mariam_mueen.txt"
string buildFilename(const PlayerName& player) {

    auto clean = [&](string s) {
        string out;
        for (char c : s) {
            if (c == ' ') out += '_';
            else out += tolower(c);
        }
        return out;
    };

    string first = clean(player.first);
    string last  = clean(player.last);

    return "lotto_" + first + "_" + last + ".txt";
}

// function to generate a line of unique random numbers
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

// Get player ticket input with strong validation
vector<int> getUserTicket() {
    vector<int> ticket;
    int num;

    cout << "Enter 6 UNIQUE numbers between 1 and 49:\n";

    while (static_cast<int>(ticket.size()) < 6) {
        cout << "Number " << (ticket.size() + 1) << ": ";

        // FIX: Strong numeric validation
        while (!(cin >> num)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Enter WHOLE NUMBER between 1–49: ";
        }

        if (num < 1 || num > 49) {
            cout << "Number must be 1–49.\n";
        }
        else if (find(ticket.begin(), ticket.end(), num) != ticket.end()) {
            cout << "Duplicate. Enter a unique number.\n";
        }
        else {
            ticket.push_back(num);
        }
    }
    return ticket;
}

// Bonus only affects 5-match tier
int compareLines(const vector<int>& line, const vector<int>& winning) {
    int matches = 0;
    for (int n : line) {
        if (find(winning.begin(), winning.end(), n) != winning.end()) {
            matches++;
        }
    }
    return matches;
}

bool hasBonus(const vector<int>& line, int bonusNum) {
    return find(line.begin(), line.end(), bonusNum) != line.end();
}

string calculatePrize(int matches, bool bonusHit) {
    if (matches == 6 && bonusHit) return "$5,250,000";   // 6 matches + bonus
    if (matches == 6) return "$5,000,000";               // 6 matches
    if (matches == 5 && bonusHit) return "$250,000";     // 5 matches + bonus
    if (matches == 5) return "$50,000";                  // 5 matches
    if (matches == 4) return "$10,000";                  // 4 matches
    if (matches == 3) return "$1,000";                   // 3 matches
    return "Better luck next time!";
}

// FIX: FILE FUNCTION TO SAVE RESULTS PER PLAYER
// Append session results to player's file
void appendToPlayerFile(const string& filename,
                        const vector<int>& ticket,
                        const vector<int>& extraTicket,
                        const vector<int>& winning,
                        int bonusNum,
                        int resultTicket,
                        bool bonusHitTicket,
                        int resultExtra,
                        bool bonusHitExtra)
{
    ofstream file(filename, ios::app); // append mode

    // *** Timestamp block ***
    time_t now = time(0);
    tm* local = localtime(&now);

    file << "\n========================================\n";
    file << " Lottery Results — "
         << (local->tm_year + 1900) << "-"
         << (local->tm_mon + 1) << "-"
         << local->tm_mday << " "
         << local->tm_hour << ":"
         << local->tm_min << ":"
         << local->tm_sec
         << "\n========================================\n";

    file << "Your Ticket: ";
    for (int n : ticket) file << n << " ";

    if (!extraTicket.empty()) {
        file << "\nExtra Ticket: ";
        for (int n : extraTicket) file << n << " ";
    }

    file << "\nWinning Numbers: ";
    for (int n : winning) file << n << " ";

    file << "\nBonus Number: " << bonusNum << "\n";

    file << "\nYour ticket matched " << resultTicket << " numbers.\n";
    file << "Prize: " << calculatePrize(resultTicket, bonusHitTicket) << "\n";

    if (!extraTicket.empty()) {
        file << "\nYour extra ticket matched " << resultExtra << " numbers.\n";
        file << "Prize: " << calculatePrize(resultExtra, bonusHitExtra) << "\n";
    }

    file << "----------------------------------------\n";

    file.close();
}

// UPDATED LOTTERY GAME (MAIN FUNCTION)
void playLotteryGame(const PlayerName& player) {

    char playAgain = 'Y';
    string filename = buildFilename(player);

    while (playAgain == 'Y' || playAgain == 'y') {

        cout << "\n--- Lottery Game: Vector Victory Edition ---\n\n";

        // Player's main ticket
        vector<int> ticket = getUserTicket();

        // Ask if they want an EXTRA random ticket
        char extraChoice;
        vector<int> extraTicket;

        cout << "\nWould you like an extra randomly-generated ticket? (Y/N): ";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (true) {
            cin >> extraChoice;

            if (extraChoice=='Y'||extraChoice=='y'||extraChoice=='N'||extraChoice=='n')
                break;

            cout << "Please enter Y or N only: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (extraChoice == 'Y' || extraChoice == 'y') {
            extraTicket = generateUnique(6, 1, 49);
        }

        // Generate winning numbers
        vector<int> winning = generateUnique(6, 1, 49);

        // Bonus number (must not be in winning numbers)
        int bonusNum = rand() % 49 + 1;
        while (find(winning.begin(), winning.end(), bonusNum) != winning.end()) {
            bonusNum = rand() % 49 + 1;
        }

        // Sort everything for cleaner display
        sort(ticket.begin(), ticket.end());
        sort(winning.begin(), winning.end());
        if (!extraTicket.empty()) sort(extraTicket.begin(), extraTicket.end());

        // Compare results
        int resultTicket = compareLines(ticket, winning);
        bool bonusHitTicket = hasBonus(ticket, bonusNum);

        int resultExtra = 0;
        bool bonusHitExtra = false;

        if (!extraTicket.empty()) {
            resultExtra = compareLines(extraTicket, winning);
            bonusHitExtra = hasBonus(extraTicket, bonusNum);
        }

        // DISPLAY RESULTS
        cout << "\nYour Ticket: ";
        for (int n : ticket) cout << n << " ";

        if (!extraTicket.empty()) {
            cout << "\nExtra Ticket: ";
            for (int n : extraTicket) cout << n << " ";
        }

        cout << "\nWinning Numbers: ";
        for (int n : winning) cout << n << " ";

        cout << "\nBonus Number: " << bonusNum << "\n\n";

        cout << "Your ticket matched " << resultTicket << " numbers.\n";
        cout << "Prize: " << calculatePrize(resultTicket, bonusHitTicket) << "\n\n";

        if (!extraTicket.empty()) {
            cout << "Your extra ticket matched " << resultExtra << " numbers.\n";
            cout << "Prize: " << calculatePrize(resultExtra, bonusHitExtra) << "\n\n";
        }

        // Append session to file
        appendToPlayerFile(filename,
                           ticket, extraTicket,
                           winning,
                           bonusNum,
                           resultTicket, bonusHitTicket,
                           resultExtra, bonusHitExtra);

        cout << "Results saved to: " << filename << "\n";

        // Replay?
        cout << "\nBuy another lottery ticket? (Y/N): ";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (true) {
            cin >> playAgain;

            if (playAgain=='Y'||playAgain=='y'||playAgain=='N'||playAgain=='n')
                break;

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
