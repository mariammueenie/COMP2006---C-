#include <iostream>
using namespace std;

// This function displays the credits for the Mini Arcade.
// It includes the version, group number, and developer names.
// A replay loop allows the player to view the credits again or return to the menu.
void showCredits() {
    char viewAgain = 'Y';

    // This loop permits viewing the credits multiple times in a row.
    while (viewAgain == 'Y' || viewAgain == 'y') {

        cout << "\n=====================================\n";
        cout << "               CREDITS\n";
        cout << "=====================================\n\n";

        // ASCII art title or decorative banner can be inserted here if desired.
        // This section is intentionally left flexible for styling.
        cout << "[ Mini Arcade - Version 4.1 ]\n\n";

        // Core credit information as required.
        cout << "Developed by: Group 9\n";
        cout << "Programmer: Mariam Mueen\n";
        cout << "Programmer: Fayzabanu Diwan\n\n";

        cout << "Thank you for playing the Mini Arcade!\n\n";

        // Ask if the user wants to see the credits again.
        cout << "Would you like to view the credits again? (Y/N): ";
        cin >> viewAgain;

        if (viewAgain == 'Y' || viewAgain == 'y') {
            // Loop again and redraw the credits.
            continue;
        }

        // If not viewing again, offer to return to main menu.
        char returnToMenu;
        cout << "Return to main menu? (Y/N): ";
        cin >> returnToMenu;

        // Returning from this function hands control back to the main menu loop.
        return;
    }
}
