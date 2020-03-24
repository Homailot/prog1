#include "gameIO.h"
#include "game.h"
#include "common.h"
#include "board.h"
#include <map>
#include <sstream>

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

void playSingle() {
	SingleBoard gameBoard = initializeSingleBoard();

	gameBoard.playerOrder = rockPaperScissors();
}

void playMulti() {
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

	startMultiGame(gameBoard);
}