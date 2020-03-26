#include "board.h"
#include "common.h"
#include "gameIO.h"
#include "color.h"
#include <iostream>
#include <limits>
#include <string>
#include <sstream>

void getString(std::string &string) {
	std::getline(std::cin, string);
}

void printBoard(Board gameBoard) {
	for (int row = 0; row < 2; row++) {
		std::cout << "Storage " << row << ": " << gameBoard.storage[row] << std::endl;

		for (int column = 0; column < 6; column++) {
			std::cout << gameBoard.holes[row][column] << " ";
		}

		std::cout << std::endl;
	}
}

void printMessage(std::string message, std::string end) {
	std::cout << message << end;
}

void printMessage(std::string message, int bgColor, int fgColor, std::string end) {
	std::cout << "\033[" << COLOR[bgColor].first << ";" << COLOR[fgColor].second << "m" << message << "\033[0m" << end;
}

bool checkStop(char input) {
	return std::cin.eof() || std::toupper(input) == 'S';
}

bool requestStop(int player, Board gameBoard, bool multiplayer) {
	char input;
	std::cin.clear();

	std::stringstream ss;
	ss <<" "<< gameBoard.playerNames[player] << " has declared an infinite cycle or wants to stop.";
	printMessage(ss.str());

	if (!multiplayer) return true;

	ss.str(std::string());
	ss << " " << gameBoard.playerNames[trueMod(player + 1, 2)] << " do you agree? (Y/N) ";
	printMessage(ss.str());

	while (!checkInput(input) || (std::toupper(input) != 'Y' && std::toupper(input) != 'N')) {
		printMessage("Invalid input, please try again.");

		ss.str(std::string());
		ss << " " << gameBoard.playerNames[trueMod(player + 1, 2)] << " do you agree? (Y/N) ";
		printMessage(ss.str());
	}

	return (toupper(input) == 'Y');
}

void clearScreen() {
	std::cout << "\033[2J\033[1;1H";
}

void waitForKey() {
	printMessage("Press any key to continue...", WHITE, BLACK, "");
	std::cin.get();
}