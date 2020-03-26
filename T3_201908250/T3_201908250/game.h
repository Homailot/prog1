#pragma once
#include "board.h"
#include "position.h"

bool isIllegalMove(Position positionS, Board gameBoard);
void startSingleGame();
void startMultiGame();
Position sow(Position positionS, Board& gameBoard, bool changeBoard = true);
int capture(int playerOrig, Position positionS, Board& gameBoard, bool changeBoard = true);
int getNumberOfSeeds(int player, Board gameBoard);