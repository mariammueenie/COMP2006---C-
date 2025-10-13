#include <iostream>
#include <string>
#include <ctime>
#include <limits>
#include <cctype>
using namespace std; 

/*
PROGRAM OUTLINE
 ARCADE LOOP: INTRODUCTION, TITLE, GET NAME FROM USER, GAME CHOICE SCREEN LOOP (Fayzabanu)
 GAME 1 - Guessing Game 
 GAME 2 - Roll the dice 
 GAME 3 - Lottery 
 CREDITS - Writers of Program
 EXIT - Exit the program
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
    cout << "Please enter your last name:" << "\n\n ";
    cin >> lastName;

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
            cout <<"LOTO MAX Random Number Game" ".\n\n";

            // game loop beings
            char playAgain = 'y';
            do {
                // get number guess from user
                cout << "Please enter your LOTTO numbers (You should input seven numbers) from 1-49, " << firstName << ".\n\n"; 

                // declare variables
                int NumberGuess1, NumberGuess2, NumberGuess3, NumberGuess4, NumberGuess5, NumberGuess6, NumberGuess7;

                // Pick #1
                while (true) {
                    cout << "Pick #1 (1-49): \n\n";
                    if (!(cin >> NumberGuess1)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n'); continue; }
                    if (NumberGuess1 < 1 || NumberGuess1 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
                    break;
                }

                // Pick #2
                while (true) {
                    cout << "Pick #2 (1-49): \n\n";
                    if (!(cin >> NumberGuess2)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n'); continue; }
                    if (NumberGuess2 < 1 || NumberGuess2 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
                    if (NumberGuess2 == NumberGuess1) { cout << "Repeat number. Try again.\n\n"; continue; }
                    break;
                }

                // Pick #3
                while (true) {
                    cout << "Pick #3 (1-49): \n\n";
                    if (!(cin >> NumberGuess3)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n'); continue; }
                    if (NumberGuess3 < 1 || NumberGuess3 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
                    if (NumberGuess3 == NumberGuess1 || NumberGuess3 == NumberGuess2) { cout << "Repeat number. Try again.\n\n"; continue; }
                    break;
                }

                // Pick #4
                while (true) {
                    cout << "Pick #4 (1-49): \n\n";
                    if (!(cin >> NumberGuess4)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n'); continue; }
                    if (NumberGuess4 < 1 || NumberGuess4 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
                    if (NumberGuess4 == NumberGuess1 || NumberGuess4 == NumberGuess2 || NumberGuess4 == NumberGuess3) { cout << "Repeat number. Try again.\n\n"; continue; }
                    break;
                }

                // Pick #5
                while (true) {
                    cout << "Pick #5 (1-49): \n\n";
                    if (!(cin >> NumberGuess5)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n'); continue; }
                    if (NumberGuess5 < 1 || NumberGuess5 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
                    if (NumberGuess5 == NumberGuess1 || NumberGuess5 == NumberGuess2 || NumberGuess5 == NumberGuess3 || NumberGuess5 == NumberGuess4) { cout << "Repeat number. Try again.\n\n"; continue; }
                    break;
                }

                // Pick #6
                while (true) {
                    cout << "Pick #6 (1-49): \n\n";
                    if (!(cin >> NumberGuess6)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n'); continue; }
                    if (NumberGuess6 < 1 || NumberGuess6 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
                    if (NumberGuess6 == NumberGuess1 || NumberGuess6 == NumberGuess2 || NumberGuess6 == NumberGuess3 ||
                        NumberGuess6 == NumberGuess4 || NumberGuess6 == NumberGuess5) { cout << "Repeat number. Try again.\n\n"; continue; }
                    break;
                }

                // get 7 numbers from user, and validate inputs
                while (true) {
                    cout << "Pick #7 (1-49): \n\n";
                    if (!(cin >> NumberGuess7)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n'); continue; }
                    if (NumberGuess7 < 1 || NumberGuess7 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
                    if (NumberGuess7 == NumberGuess1 || NumberGuess7 == NumberGuess2 || NumberGuess7 == NumberGuess3 ||
                    NumberGuess7 == NumberGuess4 || NumberGuess7 == NumberGuess5 || NumberGuess7 == NumberGuess6) { cout << "Repeat number. Try again.\n\n"; continue; }
                    break;
                }

                // print user input numbers to console
                cout << "You guessed: \n\n"
                << NumberGuess1 << ' ' << NumberGuess2 << ' ' << NumberGuess3 << ' '
                << NumberGuess4 << ' ' << NumberGuess5 << ' ' << NumberGuess6 << ' '
                << NumberGuess7 << ".\n\n";
                                
                // generate 7 random numbers between 1 and 49
                // Reference: https://cplusplus.com/reference/cstdlib/rand/
                // Chose to find more efficient way of generating random numbers lol 
                // generate 7 random numbers between 1 and 49
                int GeneratedNumber1, GeneratedNumber2, GeneratedNumber3,
                GeneratedNumber4, GeneratedNumber5, GeneratedNumber6, GeneratedNumber7;
                
                GeneratedNumber1 = (rand() % 49) + 1;
                do { GeneratedNumber2 = (rand() % 49) + 1; } while (GeneratedNumber2 == GeneratedNumber1);
                do { GeneratedNumber3 = (rand() % 49) + 1; } while (GeneratedNumber3 == GeneratedNumber1 || GeneratedNumber3 == GeneratedNumber2);
                do { GeneratedNumber4 = (rand() % 49) + 1; } while (GeneratedNumber4 == GeneratedNumber1 || GeneratedNumber4 == GeneratedNumber2 || GeneratedNumber4 == GeneratedNumber3);
                do { GeneratedNumber5 = (rand() % 49) + 1; } while (GeneratedNumber5 == GeneratedNumber1 || GeneratedNumber5 == GeneratedNumber2 || GeneratedNumber5 == GeneratedNumber3 || GeneratedNumber5 == GeneratedNumber4);
                do { GeneratedNumber6 = (rand() % 49) + 1; } while (GeneratedNumber6 == GeneratedNumber1 || GeneratedNumber6 == GeneratedNumber2 || GeneratedNumber6 == GeneratedNumber3 || GeneratedNumber6 == GeneratedNumber4 || GeneratedNumber6 == GeneratedNumber5);
                do { GeneratedNumber7 = (rand() % 49) + 1; } while (GeneratedNumber7 == GeneratedNumber1 || GeneratedNumber7 == GeneratedNumber2 || GeneratedNumber7 == GeneratedNumber3 || GeneratedNumber7 == GeneratedNumber4 || GeneratedNumber7 == GeneratedNumber5 || GeneratedNumber7 == GeneratedNumber6);
                            
                // print generated numbers to console
                cout << "The lucky LOTO numbers are: "
                << GeneratedNumber1 << " "
                << GeneratedNumber2 << " "
                << GeneratedNumber3 << " "
                << GeneratedNumber4 << " "
                << GeneratedNumber5 << " "
                << GeneratedNumber6 << " "
                << GeneratedNumber7 << "\n\n";
                                    
                // compare user input numbers to generated numbers
                bool allEqual = true;

                for (int i = 1; i<=7; i++) {
                    int guess = 0, draw = 0;

                    switch(i) {
                        case 1:
                            guess = NumberGuess1; 
                            draw = GeneratedNumber1; 
                            break;
                        case 2:
                            guess = NumberGuess2;
                            draw = GeneratedNumber2;
                            break;
                        case 3:
                            guess = NumberGuess3;
                            draw = GeneratedNumber3;
                            break;
                        case 4:
                            guess = NumberGuess4;
                            draw = GeneratedNumber4;
                            break;
                        case 5:
                            guess = NumberGuess5;
                            draw = GeneratedNumber5;
                            break;
                        case 6:
                            guess = NumberGuess6;
                            draw = GeneratedNumber6;
                            break;
                        case 7:
                            guess = NumberGuess7;
                            draw = GeneratedNumber7;
                        break;
                        }
                        if (guess != draw) {
                                allEqual = false; // at least one pair is not equal
                                break; // no need to check further 
                        }
                    }
                    if (allEqual) {
                        cout << "Congratulations " << firstName << "! Your numbers matched! You win the jackpot!\n\n";
                    } else {
                        cout << "Sorry, not all the numbers matched. Better luck next time!\n\n";
                    }

                    // thank player, and end game 
                    cout << "Thank you for playing, " << firstName << "." ".\n\n";
                    cout << "Do you want to play again? (y/n): " "\n\n";
                    cin >> playAgain;

                } 
                while (tolower(playAgain) == 'y');
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
