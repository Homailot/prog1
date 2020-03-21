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

int trueMod(int n, int divisor) {
	int result = n % divisor;

	if (result < 0) {
		return result + divisor;
	}
	return result;
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

// Exercise 9

bool isLeapYear(int year) {
	return year % 400 == 0 || (year % 4 == 0 && year % 100 != 0);
}

int getNumberOfDays(int year, int month) {
	if (month == 2) {
		if (isLeapYear(year)) return 29;
		else return 28;
	}
	else if ((month < 8 && month % 2 == 0) || (month > 8 && month % 2 != 0)) {
		return 30;
	}
	else {
		return 31;
	}
}

int getMonthCode(int year, int month) {
	int codeMap[12] = { 0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5 };

	if (isLeapYear(year)) {
		if (month == 1) return 6;
		if (month == 2) return 2;
	}

	return codeMap[month - 1];
}

int getDayOfWeek(int year, int month, int day) {
	int s, a, c = getMonthCode(year, month);
	s = year / 100;
	a = year % 100;

	return ((int)floor(5 * a / 4) + c + day - 2 * (s % 4) + 7) % 7;
}

string dayOfWeekToString(int dayOfWeek) {
	string days[7] = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };

	return days[dayOfWeek];
}

string monthToString(int month) {
	string months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };

	return months[month - 1];
}

void showCalendar(int year, int month) {
	string days[7] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
	cout << monthToString(month) << "/" << year << endl;
	
	for (size_t i = 0; i < 7; i++) {
		if (i != 0) cout << setw(6);
		else cout << setw(3);
		cout << right << days[i];
	}
	cout << endl;

	int curWeekDay = trueMod(getDayOfWeek(year, month, 1) - 1, 7);
	int totalDays = getNumberOfDays(year, month), day = 1;
	cout << setw((long long)(curWeekDay) * 6) << "";

	while (true) {
		cout << setw(3) << right << day;
	
		if (curWeekDay == 6) {
			curWeekDay = 0;
			cout << endl;
		}
		else {
			curWeekDay++;
			if (day < totalDays) cout << setw(3) << "";
			else break;
		}

		day++;
	}

	cout << endl;
}

int main()
{
	showCalendar(2012, 1);

	return 0;
}

