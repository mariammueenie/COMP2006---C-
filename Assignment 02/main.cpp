#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <limits>
#include <iomanip>
#include <cctype>
using namespace std; 

/*
// PROGRAM OUTLINE
PART A: INTRODUCTION, TITLE, GET NAME FROM USER, GAME CHOICE SCREEN LOOP (Fayzabanu)
PART B: GAME 1: Guessing Game (Mariam)
Part C: GAME 2: Roll the dice (Fayzabanu)
Part D: GAME 3: Lottery (Mariam)
*/

int main() {
    // Declare variables 
    string firstName, lastName;
    int gameChoice;
    srand(static_cast<unsigned int>(time(0))); // Seed random number generator

    // Ask for players first and last name
    cout << "Welcome to The Mini Arcade!!\n" << endl;
    cout << "Please enter your first name:\n ";
    cin >> firstName;
    cout << "Please enter your last name:\n ";
    cin >> lastName;

    // Greet the player
    cout << "Hello," << firstName << " " << lastName << "! Lets play a game.\n" << endl;

/* ========== MENU LOOP STARTS HERE ========== */
    do {

        // Display game choices 
        cout << "================================"<< endl;
        cout << "           GAME MENU            "<< endl;
        cout << "================================"<< endl;
        cout << "1. Guessing Game" << endl;
        cout << "2. Roll the Dice" << endl;
        cout << "3. Lottery" << endl;   
        cout << "4. Credits" << endl;
        cout << "5. Exit" << endl;
        cout << "================================"<< endl;
        cout << "Please enter the number of the game you would like to play: ";

        cin >> gameChoice;
            if (!cin) {
                cout << "Invalid input. Please enter a number between 1 and 5." << endl;
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                gameChoice = 0; // Reset gameChoice to an invalid value
            }

        // Game choice logic. 
        switch(gameChoice) {
        /* ========== GAME 1: GUESSING GAME ========== */
            case 1: {
                // Guessing game logic here
                cout << "Hello, " << firstName << " welcome to the Guessing Game!" << endl;
                
                // Explain game to user.
                cout << "In this game, you will try to guess a number between 1 and 100." << endl;
                cout << "You will have 3 attempts to guess the correct number." << endl;

                // Limit the number of attempts to 3
                int limit = 3; 
                int count = 0;

                do {
                    // std::cout << "Count." << count << std::endl;
                    // Generate random number between 1 and 100
                    int randomNumber = (rand() % 100) + 1; // Random number between 1 and 100

                    // Get user's guess with validation loop
                    cout << "Enter your guess (1-100): ";
                    int userGuess;
                    cin >> userGuess;

                    if (userGuess < 1 || userGuess > 100) {
                        cout << "Invalid input. Please enter a number between 1 and 100." << endl;
                        continue; // Skip to the next iteration of the loop

                    }

                    count++; // Increment attempt count

                    if (userGuess < randomNumber) {
                        cout << "Too low! Try again." << endl;
                    }

                    else if (userGuess > randomNumber) {
                        cout << "Too high! Try again." << endl;
                    }

                    else (userGuess == randomNumber) {
                        cout << "Congratulations " << firstName << "! You guessed the correct number!" << endl;
                        break; // Exit the loop if the user guesses correctly
                    }
                
                } while (count < limit);

                cout << "Returning to main menu..." << endl;
                break;
            } // End of case 1

        /* ========== GAME 2: ROLL THE DICE ========== */
            case 2:

                // Game 2: Roll the Dice - Loop begins here

                char playAgain;
                do {
                // Roll the dice logic here
                cout << "Hello, " << firstName << " welcome to Roll the Dice!" << endl;
                
                    // Fayzabanu's code will go here
                    // --------- GAME 2: Roll the Dice with full validation ---------

                    cout << "Hello, " << firstName << " welcome to Roll the Dice!" << endl;
                    cout << "In this game, you will roll two dice and try to get 2 matching numbers!" << endl;
                    cout << "If you get doubles, you win!" << endl;
                    cout << "Press Enter to roll the dice...";

                    // roll dice when user presses enter
                    int userDie1 = (rand()% 6) + 1; // Random number between 1 and 6
                    int UserDie2 = (rand()% 6) + 1; // Random number between 1 and 6

                    // roll dice for computer
                    int compDie1 = (rand()% 6) + 1; // Random number between 1 and 6
                    int compDie2 = (rand()% 6) + 1; // Random number between 1 and 6

                    // Print the results
                    cout << "\nYou rolled: " << userDie1 << " and " << UserDie2 << endl;
                    cout << "The computer rolled: " << compDie1 << " and " << compDie2 << endl; 

                    // Determine the winner
                    if (userDie1 == UserDie2 && compDie1 == compDie2) {
                        cout << "It's a tie! Both you and the computer rolled doubles!" << endl;
                    } 
                    else if (userDie1 == UserDie2) {
                        cout << "Congratulations " << firstName << "! You win with doubles!" << endl;
                    } 
                    else if (compDie1 == compDie2) {
                        cout << "The computer wins with doubles! Better luck next time, " << firstName << "!" << endl;
                    } 
                    else {
                        cout << "No doubles rolled. It's a draw!" << endl;
                    }
                } while (tolower(playAgain) == 'y');
                cout << "Returning to main menu..." << endl;
                break;

        /* ========== GAME 3: LOTTERY ========== */
            case 3:
                // Lottery logic here
                cout << "Hello, " << firstName << " welcome to the Lottery!" << endl;

                cout << "Returning to main menu..." << endl;
                break;

        /* ========== CREDITS ========== */
            case 4:
                // Credits logic here
                cout << "CREDITS\n";
                cout << "This Mini Arcade was created by:\n";
                cout << "Mariam Mueen\n";
                cout << "Fayzabanu Diwan\n";
                cout << "Group 9\n";
                cout << "Returning to main menu..." << endl;
                break;

        /* ========== EXIT LOGIC ========== */
            case 5:
                // Exit logic here
                cout << "Thank you for playing, " << firstName << "! See you next time.\n";
                break;

        /* ========== INVALID INPUT HANDLING ========== */
            default: 
                // When input is invalid
                cout << "Invalid choice. Please select a valid option from the menu.\n";
                break;

        } 
        cout << endl; // Extra line between loops for readability

    } while (gameChoice != 5); // End game choice loop
/* ========== MENU LOOP ENDS HERE ========== */

return 0;

}














// {
//     // Title and group info
//     cout << " MINI ARCADE \n";
//     cout << "Written by Mariam Mueen\n";
//     cout << "and Fayzabanu Diwan\n";
//     cout << "Group 9\n\n";

//     // Step 1: Get player details
//     string firstName, lastName;
//     cout << "Please enter your first name: ";
//     cin >> firstName;
//     cout << "Please enter your last name: ";
//     cin >> lastName;

//     cout << "\nHello " << firstName << " " << lastName << "!\n";

//     // Ask if they want to play
//     char playChoice;
//     cout << "Would you like to play a game? (Y/N): ";
//     cin >> playChoice;
//     playChoice = toupper(playChoice);

//     if (playChoice == 'Y') {
//         // Show main menu
//         cout << "\n Choose your game\n";
//         cout << "1 -  Guessing Game\n";
//         cout << "2 -  Roll the Dice\n";
//         cout << "3 -  Lottery\n";
//         cout << "4 -  Exit\n";
//         cout << "\nEnter your choice (1-4): ";
//         //  We'll add logic for choices in the next step
//     }
//     else {
//         cout << "\nThank you, " << firstName << "! See you next time \n";
//     }

//     return 0;
// }


