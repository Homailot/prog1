#pragma once
#include "board.h"
double scoreFromHoles(int player, const Board gameBoard);
double evaluateBoard(int player, const Board gameBoard);
int chooseHole(int player, const Board gameBoard);