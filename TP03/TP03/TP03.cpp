// TP03.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <algorithm>
#include <limits>
#include <iomanip>
#include <iostream>
#include <complex>

template <typename T>
bool checkInput(T& input, char delimiter = '\n') {
	cin >> input;

	if (cin.fail()) {
		cin.clear();
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		return false;
	}
	else if (cin.peek() != delimiter) {
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		return false;
	}
	
	if (delimiter != '\n') {
		cin.ignore(1);
	}

	return true;
}

template <typename T>
bool checkLineInput(T& input) {
	cin >> input;

	if (cin.fail()) {
		cin.clear();
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		return false;
	}
	if (cin.peek() == '\n') {
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');
		return false;
	}

	return true;
}

// Exercise 4

double round(double x, unsigned n) {
	int factor = pow(10, n);


	return floor(x * factor + 0.5) / factor;
}

// Exercise 5

int gcd(int n1, int n2) {
	if (n1 == 0) return n2;
	else if (n2 == 0) return n1;

	while (n1 != n2) {
		if (n1 > n2) n1 -= n2;
		else n2 -= n1;
	}

	return n1;
}

// Exercise 6

time_t timeElapsed() {
	static time_t timeStarted = time(NULL);
	time_t timeNow = time(NULL);

	return timeNow - timeStarted;
}

// Exercise 8

bool readFraction(int& numerator, int& denominator) {
	char delimiter;

	if (!checkLineInput(numerator)) return false;
	if (!checkLineInput(delimiter) || delimiter != '/') return false;
	if (!checkInput(denominator)) return false;

	return true;
}

void reduceFraction(int& numerator, int& denominator) {
	int divisor = gcd(numerator, denominator);

	numerator /= divisor;
	denominator /= divisor;
}



void testFractions() {
	int numerator, denominator;

	if (readFraction(numerator, denominator)) {
		reduceFraction(numerator, denominator);
		cout << numerator << "/" << denominator << endl;
	}
}

int main()
{
	testFractions();

	return 0;
}

