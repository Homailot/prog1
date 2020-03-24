#include "board.h"


Board initializeBoard() {
	Board newBoard;

	for (int row = 0; row < 2; row++) {
		newBoard.storage[row] = 0;

		for (int column = 0; column < 6; column++) {
			newBoard.holes[row][column] = 4;
		}
	}

	return newBoard;
}

Board testBoard() {
	Board newBoard;

	int holes[2][6] = {
		{0,0,0,0,0,1},
		{0,0,0,0,0,0},
	};

	for (int row = 0; row < 2; row++) {
		newBoard.storage[row] = 0;

		for (int column = 0; column < 6; column++) {
			newBoard.holes[row][column] = holes[row][column];
		}
	}

	return newBoard;
}