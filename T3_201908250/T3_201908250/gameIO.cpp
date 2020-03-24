#include "board.h"
#include <iostream>
#include <limits>
#include <string>

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

void printMessage(std::string message, std::string end = "\n") {
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