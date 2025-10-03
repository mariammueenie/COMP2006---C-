#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <vector>
#include <set>
#include <algorithm>
#include <limits>
#include <cctype>


using namespace std;   

int main() {
    // print title of game, then, new line
    cout <<"LOTO MAX Random Number Game" ".\n\n";

    // get player name
    string firstName;

    // game loop beings
    char playAgain = 'y';
    do {
    
        // print group members and group number to console 
        cout << "Written by Mariam Mueen" ".\n" 
                "and Fayzabanu Diwan" ".\n"
                "Group 9" ".\n";
        // get number guess from user
        cout << "Please enter your LOTO numbers (You should input seven numbers) from 1-49, " << firstName << ".\n\n"; 

        // declare variables
        int NumberGuess1, NumberGuess2, NumberGuess3, NumberGuess4, NumberGuess5, NumberGuess6, NumberGuess7;

        // Pick #1
        while (true) {
            cout << "Pick #1 (1-49): ";
            if (!(cin >> NumberGuess1)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n\n'); continue; }
            if (NumberGuess1 < 1 || NumberGuess1 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
            break;
        }

        // Pick #2
        while (true) {
            cout << "Pick #2 (1-49): ";
            if (!(cin >> NumberGuess2)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n\n'); continue; }
            if (NumberGuess2 < 1 || NumberGuess2 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
            if (NumberGuess2 == NumberGuess1) { cout << "Repeat number. Try again.\n\n"; continue; }
            break;
        }

        // Pick #3
        while (true) {
            cout << "Pick #3 (1-49): ";
            if (!(cin >> NumberGuess3)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n\n'); continue; }
            if (NumberGuess3 < 1 || NumberGuess3 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
            if (NumberGuess3 == NumberGuess1 || NumberGuess3 == NumberGuess2) { cout << "Repeat number. Try again.\n\n"; continue; }
            break;
        }

        // Pick #4
        while (true) {
            cout << "Pick #4 (1-49): ";
            if (!(cin >> NumberGuess4)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n\n'); continue; }
            if (NumberGuess4 < 1 || NumberGuess4 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
            if (NumberGuess4 == NumberGuess1 || NumberGuess4 == NumberGuess2 || NumberGuess4 == NumberGuess3) { cout << "Repeat number. Try again.\n\n"; continue; }
            break;
        }

        // Pick #5
        while (true) {
            cout << "Pick #5 (1-49): ";
            if (!(cin >> NumberGuess5)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n\n'); continue; }
            if (NumberGuess5 < 1 || NumberGuess5 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
            if (NumberGuess5 == NumberGuess1 || NumberGuess5 == NumberGuess2 || NumberGuess5 == NumberGuess3 || NumberGuess5 == NumberGuess4) { cout << "Repeat number. Try again.\n\n"; continue; }
            break;
        }

        // Pick #6
        while (true) {
            cout << "Pick #6 (1-49): ";
            if (!(cin >> NumberGuess6)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n\n'); continue; }
            if (NumberGuess6 < 1 || NumberGuess6 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
            if (NumberGuess6 == NumberGuess1 || NumberGuess6 == NumberGuess2 || NumberGuess6 == NumberGuess3 ||
                NumberGuess6 == NumberGuess4 || NumberGuess6 == NumberGuess5) { cout << "Repeat number. Try again.\n\n"; continue; }
            break;
        }

        // get 7 numbers from user, and validate inputs
        while (true) {
            cout << "Pick #7 (1-49): ";
            if (!(cin >> NumberGuess7)) { cout << "Not a number. Try again.\n\n"; cin.clear(); cin.ignore(10000,'\n\n'); continue; }
            if (NumberGuess7 < 1 || NumberGuess7 > 49) { cout << "Out of range. Try again.\n\n"; continue; }
            if (NumberGuess7 == NumberGuess1 || NumberGuess7 == NumberGuess2 || NumberGuess7 == NumberGuess3 ||
             NumberGuess7 == NumberGuess4 || NumberGuess7 == NumberGuess5 || NumberGuess7 == NumberGuess6) { cout << "Repeat number. Try again.\n\n"; continue; }
            break;
        }

        // print user input numbers to console
        cout << "You guessed: "
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
                cout << "Sorry " << firstName << ", not all the numbers matched. Better luck next time!\n\n";
            }

            // thank player, and end game 
            cout << "Thank you for playing, " << firstName << "." ".\n\n";
            cout << "Do you want to play again? (y/n): " "\n\n";
            cin >> playAgain;

        } while (tolower(playAgain) == 'y');
    }
        