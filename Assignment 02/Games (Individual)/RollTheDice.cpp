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

string firstName, lastName;
int gameChoice;

// Ask for players first and last name
    cout << "Welcome to The Mini Arcade!!\n" << endl;
    cout << "Please enter your first name:\n ";
    cin >> firstName;
    cout << "Please enter your last name:\n ";
    cin >> lastName;

    // Greet the player
    cout << "Hello," << firstName << " " << lastName << "! Lets play a game.\n" << endl;

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
                    int userDie2 = (rand()% 6) + 1; // Random number between 1 and 6

                    // roll dice for computer
                    int compDie1 = (rand()% 6) + 1; // Random number between 1 and 6
                    int compDie2 = (rand()% 6) + 1; // Random number between 1 and 6

                    // Print the results
                    cout << "\nYou rolled: " << userDie1 << " and " << userDie2 << endl;
                    cout << "The computer rolled: " << compDie1 << " and " << compDie2 << endl; 

                    // Determine the winner
                    if (userDie1 == userDie2 && compDie1 == compDie2) {
                        cout << "It's a tie! Both you and the computer rolled doubles!" << endl;
                    } 
                    else if (userDie1 == userDie2) {
                        cout << "Congratulations " << firstName << "! You win with doubles!" << endl;
                    } 
                    else if (compDie1 == compDie2) {
                        cout << "The computer wins with doubles! Better luck next time, " << firstName << "!" << endl;
                    } 
                    else {
                        cout << "No doubles rolled. It's a draw!" << endl;
                    }
                    // Ask if the user wants to play again
                    cout << "Do you want to play again? (y/n): ";
                    cin >> playAgain;
                } while (tolower(playAgain) == 'y');

                cout << "Returning to main menu..." << endl;
            } // End of case 2