#ifndef ARCADE_GLOBALS_H
#define ARCADE_GLOBALS_H

#include <string>
using std::string;

namespace arcade {

    // ============================
    // PlayerName struct
    // ============================
    struct PlayerName {
        string first;
        string last;
    };

    // global player object so all games can access
    extern PlayerName player;

    // =========================================================
    // YES/NO strictly-controlled validator (only Y/N/YES/NO)
    // Since used in multiple games, defined here globally
    // Muuuch easier than checking inline every time lmao
    // =========================================================
    string getYesNo(const string& prompt);

    // =========================================================
    // NAME VALIDATION
    // validFirstName() -> First name: letters + hyphen
    // validLastName()  -> Last name: letters + apostrophe
    // =========================================================
    bool validFirstName(const string& s);
    bool validLastName(const string& s);

    // =========================================================
    // GetPlayerName: Prompts until both names valid
    // =========================================================
    PlayerName getPlayerName();

    // =========================================================
    // STRICT INTEGER INPUT FUNCTION
    // Used ALL over the program
    // =========================================================
    int getStrictInteger(const string& prompt, int minV, int maxV);

    // =========================================================
    // Assignment 05 specific GLOBAL FUNCTIONS
    // =========================================================
    void showHelp();                  // Help/info page
    void playRockPaperScissors(int& winnings); // Lottery gamble feature

}

#endif
