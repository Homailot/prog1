#include "board.h"
#include "common.h"
#include "gameIO.h"
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

std::string stringToUpper(std::string str) {
	std::string::iterator it;
	std::string newCopy = str;

	for (it = newCopy.begin(); it != newCopy.end(); it++) {
		(*it) = toupper((*it));
	}

	return newCopy;
}

bool checkStop(char input) {
	return std::cin.eof() || std::toupper(input) == 'S';
}

bool requestStop(int player, Board gameBoard) {
	char input;
	std::cin.clear();

	std::stringstream ss;
	ss << gameBoard.playerNames[player] << " has declared an infinite cycle or wants to stop.";
	printMessage(ss.str());

	ss.str(std::string());
	ss << gameBoard.playerNames[trueMod(player + 1, 2)] << " do you agree? (Y/N) ";
	printMessage(ss.str());

	while (!checkInput(input) || (std::toupper(input) != 'Y' && std::toupper(input) != 'N')) {
		printMessage("Invalid input, please try again.");

		ss.str(std::string());
		ss << gameBoard.playerNames[trueMod(player + 1, 2)] << " do you agree? (Y/N) ";
		printMessage(ss.str());
	}

	return (toupper(input) == 'Y');
}