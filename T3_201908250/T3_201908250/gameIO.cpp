#include <iostream>
#include <limits>
#include <string>

void getString(std::string &string) {
	std::getline(std::cin, string);
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