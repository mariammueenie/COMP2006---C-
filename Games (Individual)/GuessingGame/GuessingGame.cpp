#include <iostream>
#include <string>
//#include <cmath>
#include <ctime>
#include <limits>
//#include <iomanip>
#include <cctype>
#include <cstdio> // for printf
// stops windows.h from defining min and max macros
//#define NOMINMAX
//#include <windows.h> // For Sleep function
#include <thread> // For this_thread::sleep_for
#include <chrono> // For chrono::milliseconds
#include <conio.h> // For _kbhit() and _getch()
#include <cstdlib> // For rand and srand

using namespace std; 
using namespace std::chrono_literals; // for using 45ms

// Here is how to run game in VS Developer Command Prompt
/*

cd "C:\Users\maria\Documents\GitHub\COMP2006---C-\Assignment 02\Games (Individual)"
if not exist build mkdir build
cl /std:c++17 /EHsc GuessingGame.cpp /Fe:build\GuessingGame.exe
build\GuessingGame.exe

*/

/*
// PROGRAM OUTLINE
PART A: INTRODUCTION, TITLE, GET NAME FROM USER, GAME CHOICE SCREEN LOOP (Fayzabanu)
PART B: GAME 1: Guessing Game (Mariam)
Part C: GAME 2: Roll the dice (Fayzabanu)
Part D: GAME 3: Lottery (Mariam)
*/

// Simulated typing effect using standard C++ sleep
void Type(const char* p) {
    if (!p) return;
    bool skip = false;

    while (*p) {
        // Check if a key has been pressed to skip the animation
        if (_kbhit()) {
            int ch = _getch(); // Get the pressed key
            if (ch == 13) { // ASCII code for Enter key
                skip = true;
            }
        }
        if (skip) {
            // If skipping, print the rest of the string immediately
            printf("%s", p);
            break;
        }

        // print the next character followed by a block, then erase the block
        printf("%c\xDB", *p++);
        std::this_thread::sleep_for(60ms);
        printf("\b \b");
        std::this_thread::sleep_for(30ms);
    }
    std::this_thread::sleep_for(300ms);
}

int main( int argc, const char * argv[]) {

string firstName, lastName;
int gameChoice;

// Ask for players first and last name
    //cout << "Welcome to The Mini Arcade!!\n" << endl;
    Type("Welcome to The Mini Arcade!!\n");
    //cout << "Please enter your first name:\n ";
    Type("Please enter your first name:\n ");
    cin >> firstName;
    Type("Please enter your first name:\n");
    //cout << "Please enter your last name:\n ";
    cin >> lastName;

    // Greet the player
    //cout << "Hello," << firstName << " " << lastName << "! Lets play a game.\n" << endl;
   Type((("Hello, " + firstName.c_str() + " " + lastName.c_str() + "! Let's play a game.\n\n")));



// Guessing game logic here
                //cout << "Hello, " << firstName << " welcome to the Guessing Game!" << endl;
                Type("Hello, " + firstName.c_str() + " Welcome to the Guessing Game!\n");
                
                // Explain game to user.
                Type("In this game, you will try to guess a number between 1 and 100.\n");
                //cout << "In this game, you will try to guess a number between 1 and 100." << endl;
                //cout << "You will have 3 attempts to guess the correct number." << endl;
                Type("You will have 3 attempts to guess the correct number.\n");
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
                    //cout << "Enter your guess (1-100): ";
                    Type("Enter your guess (1-100): ");
                    int userGuess;
                    cin >> userGuess;
                    
                    if (!cin) {
                        //cout << "Invalid input. Please enter a number between 1 and 100." << endl;
                        Type("Invalid input. Please enter a number between 1 and 100.\n\n");
                        cin.clear(); // Clear the error flag
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
                        continue; // Skip to the next iteration of the loop
                    }

                    if (userGuess < 1 || userGuess > 100) {
                        //cout << "Invalid input. Please enter a number between 1 and 100." << endl;
                        Type("Invalid input. Please enter a number between 1 and 100.\n\n");
                        continue; // Skip to the next iteration of the loop

                    }

                    count++; // Increment attempt count
                    //cout << "Attempt " << count << " of " << limit << "." << endl;
                    Type(("Attempt " + to_string(count) + " of " + to_string(limit) + ".\n\n").c_str());
                    //cout << "Try again." << endl;
                    Type("Try again.\n\n"); 

                    if (userGuess < randomNumber) {
                        Type("Too low!\n");
                        //cout << "Too low!" << endl;
                    }

                    else if (userGuess > randomNumber) {
                        Type("Too high!\n");
                        //cout << "Too high!" << endl;
                    }

                    else if (userGuess == randomNumber) {
                        Type("Congratulations " + firstName.c_str() + "! You guessed the correct number!\n\n");
                        //cout << "Congratulations " << firstName << "! You guessed the correct number!" << endl;
                        break; // Exit the loop if the user guesses correctly
                    }
                    if (count == limit) {
                        Type("Sorry, you've used all your attempts. The correct number was " + to_string(randomNumber) + ".\n\n");
                        //cout << "Sorry, you've used all your attempts. The correct number was " << randomNumber << "." << endl;
                    }
                } while (count < limit);
                
                // Ask if the user wants to play again
                    //cout << "Do you want to play again? (y/n): ";
                    Type("Do you want to play again? (y/n): \n");
                    cin >> playAgain;

            } while  (tolower(playAgain) == 'y');

                //cout << "Returning to main menu..." << endl;
                Type("Returning to main menu...\n\n");

            } // End of case 1
        


/* ========== REFERENCES ========== */

    /* ===== 1. Simulated Typing Effect ===== */ 
            // https://www.youtube.com/watch?v=7aPJIp2J1J0
            // https://cplusplus.com/forum/beginner/56011/
            // https://stackoverflow.com/questions/16884607/character-by-character-output-to-simulate-a-typing-effect
    /* ===== 2. Enter to Skip Animation ========== */
            // https://learn.microsoft.com/en-us/cpp/c-runtime-library/console-and-port-i-o?view=msvc-170
            // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/getch-getwch?view=msvc-170
            // https://learn.microsoft.com/en-us/cpp/c-runtime-library/reference/kbhit?view=msvc-170] 

/* ========== Extra Code Snippets from Earlier Iterations ========== */

    /* ===== 1. Original Type function using Windows Sleep function ===== */ 
        // void Type (const char * p)
        // {
        //     if (NULL == p) return;
        //     while (*p)
        //     {
        //         printf("%c\xDB", *p++);
        //         ::Sleep(45);
        //         printf("\b \b");
        //         ::Sleep(45);
        //     }
        //     ::Sleep(300);
        // }