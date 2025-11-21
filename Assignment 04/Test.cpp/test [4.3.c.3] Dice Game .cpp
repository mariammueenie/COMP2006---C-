#include <iostream>
#include <limits>
using namespace std;

// This function implements the Dice Game with safe input handling,
// streamlined replay logic, and improvements commented clearly.

/* =========================================================
   Dice Game- with interactive ENTER pauses
   ========================================================= */
void playDiceGame() {
    string playAgain = "Y";

    while (playAgain == "Y") {

        cout << "\n--- Dice Game ---\n\n";

        // Clear leftover newline before pauses
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // === Prompt before starting ===
        cout << "Welcome to the Dice Game!\n";
        cout << "In this game, you will select 2 values from 1-6.\n";
        cout << "Then, you will roll two dice.\n";
        cout << "If both dice match your selected values, you win!\n\n";
        cout << "Press ENTER to get started...";
        {
            string pause;
            getline(cin, pause);
        }

        // Get user input for their two chosen values
        int getStrictDieGameInt(const string& prompt, int minV, int maxV) 
        {
            while (true)
            {
                cout << prompt;
                 
                string line;
                getline(cin, line);

                // Trim whitespace from both ends
                while (!line.empty() && isspace(line.front()))
                  line.erase(0, 1);
                while (!line.empty() && isspace(line.back()))
                  line.pop_back();

                // check for empty input
                if (line.empty()) {
                    cout << "Invalid input. Please enter ONE whole number.\n"; // if user enters multiple values, even if values are valid
                    continue;

                // Ensure every character is a digit
                // REFERENCE: https://cplusplus.com/reference/cctype/isdigit/
                // REFERENCE: https://en.cppreference.com/w/cpp/language/range-for.html
                // REFERENCE: https://www.learncpp.com/cpp-tutorial/logical-operators/
                // REFERENCE: https://cplusplus.com/doc/tutorial/variables/

                bool bad = false;
                for (char c : line) {
                    if (!isdigit(c)) {
                        bad = true;
                        break;
                    }
                }
                // if non-digit found, prompt again
                if (bad) {
                    cout << "Invalid input. ONLY digits 1-6 allowed.\n";
                    continue;
                }

                int value = stoi(line);

                if (value < minV || value > maxV) {
                    cout << "Number must be between " << minV << " and " << maxV << ".\n";
                    continue;
                }
                return value;
            }
        }

        // Get first die value from user
        int userDie1 = getStrictDieGameInt("Enter your first die value (1-6): ", 1, 6);
        int userDie2 = getStrictDieGameInt("Enter your second die value (1-6): ", 1, 6);




        // Generate both dice values AFTER the player engages
        int die1 = rand() % 6 + 1;
        int die2 = rand() % 6 + 1;

        // === Reveal Die 1 ===
        cout << "Press ENTER to roll the first die...";
        {
            string pause;
            getline(cin, pause);
        }

        cout << "Die 1: " << die1 << "\n\n";

        // === Reveal Die 2 ===
        cout << "Press ENTER to roll the second die...";
        {
            string pause;
            getline(cin, pause);
        }

        cout << "Die 2: " << die2 << "\n\n";

        // === Compare Dice rolls to User Input ===


        if (die1 == die2) {
            cout << "They match! You win!\n";
        } else {
            cout << "They do not match. You lose.\n";
        }

        playAgain = getYesNo("\nRoll again? (Y/N): ");
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (playAgain == "N") {
            cout << "\nReturning to main menu...\n";
            return;
        }
    }
}}

// CHANGES TO MAKE
// TODO: Fix game logic, suppose to compare 2 user inputs to dice rolls, not dice to dice 
// TODO: remove cin.clear that causes extra line issue
// TODO: Ensure that removing cin.clear does not reintroduce input handling issues 
// TODO: Add dice roll animation??? maybe??
