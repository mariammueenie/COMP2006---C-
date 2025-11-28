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
using namespace std;

// FAIR WARNING: Commented the heck out of this code, mostly for my own understanding
// You know u understand something if u can explain it, or something lol 

// ============================
// PlayerName struct
// ============================
    struct PlayerName {
        string first;
        string last;
    };
    // Global player object so any game can access player.first / player.last
    // And so that games don't break
    PlayerName player;

// =========================================================
// YES/NO strictly-controlled validator (only Y/N/YES/NO)
// Since used in multiple games, defined here globally
// Muuuch easier than checking inline every time lmao
// =========================================================
    string getYesNo(const string& prompt) {
        cout << prompt;

        string input;
        while (true) {
            cin >> input;

            // lowercase whole string
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
// Function declarations
// =========================================================
    PlayerName getPlayerName();
    int getStrictInteger(const string& prompt, int minV, int maxV);
    void playGuessingGame();
    void playDiceGame();
    void playLotteryGame();
    void playNameGuessingGame();
    void showCredits();

// =========================================================
// main() Game / Menu Loop
// =========================================================
    int main() {

        cout << "\nWelcome to the Mini Arcade!\n";
        cout << "Please hit enter to get started...\n";
        player = getPlayerName();    // assign to the global player

        int choice = 0;
        // seed timer once for entire program
        srand(static_cast<unsigned int>(time(0)));

        do {
            // Display main menu
            cout << "\n==============================\n";
            cout << "         MINI ARCADE\n";
            cout << "==============================\n";

            cout << "Player: " << player.first << " " << player.last << "\n\n";

            cout << "1. Guessing Game (Numbers)\n";
            cout << "2. Dice Game (Match to Win)\n";
            cout << "3. Lottery Game (Vector Victory)\n";
            cout << "4. Guessing Name Game\n";
            cout << "5. Credits\n";
            cout << "6. Exit\n";

            // strict menu input system
            // Does 4 things 
            // 1. Read whole input as a string 
            // 2. Trim whitespace 
            // 3. Check that string contains ONLY digits 
            // 4. Convert string to integer and check range
            string line; // treated as string so that ANYTHING user types can be caught/validated
            cout << "Enter your choice (1-6): ";
            // prevents issues with leftover newlines
            // better than cin.ignore() alone
            // better than cin >> choice
            getline(cin, line);

            // trim leading spaces
            while (!line.empty() && isspace(line.front()))
                line.erase(0, 1);
            // trim trailing spaces
            while (!line.empty() && isspace(line.back()))
                line.pop_back();

            bool badInput = false;

            // checks if line is empty
            if (line.empty()) {
                badInput = true;
            } else {
                // checks if all characters are digits
                for (size_t i = 0; i < line.length(); i++) {
                    // REFERENCE: MURACH'S C++ PROGRAMMING, 2nd Edition
                    //            CHAPTER 6 SLIDES: 
                    //            How to Work with Data Types, Strings, and Vectors
                    if (!isdigit(static_cast<unsigned char>(line[i]))) {
                        badInput = true;
                        break;
                    }
                }
            }

            // If invalid input, prompted again
            if (badInput) {
                cout << "Invalid input. Please enter ONE single integer only.\n";
                continue;
            }

            // convert to integer
            // REFERENCE: https://en.cppreference.com/w/cpp/string/basic_string/stol
            // REFERENCE: https://cplusplus.com/reference/string/stoi/
            choice = stoi(line);

            // range check
            if (choice < 1 || choice > 6) {
                cout << "Invalid choice. Please select a number between 1 and 6.\n";
                continue;
            }
            // Main Menu Choice Handling
            switch (choice) {
                case 1: playGuessingGame(); break;
                case 2: playDiceGame(); break;
                case 3: playLotteryGame(); break;
                case 4: playNameGuessingGame(); break;
                case 5: showCredits(); break;
                case 6: {
                    string ans = getYesNo("Are you sure you want to exit? (Y/N): ");
                    if (ans == "Y") {
                        cout << "Exiting the Mini Arcade. Goodbye!\n";
                    } else {
                        choice = 0;
                    }
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                }
            }
        } while (choice != 6); // Press 6 to exit
    return 0;
    }

// =========================================================
// NAME INPUT + VALIDATION
// Has 3 parts:
//    validFirstName() -> First name: letters + hyphen
//    validLastName()  -> Last name:  letters + apostrophe
//    getPlayerName()  -> Loops until valid
// ==========================================================

    // Validates first name (letters + hyphen only)
    // For names like "Mary-Jane" or "Micheal-Paul"
    // Uses static_cast<unsigned char> to avoid potential issues with negative char values
    // Uses !isalpha() to check for non-letter characters
    bool validFirstName(const string& s) {
        if (s.empty()) return false;

        for (size_t i = 0; i < s.length(); i++) {
            char c = s[i];
            if (!isalpha(static_cast<unsigned char>(c)) && c != '-') {
                return false;
            }
        }
        return true;
    }

    // Validates last name (letters + apostrophe only)
    // For names like "O'Connor" or "D'Angelo"
    //
    bool validLastName(const string& s) {
        if (s.empty()) return false;

        for (size_t i = 0; i < s.length(); i++) {
            char c = s[i];
            if (!isalpha(static_cast<unsigned char>(c)) && c != '\'') {
                return false;
            }
        }
        return true;
    }

    // 1. Prompts user for first name, keeps prompting until getFirstName() requirements satisfied 
    // 2. Prompts user for last name, keeps prompting until getLastName() requirements satisfied
    // 3. Returns PlayerName struct with valid names
    PlayerName getPlayerName() {
        PlayerName p;
        string input;

        // Clear leftover newline before getline()
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // FIRST NAME
            while (true) {
                cout << "Enter your FIRST name (letters and '-' only): ";
                getline(cin, input);

                // Trim start/end whitespace
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
// STRICT INTEGER INPUT FUNCTION
// Function that strictly validates integer input within a specified range.
// Nice and can be used in multiple games

// getline()
//    REFERENCE: https://en.cppreference.com/w/cpp/string/basic_string/getline
//    REFERENCE: https://en.cppreference.com/w/cpp/io/basic_istream/ignore
//    REFERENCE: 
// isspace(), isdigit(), isalpha()
//    REFERENCE: MURACHS C++ PROGRAMMING, 2nd Edition
//            CHAPTER 6 SLIDES: How to Work with Data Types, Strings, and Vectors
// trim w/ isspace() isdigit()
//    REFERENCE: https://en.cppreference.com/w/cpp/string/byte/isspace
//    REFERENCE: https://en.cppreference.com/w/cpp/string/byte/isdigit
// line.erase
//    REFERENCE: https://en.cppreference.com/w/cpp/string/basic_string/erase
// stoi()
//    REFERENCE: https://cplusplus.com/reference/string/stoi/
//               https://en.cppreference.com/w/cpp/string/basic_string/stol
// range check, minV, maxV
// -> Used minV and maxV to make function reusable in multiple games
//     ngl the idea was suggested by ChatGPT but I coded it myself
//     cuz I was thinking about how to do it anyway, and I was like umm
//     surely there is an easier way to do this than repeating the same code 
//     for each game but I wasn't sure how to do it
// guarantees ONE valid integer per line
// ============================================================

    int getStrictInteger(const string& prompt, int minV, int maxV)
    {
        while (true)
        {
            cout << prompt;
            string line;
            getline(cin, line);

            // Trim whitespace
            while (!line.empty() && isspace(static_cast<unsigned char>(line.front())))
                line.erase(0, 1);
            while (!line.empty() && isspace(static_cast<unsigned char>(line.back())))
                line.pop_back();

            if (line.empty()) {
                cout << "Invalid input. Please enter ONE whole number.\n";
                continue;
            }

            // Initializes bool bad to false (ie: Assume input is valid, unless proven to be bad)
            bool bad = false;
            for (char c : line) { // iterate through each character within input 
                if (!isdigit(static_cast<unsigned char>(c))) { // Check if c is NOT a digit
                    bad = true; // If non-digit character is found, set bool to true (ie: input IS bad)
                    break; // exit loop, since we now know input is bad
                }
            }
            if (bad) {
                cout << "Invalid input. Please enter an integer in the accepted range.\n";
                continue;
            }

            // converts string to int
            int value = stoi(line);

            // If value is singular integer, but too big/small
            if (value < minV || value > maxV) {
                cout << "Number must be between " << minV << " and " << maxV << ".\n";
                continue;
            }

            return value;
        }
    }

// =========================================================
// Guessing Game
// =========================================================

    void playGuessingGame() {
        string playAgain = "Y";

        // Loop continues while player answer continues to be 'Yes'
        while (playAgain == "Y") {

            cout << "\n--- # Guessing Game ---\n\n";

            int secretNumber = rand() % 100 + 1;
            int guess;
            int attempts = 7;
            // Loop starts with assumption that player does not know random number
            // Therefore guess = false
            // Once player guesses some value, it is compared to intSecretNumber 
            // If int guess = int secret number, the loop ends early, and player wins!
            // If not, loop continues to end. 
            // If int attempts reaches 7, and int guess does NOT equal int secretNumber,
            //   then bool guessed = false, and loop ends, telling player they lost. 
            bool guessed = false;

            cout << "Hello, " << player.first
                << ". I am thinking of a whole number between 1 and 100.\n";
            cout << "Can you guess what it is?\n";
            cout << "You have " << attempts << " attempts.\n\n";

        
            // To track previous guesses
            // Comma used to separate strings to avoid partial matches
            string previousGuesses = ",";

            for (int i = 1; i <= attempts; i++) {

                guess = getStrictInteger(
                    "Attempt " + to_string(i) + "/" + to_string(attempts) + ": ",
                    1, 100
                );

                // Read string to check for previous guesses 
                // Initially separated with only spaces initially to avoid partial matches 
                // Realized that better separator is comma + space
                // Store guesses with comma's to avoid partial match issues 
                string guessToken = "," + to_string(guess) + ",";

                if (previousGuesses.find(guessToken) != string::npos) {
                    cout << "You already guessed " << guess
                        << "! Try a different number.\n\n";
                    i--;
                    continue;
                }

                // Append to previous guesses
                previousGuesses += guessToken;

                if (guess == secretNumber) {
                    cout << "\nCorrect! The number was " << secretNumber << ".\n";
                    guessed = true;
                    break;
                }
                else if (guess < secretNumber) {
                    cout << "Too low.\n";
                }
                else {
                    cout << "Too high.\n";
                }

                if (i < attempts) {
                    cout << "Try again!\n\n";
                }
            }

            // If int secretNumber is not guessed:
            if (!guessed) {
                cout << "You are out of attempts. The number was "
                    << secretNumber << ".\n";
            }

            playAgain = getYesNo("\nPlay again? (Y/N): ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (playAgain == "N") {
                cout << "\nReturning to main menu...\n";
                return;
            }
        }
    }

/* =========================================================
   Dice Game
   ========================================================= */
    // Forward declaration for your existing helper
    // Purpose is to 'tell' compiler, trust me bro the function I referenced
    //   is coming soon, just keep reading, don't throw an error plz
    // Specifically for the Yes/No function in the game loop
    // Solved error :)
    // REFERENCE: https://www.geeksforgeeks.org/cpp/what-are-forward-declarations-in-c/
    // REFERENCE: https://favtutor.com/blogs/forward-declaration-cpp
    string getYesNo(const string& prompt);

    // ======================================================
    // NEW FUNCTION ADDED: ASCII Dice Printer
    // REFERENCE for ASCII dice style:
    // https://ascii.co.uk/art/dice
    // https://www.asciiart.eu/miscellaneous/dice
    // ======================================================
    void printDice(int value) {
        switch (value) {
            case 1:
                // dice rolls 1
                cout << " -----\n"
                        "|     |\n"
                        "|  *  |\n"
                        "|     |\n"
                        " -----\n";
                break;
            case 2:
                // dice rolls 2
                cout << " -----\n"
                        "|*    |\n"
                        "|     |\n"
                        "|    *|\n"
                        " -----\n";
                break;
            case 3:
                // dice rolls 3
                cout << " -----\n"
                        "|*    |\n"
                        "|  *  |\n"
                        "|    *|\n"
                        " -----\n";
                break;
            case 4:
                // dice rolls 4
                cout << " -----\n"
                        "|*   *|\n"
                        "|     |\n"
                        "|*   *|\n"
                        " -----\n";
                break;
            case 5:
                // dice rolls 5
                cout << " -----\n"
                        "|*   *|\n"
                        "|  *  |\n"
                        "|*   *|\n"
                        " -----\n";
                break;
            case 6:
                // dice rolls 6
                cout << " -----\n"
                        "|*   *|\n"
                        "|*   *|\n"
                        "|*   *|\n"
                        " -----\n";
                break;
        }
    }

    // ======================================================
    // NEW FUNCTION ADDED: Fake Rolling Effect
    // Reference for console loading animation concept:
    // https://stackoverflow.com/questions/14513676/
    // ======================================================
    void rollingEffect() {
        cout << "Rolling";
        // print 3 dots, one at a time, 0.3 seconds between each print
        for (int i = 0; i < 3; i++) {
            this_thread::sleep_for(chrono::milliseconds(300));   // small pause
            cout << ".";
        }
        cout << "\n";
    }

    // ======================================================
    // MAIN GAME
    // ======================================================
    void playDiceGame() {
        string playAgain = "Y";

        // Loop continues while playAgain is 'Yes'
        while (playAgain == "Y") {

            cout << "\n--- Dice Game ---\n\n";
            cout << "Welcome to the Dice Game!\n";
            cout << "You will choose TWO numbers from 1-6.\n";
            cout << "Then press ENTER to roll each die.\n";
            cout << "WIN = both dice match your two chosen numbers.\n\n";

            // Initialize guesses
            int guess1 = 0;
            int guess2 = 0;

            // ===========================================================
            // STRICT INPUT VALIDATION
            // ===========================================================

            // FIRST USER INPUT
            while (true) {
                string line;
                cout << "Enter your FIRST number (1-6): ";
                getline(cin, line);

                // trim whitespace
                while (!line.empty() && isspace((unsigned char)line.front())) line.erase(0, 1);
                while (!line.empty() && isspace((unsigned char)line.back())) line.pop_back();

                // Assume input is bad, until proven otherwise 
                bool badInput = false;

                // If line empty, badInput=true
                if (line.empty()) badInput = true;
                else {
                    // If input is digit, with some addition, input is bad (prevents multiple valid inputs)
                    for (char c : line)
                        if (!isdigit((unsigned char)c)) badInput = true;
                }

                // If input is bad, request another
                if (badInput) {
                    cout << "Invalid input. Please enter ONE single integer only.\n";
                    continue;
                }

                // Convert string to int, to allow for range check
                int value = stoi(line);

                // Range check
                if (value < 1 || value > 6) {
                    cout << "Invalid choice. Please select a number between 1 and 6.\n";
                    continue;
                }

                guess1 = value;
                break;
            }

            // SECOND USER INPUT
            while (true) {
                string line;
                cout << "Enter your SECOND number (1-6): ";
                getline(cin, line);

                // trim whitespace
                while (!line.empty() && isspace((unsigned char)line.front())) line.erase(0, 1);
                while (!line.empty() && isspace((unsigned char)line.back())) line.pop_back();


                bool badInput = false;

                // Check input for non-numerical values
                if (line.empty()) badInput = true;
                else {
                    for (char c : line)
                        if (!isdigit((unsigned char)c)) badInput = true;
                }

                // If input is bad, prompt for new
                if (badInput) {
                    cout << "Invalid input. Please enter ONE single integer only.\n";
                    continue;
                }

                // String to int
                int value = stoi(line);

                // Range check
                if (value < 1 || value > 6) {
                    cout << "Invalid choice. Please select a number between 1 and 6.\n";
                    continue;
                }

                guess2 = value;
                break;
            }

            // ===========================================================
            // DICE ROLLING WITH NEW ANIMATION + MUST CLICK ENTER-TO-REVEAL
            // Additional interactivity
            // ===========================================================

            cout << "\nPress ENTER to roll the dice...";
            cin.get();

            // DICE 1
            int die1 = (rand() % 6) + 1;

            cout << "\nRolling Die 1... Press ENTER to roll!";
            cin.get();

            rollingEffect();       // NEW: fake roll animation
            printDice(die1);       // NEW: ASCII reveal
            cout << "Die 1 rolled: " << die1 << "\n\n";

            // DICE 2
            int die2 = (rand() % 6) + 1;

            cout << "Rolling Die 2... Press ENTER to roll!";
            cin.get();

            rollingEffect();       // NEW: fake roll animation
            printDice(die2);       // NEW: ASCII reveal
            cout << "Die 2 rolled: " << die2 << "\n\n";

            // ===========================================================
            // WIN CONDITION
            // ===========================================================
            bool win =
                // Order does not matter, so check both possibilities
                ((die1 == guess1 && die2 == guess2) ||
                (die1 == guess2 && die2 == guess1));

            if (win) {
                cout << "YOU WIN! Both dice matched your numbers!\n";
            } else {
                cout << "You lose. Better luck next time!\n";
            }

            // ===========================================================
            // PLAY AGAIN?
            // ===========================================================
            playAgain = getYesNo("\nPlay again? (Y/N): ");

            if (playAgain == "N") {
                cout << "\nReturning to main menu...\n";
                return;
            }
        }
    }

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

    // Returns 6 unique numbers from 1-49
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

    // Used to get 6 unique ints from 1-49 from user
    vector<int> getUserTicket() {
        vector<int> ticket;

        cout << "Enter 6 UNIQUE numbers between 1 and 49.\n";

        while ((int)ticket.size() < 6) { // loop until 6 ints entered
            int num = getSingleInteger( // request next int
                "Number " + to_string(ticket.size() + 1) + ": ", 
                1, 49
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
            cout << "In this game, you will select 6 unique numbers between 1 and 49.\n";
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
                extraTicket = generateUnique(6, 1, 49);

            // generate winning numbers
            vector<int> winning = generateUnique(6, 1, 49);

            // generate bonus number
            int bonusNum = rand() % 49 + 1;
            // if bonus number is already in winning line, generate new bonus
            while (find(winning.begin(), winning.end(), bonusNum) != winning.end())
                bonusNum = rand() % 49 + 1;
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

/* =========================================================
   Name Guessing Game
   ========================================================= */

    // Checks if user input (guess) is the same as Name (answer)
    bool equalsIgnoreCase(const string& a, const string& b) // No case-sensitivity in comparison
    {
        if (a.length() != b.length()) // If string lengths are not same, names are not same automatically
            return false; // exit loop

        for (size_t i = 0; i < a.length(); i++) {
            if (tolower(static_cast<unsigned char>(a[i])) != // make both string fully lowercase
                tolower(static_cast<unsigned char>(b[i]))) { // check if full match
                return false; // If no match, exit
            }
        }
        return true; // If match, win!
    }

    // Retrieve name (answer)
    string getNameByIndex(int index) {
        switch (index) {
            case 1: return "Ali";         // TODO: ADD LENGTH 4 
            case 2: return "Diwan";       
            case 3: return "Mariam";
            case 4: return "Fayzan";
            case 5: return "Jessica";
            case 6: return "Benjamin";
            case 7: return "Alexander";
        }
        return "Mariam";
    }

    bool compareNames(const string& guess, const string& answer) {
        return equalsIgnoreCase(guess, answer);
    }

    string getMatchedLetters(const string& guess, const string& answer) {
        string result;

        for (size_t i = 0; i < answer.length(); i++) {
            if (i < guess.length() &&
                tolower(static_cast<unsigned char>(guess[i])) ==
                tolower(static_cast<unsigned char>(answer[i]))) {
                result += answer[i];
            } else {
                result += '_';
            }

            if (i < answer.length() - 1)
                result += ' ';
        }

        return result;
    }

    // choose random name length
    string getRandomName() {
        int i = rand() % 7 + 1;
        return getNameByIndex(i);
    }

    // If user asks for name of certain length
    // Read various switch cases, choose based on length of string
    string getRandomNameByLength(int lengthChoice) {
        int count = 0; // initialize 

        for (int i = 1; i <= 7; i++) // when user asks for name from 1-7 letters long
            if ((int)getNameByIndex(i).length() == lengthChoice)
                count++;

        if (count == 0)
            return getRandomName();

        int target = rand() % count + 1;
        int seen = 0;

        // read length of name
        for (int i = 1; i <= 7; i++) {
            string n = getNameByIndex(i);
            if ((int)n.length() == lengthChoice) {
                seen++;
                if (seen == target)
                    return n;
            }
        }

        return getRandomName();
    }

    // MAIN GAME LOOP
    void playNameGuessingGame() {

        string playAnother = "Y";

        cout << "\n=== Guessing Name: Figuring Out the Name Edition ===\n\n";

        while (playAnother == "Y") {

            int mode = 0;

            while (true) {
                cout << "Choose an option:\n";
                cout << "1. Random name\n";
                cout << "2. Choose name length (3-10 letters)\n";
                cout << "Enter choice (1 or 2): ";

                // If user does not enter valid choice
                if (!(cin >> mode)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Enter 1 or 2.\n";
                    continue;
                }

                // If user enters valud choice
                if (mode == 1 || mode == 2)
                    break;

                cout << "Invalid choice. Enter 1 or 2.\n";
            }

            int length = 0;
            string secret;

            // If user wants to choose the length of the name they guess
            if (mode == 1) {
                secret = getRandomName();
            } else {
                while (true) {
                    cout << "Enter desired name length (3-10): ";
                    // check if input is number
                    if (!(cin >> length)) {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Invalid input. Enter a WHOLE number 3-10.\n";
                        continue;
                    }
                    // if input is number, range check
                    if (length < 3 || length > 10) {
                        cout << "Length must be between 3 and 10 letters.\n";
                    } else break;
                }
                secret = getRandomNameByLength(length);
            }

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // Initialize guess
            bool guessed = false;

            while (!guessed) {

                cout << "\nGuess the name (" << secret.length() << " letters): ";
                string guess;
                // get user guess
                getline(cin, guess);

                // if user guess is correct
                if (compareNames(guess, secret)) {
                    cout << "\nCorrect! The name was: " << secret << "\n";
                    guessed = true;
                    break;
                }

                cout << "Matching letters:\n";
                // if some letters are correct, display them
                cout << getMatchedLetters(guess, secret) << "\n";

                // encourage user to continue, ask if they keep going
                // if yes continue
                string trySame = getYesNo("Not quite... keep trying? (Y/N): ");
                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                // if no, break loop
                if (trySame == "N") break;
            }

            playAnother = getYesNo("\nPlay again with a NEW name? (Y/N): ");
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (playAnother == "N") {
                cout << "Returning to menu...\n";
                return;
            }
        }
    }

/* =========================================================
   Credits
   ========================================================= */
void showCredits() {

    string again = "Y";

    while (again == "Y") {

        cout << "\n=====================================\n";
        cout << "               CREDITS\n";
        cout << "=====================================\n\n";

        cout << "[ Mini Arcade - Version 4.7 ]\n\n";

        cout << "Developed by: Group 9\n";
        cout << "Programmer: Mariam Mueen\n";
        cout << "Programmer: Fayzabanu Diwan\n\n";

        cout << "Thank you for playing the Mini Arcade!\n\n";

        again = getYesNo("View the credits again? (Y/N): ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (again == "N") {
            cout << "\nReturning to main menu...\n";
            return;
        }
    }
}

//Fixes:
// guessing # game
    // if you previously guessed a 2 digit number, and enter the digit in the ones column as its own
    // the game prompts you to try again, thinking that the guess is a repeat even when it is not :/

    // https://www.geeksforgeeks.org/cpp/hangman-game-in-cpp/

    // REFERENCE: https://cplusplus.com/doc/tutorial/files/



