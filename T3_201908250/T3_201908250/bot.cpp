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

double scoreFromHoles(int player, Board gameBoard) {
	double score = 0;
	Position position;

	for (int hole = 0; hole < 6; hole++) {
		position.hole = hole; position.player = player;

		position = sow(position, gameBoard, false);

		if (gameBoard.holes[player][hole] > 12) {
			if (position.player == player || isIllegalMove(position, gameBoard)) {
				score += 1;
				continue;
			}

			score += (double)capture(player, position, gameBoard, false) * 1.25 + 1;
		}

		if (position.player != player) {
			if (!isIllegalMove(position, gameBoard)) {
				score += capture(player, position, gameBoard, false) * 1.25;
			}
		}
	}

	player = trueMod(player + 1, 2);

	for (int opponentHole = 0; opponentHole < 6; opponentHole++) {
		if (gameBoard.holes[player][opponentHole] == 1 || gameBoard.holes[player][opponentHole] == 2) score += 1.75;
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
		capture(player, position, boardCopy);
		
		evalDiff = evaluateBoard(player, boardCopy) - boardEvaluation;

		if (evalDiff >= maxEvalDiff) {
			if (evalDiff > maxEvalDiff) {
				maxEvalDiff = evalDiff;
				possibleChoices.clear();
			}
			
			possibleChoices.push_back(hole);
		}
	}
	return possibleChoices[randomInt(possibleChoices.size() - 1, 0)];
}