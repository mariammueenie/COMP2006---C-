#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

// Helper function to generate a line of unique random numbers.
// This supports the requirement to use vectors for storing lottery numbers.
vector<int> generateUnique(int count, int minVal, int maxVal) {
    vector<int> nums;

    // Continue generating until the vector has the required count of unique numbers.
    while (static_cast<int>(nums.size()) < count) {
        int n = rand() % maxVal + minVal;

        // Only add the number if it is not already in the vector.
        if (find(nums.begin(), nums.end(), n) == nums.end()) {
            nums.push_back(n);
        }
    }

    return nums;
}

// This function collects the user's lottery ticket.
// It allows either manual entry or a randomly generated ticket.
// Validation ensures numbers are unique and within 1-49.
vector<int> getUserTicket() {
    vector<int> ticket;
    char choice;

    cout << "Would you like your ticket randomly generated? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y') {
        // Use the shared helper to generate 6 unique numbers between 1 and 49.
        ticket = generateUnique(6, 1, 49);
        cout << "Your ticket was randomly generated.\n";
        return ticket;
    }

    cout << "Enter 6 UNIQUE numbers between 1 and 49:\n";
    int num;

    // Continue accepting input until 6 valid unique numbers are collected.
    while (static_cast<int>(ticket.size()) < 6) {
        cout << "Number " << ticket.size() + 1 << ": ";
        cin >> num;

        // Validate number range.
        if (num < 1 || num > 49) {
            cout << "Number must be between 1 and 49.\n";
        }
        // Validate uniqueness within the ticket.
        else if (find(ticket.begin(), ticket.end(), num) != ticket.end()) {
            cout << "Duplicate number detected. Please enter a unique number.\n";
        } else {
            ticket.push_back(num);
        }
    }

    return ticket;
}

// This function generates a random bonus line of 6 unique numbers.
// It reuses the generateUnique helper and keeps the code modular.
vector<int> generateRandomLine() {
    return generateUnique(6, 1, 49);
}

// This function compares a player's line to the winning numbers.
// It counts how many matches there are and also checks if the bonus number matches.
// The bonus number counts as one extra match.
int compareLines(const vector<int>& line, const vector<int>& winning, int bonusNum) {
    int matches = 0;

    // Check each number in the player's line for a match with the main winning numbers.
    for (int n : line) {
        if (find(winning.begin(), winning.end(), n) != winning.end()) {
            matches++;
        }
    }

    // Check if the line contains the bonus number and count it as a match if it does.
    if (find(line.begin(), line.end(), bonusNum) != line.end()) {
        matches++;
    }

    return matches;
}

// This function determines prize money based on the number of matches.
// It follows the specific prize rules defined in the assignment.
string calculatePrize(int matches) {
    // Matches include the bonus number, which is treated as a regular match.
    switch (matches) {
        case 6: return "$5,000,000";
        case 5: return "$250,000";
        case 4: return "$10,000";
        case 3: return "$1,000";
        default: return "Better luck next time!";
    }
}

// This function writes the ticket, bonus line, winning numbers, and prize results
// to an output file named lottery_ticket.txt using ofstream.
void writeTicketToFile(const vector<int>& ticket,
                       const vector<int>& bonusLine,
                       const vector<int>& winning,
                       int bonusNum,
                       int resultTicket,
                       int resultBonus) {
    ofstream file("lottery_ticket.txt");

    // Writing main details about the lines and winning numbers.
    file << "Your Ticket: ";
    for (int n : ticket) file << n << " ";
    file << "\nBonus Line: ";
    for (int n : bonusLine) file << n << " ";
    file << "\nWinning Numbers: ";
    for (int n : winning) file << n << " ";
    file << "\nBonus Number: " << bonusNum << "\n";

    // Writing match counts and prizes for both the ticket and the bonus line.
    file << "\nYour ticket matched " << resultTicket << " numbers.\n";
    file << "Prize: " << calculatePrize(resultTicket) << "\n";

    file << "\nBonus line matched " << resultBonus << " numbers.\n";
    file << "Prize: " << calculatePrize(resultBonus) << "\n";

    file.close();
}

// This function brings together all the lottery logic.
// It uses vectors for all lines, generates winning numbers and a bonus,
// compares results, displays them, and saves them to a file.
// A replay loop allows the player to buy another ticket or return to the menu.
void playLotteryGame() {
    char playAgain = 'Y';

    // This outer loop allows the player to play multiple rounds of the lottery.
    while (playAgain == 'Y' || playAgain == 'y') {
        cout << "\n--- Lottery Game: Vector Victory Edition ---\n\n";

        // Get player's ticket via manual entry or random generation.
        vector<int> ticket = getUserTicket();

        // Generate bonus line, using the required random/unique logic.
        vector<int> bonusLine = generateRandomLine();

        // Create 6 unique winning numbers.
        vector<int> winning = generateUnique(6, 1, 49);

        // Generate a bonus number that is not one of the main winning numbers.
        int bonusNum = rand() % 49 + 1;
        while (find(winning.begin(), winning.end(), bonusNum) != winning.end()) {
            bonusNum = rand() % 49 + 1;
        }

        // Compare both lines with the winning numbers and bonus.
        int resultTicket = compareLines(ticket, winning, bonusNum);
        int resultBonus  = compareLines(bonusLine, winning, bonusNum);

        // Display all results clearly in the console.
        cout << "\nYour Ticket: ";
        for (int n : ticket) cout << n << " ";
        cout << "\nBonus Line: ";
        for (int n : bonusLine) cout << n << " ";
        cout << "\nWinning Numbers: ";
        for (int n : winning) cout << n << " ";
        cout << "\nBonus Number: " << bonusNum << "\n\n";

        cout << "Your ticket matched " << resultTicket << " numbers.\n";
        cout << "Prize: " << calculatePrize(resultTicket) << "\n\n";

        cout << "Bonus line matched " << resultBonus << " numbers.\n";
        cout << "Prize: " << calculatePrize(resultBonus) << "\n\n";

        // Save the outcome to the text file as required.
        writeTicketToFile(ticket, bonusLine, winning, bonusNum, resultTicket, resultBonus);

        cout << "Results have been saved to lottery_ticket.txt.\n";

        // Replay prompt specific to the lottery game.
        cout << "\nWould you like to buy another lottery ticket? (Y/N): ";
        cin >> playAgain;

        if (playAgain == 'Y' || playAgain == 'y') {
            // Loop back to start a new lottery round.
            continue;
        }

        // Ask if the player wants to return to the main menu.
        char returnToMenu;
        cout << "Return to main menu? (Y/N): ";
        cin >> returnToMenu;

        // Returning ends this function, so control goes back to the main menu function.
        return;
    }
}
