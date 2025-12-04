#include <iostream>
#include <cstdlib>      // rand(), srand()
#include <ctime>        // time()
#include <limits>       // numeric_limits
#include <string>       // string
#include <sstream>      // stringstream / stoi references (future-safe)
#include <vector>       // ONLY for lottery game (allowed there)
#include <iomanip>      // for setw, left, right (Murach-style formatting)
#include <algorithm>    // sort, find
#include <fstream>      // file output in lottery game
#include <cctype>       // isalpha, isspace, tolower, isdigit
#include <thread>       // for dice rolling effect (sleep)
#include <chrono>       // for milliseconds (sleep)
#include <ctime>        // for date/time()

// Headers
#include "../include/LotteryGame.h"
#include "../include/ArcadeGlobals.h"

namespace arcade {

// =========================================================
// Lottery Game — Vector Victory
// =========================================================


// =========================================================
// Helper: filename builder from PlayerName
// =========================================================
string buildFilename(const PlayerName& playerRef) {

    auto clean = [&](string s) {
        string out;
        for (char c : s) {
            if (c == ' ')
                out += '_';
            else
                out += static_cast<char>(tolower(static_cast<unsigned char>(c)));
        }
        return out;
    };

    string first = clean(playerRef.first);
    string last  = clean(playerRef.last);

    string base = "lotto_" + first + "_" + last + "_";

    int counter = 1;
    while (true) {
        string candidate = base + to_string(counter) + ".txt";
        ifstream test(candidate);
        if (!test.good()) return candidate;
        counter++;
    }
}


// =========================================================
// Helper: generateUnique()
// Generates <count> unique ints between minVal and maxVal
// =========================================================

//remove: Original version used 1–49 
//new:    Updated for Assignment 05 → 1–40

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

// =========================================================
// Helper: getSingleInteger()
// Reads EXACTLY one integer, validates range
// =========================================================

int getSingleInteger(const string& prompt, int minV, int maxV) {

    while (true) {
        cout << prompt;

        string line;
        getline(cin, line);

        while (!line.empty() && isspace(static_cast<unsigned char>(line.front())))
            line.erase(0, 1);
        while (!line.empty() && isspace(static_cast<unsigned char>(line.back())))
            line.pop_back();

        if (line.empty()) {
            cout << "Invalid input. Please enter ONE whole number.\n";
            continue;
        }

        bool bad = false;
        for (char c : line) {
            if (!isdigit(static_cast<unsigned char>(c))) {
                bad = true;
                break;
            }
        }

        if (bad) {
            //new: 1-40, NOT 1-49
            cout << "Invalid input. ONLY integers " << minV << "-" << maxV << " allowed.\n";
            continue;
        }

        int value = stoi(line);

        if (value < minV || value > maxV) {
            cout << "Number must be between " << minV << " and " << maxV << ".\n";
            continue;
        }

        return value;
    }
}

// =========================================================
// Helper: getUserTicket()
// User enters 6 unique numbers between 1 and 40
// Assignment 05 change, no longer 1--49
// =========================================================

vector<int> getUserTicket() {
    vector<int> ticket;

    //remove: Old text said 1–49.
    //new:
    cout << "Enter 6 UNIQUE numbers between 1 and 40.\n";

    while ((int)ticket.size() < 6) {
        int num = getSingleInteger(
            "Number " + to_string(ticket.size() + 1) + ": ",
            1, 40
        );

        if (find(ticket.begin(), ticket.end(), num) != ticket.end()) {
            cout << "Duplicate number. Enter a UNIQUE number.\n";
            continue;
        }

        ticket.push_back(num);
    }
    return ticket;
}


// =========================================================
// Helper: compareLines() -> count REGULAR matches
// =========================================================

int compareLines(const vector<int>& line, const vector<int>& winning) {
    int matches = 0;
    for (int n : line) {
        if (find(winning.begin(), winning.end(), n) != winning.end()) {
            matches++;
        }
    }
    return matches;
}


// =========================================================
// Helper: hasBonus() -> check for BONUS number
// =========================================================

bool hasBonus(const vector<int>& line, int bonusNum) {
    return find(line.begin(), line.end(), bonusNum) != line.end();
}


// =========================================================
// REMOVE old calculatePrize()
// =========================================================

//remove: Old calculatePrize() merged bonus + regular prize incorrectly.
//remove: Assignment 05 requires SEPARATE prize streams.
//remove:
//
// string calculatePrize(int matches, bool bonusHit) {
//     if (matches == 6 && bonusHit) return "$5,250,000";
//     if (matches == 6) return "$5,000,000";
//     if (matches == 5 && bonusHit) return "$250,000";
//     if (matches == 5) return "$50,000";
//     if (matches == 4) return "$10,000";
//     if (matches == 3) return "$1,000";
//     return "Better luck next time!";
// }

//new: Replacement function will appear later, above playLotteryGame().
//new: This keeps helpers grouped cleanly before main logic.
// =========================================================
// Helper: appendToPlayerFile()
// Writes BOTH regular + bonus prizes
// =========================================================

// This will be upgraded, because it must now output:
//   Regular Prize
//   Bonus Prize
// For now, helper left intact.

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
    file << " Lottery Results - "
         << (local->tm_year + 1900) << "-"
         << (local->tm_mon + 1) << "-"
         << local->tm_mday << " "
         << local->tm_hour << ":"
         << local->tm_min << ":\n";
    file << "========================================\n";

    file << "Your Ticket: ";
    for (int n : ticket) file << n << " ";

    if (!extraTicket.empty()) {
        file << "\nExtra Ticket: ";
        for (int n : extraTicket) file << n << " ";
    }

    file << "\nWinning Numbers: ";
    for (int n : winning) file << n << " ";

    file << "\nBonus Number: " << bonusNum << "\n";

    //remove: Old prize output using calculatePrize() is outdated.
    //new: insert separate Regular/Bonus/TOTAL lines

    file << "\nYour ticket matched " << resultTicket << " numbers.\n";
    file << "(Prize output to be upgraded in Section 4)\n";

    if (!extraTicket.empty()) {
        file << "\nYour extra ticket matched " << resultExtra << " numbers.\n";
        file << "(Prize output to be upgraded in Section 4)\n";
    }
}

// ==========================================
// MAIN GAME LOOP FOR LOTTERY
// ==========================================
void playLotteryGame(const PlayerName& player)
{
    cout << "\n========================================\n";
    cout << "         Welcome to LOTTERY Game!\n";
    cout << "========================================\n";

    srand(static_cast<unsigned>(time(nullptr)));

    //remove: Outdated reference to 1–49 selection.
    //new:
    cout << "In this game, you will enter 6 UNIQUE numbers between 1 and 40\n";
    cout << "OR you may choose to have your numbers randomly generated.\n";
    cout << "After that, you may optionally receive TWO extra random bonus tickets.\n";

    // ==========================================
    // TICKET #1: User MUST choose manual or generated
    // ==========================================
    cout << "\nTicket #1 Setup\n";
    cout << "-----------------------------------------\n";

    string modeChoice;

    // user must choose 1 or 2
    while (true)
    {
        cout << "Choose how to create your first ticket:\n";
        cout << "  1 -> Enter your own 6 unique numbers (manual)\n";
        cout << "  2 -> System will generate 6 numbers for you (random)\n";
        cout << "Enter choice (1 or 2): ";

        getline(cin, modeChoice);

        if (modeChoice == "1" || modeChoice == "2")
            break;

        cout << "Invalid input. Please enter 1 or 2.\n";
    }

    vector<int> ticket1;

    if (modeChoice == "1")
    {
        //new:
        cout << "\nYou chose MANUAL entry.\n";
        ticket1 = getUserTicket();
    }
    else
    {
        //new:
        cout << "\nYou chose RANDOM generation.\n";
        ticket1 = generateUnique(6, 1, 40);
        sort(ticket1.begin(), ticket1.end());

        cout << "Your randomly generated Ticket #1 numbers are: ";
        for (int n : ticket1) cout << n << " ";
        cout << "\n";
    }

    // ==========================================
    // Ask user if they want 2 EXTRA TICKETS
    // Tickets #2 and #3 will be randomly generated
    // ==========================================
    cout << "\nWould you like TWO bonus tickets? (Y/N): ";

    string bonusChoice;
    getline(cin, bonusChoice);

    vector<int> ticket2; // empty unless user says Y
    vector<int> ticket3;

    if (!bonusChoice.empty() &&
        (bonusChoice == "Y" || bonusChoice == "y"))
    {
        //new:
        cout << "\nGenerating BONUS Ticket #2...\n";
        ticket2 = generateUnique(6, 1, 40);
        sort(ticket2.begin(), ticket2.end());

        cout << "Bonus Ticket #2 numbers -> ";
        for (int n : ticket2) cout << n << " ";
        cout << "\n";

        cout << "Generating BONUS Ticket #3...\n";
        ticket3 = generateUnique(6, 1, 40);
        sort(ticket3.begin(), ticket3.end());

        cout << "Bonus Ticket #3 numbers -> ";
        for (int n : ticket3) cout << n << " ";
        cout << "\n";
    }
    else
    {
        //new:
        cout << "\nNo bonus tickets selected.\n";
    }

// ==========================================
// Generate Winning Numbers + Bonus
// ==========================================

    //new: Create official winning line (6 unique numbers 1–40)
    vector<int> winning = generateUnique(6, 1, 40);
    sort(winning.begin(), winning.end());

    cout << "\n========================================\n";
    cout << "        OFFICIAL WINNING NUMBERS\n";
    cout << "========================================\n";

    cout << "Winning Numbers -> ";
    for (int n : winning) cout << n << " ";
    cout << "\n";

    //new: Generate BONUS number separate from winning
    int bonusNum;
    while (true)
    {
        int n = rand() % 40 + 1;
        if (find(winning.begin(), winning.end(), n) == winning.end()) {
            bonusNum = n;
            break;
        }
    }

    cout << "Bonus Number -> " << bonusNum << "\n";

    // ==========================================
    // Count matches for Ticket #1
    // ==========================================

    int matches1 = compareLines(ticket1, winning);
    bool bonusHit1 = hasBonus(ticket1, bonusNum);

    cout << "\n========================================\n";
    cout << "       RESULTS FOR TICKET #1\n";
    cout << "========================================\n";

    cout << "Ticket #1 numbers -> ";
    for (int n : ticket1) cout << n << " ";
    cout << "\n";

    cout << "Matches -> " << matches1 << "\n";

    if (bonusHit1)
        cout << "Bonus HIT -> +$333\n";
    else
        cout << "Bonus NOT hit.\n";

    //new: Regular Prize calculation
    int regularPrize1 = 0;
    if (matches1 == 6)      regularPrize1 = 5000000;
    else if (matches1 == 5) regularPrize1 = 50000;
    else if (matches1 == 4) regularPrize1 = 10000;
    else if (matches1 == 3) regularPrize1 = 1000;

    //new: Bonus prize added SEPARATELY
    int bonusPrize1 = bonusHit1 ? 333 : 0;

    int totalPrize1 = regularPrize1 + bonusPrize1;

    cout << "Regular Prize -> $" << regularPrize1 << "\n";
    cout << "Bonus Prize -> $" << bonusPrize1 << "\n";
    cout << "TOTAL -> $" << totalPrize1 << "\n";

    // ==========================================
    // If user selected bonus tickets, evaluate them
    // ==========================================

    int matches2 = 0, matches3 = 0;
    bool bonusHit2 = false, bonusHit3 = false;
    int regularPrize2 = 0, regularPrize3 = 0;
    int bonusPrize2 = 0, bonusPrize3 = 0;
    int totalPrize2 = 0, totalPrize3 = 0;

    if (!ticket2.empty())
    {
        // Ticket #2 matches
        matches2 = compareLines(ticket2, winning);
        bonusHit2 = hasBonus(ticket2, bonusNum);

        // Regular prize for #2
        if (matches2 == 6)      regularPrize2 = 5000000;
        else if (matches2 == 5) regularPrize2 = 50000;
        else if (matches2 == 4) regularPrize2 = 10000;
        else if (matches2 == 3) regularPrize2 = 1000;

        // Does ticket #2 have bonus
        bonusPrize2 = bonusHit2 ? 333 : 0;
        totalPrize2 = regularPrize2 + bonusPrize2;

        cout << "\n========================================\n";
        cout << "       RESULTS FOR BONUS TICKET #2\n";
        cout << "========================================\n";

        cout << "Ticket #2 numbers -> ";
        for (int n : ticket2) cout << n << " ";
        cout << "\n";

        cout << "Matches -> " << matches2 << "\n";
        cout << "Regular Prize -> $" << regularPrize2 << "\n";
        cout << "Bonus Prize -> $" << bonusPrize2 << "\n";
        cout << "TOTAL -> $" << totalPrize2 << "\n";
    }

    if (!ticket3.empty())
    {
        // Ticket #3 matches
        matches3 = compareLines(ticket3, winning);
        bonusHit3 = hasBonus(ticket3, bonusNum);

        if (matches3 == 6)      regularPrize3 = 5000000;
        else if (matches3 == 5) regularPrize3 = 50000;
        else if (matches3 == 4) regularPrize3 = 10000;
        else if (matches3 == 3) regularPrize3 = 1000;

        bonusPrize3 = bonusHit3 ? 333 : 0;
        totalPrize3 = regularPrize3 + bonusPrize3;

        cout << "\n========================================\n";
        cout << "       RESULTS FOR BONUS TICKET #3\n";
        cout << "========================================\n";

        cout << "Ticket #3 numbers -> ";
        for (int n : ticket3) cout << n << " ";
        cout << "\n";

        cout << "Matches -> " << matches3 << "\n";
        cout << "Regular Prize -> $" << regularPrize3 << "\n";
        cout << "Bonus Prize -> $" << bonusPrize3 << "\n";
        cout << "TOTAL -> $" << totalPrize3 << "\n";
    }

    // ==========================================
    // SECTION 4 — Optional RPS Gamble
    // ==========================================

    int combinedTotal = totalPrize1;

    // If bonus tickets exist, add their totals too
    if (!ticket2.empty()) combinedTotal += totalPrize2;
    if (!ticket3.empty()) combinedTotal += totalPrize3;

    cout << "\n========================================\n";
    cout << "     OPTIONAL ROCK–PAPER–SCISSORS\n";
    cout << "========================================\n";

    cout << "Your combined winnings so far -> $" << combinedTotal << "\n";

    string gambleChoice;
    cout << "Would you like to gamble your winnings in Rock–Paper–Scissors? (Y/N): ";
    getline(cin, gambleChoice);

    bool rpsPlayed = false;
    bool rpsWon = false;
    bool rpsTie = false;

    if (!gambleChoice.empty() &&
        (gambleChoice == "Y" || gambleChoice == "y"))
    {
        rpsPlayed = true;

        //new: Clean, validated RPS input
        string userMove;
        while (true)
        {
            cout << "Enter R (Rock), P (Paper), or S (Scissors): ";
            getline(cin, userMove);

            if (userMove == "R" || userMove == "r" ||
                userMove == "P" || userMove == "p" ||
                userMove == "S" || userMove == "s")
                break;

            cout << "Invalid input. Try again.\n";
        }

        //new: Computer randomly selects a move
        vector<char> moves = {'R','P','S'};
        char compMove = moves[rand() % 3];

        auto fullMove = [&](char m){
            if (m=='R') return "Rock";
            if (m=='P') return "Paper";
            return "Scissors";
        };

        cout << "\nYou chose -> " << fullMove(toupper(userMove[0])) << "\n";
        cout << "Computer chose -> " << fullMove(compMove) << "\n";

        // Determine result
        char u = toupper(userMove[0]);

        if (u == compMove)
        {
            rpsTie = true;
            cout << "It's a TIE! Your winnings remain the same.\n";
        }
        else if ((u=='R' && compMove=='S') ||
                 (u=='P' && compMove=='R') ||
                 (u=='S' && compMove=='P'))
        {
            rpsWon = true;
            cout << "You WON the gamble! Your winnings DOUBLE.\n";
            combinedTotal *= 2;
        }
        else
        {
            cout << "You LOST the gamble! Your winnings drop to $0.\n";
            combinedTotal = 0;
        }
    }
    else
    {
        cout << "You chose not to gamble. Keeping your winnings.\n";
    }


// ==========================================
// Write FINAL RESULTS to output file
// ==========================================

    cout << "\n========================================\n";
    cout << "               RESULTS\n";
    cout << "========================================\n";


    //print file contents
    string filename = buildFilename(player);
    ofstream file(filename, ios::app);

    time_t now2 = time(0);
    tm* local2 = localtime(&now2);

    file << "\n========================================\n";
    file << " Lottery Results - "
         << (local2->tm_year + 1900) << "-"
         << (local2->tm_mon + 1) << "-"
         << local2->tm_mday << " "
         << local2->tm_hour << ":"
         << local2->tm_min << "\n";
    file << "========================================\n";

    // Write winning line
    file << "Winning Numbers -> ";
    for (int n : winning) file << n << " ";
    file << "\nBonus Number -> " << bonusNum << "\n";

    // -----------------------------
    // Ticket #1
    // -----------------------------
    file << "\nTICKET #1 -> ";
    for (int n : ticket1) file << n << " ";
    file << "\nMatches -> " << matches1;

    file << "\nRegular Prize -> $" << regularPrize1;
    file << "\nBonus Prize -> $" << bonusPrize1;
    file << "\nTOTAL -> $" << totalPrize1 << "\n";

    // -----------------------------
    // Ticket #2 (optional)
    // -----------------------------
    if (!ticket2.empty())
    {
        file << "\nTICKET #2 -> ";
        for (int n : ticket2) file << n << " ";

        file << "\nMatches -> " << matches2;
        file << "\nRegular Prize -> $" << regularPrize2;
        file << "\nBonus Prize -> $" << bonusPrize2;
        file << "\nTOTAL -> $" << totalPrize2 << "\n";
    }

    // -----------------------------
    // Ticket #3 (optional)
    // -----------------------------
    if (!ticket3.empty())
    {
        file << "\nTICKET #3 -> ";
        for (int n : ticket3) file << n << " ";

        file << "\nMatches -> " << matches3;
        file << "\nRegular Prize -> $" << regularPrize3;
        file << "\nBonus Prize -> $" << bonusPrize3;
        file << "\nTOTAL -> $" << totalPrize3 << "\n";
    }

    // -----------------------------
    // RPS Results (if played)
    // -----------------------------
    if (rpsPlayed)
    {
        file << "\n--- Rock-Paper-Scissors Results ---\n";
        if (rpsTie)
            file << "Result -> TIE (Total unchanged)\n";
        else if (rpsWon)
            file << "Result -> WIN (Total doubled)\n";
        else
            file << "Result -> LOSS (Total dropped to $0)\n";
    }

    file << "\nFINAL WINNINGS -> $" << combinedTotal << "\n";
    file << "========================================\n\n";

    cout << "Results successfully written to -> " << filename << "\n";

    // ==========================================
    // END OF GAME: Replay or return to menu?
    // ==========================================

    cout << "\nWould you like to play the Lottery again? (Y/N): ";
    string again;
    getline(cin, again);

    if (!again.empty() && (again=="Y" || again=="y"))
    {
        playLotteryGame(player);
        return;
    }

    cout << "Returning to main menu...\n";
  }
} // namespace arcade
