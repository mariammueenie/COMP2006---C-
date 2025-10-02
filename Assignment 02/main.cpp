#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
using namespace std; 

/*
// PROGRAM OUTLINE
PART A: INTRODUCTION
        TITLE
        GROUP MEMBERS
        GET NAME FROM USER
        GAME CHOICE SCREEN LOOP 
PART B: GAME 1: Guessing Game 
Part C: GAME 2: Roll the dice
Part D: GAME 3: Lottery 
*/

int main() {
    // Declare variables 
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
            case 1:
                // Guessing game logic here
                cout << "Hello, " << firstName << " welcome to the Guessing Game!" << endl;
                cout << "Game 1 will run here."<< endl;
                cout << "Returning to main menu..." << endl;
                break;

            case 2:
                // Roll the dice logic here
                cout << "Hello, " << firstName << " welcome to Roll the Dice!" << endl;
                cout << "Game 2 will run here."<< endl;
                cout << "Returning to main menu..." << endl;
                break;

            case 3:
                // Lottery logic here
                cout << "Hello, " << firstName << " welcome to the Lottery!" << endl;
                cout << "Game 3 will run here."<< endl;
                cout << "Returning to main menu..." << endl;
                break;

            case 4:
                // Credits logic here
                cout << "CREDITS\n";
                cout << "This Mini Arcade was created by:\n";
                cout << "Mariam Mueen\n";
                cout << "Fayzabanu Diwan\n";
                cout << "Group 9\n";
                cout << "Returning to main menu..." << endl;
                break;

            case 5:
                // Exit logic here
                cout << "Thank you for playing, " << firstName << "! See you next time.\n";
                break;

            default: 
                // When input is invalid
                cout << "Invalid choice. Please select a valid option from the menu.\n";
                break;


        } cout << endl; // Extra line between loops for readability

    } while (gameChoice != 5); // End game choice loop

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


