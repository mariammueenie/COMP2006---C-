#include <iostream>
using namespace std;

// This function displays the credits for the Mini Arcade.
// A replay loop allows the player to view the credits again or return to the menu.
void showCredits() {
    char viewAgain = 'Y';

    // This loop permits viewing the credits multiple times in a row
    while (viewAgain == 'Y' || viewAgain == 'y') {

        cout << "\n=====================================\n";
        cout << "               CREDITS\n";
        cout << "=====================================\n\n";

        // ASCII art title or decorative banner can be inserted here if desired
        cout << "[ Mini Arcade - Version 4.1 ]\n\n";

        // credits details 
        cout << "Developed by: Group 9\n";
        cout << "Programmer: Mariam Mueen\n";
        cout << "Programmer: Fayzabanu Diwan\n\n";

        cout << "Thank you for playing the Mini Arcade!\n\n";

        // Ask if user wants to see the credits again
        cout << "Would you like to view the credits again? (Y/N): ";
        cin >> viewAgain;

        if (viewAgain == 'Y' || viewAgain == 'y') {
            // Loop again to show credits
            continue;
        }

        // If not viewing again, offer to return to main menu
        char returnToMenu;
        cout << "Return to main menu? (Y/N): ";
        cin >> returnToMenu;

        // Returning from this function hands control back to the main menu loop
        return;
    }
}

// CHANGES TO MAKE 
// add version number to credits menu 
// maybe add references to credits menu 
// reference the course + prof? i think that could be fun 
// maybe add some ascii art at some point 