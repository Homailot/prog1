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

SingleBoard initializeSingleBoard() {
	SingleBoard newBoard;

	for (int row = 0; row < 2; row++) {
		newBoard.storage[row] = 0;

		for (int column = 0; column < 6; column++) {
			newBoard.holes[row][column] = 4;
		}
	}

	return newBoard;
}