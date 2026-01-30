#ifndef ARCADE_GLOBALS_H
#define ARCADE_GLOBALS_H

#include <string>
using std::string;

namespace arcade {

    struct PlayerName {
        string first;
        string last;
    };

    extern PlayerName player;

    string getYesNo(const string& prompt);

    bool validFirstName(const string& s);
    bool validLastName(const string& s);

    PlayerName getPlayerName();

    int getStrictInteger(const string& prompt, int minV, int maxV);

    void showHelp();

    void playRockPaperScissors(int& winnings);

}

#endif
