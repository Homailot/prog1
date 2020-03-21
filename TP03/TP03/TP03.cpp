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
#include <assert.h> 

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
		return 28 + isLeapYear(year);
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
	if (month < 1 || month > 12) {
		cout << "Invalid month" << endl;
		return;
	}

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

	while (day <= totalDays) {
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

void showCalendars(int year) {
	for (int month = 1; month <= 12; month++) {
		showCalendar(year, month);
		cout << endl;
	}
}

// Exercises 1 and 12

float distance(pair<float, float> coord1, pair<float, float> coord2) {
	return sqrt(pow(coord2.first - coord1.first, 2) + pow(coord2.second - coord1.second, 2));
}

float area(pair<float, float> vertex1, pair<float, float> vertex2, pair<float, float> vertex3) {
	// Area of a triangle knowing the coordinates of its vertices
	pair<float, float> coordinates[3] = { vertex1, vertex2, vertex3 };
	float perimiter = 0, sideLengths[3], s, area;

	for (int i = 0; i < 3; i++) {
		int next = (i + 1) % 3;
		sideLengths[i] = distance(coordinates[i], coordinates[next]);
		perimiter += sideLengths[i];
	}
	s = perimiter / 2.0f;

	area = sqrt(s * (s - sideLengths[0]) * (s - sideLengths[1]) * (s - sideLengths[2]));
	return area;
}

float area(float radius) {
	// Area of a circle knowing its radius
	return (float)M_PI * radius * radius;
}

float area(pair<float, float> vertex1, pair<float, float> vertex2) {
	// Area of a rectangle, knowing two of its opposite vertices
	pair<float, float> vertex3 = make_pair(vertex1.first, vertex2.second);
	float side1 = distance(vertex1, vertex3);
	float side2 = distance(vertex3, vertex2);

	return side1 * side2;
}

// Exercise 13

int rollDie(int low = 1, int high = 6)
{
	assert(high >= low);
	return (rand() % (high - low + 1)) + low;
}

// Exercise 14

double integrateTR(double f(double), double a, double b, int n) {
	double width = (b - a) / n, sum = 0;

	for (int i = 1; i <= n; i++) {
		sum += width / 2 * (f(a + (i - 1) * width) + f(a + i * width));
	}

	return sum;
}

double g(double x) {
	return x * x;
}

double h(double x) {
	return sqrt(4 - x * x);
}


int main()
{
	cout << integrateTR(h, -2, 2, 100);

	return 0;
}

