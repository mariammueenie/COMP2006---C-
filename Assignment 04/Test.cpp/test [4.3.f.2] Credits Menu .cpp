#include <iostream>
#include <limits>
using namespace std;

// This function displays the credits for the Mini Arcade.
// Improvements include: safe Y/N validation, buffer cleanup, streamlined replay logic, 
// prevention of accidental exits, and user-friendly messages
void showCredits() {
    char viewAgain = 'Y';

    while (viewAgain == 'Y' || viewAgain == 'y') {

        cout << "\n=====================================\n";
        cout << "               CREDITS\n";
        cout << "=====================================\n\n";

        // TODO: INSERT VERSION NUMBER IN FINAL VERSION!!!!!
        cout << "[ Mini Arcade - Version { //TODO: ADD VERSION NUMBER}} ]\n\n";

        cout << "Developed by: Group 9\n";
        cout << "Programmer: Mariam Mueen\n";
        cout << "Programmer: Fayzabanu Diwan\n\n";

        // TODO: Add references here 
        // TODO: Add course + prof reference
        // TODO: Add textbook reference 
        // TODO: Add any libraries or online resources used

        cout << "Thank you for playing the Mini Arcade!\n\n";

        // FIX: Clear leftover newline characters
        // Prevents immediate skipping caused by buffered '\n'.
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // FIX: Streamlined replay logic (ONE Y/N question only)
        // ============================================================
        cout << "View the credits again? (Y/N): ";

        // FIX: Full safe Y/N validation
        // Prevents garbage inputs (like $, !!, 'abc', 123) from exiting.
        // Only Y/y/N/n are accepted.
        while (true) {
            cin >> viewAgain;

            if (viewAgain == 'Y' || viewAgain == 'y' ||
                viewAgain == 'N' || viewAgain == 'n') {
                break;  // valid input
            }

            cout << "Please enter Y or N only: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        // If the user chooses NOT to view again
        if (viewAgain == 'N' || viewAgain == 'n') {

            // FIX: Add return-to-menu message
            // Matches style used in Guessing/Dice/Lottery games
            cout << "\nReturning to main menu...\n";
            return;  // exit credits and return to menu
        }

        // If 'Y', the loop restarts and credits display again.

    } // end while
}

// CHANGES TO MAKE
// TODO: Add ASCII art header / decorative banner here later.
// TODO: Add a small version timeline for project evolution.
// TODO: Insert version number 
// TODO: add references to credits menu
// TODO: reference the course + prof? i think that could be fun
// TODO: maybe add some ascii art at some point