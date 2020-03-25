#include<random>
#include<string>

std::string stringToUpper(std::string str) {
	std::string::iterator it;
	std::string newCopy = str;

	for (it = newCopy.begin(); it != newCopy.end(); it++) {
		(*it) = toupper((*it));
	}

	return newCopy;
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