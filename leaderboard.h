#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "constants.h"

void loadLeaderboard(LeaderboardEntry entries[LEADERBOARD_SIZE], int size);
void saveLeaderboard(LeaderboardEntry entries[LEADERBOARD_SIZE], int size);
void updateLeaderboard(const char* name, int score, int size);

#endif
