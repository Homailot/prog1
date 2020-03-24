#include "gameIO.h"
#include "game.h"
#include "common.h"
#include "board.h"
#include <map>
#include <sstream>

void gameMultiLoop(Board gameBoard);
int collect(int player, Board gameBoard); 
int sow(int player, int position, Board& gameBoard);

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
	int player = 0, seeds = 0, position;

	while (true) {
		ss.str(std::string());
		ss << gameBoard.playerNames[player] << ", it is your turn.";
		printMessage(ss.str());
		
		position = collect(player, gameBoard);



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

int sow(int player, int position, Board& gameBoard) {

}
