#pragma once
#include<string>

typedef struct {
	int holes[2][6];
	int storage[2];
	std::string playerNames[2];
} Board;

Board initializeBoard();

typedef struct {
	int holes[2][6];
	int storage[2];
	std::string playerName;
	int playerOrder;
} SingleBoard;

SingleBoard initializeSingleBoard();