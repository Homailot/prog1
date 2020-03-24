#include "gameIO.h"
#include "game.h"
#include "common.h"
#include "board.h"
#include "position.h"
#include <map>
#include <sstream>

void gameMultiLoop(Board gameBoard);
int collect(int player, Board gameBoard); 
Position sow(Position positionS, Board& gameBoard);
void capture(int playerOrig, Position positionS, Board& gameBoard);

int getNumberOfNonEmptyHoles(int player, Board gameBoard) {
	int sum = 0;

	for (int hole = 0; hole < 6; hole++) {
		if (gameBoard.holes[player][hole] != 0) {
			sum++;
		}
	}

	return sum;
}

int getNumberOfSeeds(int player, Board gameBoard) {
	int sum = 0;

	for (int hole = 0; hole < 6; hole++) {
		sum += gameBoard.holes[player][hole];
	}

	return sum;
}

bool isIllegalMove(Position positionS, Board gameBoard) {
	int player = positionS.player;
	int position = positionS.hole;
	int numHoles = getNumberOfNonEmptyHoles(player, gameBoard);

	while (position >= 0 && (gameBoard.holes[player][position] == 2 || gameBoard.holes[player][position] == 3)) {
		position--;
		numHoles--;
	}

	return (numHoles == 0);
}

bool onlyIllegalMoves(int player, Board gameBoard) {
	Board boardCopy;
	Position position;

	for (int hole = 0; hole < 6; hole++) {
		// Copy the gameBoard to boardCopy
		for (int row = 0; row < 2; row++) {
			for (int column = 0; column < 6; column++) {
				boardCopy.holes[row][column] = gameBoard.holes[row][column];
			}
		}
		// -------------------------------------------
		if (boardCopy.holes[player][hole] == 0) continue;

		if (boardCopy.holes[player][hole] <= (5 - hole)) {
			if (getNumberOfNonEmptyHoles(trueMod(player + 1, 2), boardCopy) != 0) return false;
		}

		if (boardCopy.holes[player][hole] > (5 - hole)) {
			position.player = player;
			position.hole = hole;

			position = sow(position, boardCopy);

			if (player != position.player && !isIllegalMove(position, boardCopy)) {
				return false;
			}
		}
	}

	return true;
}

int rockPaperScissors() {
	std::string input;
	std::map<std::string, int> inputToInt = {
		{"ROCK", 0},
		{"PAPER", 1},
		{"SCISSORS", 2}
	};

	printMessage("Rock, Paper, or Scissors? ", "");
	while (!checkInput(input) || inputToInt.find(stringToUpper(input)) == inputToInt.end()) {
		printMessage("Invalid input, please try again.");
		printMessage("Rock, Paper, or Scissors? ", "");
	}

	int computerChoice = randomInt(2, 0);
	int humanChoice = inputToInt.at(stringToUpper(input));
	if (humanChoice == trueMod(computerChoice + 1, 3)) {
		printMessage("Player wins!");
		return 0;
	}
	else {
		printMessage("Computer wins.");
	}

	return 1;
}


void startMultiGame() {
	Board gameBoard = testBoard();

	std::stringstream ss;
	std::string playerName;

	for (int player = 0; player < 2; player++) {
		ss.str(std::string());

		ss << "Player " << player << ", what is your name? ";
		printMessage(ss.str(), "");

		getString(playerName);
		gameBoard.playerNames[player] = playerName;

		ss.str(std::string());
		ss << "Welcome " << playerName << ".";

		printMessage(ss.str());
	}

	printMessage("");
	gameMultiLoop(gameBoard);
}

void gameMultiLoop(Board gameBoard) {
	std::stringstream ss;
	int player = 0, seeds = 0;
	Position position;

	while (true) {
		position.player = player;
		ss.str(std::string());

		if (getNumberOfNonEmptyHoles(player, gameBoard) == 0) {
			ss << "Because " << gameBoard.playerNames[player] << " has no seeds, their turn will be skipped.";
			printMessage(ss.str());

			printMessage("");
			player = trueMod(player + 1, 2);
			continue;
		}
		else if (onlyIllegalMoves(player, gameBoard)) {
			ss << "Because " << gameBoard.playerNames[player] << " can't do any legal moves, each player collects their seeds and the match ends.";
			printMessage(ss.str());

			gameBoard.storage[0] += getNumberOfSeeds(0, gameBoard);
			gameBoard.storage[1] += getNumberOfSeeds(1, gameBoard);
			break;
		}


		ss << gameBoard.playerNames[player] << ", it is your turn.";
		printMessage(ss.str());
		
		position.hole = collect(player, gameBoard);

		position = sow(position, gameBoard);


		if (player != position.player) {
			if (isIllegalMove(position, gameBoard)) {
				printMessage("You have executed an illegal move and, therefore, cannot capture any seeds.");
			}
			else {
				capture(player, position, gameBoard);
			}
		}
		if (gameBoard.storage[player] > 24) break;
		else if (gameBoard.storage[trueMod(player + 1, 2)] == 24 && gameBoard.storage[player] == 24) break;

		printBoard(gameBoard);
		printMessage("");
		player = trueMod(player + 1, 2);
	}

	ss.str(std::string());
	if (gameBoard.storage[0] == gameBoard.storage[1]) {
		printMessage("It's a draw!");
	}
	else if (gameBoard.storage[0] > gameBoard.storage[1]) {
		ss << gameBoard.playerNames[0] << " wins!";
		printMessage(ss.str());
	}
	else {
		ss << gameBoard.playerNames[1] << " wins!";
		printMessage(ss.str());
	}
}

int collect(int player, Board gameBoard) {
	char input;
	int conversion;

	printMessage("Which hole will you choose to collect your seeds? ", "");
	do {
		while (!checkInput(input) || std::toupper(input) > 'F' || std::toupper(input) < 'A') {
			printMessage("Invalid input, please try again.");
			printMessage("Which hole will you choose to collect your seeds? ", "");
		}
		conversion = std::toupper(input) - 'A';

		if (gameBoard.holes[player][conversion] == 0) {
			printMessage("The chosen hole has no seeds, choose another hole: ", "");
		} else if (gameBoard.holes[player][conversion] <= (5 - conversion)) {
			if (getNumberOfNonEmptyHoles(trueMod(player + 1, 2), gameBoard) == 0) {
				printMessage("You have to choose a hole that allows the other player to continue to play, try again: ", "");
			}
			else break;
		}
		else break;
	} while (true);
	

	return std::toupper(input) - 'A';
}


Position sow(Position positionS, Board& gameBoard) {
	int seeds;
	int player = positionS.player;
	int position = positionS.hole;

	for (seeds = gameBoard.holes[player][position], gameBoard.holes[player][position] = 0; seeds > 0; seeds--) {
		if (position + 1 > 5) {
			position = 0;
			player = trueMod(player + 1, 2);
		}
		else {
			position++;
		}

		gameBoard.holes[player][position] += 1;
	}

	positionS.hole = position;
	positionS.player = player;
	return positionS;
}

void capture(int playerOrig, Position positionS, Board& gameBoard) {
	int player = positionS.player;
	int position = positionS.hole;

	while (position >= 0 && (gameBoard.holes[player][position] == 2 || gameBoard.holes[player][position] == 3)) {
		gameBoard.storage[playerOrig] += gameBoard.holes[player][position];
		gameBoard.holes[player][position] = 0;

		position--;
	}
}
