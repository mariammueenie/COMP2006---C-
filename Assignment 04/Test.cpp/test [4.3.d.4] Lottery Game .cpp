#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <limits>
#include <ctime>
#include <string>
#include <sstream>
using namespace std;

/*
===========================================================
 BIG FIXXX: NEW INPUT SYSTEM FOR LOTTERY GAME
 ----------------------------------------------------------
 This replaces all old uses of:
    cin >> num

 PROBLEM:
    cin >> allows:
        "10 20 30" → all 3 values get consumed
        leftover numbers pollute the next input
        letters or symbols break the input stream

 FIX:
    EXACT SAME LOGIC AS MAIN MENU:
        1. Read entire line using getline()
        2. Trim whitespace
        3. Ensure ONLY digits 0–9 exist
        4. Convert using stoi()
        REFERENCE: 
        5. Range-check (1–49)
        6. Accept ONE and ONLY ONE integer per input line
===========================================================
*/

// FIX: Build filename from player name
// Helper to convert names into clean filename format
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

// ----------------------------------------------------
vector<int> generateUnique(int count, int minVal, int maxVal) {
    vector<int> nums;

    while ((int)nums.size() < count) {
        int n = rand() % maxVal + minVal;
        if (find(nums.begin(), nums.end(), n) == nums.end()) {
            nums.push_back(n);
        }
    }
    return nums;
}

// STRICT SINGLE-INTEGER VALIDATION
int getSingleInteger(const string& prompt, int minV, int maxV) {

    while (true) {
        cout << prompt;

        string line;
        getline(cin, line);

        // Trim whitespace
        while (!line.empty() && isspace(line.front()))
            line.erase(0, 1);
        while (!line.empty() && isspace(line.back()))
            line.pop_back();

        if (line.empty()) {
            cout << "Invalid input. Please enter ONE whole number.\n";
            continue;
        }

        // Ensure all characters are digits
        for (size_t i = 0; i < line.length(); i++) {
            if (!isdigit(line[i])) {
                cout << "Invalid input. ONLY digits 0–9 allowed.\n";
                line.clear();
                break;
            }
        }
        if (line.empty()) continue;

        int value = stoi(line);

        if (value < minV || value > maxV) {
            cout << "Number must be between " << minV << " and " << maxV << ".\n";
            continue;
        }

        return value;
    }
}

// ----------------------------------------------------
vector<int> getUserTicket() {
    vector<int> ticket;

    cout << "Enter 6 UNIQUE numbers between 1 and 49.\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    while ((int)ticket.size() < 6) {

        // EXACTLY ONE INTEGER PER INPUT
        int num = getSingleInteger(
            "Number " + to_string(ticket.size() + 1) + ": ",
            1, 49
        );

        if (find(ticket.begin(), ticket.end(), num) != ticket.end()) {
            cout << "Duplicate number. Enter a UNIQUE number.\n";
            continue;
        }

        ticket.push_back(num);
    }
    return ticket;
}

// ----------------------------------------------------
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
    if (matches == 6 && bonusHit) return "$5,250,000";
    if (matches == 6) return "$5,000,000";
    if (matches == 5 && bonusHit) return "$250,000";
    if (matches == 5) return "$50,000";
    if (matches == 4) return "$10,000";
    if (matches == 3) return "$1,000";
    return "Better luck next time!";
}

// ----------------------------------------------------
void appendToPlayerFile(
    const string& filename,
    const vector<int>& ticket,
    const vector<int>& extraTicket,
    const vector<int>& winning,
    int bonusNum,
    int resultTicket,
    bool bonusHitTicket,
    int resultExtra,
    bool bonusHitExtra)
{
    ofstream file(filename, ios::app);

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
}

void playLotteryGame(const PlayerName& player) {

    char playAgain = 'Y';
    string filename = buildFilename(player);

    while (playAgain == 'Y' || playAgain == 'y') {

        cout << "\n--- Lottery Game: Vector Victory Edition ---\n\n";

        vector<int> ticket = getUserTicket();

        char extraChoice;
        vector<int> extraTicket;

        cout << "\nWould you like an extra randomly-generated ticket? (Y/N): ";
        cin >> extraChoice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (extraChoice!='Y'&&extraChoice!='y'&&
               extraChoice!='N'&&extraChoice!='n') {

            cout << "Please enter Y or N only: ";
            cin >> extraChoice;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (extraChoice == 'Y' || extraChoice == 'y')
            extraTicket = generateUnique(6, 1, 49);

        vector<int> winning = generateUnique(6, 1, 49);

        int bonusNum = rand() % 49 + 1;
        while (find(winning.begin(), winning.end(), bonusNum) != winning.end())
            bonusNum = rand() % 49 + 1;

        sort(ticket.begin(), ticket.end());
        sort(winning.begin(), winning.end());
        if (!extraTicket.empty()) sort(extraTicket.begin(), extraTicket.end());

        int resultTicket = compareLines(ticket, winning);
        bool bonusHitTicket = hasBonus(ticket, bonusNum);

        int resultExtra = 0;
        bool bonusHitExtra = false;

        if (!extraTicket.empty()) {
            resultExtra = compareLines(extraTicket, winning);
            bonusHitExtra = hasBonus(extraTicket, bonusNum);
        }

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

        // FIX: changed indentation
        appendToPlayerFile(
            filename,
            ticket,
            extraTicket,
            winning,
            bonusNum,
            resultTicket,
            bonusHitTicket,
            resultExtra,
            bonusHitExtra
        );

        cout << "Results saved to: " << filename << "\n";

        cout << "\nBuy another lottery ticket? (Y/N): ";
        cin >> playAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (playAgain!='Y'&&playAgain!='y'&&
               playAgain!='N'&&playAgain!='n') {

            cout << "Please enter Y or N only: ";
            cin >> playAgain;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        if (playAgain=='N'||playAgain=='n') {
            cout << "\nReturning to main menu...\n";
            return;
        }
    }
}

// CHANGES TO MAKE
// TODO: Fix file writing system to either make a new file each time, or append the text
//       file at the top, instead of the bottom. Also maybe add some decoration to lines
//       where a user has won money?
// TODO: RESULTS SHOULD BE FORMATTED TO LOOK NICER, and bonus number too 
// TODO: Allow user to manually enter a bonus number, and THEN ask if they would like an extra ticket
// TODO: https://cplusplus.com/doc/tutorial/files/
// TODO: Add game instructions from assignment 03
// TODO: BONUS NUMBER COUNTS AS A REGULAR MATCH DUMMY