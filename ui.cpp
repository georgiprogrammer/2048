#include <iostream>
#include <cstring>
#include "ui.h"
#include "game.h"
#include "utils.h"
#include "leaderboard.h"

using namespace std;

void printBoard(int board[MAX_SIZE][MAX_SIZE], int size, int score) {
    cout << "\n--- Current Score: " << score << " ---\n" << endl;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) cout << ".\t";
            else cout << board[i][j] << "\t";
        }
        cout << "\n" << endl;
    }
}

void showLeaderboard() {
    int size;
    cout << "Enter board size to view (4-10): ";
    cin >> size;
    if (size < MIN_SIZE || size > MAX_SIZE) { cout << "Invalid size!" << endl; return; }

    LeaderboardEntry entries[LEADERBOARD_SIZE];
    loadLeaderboard(entries, size);
    cout << "\n--- TOP RESULTS FOR " << size << "x" << size << " ---" << endl;
    for (int i = 0; i < LEADERBOARD_SIZE; i++) {
        if (entries[i].score != -1) cout << i + 1 << ". " << entries[i].name << " : " << entries[i].score << endl;
    }
    waitForEnter();
}

void startGame() {
    char name[MAX_NAME_LENGTH + 1];
    int size, score = 0;
    int board[MAX_SIZE][MAX_SIZE];
    bool validName = false;
    while (!validName) {
        cout << "Enter nickname (no spaces): ";
        if (cin.peek() == '\n') cin.ignore();
        cin.getline(name, MAX_NAME_LENGTH);
        if (strchr(name, ' ') != nullptr || strlen(name) == 0) cout << "Invalid name! No spaces allowed.\n";
        else validName = true;
    }

    cout << "Enter board size (4-10): ";
    cin >> size;
    if (size < MIN_SIZE || size > MAX_SIZE) { cout << "Invalid board size!" << endl; return; }

    clearBoard(board, size);
    addRandomTile(board, size); addRandomTile(board, size);

    while (hasMoves(board, size)) {
        clearScreen();
        printBoard(board, size, score);
        cout << "Move (w/a/s/d): ";
        char move; cin >> move;
        if (processMove(board, size, move, score)) addRandomTile(board, size);
    }
    clearScreen();
    printBoard(board, size, score);
    cout << "Game Over! Final Score: " << score << endl;
    updateLeaderboard(name, score, size);
    waitForEnter();
}

void runApplication() {
    int choice = 0;
    while (choice != 3) {
        clearScreen();
        cout << "==== 2048 CONSOLE ====\n1. Start Game\n2. Leaderboard\n3. Exit\nChoice: ";
        if (!(cin >> choice)) { cin.clear(); cin.ignore(1000, '\n'); continue; }
        switch (choice) {
        case 1: startGame(); break;
        case 2: showLeaderboard(); break;
        case 3: cout << "Goodbye!" << endl; break;
        }
    }
}