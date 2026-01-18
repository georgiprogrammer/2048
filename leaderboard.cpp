#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <cstring>
#include "leaderboard.h"

using namespace std;

void getLeaderboardFilename(int size, char* filename) {
    sprintf(filename, "leaderboard_%dx%d.txt", size, size);
}

void loadLeaderboard(LeaderboardEntry entries[LEADERBOARD_SIZE], int size) {
    char filename[50];
    getLeaderboardFilename(size, filename);
    ifstream file(filename);
    for (int i = 0; i < LEADERBOARD_SIZE; i++) {
        entries[i].score = -1; strcpy(entries[i].name, "---");
    }
    if (!file.is_open()) return;
    for (int i = 0; i < LEADERBOARD_SIZE; i++) {
        if (!(file >> entries[i].name >> entries[i].score)) break;
    }
    file.close();
}

void saveLeaderboard(LeaderboardEntry entries[LEADERBOARD_SIZE], int size) {
    char filename[50];
    getLeaderboardFilename(size, filename);
    ofstream file(filename);
    for (int i = 0; i < LEADERBOARD_SIZE; i++) {
        if (entries[i].score != -1) file << entries[i].name << " " << entries[i].score << endl;
    }
    file.close();
}

void updateLeaderboard(const char* name, int score, int size) {
    LeaderboardEntry entries[LEADERBOARD_SIZE];
    loadLeaderboard(entries, size);
    int pos = -1;
    for (int i = 0; i < LEADERBOARD_SIZE; i++) {
        if (score > entries[i].score) { pos = i; break; }
    }
    if (pos != -1) {
        for (int j = LEADERBOARD_SIZE - 1; j > pos; j--) entries[j] = entries[j - 1];
        strncpy(entries[pos].name, name, MAX_NAME_LENGTH);
        entries[pos].name[MAX_NAME_LENGTH] = '\0';
        entries[pos].score = score;
        saveLeaderboard(entries, size);
    }
}