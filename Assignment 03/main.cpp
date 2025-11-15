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

/* ========== ARCADE LOOP ==========*/
int main() {
    // Declare variables 
    string firstName, lastName;
    int gameChoice;
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    // Ask for players first and last name
    cout << "Welcome to The Mini Arcade!!" << "\n\n" ;
    cout << "Please enter your first name: " << "\n\n ";
    cin >> firstName;
    cout << "\n"; // ADDED: fix spacing issues
    cout << "Please enter your last name:" << "\n\n ";
    cin >> lastName;
    cout << "\n"; // ADDED: fix spacing issues

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
        cout << "Please enter the number of the game you would like to play: " "\n\n";

        cin >> gameChoice;
            if (!cin) {
                cout << "Invalid input. Please enter a number between 1 and 5.\n\n";
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                gameChoice = 0; // Reset gameChoice to an invalid value
            }

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
                    // std::cout << "Count." << count << std::endl;
                    // Generate random number between 1 and 100

                    // Get user's guess with validation loop
                    cout << "Enter your guess (1-100): ";
                    int userGuess;
                    cin >> userGuess;
                    
                    if (!cin) {
                        cout << "Invalid input. Please enter a number between 1 and 100.\n\n";
                        cin.clear(); // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        continue; // Skip to the next iteration of the loop
                    }

                    if (userGuess < 1 || userGuess > 100) {
                        cout << "Invalid input. Please enter a number between 1 and 100.\n\n" << endl;
                        continue; // Skip to the next iteration of the loop

                    }

                    count++; // Increment attempt count
                    cout << "Attempt " << count << " of " << limit << ".\n\n" << endl;


                    if (userGuess < randomNumber) {
                        cout << "Too low!\n\n" << endl;
                    }

                    else if (userGuess > randomNumber) {
                        cout << "Too high!\n\n" << endl;
                    }

                    else if (userGuess == randomNumber) {
                        cout << "Congratulations " << firstName << "! You guessed the correct number!\n\n" << endl;
                        break; // Exit the loop if the user guesses correctly
                    }
                    if (count == limit) {
                        cout << "Sorry, you've used all your attempts. The correct number was " << randomNumber << ".\n\n" << endl;
                    }
                } while (count < limit);
                
                // Ask if the user wants to play again
                    cout << "Do you want to play again? (y/n): \n\n";
                    cin >> playAgain;

            } while  (tolower(playAgain) == 'y');

                cout << "Returning to main menu...\n\n" << endl;
                break;
            }
// End of GAME 1

/* ========== GAME 2 - ROLL THE DICE ========== */
            case 2: {
                char playAgain;
                do {
                    // explain the game
                    cout << "Hello, " << firstName << ". 1Lets play Roll the Dice!\n";
                    cout << "Enter two numbers (1-6). If BOTH match the computer's roll (in order), you win!\n\n";

                    // get two numbers from user
                    int firstRoll, secondRoll;

                    // validation
                    while (true) {
                        cout << "Enter your first number (1-6): \n\n";
                        if (!(cin >> firstRoll)) {
                            cout << "Not a number. Try again.\n\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            continue;
                        }
                        if (firstRoll < 1 || firstRoll > 6) {
                            cout << "Out of range. Try again.\n\n";
                            continue;
                        }
                        break;
                    }

                    // validation
                    while (true) {
                        cout << "Enter your second number (1-6): \n\n";
                        if (!(cin >> secondRoll)) {
                            cout << "Not a number. Try again.\n\n";
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n\n');
                            continue;
                        }
                        if (secondRoll < 1 || secondRoll > 6) {
                            cout << "Out of range. Try again.\n\n";
                            continue;
                        }
                        break;
                    }

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
                    cout << "Play again? (y/n): \n\n";
                    cin >> playAgain;
                    cout << "\n";

                } while (tolower(playAgain) == 'y'); // end of game loop
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

                // ADDED: Vector for user input
                vector<int> userNumbers;

                // ADDED: Vector for auto-generated numbers
                vector<int>autoGeneratedNumbers;

                // ADDED: Vector for winning numbers
                vector<int> winningNumbers;

                cout << "\n" "Please enter your 7 unique numbers between 1 and 49:\n\n";

                // ADDED: Validation loop for userNumbers
                while (userNumbers.size() < 7) {
                    cout << "Enter number " << (userNumbers.size() + 1) << " (1-49): ";
                    int num;

                    // what to do if userGuess is not a number
                    if (!(cin >> num)) {
                        cout << "Invalid input. Please enter a number between 1 and 49." << endl;
                        cin.clear(); // clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
                        continue; // skip to the next iteration of the loop
                    }

                    // what to do if userGuess is out of range
                    if (num < 1 || num > 49 ) {
                        cout << "Out of range. Please enter a number between 1 and 49." << endl;
                        continue;
                    }

                    // what to do if userGuess is a duplicate
                    bool dup = false;
                    for (int x : userNumbers) if (x == num) { dup = true; break; }
                    if (dup) {
                        cout << "Duplicate number. Please enter a different number." << endl;
                        continue;
                    }
                    userNumbers.push_back(num); // ADDED: add validated number to vector userGuesses
                }
                
                // ADDED: Auto-generate 7 unique random numbers between 1 and 49
                while (autoGeneratedNumbers.size() < 7) {
                    int randNum = (rand() % 49) +1; // random number between 1 and 49
                    bool exists = false; // exists will allow checks for duplicates in autoGeneratedNumbers
                    for (int x : autoGeneratedNumbers) if (x == randNum) { exists = true; break;} // check for duplicates
                    if (!exists) autoGeneratedNumbers.push_back(randNum); // add unique number to vector
                }

                // ADDED: Generate 7 unique winning numbers between 1 and 49
                while (winningNumbers.size() < 7) {
                    int winNum = (rand() % 49) +1; // random number between 1 and 49
                    bool exists = false; // exists will allow checks for duplicates in winningNumbers
                    for (int x : winningNumbers) if (x == winNum) { exists = true; break;} // check for duplicates
                    if (!exists) winningNumbers.push_back(winNum);
                }

                // ADDED: Order-Independent sorting of vectors autoGeneratedNumbers and winningNumbers
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
                    return matches; // return total matches found
                };

                // ADDED: Count matches between userNumbers/autoGeneratedNumbers and winningNumbers
                int matchUser = countMatches(userNumbers, winningNumbers); // count matches between userNumbers and winningNumbers
                int matchAuto = countMatches(autoGeneratedNumbers, winningNumbers); // count matches between autoGeneratedNumbers and winningNumbers

                // ADDED: Prize tiers for matches 
                auto prizeFor = [](int matches) -> double {
                    // switch (matches) will switch between cases on the basis of the value of matches
                    switch (matches) {
                        case 6: return 5000000.00; // 6 matches, $5MILL Prize
                        case 5: return 250000.00; // 5 matches, $250K Prize
                        case 4: return 10000.00; // 4 matches, $10K Prize
                        case 3: return 1000.00; // 3 matches, $1K Prize
                        default: return 0.00; // Less than 3 matches, no prize
                    }
                }; 
                
                //
                double prizeUser = prizeFor(matchUser); // determine prize for userNumbers
                double prizeAuto = prizeFor(matchAuto); // determine prize for autoGeneratedNumbers

                 // ADDED: ticket summary + results (setw-aligned)
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

                // ADDED: Log results to txt file
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

                // ADDED: Ask to play again
                cout << "\nYour results have been saved to 'lottery_ticket.txt'.\n";
                cout << "Play Lottery again? (y/n): ";
                cin >> playAgain;

                // ADDED: Clean vectors for next potential round
               if (!cin) { cin.clear(); cin.ignore(numeric_limits<streamsize>::max(), '\n'); playAgain = 'n'; }

                } while (tolower(playAgain) == 'y');
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
                // When input is invalid
                cout << "Invalid choice. Please select a valid option from the menu.\n\n";
                break;
        } 
        cout << endl; // Extra line between loops for readability

    } while (gameChoice != 5); // End game choice loop

/* ========== MENU LOOP ENDS HERE ========== */

return 0;

}


// Notes for improvement:
// Intro: FIX NAME VALIDATION (no numbers/special chars/MULTIPLE entries)
// CHOOSING VALIDATION (dont carry multiple entries from 1 value)
// Intro: Ask user if they want to play game at start 
// Lottery: Make instructions less spaced out
// Lottery: Add ability to choose how many tickets to buy at once
// Lottery: Add ability to choose custom number ranges and ticket prices
// Lottery: Add ability to view past tickets from txt file within program
// Lottery: Add ability to choose numbers vs auto-generate
// Lottery: Add ability to save ticket with custom name
// VALIDATE VALIDATE VALIDATE inputs everywhere
// iNCLUDE user name in lottery ticket file
// Include version number and date? and such in credits 
// FOLLOW INSTRUCTIONS TO A T. LETTER FOR LETTER