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
		{1,1,1,5,11,10},
		{0,0,0,0,8,8},
	};

	for (int row = 0; row < 2; row++) {
		newBoard.storage[row] = 0;

		for (int column = 0; column < 6; column++) {
			newBoard.holes[row][column] = holes[row][column];
		}
	}
	newBoard.storage[0] = 3;
	newBoard.storage[1] = 0;

	return newBoard;
}


Board testBoard2() {
	Board newBoard;

	int holes[2][6] = {
		{0,13,0,0,0,0},
		{0,2,3,6,1,6}
	};

	for (int row = 0; row < 2; row++) {
		newBoard.storage[row] = 0;

		for (int column = 0; column < 6; column++) {
			newBoard.holes[row][column] = holes[row][column];
		}
	}
	newBoard.storage[0] = 11;
	newBoard.storage[1] = 06;

	return newBoard;
}

Board copyBoard(Board board) {
	Board boardCopy;

	for (int row = 0; row < 2; row++) {
		boardCopy.storage[row] = board.storage[row];

		for (int column = 0; column < 6; column++) {
			boardCopy.holes[row][column] = board.holes[row][column];
		}
	}

	return boardCopy;
}