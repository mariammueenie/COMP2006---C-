// #include "ArcadeGlobals.h"

// #include <iostream>      // cout, cin
// #include <string>        // std::string, to_string
// #include <vector>        // std::vector
// #include <algorithm>     // sort, find
// #include <fstream>       // ifstream, ofstream
// #include <limits>        // numeric_limits
// #include <thread>        // this_thread::sleep_for
// #include <chrono>        // chrono::milliseconds
// using namespace std;

// // ==========================================================
// // All global definitions for global functions 
// // Ie: functions used in multiple / all games / menu options 
// // ==========================================================

// namespace arcade {
//     using namespace std;
//     // Define the global player object
//     PlayerName player;

//     // =========================================================
//     // YES/NO strictly-controlled validator (only Y/N/YES/NO)
//     // Since used in multiple games, defined here globally
//     // Muuuch easier than checking inline every time lmao
//     // =========================================================
//     string getYesNo(const string& prompt) {
//         cout << prompt;

//         string input;
//         while (true) {
//             cin >> input;

//             // lowercase whole string
//             for (char &c : input) {
//                 c = tolower(static_cast<unsigned char>(c));
//             }
//             if (input == "y" || input == "yes") {
//                 return "Y";
//             }
//             if (input == "n" || input == "no") {
//                 return "N";
//             }

//             cout << "Please enter Y, N, YES, or NO only: ";
//             cin.clear();
//         }
//     }

//     // =========================================================
//     // Validates first name (letters + hyphen only)
//     // =========================================================
//     bool validFirstName(const string& s) {
//         if (s.empty()) return false;

//         for (size_t i = 0; i < s.length(); i++) {
//             char c = s[i];
//             if (!isalpha(static_cast<unsigned char>(c)) && c != '-') {
//                 return false;
//             }
//         }
//         return true;
//     }

//     // =========================================================
//     // Validates last name (letters + apostrophe only)
//     // =========================================================
//     bool validLastName(const string& s) {
//         if (s.empty()) return false;

//         for (size_t i = 0; i < s.length(); i++) {
//             char c = s[i];
//             if (!isalpha(static_cast<unsigned char>(c)) && c != '\'') {
//                 return false;
//             }
//         }
//         return true;
//     }

//     // =========================================================
//     // getPlayerName()
//     // =========================================================
//     PlayerName getPlayerName() {
//         PlayerName p;
//         string input;

//         // Clear leftover newline before getline()
//         cin.ignore(numeric_limits<streamsize>::max(), '\n');

//         // FIRST NAME
//         while (true) {
//             cout << "Enter your FIRST name (letters and '-' only): ";
//             getline(cin, input);

//             // Trim start/end whitespace
//             while (!input.empty() && isspace(static_cast<unsigned char>(input.front())))
//                 input.erase(0, 1);
//             while (!input.empty() && isspace(static_cast<unsigned char>(input.back())))
//                 input.pop_back();

//             if (validFirstName(input)) {
//                 p.first = input;
//                 break;
//             }
//             cout << "Invalid. First name must contain only letters and hyphens.\n";
//         }

//         // LAST NAME
//         while (true) {
//             cout << "Enter your LAST name (letters and '\'' only): ";
//             getline(cin, input);

//             while (!input.empty() && isspace(static_cast<unsigned char>(input.front())))
//                 input.erase(0, 1);
//             while (!input.empty() && isspace(static_cast<unsigned char>(input.back())))
//                 input.pop_back();

//             if (validLastName(input)) {
//                 p.last = input;
//                 break;
//             }
//             cout << "Invalid. Last name must contain only letters and apostrophes.\n";
//         }

//         return p;
//     }

//     // =========================================================
//     // STRICT INTEGER INPUT FUNCTION
//     // =========================================================
//     int getStrictInteger(const string& prompt, int minV, int maxV)
//     {
//         while (true)
//         {
//             cout << prompt;
//             string line;
//             getline(cin, line);

//             // Trim whitespace
//             while (!line.empty() && isspace(static_cast<unsigned char>(line.front())))
//                 line.erase(0, 1);
//             while (!line.empty() && isspace(static_cast<unsigned char>(line.back())))
//                 line.pop_back();

//             if (line.empty()) {
//                 cout << "Invalid input. Please enter ONE whole number.\n";
//                 continue;
//             }

//             bool bad = false;
//             for (char c : line) {
//                 if (!isdigit(static_cast<unsigned char>(c))) {
//                     bad = true;
//                     break;
//                 }
//             }
//             if (bad) {
//                 cout << "Invalid input. Please enter an integer in the accepted range.\n";
//                 continue;
//             }

//             int value = stoi(line);

//             if (value < minV || value > maxV) {
//                 cout << "Number must be between " << minV << " and " << maxV << ".\n";
//                 continue;
//             }

//             return value;
//         }
//     }

//     // =========================================================
//     // showHelp(): required for Assignment 05
//     // =========================================================
//     void showHelp() {
//         time_t now = time(nullptr);

//         cout << "\n===== HELP MENU =====\n";
//         cout << "Welcome to the Mini Arcade Assignment 05!\n";
//         cout << "Player: " << player.first << " " << player.last << "\n";
//         cout << "Date/Time: " << ctime(&now) << "\n";

//         cout << "\nGames Included:\n";
//         cout << "- Guessing Game (numbers)\n";
//         cout << "- Dice Game\n";
//         cout << "- Lottery Game (1-40, bonus, extra lines)\n";
//         cout << "- Guessing Name Game\n";

//         cout << "\nFeatures Shown:\n";
//         cout << "- Namespaces & Header Files\n";
//         cout << "- Input Validation Everywhere\n";
//         cout << "- Vectors (Lottery)\n";
//         cout << "- File Output (Lottery Ticket)\n";
//         cout << "- Bonus Gameplay (Rock-Paper-Scissors)\n";
//     }

//     // =========================================================
//     // Rock Paper Scissors: Feature
//     // Since rock paper scissors could potentially be used in multiple games
//     // For now only 1 but u never know
//     // (simple placeholder — you will fill in lottery logic later)
//     // =========================================================
//     void playRockPaperScissors(int& winnings) {
//         cout << "\n[RPS Placeholder] — You will implement prize doubling here!\n";
//         cout << "Current winnings: $" << winnings << "\n";
//     }

// } // namespace arcade
#include "ArcadeGlobals.h"

#include <iostream>      
#include <string>        
#include <vector>        
#include <algorithm>     
#include <fstream>       
#include <limits>        
#include <thread>        
#include <chrono>        
using namespace std;

// ==========================================================
// All global definitions for global functions 
// Ie: functions used in multiple / all games / menu options 
// ==========================================================

namespace arcade {
    using namespace std;

    // Define the global player object
    PlayerName player;

    // =========================================================
    // YES/NO strictly-controlled validator (only Y/N/YES/NO)
    // =========================================================
    string getYesNo(const string& prompt) {
        cout << prompt;

        string input;
        while (true) {
            cin >> input;

            for (char &c : input) {
                c = tolower(static_cast<unsigned char>(c));
            }
            if (input == "y" || input == "yes") {
                return "Y";
            }
            if (input == "n" || input == "no") {
                return "N";
            }

            cout << "Please enter Y, N, YES, or NO only: ";
            cin.clear();
        }
    }

    // =========================================================
    // Validates first name (letters + hyphen only)
    // =========================================================
    bool validFirstName(const string& s) {
        if (s.empty()) return false;

        for (char c : s) {
            if (!isalpha(static_cast<unsigned char>(c)) && c != '-') {
                return false;
            }
        }
        return true;
    }

    // =========================================================
    // Validates last name (letters + apostrophe only)
    // =========================================================
    bool validLastName(const string& s) {
        if (s.empty()) return false;

        for (char c : s) {
            if (!isalpha(static_cast<unsigned char>(c)) && c != '\'') {
                return false;
            }
        }
        return true;
    }

    // =========================================================
    // getPlayerName()
    // =========================================================
    PlayerName getPlayerName() {
        PlayerName p;
        string input;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // FIRST NAME
        while (true) {
            cout << "Enter your FIRST name (letters and '-' only): ";
            getline(cin, input);

            while (!input.empty() && isspace(static_cast<unsigned char>(input.front())))
                input.erase(0, 1);
            while (!input.empty() && isspace(static_cast<unsigned char>(input.back())))
                input.pop_back();

            if (validFirstName(input)) {
                p.first = input;
                break;
            }
            cout << "Invalid. First name must contain only letters and hyphens.\n";
        }

        // LAST NAME
        while (true) {
            cout << "Enter your LAST name (letters and '\'' only): ";
            getline(cin, input);

            while (!input.empty() && isspace(static_cast<unsigned char>(input.front())))
                input.erase(0, 1);
            while (!input.empty() && isspace(static_cast<unsigned char>(input.back())))
                input.pop_back();

            if (validLastName(input)) {
                p.last = input;
                break;
            }
            cout << "Invalid. Last name must contain only letters and apostrophes.\n";
        }

        return p;
    }

    // =========================================================
    // STRICT INTEGER
    // =========================================================
    int getStrictInteger(const string& prompt, int minV, int maxV)
    {
        while (true)
        {
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
                cout << "Invalid input. Please enter an integer in the accepted range.\n";
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
    // showHelp()
    // =========================================================
    void showHelp() {
        time_t now = time(nullptr);

        cout << "\n===== HELP MENU =====\n";
        cout << "Welcome to the Mini Arcade Assignment 05!\n";
        cout << "Player: " << player.first << " " << player.last << "\n";
        cout << "Date/Time: " << ctime(&now) << "\n";

        cout << "\nGames Included:\n";
        cout << "- Guessing Game (numbers)\n";
        cout << "- Dice Game\n";
        cout << "- Lottery Game\n";
        cout << "- Guessing Name Game\n";

        cout << "\nFeatures Shown:\n";
        cout << "- Namespaces & Header Files\n";
        cout << "- Input Validation Everywhere\n";
        cout << "- Vectors (Lottery)\n";
        cout << "- File Output\n";
        cout << "- Bonus Gameplay (Rock-Paper-Scissors)\n";
    }

    // =========================================================
    // NEW: RANDOM UNIQUE NUMBER GENERATOR FOR LOTTERY
    // =========================================================
    vector<int> generateUnique(int count, int minV, int maxV)
    {
        vector<int> nums;
        while ((int)nums.size() < count)
        {
            int n = rand() % (maxV - minV + 1) + minV;
            if (find(nums.begin(), nums.end(), n) == nums.end())
                nums.push_back(n);
        }
        return nums;
    }

    // =========================================================
    // NEW: GET USER TICKET (manual entry)
    // =========================================================
    vector<int> getUserTicket()
    {
        vector<int> ticket;

        cout << "Enter 6 UNIQUE numbers between 1 and 40:\n";
        while ((int)ticket.size() < 6)
        {
            int value = getStrictInteger("Number " + to_string(ticket.size() + 1) + ": ", 1, 40);

            if (find(ticket.begin(), ticket.end(), value) != ticket.end())
            {
                cout << "Duplicate number! Try again.\n";
                continue;
            }

            ticket.push_back(value);
        }

        sort(ticket.begin(), ticket.end());
        return ticket;
    }

    // =========================================================
    // NEW: COMPARE LINES (matches count)
    // =========================================================
    int compareLines(const vector<int>& ticket, const vector<int>& winning)
    {
        int matches = 0;
        for (int n : ticket)
            if (find(winning.begin(), winning.end(), n) != winning.end())
                matches++;
        return matches;
    }

    // =========================================================
    // NEW: HAS BONUS NUMBER
    // =========================================================
    bool hasBonus(const vector<int>& ticket, int bonusNum)
    {
        return find(ticket.begin(), ticket.end(), bonusNum) != ticket.end();
    }

    // =========================================================
    // NEW: BUILD FILENAME FOR LOTTERY OUTPUT
    // =========================================================
    string buildFilename(const PlayerName& p)
    {
        string fname = p.first + "_" + p.last + "_LotteryResults.txt";
        return fname;
    }

} // namespace arcade
