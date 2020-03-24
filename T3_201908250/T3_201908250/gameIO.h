#pragma once
#include<iostream>
#include<string>

template <typename T>
bool checkInput(T& input, char delimiter = '\n') {
	std::cin >> input;

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
		return false;
	}
	else if (std::cin.eof()) {
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

	return true;
}

void getString(std::string& string);
void printMessage(std::string message, std::string end = "\n");
std::string stringToUpper(std::string str);