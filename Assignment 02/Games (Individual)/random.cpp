#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <limits>
#include <iomanip>
#include <cctype>
#include <cstdio> // for printf
#include <thread> // For this_thread::sleep_for
#include <chrono> // For chrono::milliseconds
#include <conio.h> // For _kbhit() and _getch()
#include <cstdlib> // For rand and srand

using namespace std; 
using namespace std::chrono_literals; // for using 45ms

/*
// PROGRAM OUTLINE
PART A: INTRODUCTION, TITLE, GET NAME FROM USER, GAME CHOICE SCREEN LOOP (Fayzabanu)
PART B: GAME 1: Guessing Game (Mariam)
Part C: GAME 2: Roll the dice (Fayzabanu)
Part D: GAME 3: Lottery (Mariam)
*/

// Simulated typing effect using standard C++ sleep
// Yay! It works!! I built this using like 5 different references
// and a lot of trial and error.
// Also added the feature to skip the animation by pressing Enter
// References at the bottom of the file
// So much trial and error, but it was worth it
// Note: This function only works in Windows because of the use of <conio.h>, <cstdio> and their functions _kbhit() and _getch()
// If I want to make it work in other OS, I will have to find alternatives for these functions
void Type(const char* p) {
    while (*p) {
        if (_kbhit()) { // Check if a key has been pressed
            int ch = _getch(); // Get the pressed key
            if (ch == 13) { // ASCII code for Enter key
                // If Enter is pressed, print the rest of the string immediately
                printf("%s", p);
                break;
            }
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

    Type("Welcome to The Mini Arcade!!\n");
    Type("Please enter your first name:\n ");
    cin >> firstName;
    Type("Great! Now, please enter your last name:\n");
    cin >> lastName;
    // Greet the player (in one line)
    Type(("Hello, " + firstName + " " + lastName + "! Let's play a game.\n").c_str());

    // Greet the player
    // Type("Hello, " );
    // Type(firstName.c_str());
    // Type(" " );
    // Type(lastName.c_str());
    // Type("! Let's play a game.\n");

}

            // do while loop to compare userGuess to previous userGuesses and give hints accordingly
            
            // previousGuess = userGuess; // Store the current guess as previous for the next iteration
            
            // do () {
            //     if (count > 0) {
            //         if (abs(userGuess - randomNumber) < abs(previousGuess - randomNumber)) {
            //             cout << "Warmer! You're getting closer." << endl;
            //         } else if (abs(userGuess - randomNumber) > abs(previousGuess - randomNumber)) {
            //             cout << "Colder! You're getting further away." << endl;
            //         } else {
            //             cout << "Same distance as before!" << endl;
            //         }
            //     }

            // } while (count > 0 || count < limit);
        


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

/*
int previousGuess = -1; 
// Initialize previous guess to an invalid number

// store the current guess as previous for the next iteration
previousGuess = userGuess;
//NEW

*/

// prints message "hello u hit enter" if you hit enter key
// if ( _kbhit() ) {
//     int ch = _getch(); // Get the pressed key
//     if (ch == 13) { // ASCII code for Enter key
//         printf("hello u hit enter");
//     }
// }

