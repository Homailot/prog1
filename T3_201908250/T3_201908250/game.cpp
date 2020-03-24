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
		ss << gameBoard.playerNames[player] << ", it is your turn.";
		printMessage(ss.str());
		
		position.hole = collect(player, gameBoard);

		position = sow(position, gameBoard);

		capture(player, position, gameBoard);

		printBoard(gameBoard);
		printMessage("");
		player = trueMod(player + 1, 2);
	}
}

int collect(int player, Board gameBoard) {
	char input;

	printMessage("Which hole will you choose to collect your seeds? ", "");
	while (!checkInput(input) || std::toupper(input) > 'F' || std::toupper(input) < 'A') {
		printMessage("Invalid input, please try again.");
		printMessage("Which hole will you choose to collect your seeds? ", "");
	}

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
