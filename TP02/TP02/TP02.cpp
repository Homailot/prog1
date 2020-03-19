// TP02.cpp : This file contains the 'main' function. Program execution begins and ends there.
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
bool checkInput(T& input) {
	cin >> input;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	else if (cin.peek() != '\n') {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}

	return true;
}

//Cost of sending a package based on its weight
void ex_4() {
	int weight;
	double cost = 5.0;
	cout << "What is the weight of the package? ";
	cin >> weight;

	if (weight > 1000) {
		cost = 12.5 + (double)((weight - 1000) / 250) * 5;
	}
	else if (weight > 500) {
		cost += (weight - 500) / 100 * 1.5;
	}

	cout << "The cost is " << cost << " euros." << endl;
}

//solve the roots of a quadratic equation ax^2 + bx + c = 0
void ex_5() {
	double a, b, c, x1_real = 0, x_im = 0, x2_real = 0, binome;
	cout << "Give the values for A, B and C in Ax^2 + Bx + C: " << endl;
	cout << "A: ";
	while (!checkInput(a) || a == 0) {
		cout << "Invalid input for A, try again (A is 0 or is not a number): ";
	}
	cout << "B: "; while (!checkInput(b));
	cout << "C: "; while (!checkInput(c));

	binome = pow(b, 2) - 4 * a * c;
	if (binome < 0) {
		x_im = sqrt(fabs(binome)) / (2 * a);
	}
	else {
		x1_real = sqrt(binome);
		x2_real = -x1_real;
	}

	x1_real += (-b);
	x2_real += x1_real;

	x1_real /= (2 * a);
	x2_real /= (2 * a);

	cout << fixed << setprecision(3);
	if (x_im != 0) {
		cout << "The solution has 2 complex roots: " << x1_real << " + " << x_im << "i and " << x2_real << " - " << x_im << "i" << endl;
	}
	else if (x1_real == x2_real) {
		cout << "The solution has 1 real root: " << x1_real << endl;
	}
	else {
		cout << "The solution has 2 real roots: " << x1_real << " and " << x2_real << endl;
	}
}

void ex_5_alt() {
	double a, b, c;
	complex<double> result1, result2, binome;
	cout << "Give the values for A, B and C in Ax^2 + Bx + C: " << endl;
	cout << "A: ";
	while (!checkInput(a) || a == 0) {
		cout << "Invalid input for A, try again (A is 0 or is not a number): ";
	}
	cout << "B: "; while (!checkInput(b));
	cout << "C: "; while (!checkInput(c));

	binome = sqrt((complex<double>) pow(b, 2) - 4 * a * c);
	result1 = (-b + binome) / (2 * a);

	cout << fixed << setprecision(3);
	if (binome.imag() != 0) {
		cout << "The solution has 2 complex roots: " << result1.real() << " + " << result1.imag() << "i and " << result1.real() << " - " << result1.imag() << "i" << endl;
	}
	else if (binome.real() == 0) {
		cout << "The solution has 1 real root: " << result1.real() << endl;
	}
	else {
		result2 = (-b - binome) / (2 * a);

		cout << "The solution has 2 real roots: " << result1.real() << " and " << result2.real() << endl;
	}
}

bool isPrime(unsigned long int num) {
	if (num == 1) return false;

	for (unsigned long int divisor = (unsigned long int)sqrt(num); divisor < num; divisor++) {
		if (num % divisor == 0) {
			return false;
		}
	}

	return true;
}

void ex_7_d() {
	unsigned long int num;
	for (num = numeric_limits<unsigned long int>::max(); !isPrime(num); num--);

	cout << num << " is the largest prime number that can be stored in an unsigned long";
}

int numberOfDigits(int num) {
	num = (int) fabs(num);

	return (int)log10(num) + 1;
}

void ex_8() {
	double lowerLimit, upperLimit, interval;
	int angleSpace, biggestNumber;

	cout << "Lower Limit: ";
	while (!checkInput(lowerLimit));
	cout << "Upper Limit: ";
	while (!checkInput(upperLimit));
	cout << "Interval: ";
	while (!checkInput(interval));

	biggestNumber = max(numberOfDigits((int)lowerLimit), numberOfDigits((int)upperLimit));
	angleSpace = biggestNumber + 6;
	cout << angleSpace << endl;


	cout << fixed << setw(angleSpace) << left;
	cout << "ang" << setw(10) << "  sin" << setw(10) << "  cos" << setw(10) << "  tan" << endl;

	for (double angDeg = lowerLimit; angDeg <= upperLimit; angDeg += interval) {
		double ang = angDeg * M_PI / 180;

		cout << setw(angleSpace) << left << setprecision(3) << angDeg << setprecision(6) << setw(10) << sin(ang) << setw(10) << cos(ang) << setw(10);
		if (angDeg == 90) {
			cout << "infinite";
		}
		else {
			cout << tan(ang);
		}

		cout << endl;
	}
}

void ex_9() {
	unsigned long num, numCopy;
	int digits, lastDigit, firstDigit;
	bool isPalindrome = true;

	cout << "Enter an unsigned number: ";
	while (!checkInput(num));
	digits = numberOfDigits(num);
	numCopy = num;

	for (int curDigits = digits; curDigits > 0 ; curDigits-= 2) {
		lastDigit = numCopy % 10;
		firstDigit = numCopy / pow(10, curDigits - 1);

		if (lastDigit != firstDigit) {
			isPalindrome = false;
			break;
		}

		numCopy -= firstDigit * pow(10, curDigits - 1);
		numCopy /= 10;
	}

	cout << num;
	if (isPalindrome) {
		cout << " is a palindrome.";
	}
	else {
		cout << " is not a palindrome.";
	}

	cout << endl;
}

void ex_15() {
	srand(time(NULL));
	int number1 = rand() % 8 + 2;
	int number2 = rand() % 8 + 2;
	int answer, result = number1 * number2;
	double elapsedTime;

	time_t time1, time2;
	cout << "What is " << number1 << " x " << number2 << "? ";
	time1 = time(NULL);
	while (!checkInput(answer));
	time2 = time(NULL);
	
	elapsedTime = difftime(time2, time1);
	if (answer != result) {
		cout << "Very Bad!";
	}
	else if (elapsedTime < 5) {
		cout << "Good!";
	}
	else if (elapsedTime <= 10) {
		cout << "Satisfactory.";
	}
	else {
		cout << "Insufficient.";
	}
	
	cout << endl;
}


int main() {
	ex_15();

	return 0;
}