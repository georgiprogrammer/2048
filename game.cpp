#include <cstdlib>
#include "game.h"

void clearBoard(int board[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) board[i][j] = 0;
    }
}

void addRandomTile(int board[MAX_SIZE][MAX_SIZE], int size) {
    int emptyCount = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) if (board[i][j] == 0) emptyCount++;
    }
    if (emptyCount == 0) return;
    int target = rand() % emptyCount;
    int value = (rand() % 10 < 8) ? 2 : 4;
    int current = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) {
                if (current == target) { board[i][j] = value; return; }
                current++;
            }
        }
    }
}

bool moveLeft(int board[MAX_SIZE][MAX_SIZE], int size, int& score) {
    bool moved = false;
    for (int i = 0; i < size; i++) {
        int lastMergeCol = -1;
        for (int j = 1; j < size; j++) {
            if (board[i][j] == 0) continue;
            int col = j;
            while (col > 0 && board[i][col - 1] == 0) {
                board[i][col - 1] = board[i][col]; board[i][col] = 0;
                col--; moved = true;
            }
            if (col > 0 && board[i][col - 1] == board[i][col] && lastMergeCol != col - 1) {
                board[i][col - 1] *= 2; score += board[i][col - 1];
                board[i][col] = 0; lastMergeCol = col - 1; moved = true;
            }
        }
    }
    return moved;
}

void rotateBoard(int board[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size / 2; i++) {
        for (int j = i; j < size - i - 1; j++) {
            int temp = board[i][j];
            board[i][j] = board[size - 1 - j][i];
            board[size - 1 - j][i] = board[size - 1 - i][size - 1 - j];
            board[size - 1 - i][size - 1 - j] = board[j][size - 1 - i];
            board[j][size - 1 - i] = temp;
        }
    }
}

bool processMove(int board[MAX_SIZE][MAX_SIZE], int size, char direction, int& score) {
    bool moved = false;
    if (direction == 'a') moved = moveLeft(board, size, score);
    else if (direction == 'w') { rotateBoard(board, size); rotateBoard(board, size); rotateBoard(board, size); moved = moveLeft(board, size, score); rotateBoard(board, size); }
    else if (direction == 'd') { rotateBoard(board, size); rotateBoard(board, size); moved = moveLeft(board, size, score); rotateBoard(board, size); rotateBoard(board, size); }
    else if (direction == 's') { rotateBoard(board, size); moved = moveLeft(board, size, score); rotateBoard(board, size); rotateBoard(board, size); rotateBoard(board, size); }
    return moved;
}

bool hasMoves(int board[MAX_SIZE][MAX_SIZE], int size) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == 0) return true;
            if (i < size - 1 && board[i][j] == board[i + 1][j]) return true;
            if (j < size - 1 && board[i][j] == board[i][j + 1]) return true;
        }
    }
    return false;
}