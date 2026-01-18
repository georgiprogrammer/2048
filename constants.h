#ifndef CONSTANTS_H
#define CONSTANTS_H

const int MAX_SIZE = 10;
const int MIN_SIZE = 4;
const int MAX_NAME_LENGTH = 100;
const int LEADERBOARD_SIZE = 5;

struct LeaderboardEntry {
    char name[MAX_NAME_LENGTH + 1];
    int score;
};

#endif