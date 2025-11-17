#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include <cctype>
#include <vector> // For using vectors in Game 3: Lottery
#include <fstream> // For file handling to log Game 3: Lottery results
#include <iomanip> // For formatting file output
using namespace std; 
using std::vector; // For using vectors in Game 3: Lottery

/*
PROGRAM OUTLINE
 ARCADE LOOP: INTRODUCTION, TITLE, GET NAME FROM USER, GAME CHOICE SCREEN LOOP (Fayzabanu)
 GAME 1 - Guessing Game 
 GAME 2 - Roll the dice 
 GAME 3 - Lottery 
 CREDITS - Writers of Program
 EXIT - Exit the program
*/

    /* To build and test on VS Developer Command Prompt
    first:
        cd C:\Users\maria\Documents\GitHub\COMP2006---C-\Assignment 02>build\main.cpp
        cl /std:c++17 /EHsc main.cpp /Fe:build\app.exe
        build\app.exe
    */

/* ============================================================
   VALIDATION HELPERS
   These three functions are the core of your "airtight" input:
   - they validate
   - they clear bad state
   - they flush leftover characters on the line
   ============================================================ */

// *** ADDED FOR AIRTIGHT VALIDATION ***
// gets a single-token name and rejects digits/symbols
string get_valid_name(const string& prompt) {
    while (true) {
        string name;
        cout << prompt;
        if (!(cin >> name)) { // stream error (e.g. EOF, weird type)
            cout << "Invalid input. Please enter letters only.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush line
            continue;
        }

        bool ok = true;
        for (char c : name) {
            if (!isalpha(static_cast<unsigned char>(c))) { // reject digits/symbols
                ok = false;
                break;
            }
        }

        // *** IMPORTANT: throw away anything else the user typed on this line
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // *** ADDED: prevents "multiple entries" carrying over

        if (!ok) {
            cout << "Name can only contain letters (no numbers or symbols).\n\n";
            continue;
        }

        return name; // valid, clean token
    }
}

// *** ADDED FOR AIRTIGHT VALIDATION ***
// gets an int in a specific [min, max] range and flushes the rest of the line
int get_int_in_range(const string& prompt, int min, int max) {
    while (true) {
        int value;
        cout << prompt;
        if (!(cin >> value)) { // not an int at all
            cout << "Invalid input. Please enter a whole number.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // flush junk
            continue;
        }

        // throw away any extra characters on the same line
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // *** ADDED: kills "3 4 5" leftovers

        if (value < min || value > max) {
            cout << "Out of range. Please enter a number between "
                 << min << " and " << max << ".\n\n";
            continue;
        }

        return value; // valid
    }
}

// *** ADDED FOR AIRTIGHT VALIDATION ***
// gets a yes/no char, forces y/n, and flushes the rest of the line
char get_yes_no(const string& prompt) {
    while (true) {
        char c;
        cout << prompt;
        if (!(cin >> c)) {
            cout << "Invalid input. Please enter y or n.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        // flush everything else on this line so it doesn't bleed into next input
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // *** ADDED: kill leftovers

        c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        if (c == 'y' || c == 'n') {
            return c;
        }

        cout << "Please enter y or n.\n\n";
    }
}

/* ========== ARCADE LOOP ==========*/
int main() {
    // Declare variables 
    string firstName, lastName;
    int gameChoice;
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    // Ask for player's first and last name
    cout << "Welcome to The Mini Arcade!!" << "\n\n" ;

    // *** UPDATED: use helper so name has only letters and no extra junk on the line
    firstName = get_valid_name("Please enter your first name: \n\n ");   // *** ADDED HELPER
    cout << "\n";
    lastName  = get_valid_name("Please enter your last name:  \n\n ");   // *** ADDED HELPER
    cout << "\n";

    // Greet the player
    cout << "Hello, " << firstName << " " << lastName << "! Lets play a game.\n\n";


/* ========== MENU LOOP STARTS HERE ========== */
    do {

        // Display game choices 
        cout << "================================"<< "\n";
        cout << "           GAME MENU            "<< "\n";
        cout << "================================"<< "\n";
        cout << "1. Guessing Game" << "\n";
        cout << "2. Roll the Dice" << "\n";
        cout << "3. Lottery" << "\n";   
        cout << "4. Credits" << "\n";
        cout << "5. Exit" << "\n";
        cout << "================================"<< "\n";

        // *** UPDATED: use helper so menu choice is always 1-5 and never carries extra input
        gameChoice = get_int_in_range(
            "Please enter the number of the game you would like to play: \n\n",
            1, 5); // *** ADDED HELPER CALL

        cout << "\n"; // ADDED: fix spacing issues 

        // Game choice logic. 
        switch(gameChoice) {

/* ========== GAME 1 - GUESSING GAME ========== */
            case 1: {
                // Guessing game logic here
                cout << "Hello, " << firstName << " Welcome to the Guessing Game!" << "\n\n";
                
                // Explain game to user.
                cout << "In this game, you will try to guess a number between 1 and 100.\n\n";
                cout << "You will have 3 attempts to guess the correct number.\n\n";

                char playAgain;

                do {
                    // Limit the number of attempts to 3
                    int limit = 3; 
                    int count = 0;
                    int randomNumber = (rand() % 100) + 1; // Random number between 1 and 100

                    do {
                        // Get user's guess with validation
                        // *** UPDATED: use helper so guess is 1–100 and no leftover input stays in the buffer
                        int userGuess = get_int_in_range(
                            "Enter your guess (1-100): ",
                            1, 100); // *** ADDED HELPER CALL

                        count++; // Increment attempt count
                        cout << "Attempt " << count << " of " << limit << ".\n\n" << endl;

                        if (userGuess < randomNumber) {
                            cout << "Too low!\n\n" << endl;
                        }
                        else if (userGuess > randomNumber) {
                            cout << "Too high!\n\n" << endl;
                        }
                        else {
                            cout << "Congratulations " << firstName
                                 << "! You guessed the correct number!\n\n" << endl;
                            break; // Exit the loop if the user guesses correctly
                        }

                        if (count == limit) {
                            cout << "Sorry, you've used all your attempts. The correct number was "
                                 << randomNumber << ".\n\n" << endl;
                        }
                    } while (count < limit);
                
                    // Ask if the user wants to play again
                    // *** UPDATED: use helper so only y/n is accepted and buffer is clean
                    playAgain = get_yes_no("Do you want to play again? (y/n): \n\n"); // *** ADDED HELPER CALL

                } while  (playAgain == 'y'); // helper already lowercases
                cout << "Returning to main menu...\n\n" << endl;
                break;
            }
// End of GAME 1

/* ========== GAME 2 - ROLL THE DICE ========== */
            case 2: {
                char playAgain;
                do {
                    // explain the game
                    cout << "Hello, " << firstName << ". Lets play Roll the Dice!\n";
                    cout << "Enter two numbers (1-6). If BOTH match the computer's roll (in order), you win!\n\n";

                    // get two numbers from user
                    int firstRoll, secondRoll;

                    // *** UPDATED: use helper to validate 1–6 and flush line
                    firstRoll = get_int_in_range(
                        "Enter your first number (1-6): \n\n",
                        1, 6); // *** ADDED HELPER CALL

                    // *** UPDATED: same for second roll
                    secondRoll = get_int_in_range(
                        "Enter your second number (1-6): \n\n",
                        1, 6); // *** ADDED HELPER CALL

                    // computer rolls
                    int comp1 = (rand() % 6) + 1;
                    int comp2 = (rand() % 6) + 1;

                    // print results
                    cout << "You chose: " << firstRoll << " " << secondRoll << "\n\n";
                    cout << "Computer rolled: " << comp1 << " " << comp2 << "\n\n";

                    // determine if user won
                    if (firstRoll == comp1 && secondRoll == comp2) {
                        cout << "Both numbers match, YOU WIN!\n\n";
                    } else {
                        cout << "At least one number didn't match, you lose.\n\n";
                    }

                    // ask to play again
                    // *** UPDATED: helper for y/n validation, flushes line
                    playAgain = get_yes_no("Play again? (y/n): \n\n"); // *** ADDED HELPER CALL
                    cout << "\n";

                } while (playAgain == 'y'); // end of game loop
                cout << "Returning to main menu..." << endl;
                break;
            } 
// End of GAME 2

/* ========== GAME 3 - LOTTERY ========== */
            case 3: {

            // Lottery logic here
            cout << "Hello, " << firstName << " welcome to the Lottery!\n\n";

            // print title of game, then, new line
            cout <<"LOTTO MAX Random Number Game - Vector Edition" ".\n\n";

            // Explain the game to the user
            cout << "In this game, you will select 7 unique numbers between 1 and 49.\n\n";
            cout << "The computer will also generate 7 unique random numbers between 1 and 49 for you.\n\n";
            cout << "Finally, 7 winning numbers will be drawn.\n\n";
            cout << "If your numbers match 3 or more winning numbers (regardless of order), you win a prize!\n\n";
            cout << "The computer generated numbers will also be checked, and if they match, you could win prizes!\n\n";
            cout << "The more numbers you match, the bigger the prize!\n\n";

            // ADDED: Price per ticket for LOTTO Game
            cout << "Each ticket costs $5.00 CAD.\n\n";

            // Replay loop variable 
            char playAgain = 'y';

            do { 

                // Vector for user input
                vector<int> userNumbers;

                // Vector for auto-generated numbers
                vector<int> autoGeneratedNumbers;

                // Vector for winning numbers
                vector<int> winningNumbers;

                cout << "\n" "Please enter your 7 unique numbers between 1 and 49:\n\n";

                // Validation loop for userNumbers
                while (userNumbers.size() < 7) {
                    cout << "Enter number " << (userNumbers.size() + 1) << " (1-49): ";
                    int num;

                    // *** UPDATED: same pattern as get_int_in_range, but we keep the duplicate logic here
                    if (!(cin >> num)) {
                        cout << "Invalid input. Please enter a number between 1 and 49." << endl;
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // *** ADDED: flush whole line
                        continue;
                    }

                    // throw away any trailing junk on the same line
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // *** ADDED: stop extra numbers from carrying into the next prompt

                    if (num < 1 || num > 49 ) {
                        cout << "Out of range. Please enter a number between 1 and 49." << endl;
                        continue;
                    }

                    // check for duplicates
                    bool dup = false;
                    for (int x : userNumbers) {
                        if (x == num) { dup = true; break; }
                    }
                    if (dup) {
                        cout << "Duplicate number. Please enter a different number." << endl;
                        continue;
                    }
                    userNumbers.push_back(num);
                }
                
                // Auto-generate 7 unique random numbers between 1 and 49
                while (autoGeneratedNumbers.size() < 7) {
                    int randNum = (rand() % 49) +1; // random number between 1 and 49
                    bool exists = false;
                    for (int x : autoGeneratedNumbers) if (x == randNum) { exists = true; break;}
                    if (!exists) autoGeneratedNumbers.push_back(randNum);
                }

                // Generate 7 unique winning numbers between 1 and 49
                while (winningNumbers.size() < 7) {
                    int winNum = (rand() % 49) +1;
                    bool exists = false;
                    for (int x : winningNumbers) if (x == winNum) { exists = true; break;}
                    if (!exists) winningNumbers.push_back(winNum);
                }

                // Order-Independent matching lambda
                auto countMatches = [](const vector<int>& a, const vector<int>& b) {
                    int matches = 0;
                    for (int i = 0; i < 7; ++i) {
                        for (int j = 0; j< 7; ++j) {
                            if (a[i] == b[j]) {
                                matches++;
                                break;
                            }
                        }
                    }
                    return matches;
                };

                int matchUser = countMatches(userNumbers, winningNumbers);
                int matchAuto = countMatches(autoGeneratedNumbers, winningNumbers);

                auto prizeFor = [](int matches) -> double {
                    switch (matches) {
                        case 6: return 5000000.00;
                        case 5: return 250000.00;
                        case 4: return 10000.00;
                        case 3: return 1000.00;
                        default: return 0.00;
                    }
                }; 
                
                double prizeUser = prizeFor(matchUser);
                double prizeAuto = prizeFor(matchAuto);

                 // ticket summary + results (setw-aligned)
                 cout << "\n==============================\n";
                 cout << "YOUR LOTTERY TICKET\n";
                 cout << "==============================\n";

                 cout << left << setw(12) << "Line 1:";
                 for (int n : userNumbers) cout << setw(3) << n;
                 cout << "\n";

                 cout << left << setw(12) << "Line 2:";
                 for (int n : autoGeneratedNumbers) cout << setw(3) << n;
                 cout << "\n";

                 cout << "\nWinning Numbers: ";
                 for (int n : winningNumbers) cout << setw(3) << n;
                 cout << "\n\n";

                cout << "==============================\n";
                cout << "RESULTS SUMMARY\n";
                cout << "==============================\n";

                 cout << "Your Numbers Matches: " << matchUser << " Match -> ";
                 if (prizeUser > 0) cout << "$" << prizeUser << " CAD\n";
                 else cout << "Better luck next time!\n";

                 cout << "Computer-Generated Matches: " << matchAuto << " Match -> ";
                 if (prizeAuto > 0) cout << "$" << prizeAuto << " CAD\n";
                 else cout << "Better luck next time!\n";

                // Log results to txt file
                {
                    ofstream file("lottery_ticket.txt", ios::app);
                    if (file) {
                        file << "==============================\n";
                        file << "Lottery Ticket (Group 9)\n";
                        file << "==============================\n";
                        file << left << setw(12) << "Line 1:";
                        for (int n : userNumbers) file << setw(3) << n;
                        file << "\n";

                        file << left << setw(12) << "Line 2:";
                        for (int n : autoGeneratedNumbers) file << setw(3) << n;
                        file << "\n";

                        file << "\nWinning Numbers: ";
                        for (int n : winningNumbers) file << setw(3) << n;
                        file << "\n";

                        file << "Line 1 Matches: " << matchUser;
                        if (prizeUser > 0) file << " -> $" << prizeUser << " CAD\n";
                        else file << " -> Better luck next time!\n";

                        file << "Line 2 Matches: " << matchAuto;
                        if (prizeAuto > 0) file << " -> $" << prizeAuto << " CAD\n";
                        else file << " -> Better luck next time!\n";

                        file << "==============================\n\n";
                    }
                }

                // Ask to play again
                // *** UPDATED: use helper instead of raw cin >> playAgain
                playAgain = get_yes_no(
                    "\nYour results have been saved to 'lottery_ticket.txt'.\n"
                    "Play Lottery again? (y/n): "); // *** ADDED HELPER CALL

                // no need for extra manual cin.clear/ignore here; helper already did it

                } while (playAgain == 'y');
                cout << "Returning to main menu..." << endl;
            break;
            } 
// End of case 3 

/* ========== CREDITS ========== */
            case 4:
                // Credits logic here
                cout << "CREDITS\n\n";
                cout << "This Mini Arcade was created by:\n\n";
                cout << "Mariam Mueen\n\n";
                cout << "Fayzabanu Diwan\n\n";
                cout << "Group 9\n\n";
                cout << "Returning to main menu..." << endl;
                break;

/* ========== EXIT LOGIC ========== */
            case 5:
                // Exit logic here
                cout << "Thank you for playing, " << firstName << "! See you next time.\n\n";
                break;

/* ========== INVALID INPUT HANDLING ========== */
            default: 
                // Now basically unreachable because menu input is clamped to 1–5,
                // but we can leave this as an extra safety net.
                cout << "Invalid choice. Please select a valid option from the menu.\n\n";
                break;
        } 
        cout << endl; // Extra line between loops for readability

    } while (gameChoice != 5); // End game choice loop

/* ========== MENU LOOP ENDS HERE ========== */

    return 0;
}
