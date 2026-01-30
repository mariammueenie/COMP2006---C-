#ifndef LOTTERYGAME_H
#define LOTTERYGAME_H

#include <string>
#include <vector>
#include "ArcadeGlobals.h"

namespace arcade {

void playLotteryGame(const PlayerName& player);

std::string buildFilename(const PlayerName& playerRef);

std::vector<int> generateUnique(int count, int minVal, int maxVal);

int getSingleInteger(const std::string& prompt, int minV, int maxV);

std::vector<int> getUserTicket();

int compareLines(const std::vector<int>& line, const std::vector<int>& winning);

bool hasBonus(const std::vector<int>& line, int bonusNum);

void appendToPlayerFile(
        const std::string& filename,
        const std::vector<int>& ticket,
        const std::vector<int>& extraTicket,
        const std::vector<int>& winning,
        int bonusNum,
        int resultTicket,
        bool bonusHitTicket,
        int resultExtra,
        bool bonusHitExtra);

}

#endif
