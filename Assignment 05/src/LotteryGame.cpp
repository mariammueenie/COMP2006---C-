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

// Headers
#include "../include/LotteryGame.h"
#include "../include/ArcadeGlobals.h"

namespace arcade {
//TODO: Implement the rock paper scissors gambling on winnings, include in file output.
//TODO: Allow user to choose 6 numbers for initial ticket, or generate  numbers for initial ticket
//TODO: Ask user if they would like 2 bonus tickets
//TODO: Ensure all tickets are unique, no values repeated
//TODO: Ensure that there are 6 winning numbers and 1 bonus number 
//TODO: Apply lotario-style prize logic
//TODO: Matches to the 6 normal winning numbers considered normally
//TODO: Match to bonus winning number considered separately rather than reg match, win $333
/* =========================================================
   Lottery Game — Vector Victory
   ========================================================= */

    // Helper to convert names into filename
    string buildFilename(const PlayerName& playerRef) {

        // Takes name string and validates input/checks
        auto clean = [&](string s) {
            string out;
            for (char c : s) { // check each character
                if (c == ' ')
                    out += '_'; // replaces spaces with '_'
                else
                    // all lowercase
                    // prevents non-standard alphanumerics
                    // append char to string
                    // this method suggested by VS Code AI 
                    // REFERENCE: https://en.cppreference.com/w/cpp/string/byte/tolower
                    // REFERENCE: https://stackoverflow.com/questions/1988516/few-questions-on-number-representation-in-computer/1988864#1988864
                    out += static_cast<char>(tolower(static_cast<unsigned char>(c)));
            }
            return out;
        };

        string first = clean(playerRef.first); // gets first name 
        string last  = clean(playerRef.last); // gets last name

        // Base name for file
        string base = "lotto_" + first + "_" + last + "_";

        // Numbered files for same player can be added later if desired
        // REFERENCE: https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c?
        // REFERENCE: https://cplusplus.com/reference/cctype/tolower/

        int counter = 1;
        while (true) {
            // decide candidate name
            string candidate = base + to_string(counter) + ".txt";

            // Check if file with current name exists
            ifstream test(candidate);
            if (!test.good()) {
                // File does NOT exist, so return base name
                return candidate;
            }
            // If same name file exists, increment counter
            // Otherwise, return base name for file
            counter++;
        } 
    }

    // FOR ASSIGN 5: 1-40 rather than 1--49
    // Returns 6 unique numbers from 1-40
    // No repeats
    vector<int> generateUnique(int count, int minVal, int maxVal) {
        // num starts as empty
        // is filled with randomly generated numbers 
        vector<int> nums;

        while ((int)nums.size() < count) { // loop cont' until nums.size=count
            int n = rand() % maxVal + minVal;
            // prevents repeat values
            if (find(nums.begin(), nums.end(), n) == nums.end()) { 
                nums.push_back(n);
            }
        }
        return nums;
    }

    // Returns 1 valid integer in range
    int getSingleInteger(const string& prompt, int minV, int maxV) {

        while (true) { // cont' loop until valid input entered
            cout << prompt;

            string line;
            getline(cin, line); // reads entire input, not just first part

            // remove leading/trailing spaces 
            // unsigned charcast to avoid problems with non-alphanumeric/non-standard chars
            while (!line.empty() && isspace(static_cast<unsigned char>(line.front())))
                line.erase(0, 1);
            while (!line.empty() && isspace(static_cast<unsigned char>(line.back())))
                line.pop_back();

            // ensures no empty input
            if (line.empty()) {
                cout << "Invalid input. Please enter ONE whole number.\n";
                continue;
            }

            // only integers allowed
            bool bad = false;
            for (char c : line) {
                if (!isdigit(static_cast<unsigned char>(c))) {
                    bad = true;
                    break;
                }
            }
            if (bad) { // re-prompt if something wrong entered
                cout << "Invalid input. ONLY integers 1-49 allowed.\n";
                continue;
            }

            // convert to int
            int value = stoi(line);

            // range check
            if (value < minV || value > maxV) {
                cout << "Number must be between " << minV << " and " << maxV << ".\n";
                continue;
            }

            return value;
        }
    }

    // Used to get 6 unique ints from 1-40 from user
    vector<int> getUserTicket() {
        vector<int> ticket;

        cout << "Enter 6 UNIQUE numbers between 1 and 40.\n";

        while ((int)ticket.size() < 6) { // loop until 6 ints entered
            int num = getSingleInteger( // request next int
                "Number " + to_string(ticket.size() + 1) + ": ", 
                1, 40
            );

            // no duplicates allowed, prompts re-entry
            if (find(ticket.begin(), ticket.end(), num) != ticket.end()) {
                cout << "Duplicate number. Enter a UNIQUE number.\n";
                continue;
            }

            // stores validated unique value
            ticket.push_back(num);
        }
        // return ticket once it has 6 ints
        return ticket;
    }

    // Line is player values 
    // Winning is official values
    int compareLines(const vector<int>& line, const vector<int>& winning) {
        int matches = 0; // start match counter
        for (int n : line) { // check each number individually
            // check if players number in winning line
            // if found, returns number 
            // REFERENCE: https://en.cppreference.com/w/cpp/algorithm/find.html
            // REFERENCE: https://learn.microsoft.com/en-us/cpp/standard-library/algorithm-functions?view=msvc-170#find
            if (find(winning.begin(), winning.end(), n) != winning.end()) {
                matches++;
            }
        }
        // after loop reads through entire player line, return matches
        return matches;
    }

    // checks if players line contains the bonus number 
    // bcuz bonus number is treated as reg match rn
    bool hasBonus(const vector<int>& line, int bonusNum) {
        return find(line.begin(), line.end(), bonusNum) != line.end(); // t or f
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

    // Create file with player results
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
        // write file
        // DONT erase old content 
        // if file doesn't exist, make it 
        // if it does, new results are added
        ofstream file(filename, ios::app);

        // add date and time, converted to human friendly format
        time_t now = time(0);
        tm* local = localtime(&now);

        file << "\n========================================\n";
        file << " Lottery Results - "
        // REFERENCE: https://en.cppreference.com/w/cpp/chrono/c/tm
            << (local->tm_year + 1900) << "-" // +1900 since starts counting from 1900
            << (local->tm_mon + 1) << "-" // reps months 0-11, but comp reps 1-12, so add 1 to make match
            << local->tm_mday << " "
            << local->tm_hour << ":"
            << local->tm_min << ":"
            << "\n========================================\n";

        // print ticket
        file << "Your Ticket: ";
        for (int n : ticket) file << n << " ";

        // will add extra ticket to file, if available
        if (!extraTicket.empty()) {
            file << "\nExtra Ticket: ";
            for (int n : extraTicket) file << n << " ";
        }

        // print bonus number
        file << "\nWinning Numbers: ";
        for (int n : winning) file << n << " ";
        file << "\nBonus Number: " << bonusNum << "\n";

        // print match count and prize, using prize calc function
        file << "\nYour ticket matched " << resultTicket << " numbers.\n";
        file << "Prize: " << calculatePrize(resultTicket, bonusHitTicket) << "\n";

        // print match count from extra ticket + prize, if available
        if (!extraTicket.empty()) {
            file << "\nYour extra ticket matched " << resultExtra << " numbers.\n";
            file << "Prize: " << calculatePrize(resultExtra, bonusHitExtra) << "\n\n";
        }
    }

    // ==========================================
    // MAIN GAME LOOP FOR LOTTERY
    // ==========================================
    void playLotteryGame() {

        string playAgain = "Y";

        while (playAgain == "Y") {

            // Build filename moved inside loop to build fresh file for each game
            string filename = buildFilename(player);
            

            // Intro
            cout << "\n--- Lottery Game: Vector Victory Edition ---\n\n";
            cout << "Hello, " << player.first << ". Welcome to the Lotto!\n\n";

            // Explain the game to the user
            cout << "In this game, you will select 6 unique numbers between 1 and 40.\n";
            cout << "You will also have the option to let us generate 6 unique random numbers between 1 and 49 for you.\n";
            cout << "Finally, 6 [+ 1 Bonus] winning number will be drawn.\n";
            cout << "If your numbers match 3 or more winning numbers (regardless of order), you win a prize!\n";
            cout << "The computer generated numbers will also be checked, and if they match, you could win prizes!\n";
            cout << "The more numbers you match, the bigger the prize!\n\n";

            // ADDED: Price per ticket for LOTTO Game
            cout << "Each ticket costs $5.00 CAD.\n\n";


            // calls getUserTicket function to get user main ticket
            vector<int> ticket = getUserTicket();

            // asks if user wants extra ticket
            string extraChoice = getYesNo("\nWould you like an extra randomly-generated ticket [Free of charge]? (Y/N): ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // generated extra ticket if desired
            vector<int> extraTicket;
            if (extraChoice == "Y")
                extraTicket = generateUnique(6, 1, 40);

            // generate winning numbers
            vector<int> winning = generateUnique(6, 1, 40);

            // generate bonus number
            int bonusNum = rand() % 40 + 1;
            // if bonus number is already in winning line, generate new bonus
            while (find(winning.begin(), winning.end(), bonusNum) != winning.end())
                bonusNum = rand() % 40 + 1;
            // sorts values from smallest -> largest
            // cleaner output
            sort(ticket.begin(), ticket.end());
            sort(winning.begin(), winning.end());
            if (!extraTicket.empty()) sort(extraTicket.begin(), extraTicket.end());

            // compare results for main player ticket
            int resultTicket = compareLines(ticket, winning);
            // checks if player picked bonus number
            bool bonusHitTicket = hasBonus(ticket, bonusNum);

            // results for extra ticket...
            int resultExtra = 0;
            bool bonusHitExtra = false;

            // ...but only if user actually has extra ticket
            if (!extraTicket.empty()) {
                resultExtra = compareLines(extraTicket, winning);
                bonusHitExtra = hasBonus(extraTicket, bonusNum);
            }

    // =============================================
    // Murach-Style aligned output 
    // REFERENCE: Murach's C++ Programming, 2nd Edition
    //            Chapter 5 Slides: How to Work with I/O Streams and Files
    // ============================================= 
            const int labelWidth   = 18;
            const int numberWidth  = 4;
            const int resultWidth  = 14;

            cout << "\n========================================\n";
            cout << "          LOTTERY RESULTS\n";
            cout << "========================================\n\n";

            // YOUR TICKET
            // Format output nicely, easier to read
            cout << left << setw(labelWidth) << "Your Ticket:";
            for (int n : ticket) {
                cout << right << setw(numberWidth) << n;
            }
            cout << "\n";

            // EXTRA TICKET (if any)
            // Format output nicely, easier to read
            if (!extraTicket.empty()) {
                cout << left << setw(labelWidth) << "Extra Ticket:";
                for (int n : extraTicket) {
                    cout << right << setw(numberWidth) << n;
                }
                cout << "\n";
            }

            // WINNING NUMBERS
            cout << left << setw(labelWidth) << "Winning Numbers:";
            for (int n : winning) {
                cout << right << setw(numberWidth) << n;
            }
            cout << "\n";

            // BONUS NUMBER
            cout << left << setw(labelWidth) << "Bonus Number:"
                << right << setw(numberWidth) << bonusNum << "\n\n";

            // MATCH SUMMARY FOR YOUR TICKET
            cout << left << setw(labelWidth) << "Matches (your ticket):"
                << right << setw(numberWidth) << resultTicket << "\n";

            cout << left << setw(labelWidth) << "Bonus hit (your ticket):"
                << right << setw(resultWidth) << (bonusHitTicket ? "YES" : "NO") << "\n";

            cout << left << setw(labelWidth) << "Prize (your ticket):"
                << right << setw(resultWidth) << calculatePrize(resultTicket, bonusHitTicket) << "\n\n";

            // MATCH SUMMARY FOR EXTRA TICKET (if any)
            if (!extraTicket.empty()) {
                cout << left << setw(labelWidth) << "Matches (extra):"
                    << right << setw(numberWidth) << resultExtra << "\n";

                cout << left << setw(labelWidth) << "Bonus hit (extra):"
                    << right << setw(resultWidth) << (bonusHitExtra ? "YES" : "NO") << "\n";

                cout << left << setw(labelWidth) << "Prize (extra):"
                    << right << setw(resultWidth) << calculatePrize(resultExtra, bonusHitExtra) << "\n\n";
            }

            // Write nicely formatted results into the per-game file too
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

            playAgain = getYesNo("\nBuy another lottery ticket? (Y/N): ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (playAgain == "N") {
                cout << "\nReturning to main menu...\n";
                return;
            }
        }
    }
} // namespace arcade