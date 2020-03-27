#include "gameIO.h"
#include "game.h"
#include "common.h"
#include "board.h"
#include "position.h"
#include "draw.h"
#include "bot.h"
#include <map>
#include <sstream>

void gameMultiLoop(Board gameBoard, bool multiplayer = true, int startingPlayer = 0);
int collect(int player, Board gameBoard, bool multiplayer); 
Position sow(Position positionS, Board& gameBoard, bool changeBoard);
int capture(int playerOrig, Position positionS, Board& gameBoard, bool changeBoard);

int rockPaperScissors() {
	bool tie = true;
	std::stringstream ss;
	std::string input;
	std::string names[3] = { "ROCK", "PAPER","SCISSORS" };
	std::map<std::string, int> inputToInt = {
		{"ROCK", 0},
		{"PAPER", 1},
		{"SCISSORS", 2}
	};

	while (tie) {
		tie = false;
		printMessage("Rock, Paper, or Scissors? ", GREEN, BLACK, "");
		while (!checkInput(input) || inputToInt.find(stringToUpper(input)) == inputToInt.end()) {
			printMessage("Invalid input, please try again.");
			printMessage("Rock, Paper, or Scissors? ", "");
		}

		int computerChoice = randomInt(2, 0);
		int humanChoice = inputToInt.at(stringToUpper(input));

		ss.str(std::string());
		ss << "Computer chooses " << names[computerChoice] << ".";
		printMessage(ss.str(), RED, BLACK);
		if (humanChoice == trueMod(computerChoice + 1, 3)) {
			printMessage("Player wins!", YELLOW, BLACK);
			return 0;
		}
		else if (humanChoice == computerChoice) {
			printMessage("TIE.", RED, BLACK);
			tie = true;
		}else {
			printMessage("Computer wins.", RED, BLACK);
		}
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
		boardCopy = copyBoard(gameBoard);
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

void startSingleGame() {
	Board gameBoard = initializeBoard();

	std::stringstream ss;
	std::string playerName;
	int player;

	ss.str(std::string());

	ss << "Player, what is your name? ";
	printMessage(ss.str(), GREEN, BLACK, "");

	getString(playerName);

	ss.str(std::string());
	ss << "Welcome " << playerName << ".";

	printMessage(ss.str());
	waitForKey();
	clearScreen();

	printMessage("You will now play a game of Rock, Paper, Scissors with the computer to determine which of you plays first.");
	player = rockPaperScissors();
	waitForKey();

	gameBoard.playerNames[player] = playerName;
	gameBoard.playerNames[trueMod(player + 1, 2)] = "COM"/*stringWithColor("Computer", RED, BLACK)*/;

	gameMultiLoop(gameBoard, false, player);
}

void startMultiGame() {
	Board gameBoard = initializeBoard();

	std::stringstream ss;
	std::string playerName;

	for (int player = 0; player < 2; player++) {
		ss.str(std::string());

		ss << "Player " << player + 1 << ", what is your name? ";
		printMessage(ss.str(), GREEN, BLACK, "");

		getString(playerName);
		gameBoard.playerNames[player] = playerName;

		ss.str(std::string());
		ss << "Welcome " << playerName << ".";

		printMessage(ss.str());
	}
	waitForKey();
	gameMultiLoop(gameBoard);
}

void endGame(Board gameBoard, bool multiplayer) {
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

	waitForKey();
}

void gameMultiLoop(Board gameBoard, bool multiplayer, int startingPlayer) {
	std::stringstream ss;
	int player = 0, seeds = 0;
	Position position;

	while (true) {
		clearScreen();
		drawBoard(player, gameBoard);
		position.player = player;
		ss.str(std::string());

		if (getNumberOfSeeds(player, gameBoard) == 0) {
			ss << " Because " << gameBoard.playerNames[player] << " has no seeds, their turn will be skipped.";
			printMessage(ss.str());
			waitForKey();

			player = trueMod(player + 1, 2);
			continue;
		}
		else if (onlyIllegalMoves(player, gameBoard)) {
			ss << " Because " << gameBoard.playerNames[player] << " can't do any legal moves, each player collects their seeds and the match ends.";
			printMessage(ss.str());

			gameBoard.storage[0] += getNumberOfSeeds(0, gameBoard);
			gameBoard.storage[1] += getNumberOfSeeds(1, gameBoard);
			break;
		}

		printMessage("");
		ss <<" "<< gameBoard.playerNames[player] << ", it is your turn.";
		printMessage(ss.str());
		
		if (player == startingPlayer || multiplayer == true) {
			position.hole = collect(player, gameBoard, multiplayer);
		}
		else {
			position.hole = chooseHole(player, gameBoard);
			ss.str(std::string());
			ss << " COM chooses hole " << (char)(position.hole + 'a') << ".";
			printMessage(ss.str());
			waitForKey();
		}

		if (position.hole == -1) {
			printMessage(" The match has ended, each player will now collect their seeds.");

			gameBoard.storage[0] += getNumberOfSeeds(0, gameBoard);
			gameBoard.storage[1] += getNumberOfSeeds(1, gameBoard);
			break;
		}
		printMessage("");
		printMessage(" Sowing...");
		position = sow(position, gameBoard);

		drawBoard(player, gameBoard);
		printMessage("");
		waitForKey();

		printMessage("");
		if (player != position.player) {
			if (isIllegalMove(position, gameBoard)) {
				printMessage(" You have executed an illegal move and, therefore, cannot capture any seeds.");
				waitForKey();
			}
			else {
				seeds = capture(player, position, gameBoard);
				if (seeds > 0) {
					ss.str(std::string());
					if (player == startingPlayer || multiplayer == true) ss << " You have captured " << seeds << " seeds!";
					else ss << "COM has captured " << seeds << " seeds.";
					printMessage(ss.str());

					drawBoard(player, gameBoard);
					waitForKey();
				}
			}
			
		}
		if (gameBoard.storage[player] > 24) break;
		else if (gameBoard.storage[trueMod(player + 1, 2)] == 24 && gameBoard.storage[player] == 24) break;

		player = trueMod(player + 1, 2);
	}

	printMessage("GAME OVER!");
	waitForKey();
	endGame(gameBoard, multiplayer);
}

int collect(int player, Board gameBoard, bool multiplayer) {
	char input;
	int conversion;

	do {
		printMessage(" Which hole will you choose to collect your seeds? ", "");

		if (!checkInputOrSTOP(input)) {
			printMessage("Invalid input, please try again.");
			
			continue;
		}

		if (checkStop(input)) {
			if (requestStop(player, gameBoard, multiplayer)) {
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
			if (getNumberOfSeeds(trueMod(player + 1, 2), gameBoard) == 0) {
				printMessage("You have to choose a hole that allows the other player to continue to play, try again.");
			}
			else break;
		}
		else break;
	} while (true);
	

	return conversion;
}


Position sow(Position positionS, Board& gameBoard, bool changeBoard) {
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
			if(changeBoard) gameBoard.holes[player][position] += 1;
			seeds--;
		}
	}

	positionS.hole = position;
	positionS.player = player;
	return positionS;
}

int capture(int playerOrig, Position positionS, Board& gameBoard, bool changeBoard) {
	int player = positionS.player;
	int position = positionS.hole;
	int sum = 0;

	while (position >= 0 && (gameBoard.holes[player][position] == 2 || gameBoard.holes[player][position] == 3)) {
		sum += gameBoard.holes[player][position];
		if (changeBoard) {
			gameBoard.storage[playerOrig] += gameBoard.holes[player][position];
			gameBoard.holes[player][position] = 0;
		}

		position--;
	}

	return sum;
}
