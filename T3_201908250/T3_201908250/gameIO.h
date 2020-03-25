#pragma once
#include"board.h"
#include<iostream>
#include<string>

template <typename T>
bool checkInput(T& input, char delimiter = '\n') {
	std::cin >> input;

	if (std::cin.eof()) {
		std::cin.clear();
		return false;
	}
	else if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		return false;
	}
	else if (std::cin.peek() != delimiter) {
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		return false;
	}

	if (delimiter != '\n') {
		std::cin.ignore(1);
	}
	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

	return true;
}

template <typename T>
bool checkInputOrSTOP(T& input, char delimiter = '\n') {
	std::cin >> input;

	if (std::cin.eof()) {
		return true;
	}
	else if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		return false;
	}
	else if (std::cin.peek() != delimiter) {
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		return false;
	}

	if (delimiter != '\n') {
		std::cin.ignore(1);
	}
	std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

	return true;
}

void getString(std::string& string);
void printBoard(Board gameBoard);
void printMessage(std::string message, std::string end = "\n");
std::string stringToUpper(std::string str);
bool checkStop(char input);
bool requestStop(int player, Board gameBoard);
void clearScreen();
void waitForKey();