#include "board.h"
#include "common.h"

double scoreFromHoles(int player, Board gameBoard) {
	double score = 0;

	for (int hole = 0; hole < 6; hole++) {
		if (gameBoard.holes[player][hole] >= 12) score += 2;
	}

	player = trueMod(player + 1, 2);

	for (int hole = 0; hole < 6; hole++) {
		if (gameBoard.holes[player][hole] == 1 || gameBoard.holes[player][hole] == 2) score += 3;
		else if (gameBoard.holes[player][hole] == 0) score += 4;
	}

	return score;
}

// Idea from http://www.joansala.com/auale/strategy/en/
double evaluateBoard(int player, Board gameBoard) {
	double totalScore = 0, tempScore;

	for (int i = 0; i < 2; i++, player = trueMod(player + 1, 2)) {
		tempScore = 0;
		tempScore += (double) gameBoard.storage[player] * 2;

		tempScore += scoreFromHoles(player, gameBoard);

		if (i == 0) totalScore += tempScore;
		else totalScore -= tempScore;
	}

	return totalScore;
}