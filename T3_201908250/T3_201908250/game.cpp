#include "gameIO.h"
#include "game.h"
#include "common.h"
#include "board.h"
#include "position.h"
#include "draw.h"
#include <map>
#include <sstream>

void gameMultiLoop(Board gameBoard);
int collect(int player, Board gameBoard); 
Position sow(Position positionS, Board& gameBoard);
int capture(int playerOrig, Position positionS, Board& gameBoard);

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
	bool notEmptyOpponentField = getNumberOfSeeds(trueMod(player + 1, 2), gameBoard) != 0;

	for (int hole = 0; hole < 6; hole++) {
		// Copy the gameBoard to boardCopy
		for (int row = 0; row < 2; row++) {
			for (int column = 0; column < 6; column++) {
				boardCopy.holes[row][column] = gameBoard.holes[row][column];
			}
		}
		// -------------------------------------------
		if (boardCopy.holes[player][hole] == 0) continue;

		//
		if (boardCopy.holes[player][hole] <= (5 - hole)) {
			if (notEmptyOpponentField) return false;
		}

		if (boardCopy.holes[player][hole] > (5 - hole)) {
			position.player = player;
			position.hole = hole;

			position = sow(position, boardCopy);

			if (player == position.player && hole > position.hole) {
				return false;
			}
			if (player != position.player && !isIllegalMove(position, boardCopy)) {
				return false;
			}
		}
	}

	return true;
}

void startMultiGame() {
	Board gameBoard = initializeBoard();

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

		printMessage(ss.str(), GREEN, BLACK);
	}
	waitForKey();
	gameMultiLoop(gameBoard);
}

void endGame(Board gameBoard) {
	clearScreen();
	std::stringstream ss;

	printMessage("And the winner is...");
	waitForKey();

	clearScreen();
	printMessage("And the winner is...");
	if (gameBoard.storage[0] == gameBoard.storage[1]) {
		printMessage("No one! It's a draw!");
	}
	else if (gameBoard.storage[0] > gameBoard.storage[1]) {
		ss << gameBoard.playerNames[0] << "! Congratulations";
		printMessage(ss.str());
	}
	else {
		ss << gameBoard.playerNames[1] << "! Congratulations";
		printMessage(ss.str());
	}
}

void gameMultiLoop(Board gameBoard) {
	std::stringstream ss;
	int player = 0, seeds = 0;
	Position position;

	while (true) {
		clearScreen();
		drawBoard(player, gameBoard);
		position.player = player;
		ss.str(std::string());

		if (getNumberOfSeeds(player, gameBoard) == 0) {
			ss << "Because " << gameBoard.playerNames[player] << " has no seeds, their turn will be skipped.";
			printMessage(ss.str());
			waitForKey();

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

		if (position.hole == -1) {
			printMessage("The match has ended, each player will now collect their seeds.");

			gameBoard.storage[0] += getNumberOfSeeds(0, gameBoard);
			gameBoard.storage[1] += getNumberOfSeeds(1, gameBoard);
			break;
		}
		printMessage("");
		printMessage("Sowing...");
		position = sow(position, gameBoard);

		drawBoard(player, gameBoard);
		waitForKey();

		printMessage("");
		if (player != position.player) {
			if (isIllegalMove(position, gameBoard)) {
				printMessage("You have executed an illegal move and, therefore, cannot capture any seeds.");
			}
			else {
				seeds = capture(player, position, gameBoard);
				if (seeds > 0) {
					ss.str(std::string());
					ss << "You have captured " << seeds << " seeds!";
					printMessage(ss.str());

					drawBoard(player, gameBoard);
				}
				else {
					printMessage("You didn't capture any seeds this round.");
				}
				
			}

			waitForKey();
		}
		if (gameBoard.storage[player] > 24) break;
		else if (gameBoard.storage[trueMod(player + 1, 2)] == 24 && gameBoard.storage[player] == 24) break;


		player = trueMod(player + 1, 2);
	}

	printMessage("GAME OVER!");
	waitForKey();
	endGame(gameBoard);
}

int collect(int player, Board gameBoard) {
	char input;
	int conversion;

	do {
		printMessage("Which hole will you choose to collect your seeds? ", "");

		if (!checkInputOrSTOP(input)) {
			printMessage("Invalid input, please try again.");
			
			continue;
		}

		if (checkStop(input)) {
			if (requestStop(player, gameBoard)) {
				return -1;
			}

			printMessage("And so the game continues...");
			continue;
		}

		input = std::toupper(input);
		conversion = input - 'A';

		if (input > 'F' || input < 'A') {
			printMessage("That hole does not exist, please try again.");
		}
		else if (gameBoard.holes[player][conversion] == 0) {
			printMessage("The chosen hole has no seeds, choose another hole.");
		} else if (gameBoard.holes[player][conversion] <= (5 - conversion)) {
			if (getNumberOfNonEmptyHoles(trueMod(player + 1, 2), gameBoard) == 0) {
				printMessage("You have to choose a hole that allows the other player to continue to play, try again.");
			}
			else break;
		}
		else break;
	} while (true);
	

	return conversion;
}


Position sow(Position positionS, Board& gameBoard) {
	int seeds, player, position;
	Position originalPosition;
	originalPosition.player = player = positionS.player;
	originalPosition.hole = position = positionS.hole;

	for (seeds = gameBoard.holes[player][position], gameBoard.holes[player][position] = 0; seeds > 0;) {
		if (position + 1 > 5) {
			position = 0;
			player = trueMod(player + 1, 2);
		}
		else {
			position++;
		}

		if (player != originalPosition.player || position != originalPosition.hole) {
			gameBoard.holes[player][position] += 1;
			seeds--;
		}
	}

	positionS.hole = position;
	positionS.player = player;
	return positionS;
}

int capture(int playerOrig, Position positionS, Board& gameBoard) {
	int player = positionS.player;
	int position = positionS.hole;
	int sum = 0;

	while (position >= 0 && (gameBoard.holes[player][position] == 2 || gameBoard.holes[player][position] == 3)) {
		sum += gameBoard.holes[player][position];
		gameBoard.storage[playerOrig] += gameBoard.holes[player][position];
		gameBoard.holes[player][position] = 0;

		position--;
	}

	return sum;
}
