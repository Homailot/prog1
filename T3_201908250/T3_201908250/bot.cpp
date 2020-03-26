//double scoreFromHoles(int player, Board gameBoard) {
//	double score = 0;
//
//	for (int hole = 0; hole < 6; hole++) {
//		if (gameBoard.holes[player][hole] >= 12) score += 2;
//	}
//
//	player = trueMod(player + 1, 2);
//
//	for (int hole = 0; hole < 6; hole++) {
//		if (gameBoard.holes[player][hole] == 1 || gameBoard.holes[player][hole] == 2) score += 3;
//		else if (gameBoard.holes[player][hole] == 0) score += 4;
//	}
//
//	return score;
//}
//
//// Idea from http://www.joansala.com/auale/strategy/en/
//double evaluateBoard(int player, Board gameBoard) {
//	double totalScore = 0, tempScore;
//
//	for (int i = 0; i < 2; i++, player = trueMod(player + 1, 2)) {
//		tempScore = 0;
//		tempScore += (double) gameBoard.storage[player] * 2;
//
//		tempScore += scoreFromHoles(player, gameBoard);
//
//		if (i == 0) totalScore += tempScore;
//		else totalScore -= tempScore;
//	}
//
//	return totalScore;
//}

#include "board.h"
#include "common.h"
#include "position.h"
#include "game.h"
#include <limits>
#include <vector>

double scoreFromHoles(int player, const Board gameBoard) {
	double score = 0, tempScore;
	int seeds, captured;
	Board boardCopy;
	Position position;

	for (int hole = 0; hole < 6; hole++) {
		position.hole = hole; position.player = player;
		boardCopy = copyBoard(gameBoard);
		seeds = boardCopy.holes[player][hole];
		if (seeds == 0) continue;

		position = sow(position, boardCopy);
		tempScore =  0.125 * seeds;
		if (tempScore > 1.5) tempScore = 1.5;

		score += tempScore;

		if (position.player != player) {
			if (!isIllegalMove(position, boardCopy)) {
				captured = capture(player, position, boardCopy);
				if (captured + gameBoard.storage[player] > 24) score += 10;
				else score += (double)captured * 2;
			}

		}
	}

	player = trueMod(player + 1, 2);

	for (int opponentHole = 0; opponentHole < 6; opponentHole++) {
		if (gameBoard.holes[player][opponentHole] == 1 || gameBoard.holes[player][opponentHole] == 2) score += 1.25;
		else if (gameBoard.holes[player][opponentHole] == 0) score += 3;
	}

	return score;
}

// Idea from http://www.joansala.com/auale/strategy/en/
double evaluateBoard(int player, const Board gameBoard) {
	double totalScore = 0, tempScore;

	for (int i = 0; i < 2; i++, player = trueMod(player + 1, 2)) {
		tempScore = 0;
		tempScore += (double)gameBoard.storage[player] * 2;

		tempScore += scoreFromHoles(player, gameBoard);

		if (i == 0) totalScore += tempScore;
		else totalScore -= tempScore;
	}

	return totalScore;
}

int chooseHole(int player, const Board gameBoard) {
	Board boardCopy;
	Position position;
	double boardEvaluation = evaluateBoard(player, gameBoard);
	double maxEvalDiff = -std::numeric_limits<double>::max();
	double evalDiff;
	std::vector<int> possibleChoices;

	for (int hole = 0; hole < 6; hole++) {
		boardCopy = copyBoard(gameBoard);

		if (boardCopy.holes[player][hole] == 0) {
			continue;
		}
		else if (boardCopy.holes[player][hole] <= (5 - hole)) {
			if (getNumberOfSeeds(trueMod(player + 1, 2), boardCopy) == 0) {
				continue;
			}
		}

		position.hole = hole;
		position.player = player;

		position = sow(position, boardCopy);
		if(position.player != player) capture(player, position, boardCopy);
		
		evalDiff = evaluateBoard(player, boardCopy) - boardEvaluation;

		if (evalDiff >= maxEvalDiff) {
			if (evalDiff > maxEvalDiff) {
				maxEvalDiff = evalDiff;
				possibleChoices.clear();
			}
			
			possibleChoices.push_back(hole);
		}
	}
	return possibleChoices[randomInt((int)possibleChoices.size() - 1, 0)];
}