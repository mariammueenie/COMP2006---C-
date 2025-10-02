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

int main()

{
    // Title and group info
    cout << " MINI ARCADE \n";
    cout << "Written by Mariam Mueen\n";
    cout << "and Fayzabanu Diwan\n";
    cout << "Group 9\n\n";

    // Step 1: Get player details
    string firstName, lastName;
    cout << "Please enter your first name: ";
    cin >> firstName;
    cout << "Please enter your last name: ";
    cin >> lastName;

    cout << "\nHello " << firstName << " " << lastName << "!\n";

    // Ask if they want to play
    char playChoice;
    cout << "Would you like to play a game? (Y/N): ";
    cin >> playChoice;
    playChoice = toupper(playChoice);

    if (playChoice == 'Y') {
        // Show main menu
        cout << "\n Choose your game\n";
        cout << "1 -  Guessing Game\n";
        cout << "2 -  Roll the Dice\n";
        cout << "3 -  Lottery\n";
        cout << "4 -  Exit\n";
        cout << "\nEnter your choice (1-4): ";
        //  We'll add logic for choices in the next step
    }
    else {
        cout << "\nThank you, " << firstName << "! See you next time \n";
    }

    return 0;
}


