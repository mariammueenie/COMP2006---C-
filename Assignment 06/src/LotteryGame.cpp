#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <cctype>
#include <thread>
#include <chrono>
#include <ctime>

#include "LotteryGame.h"
#include "ArcadeGlobals.h"

namespace arcade {
    using namespace std;

// =========================================================
// NEW: Helper to print matched numbers & full results for ANY ticket
// (Casino-style A3 formatting with setw(28))
// =========================================================
void printMatchDetails(const vector<int>& ticket,
                       const vector<int>& winning,
                       int bonusNum,
                       int ticketNumber)
{
    cout << "\n========================================\n";
    cout << "       RESULTS FOR TICKET #" << ticketNumber << "\n";
    cout << "========================================\n";

    // Ticket numbers
    cout << left << setw(28) << "Ticket Numbers:";

    for (int n : ticket) cout << n << " ";
    cout << "\n";

    // Winning numbers
    cout << left << setw(28) << "Winning Numbers:";
    for (int n : winning) cout << n << " ";
    cout << "\n";

    // Matched numbers
    cout << left << setw(28) << "Matched Numbers:";
    bool anyMatch = false;
    for (int n : ticket)
    {
        if (find(winning.begin(), winning.end(), n) != winning.end())
        {
            cout << n << " ";
            anyMatch = true;
        }
    }
    if (!anyMatch) cout << "None";
    cout << "\n";

    // Match count
    int matches = 0;
    for (int n : ticket)
        if (find(winning.begin(), winning.end(), n) != winning.end())
            matches++;
    cout << left << setw(28) << "Match Count:" << matches << "\n";

    // Bonus
    bool bonusHit = find(ticket.begin(), ticket.end(), bonusNum) != ticket.end();
    cout << left << setw(28) << "Bonus Hit:" << (bonusHit ? "YES" : "NO") << "\n";

    // Regular prize
    int regularPrize = 0;
    if (matches == 6)      regularPrize = 5000000;
    else if (matches == 5) regularPrize = 50000;
    else if (matches == 4) regularPrize = 10000;
    else if (matches == 3) regularPrize = 1000;

    int bonusPrize = bonusHit ? 333 : 0;
    int totalPrize = regularPrize + bonusPrize;

    // Prize lines
    cout << left << setw(28) << "Regular Prize:" << "$" << regularPrize << "\n";
    cout << left << setw(28) << "Bonus Prize:"   << "$" << bonusPrize << "\n";
    cout << left << setw(28) << "TOTAL:"         << "$" << totalPrize << "\n";
}



// =========================================================
// MAIN LOTTERY GAME
// =========================================================
void playLotteryGame(const PlayerName& player)
{
    cout << "\n========================================\n";
    cout << "         Welcome to LOTTERY Game!\n";
    cout << "========================================\n";

    srand(static_cast<unsigned>(time(nullptr)));

    cout << "In this game, you will enter 6 UNIQUE numbers between 1 and 40\n";
    cout << "OR you may choose to have your numbers randomly generated.\n";
    cout << "After that, you may optionally receive TWO extra random bonus tickets.\n";

    // ==========================================
    // TICKET #1
    // ==========================================
    cout << "\nTicket #1 Setup\n";
    cout << "-----------------------------------------\n";

    string modeChoice;

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
        cout << "\nYou chose MANUAL entry.\n";
        ticket1 = getUserTicket();

        // FORMAT ticket #1 display
        cout << left << setw(28) << "Ticket #1 Numbers:";
        for (int n : ticket1) cout << n << " ";
        cout << "\n";
    }
    else
    {
        cout << "\nYou chose RANDOM generation.\n";
        ticket1 = generateUnique(6, 1, 40);
        sort(ticket1.begin(), ticket1.end());

        cout << left << setw(28) << "Ticket #1 Numbers:";
        for (int n : ticket1) cout << n << " ";
        cout << "\n";
    }

    // ==========================================
    // BONUS TICKETS 2 & 3
    // ==========================================
    string bonusChoice = getYesNo("Would you like TWO bonus tickets (randomly generated)? (Y/N):");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> ticket2, ticket3;

    if (bonusChoice == "Y")
    {
        cout << "\nGenerating BONUS Ticket #2...\n";
        ticket2 = generateUnique(6, 1, 40);
        sort(ticket2.begin(), ticket2.end());

        cout << left << setw(28) << "Bonus Ticket #2:";
        for (int n : ticket2) cout << n << " ";
        cout << "\n";

        cout << "Generating BONUS Ticket #3...\n";
        ticket3 = generateUnique(6, 1, 40);
        sort(ticket3.begin(), ticket3.end());

        cout << left << setw(28) << "Bonus Ticket #3:";
        for (int n : ticket3) cout << n << " ";
        cout << "\n";
    }
    else
    {
        cout << "\nNo bonus tickets selected.\n";
    }


    // ==========================================
    // Generate Winning Numbers + BONUS
    // ==========================================
    vector<int> winning = generateUnique(6, 1, 40);
    sort(winning.begin(), winning.end());

    cout << "\n========================================\n";
    cout << "        OFFICIAL WINNING NUMBERS\n";
    cout << "========================================\n";

    cout << left << setw(28) << "Winning Numbers:";
    for (int n : winning) cout << n << " ";
    cout << "\n";

    int bonusNum;
    while (true)
    {
        int n = rand() % 40 + 1;
        if (find(winning.begin(), winning.end(), n) == winning.end()) {
            bonusNum = n;
            break;
        }
    }

    cout << left << setw(28) << "Bonus Number:" << bonusNum << "\n";

    // ==========================================
    // FULL FORMATTED RESULTS FOR ALL TICKETS
    // ==========================================
    printMatchDetails(ticket1, winning, bonusNum, 1);
    if (!ticket2.empty()) printMatchDetails(ticket2, winning, bonusNum, 2);
    if (!ticket3.empty()) printMatchDetails(ticket3, winning, bonusNum, 3);


    // ==========================================
    // COMBINE PRIZES
    // ==========================================
    auto totalFor = [&](const vector<int>& t) {
        if (t.empty()) return 0;

        int matches = compareLines(t, winning);
        bool bonusHit = hasBonus(t, bonusNum);

        int reg = 0;
        if (matches == 6)      reg = 5000000;
        else if (matches == 5) reg = 50000;
        else if (matches == 4) reg = 10000;
        else if (matches == 3) reg = 1000;

        int bonusPrize = bonusHit ? 333 : 0;
        return reg + bonusPrize;
    };

    int combinedTotal = 0;
    combinedTotal += totalFor(ticket1);
    combinedTotal += totalFor(ticket2);
    combinedTotal += totalFor(ticket3);


    // ==========================================
    // OPTIONAL ROCK-PAPER-SCISSORS + No Winning No Game
    // ==========================================

    cout << "\n========================================\n";
    cout << "     TIME FOR A LITTLE... GAMBLING?\n";
    cout << "========================================\n";

    cout << left << setw(28) << "Total Winnings:" << "$" << combinedTotal << "\n";

    // =========================================================
    // NEW: Prevent RPS if user has $0 winnings
    // =========================================================
        if (combinedTotal == 0)
        {
            cout << "\nYou don't have any winnings to bet... "
                    "you can't play Rock-Paper-Scissors!\n";
            cout << "Skipping gamble option.\n";
            
            // (No gamble, just save results and continue)
            // Jump directly to file-writing section
        }
        else
        {
            // Continue with your existing RPS prompt:
            // string gambleChoice = getYesNo("Would you like to gamble your winnings 
            //in Rock-Paper-Scissors? (Y/N): ");
            // ... existing code continues ...
        

    string gambleChoice = getYesNo
    ("Would you like to gamble your winnings in Rock-Paper-Scissors? If you win, your earnings double! If you loose, you'll loose everything. (Y/N): ");
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (gambleChoice == "Y")
    {
        bool resolved = false;

        while (!resolved)
        {
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

            char u = toupper(userMove[0]);
            vector<char> moves = {'R','P','S'};
            char compMove = moves[rand() % 3];

            auto fullMove = [&](char m){
                if (m=='R') return "Rock";
                if (m=='P') return "Paper";
                return "Scissors";
            };

            cout << "\nYou chose -> " << fullMove(u) << "\n";
            cout << "Computer chose -> " << fullMove(compMove) << "\n";

            if (u == compMove)
            {
                cout << "It's a TIE! Let's play again.\n";
                continue;
            }
            else if ((u=='R' && compMove=='S') ||
                     (u=='P' && compMove=='R') ||
                     (u=='S' && compMove=='P'))
            {
                cout << "You WON the gamble! Your winnings DOUBLE.\n";
                combinedTotal *= 2;
            }
            else
            {
                cout << "You LOST the gamble! Your winnings drop to $0.\n";
                combinedTotal = 0;
            }

            resolved = true;
        }
    }
    else
    {
        cout << "You chose not to gamble. Keeping your winnings.\n";
    }
    } // end of RPS if-block

    // ==========================================
    // WRITE FORMATTED RESULTS TO FILE
    // ==========================================
    string filename = buildFilename(player);
    ofstream file(filename, ios::app);

    time_t now2 = time(0);
    tm* local2 = localtime(&now2);

    file << "\n========================================\n";
    file << " LOTTERY RESULTS\n";
    file << "========================================\n";

    // Ticket #1
    file << left << setw(28) << "Ticket #1 Numbers:";
    for (int n : ticket1) file << n << " ";
    file << "\n";

    // Ticket #1 results
    int matches1 = compareLines(ticket1, winning);
    bool bonusHit1 = hasBonus(ticket1, bonusNum);

    file << left << setw(28) << "Matches:" << matches1 << "\n";
    file << left << setw(28) << "Bonus Hit:" << (bonusHit1 ? "YES" : "NO") << "\n";


    if (!ticket2.empty()) {
        file << left << setw(28) << "Bonus Ticket #2:";
        for (int n : ticket2) file << n << " ";
        file << "\n";

        int matches2 = compareLines(ticket2, winning);
        bool bonusHit2 = hasBonus(ticket2, bonusNum);

        file << left << setw(28) << "Matches:" << matches2 << "\n";
        file << left << setw(28) << "Bonus Hit:" << (bonusHit2 ? "YES" : "NO") << "\n";

    }

    if (!ticket3.empty()) {
        file << left << setw(28) << "Bonus Ticket #3:";
        for (int n : ticket3) file << n << " ";
        file << "\n";

        if (!ticket3.empty()) {
        file << left << setw(28) << "Bonus Ticket #3:";
        for (int n : ticket3) file << n << " ";
        file << "\n";
}

    }

    // Winning numbers
    file << left << setw(28) << "Winning Numbers:";
    for (int n : winning) file << n << " ";
    file << "\n";

    file << left << setw(28) << "Bonus Number:" << bonusNum << "\n";

    // Final total
    file << left << setw(28) << "FINAL WINNINGS:" << "$" << combinedTotal << "\n";

    file << "========================================\n";

    cout << "Results successfully written to -> " << filename << "\n";


    // ==========================================
    // PLAY AGAIN?
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

