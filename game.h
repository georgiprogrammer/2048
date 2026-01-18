#ifndef GAME_H
#define GAME_H

#include "constants.h"

void clearBoard(int board[MAX_SIZE][MAX_SIZE], int size);
void addRandomTile(int board[MAX_SIZE][MAX_SIZE], int size);
bool moveLeft(int board[MAX_SIZE][MAX_SIZE], int size, int& score);
void rotateBoard(int board[MAX_SIZE][MAX_SIZE], int size);
bool processMove(int board[MAX_SIZE][MAX_SIZE], int size, char direction, int& score);
bool hasMoves(int board[MAX_SIZE][MAX_SIZE], int size);

#endif
