#include "color.h"
#include<random>
#include<string>
#include<sstream>

std::string stringToUpper(std::string str) {
	std::string::iterator it;
	std::string newCopy = str;

	for (it = newCopy.begin(); it != newCopy.end(); it++) {
		(*it) = toupper((*it));
	}

	return newCopy;
}

std::string stringWithColor(std::string str, int bgColor, int fgColor) {
	std::stringstream ss;
	ss << "\033[" << COLOR[bgColor].first << ";" << COLOR[fgColor].second << "m" << str << "\033[0m";

	return ss.str();
}

std::string stringWithColor(std::string str, int fgColor) {
	std::stringstream ss;
	ss << "\033[" << COLOR[BLACK].first << ";" << COLOR[fgColor].second << "m" << str << "\033[0m";

	return ss.str();
}



int randomInt(int high, int low) {
	return (rand() % (high - low + 1)) + low;
}

int trueMod(int n, int divisor) {
	int result = n % divisor;

	if (result < 0) {
		return result + divisor;
	}
	return result;
}