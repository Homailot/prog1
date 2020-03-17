// TP01.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include <algorithm>
#include <limits>
#include <iomanip>
using namespace std;

template <typename T>
bool checkInput(T &input) {
	cin >> input;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	} else if(cin.peek() != '\n') {
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}

	return true;
}

void ex_2() {
	// Mean between 3 numbers
	int number1, number2, number3;
	float mean;

	cout << "Please, input 3 integer numbers" << endl << "A ? ";
	cin >> number1;
	cout << "B ? ";
	cin >> number2;
	cout << "C ? ";
	cin >> number3;

	mean = (float)(number1 + number2 + number3) / 3;
	cout << "mean = " << mean << endl;
	cout << "A-mean = " << number1 - mean << endl;
	cout << "B-mean = " << number2 - mean << endl;
	cout << "C-mean = " << number3 - mean << endl;
}

void ex_3() {
	// Gets mass of a sphere given the specific mass and radius.
	float specific_mass, radius;
	double pi = M_PI, mass;

	cout << "Specific mass of the material in Kg/m^3: ";
	cin >> specific_mass;
	cout << "Radius of the sphere in m: ";
	cin >> radius;
	
	mass = 4.0 / 3 * (specific_mass * pi * pow(radius, 3));
	cout << "The mass of the sphere in Kg is: " << mass << endl;
}

void ex_4() {
	//Solves the system of equations
	float x, y;
	map <string, float> variables = {
		{"a", 0.0},
		{"b", 0.0},
		{"c", 0.0},
		{"d", 0.0},
		{"e", 0.0},
		{"f", 0.0}
	};
	map<string, float>::iterator it;
	
	for (it = variables.begin(); it != variables.end(); ++it) {
		cout << it->first << " = ";
		cin >> it->second;
	}

	x = (float)(variables["c"] * variables["e"] - variables["b"] * variables["f"]) /
		(variables["a"] * variables["e"] - variables["b"] * variables["d"]);
	y = (float)(variables["a"] * variables["f"] - variables["c"] * variables["d"]) /
		(variables["a"] * variables["e"] - variables["b"] * variables["d"]);

	cout << "x is " << x << ", y is " << y << endl;
}

void ex_5() {
	//Add two times together
	long int totalSeconds;
	int time1[3], time2[3];
	map <string, int> resultTime = {
		{"day", 0},
		{"hour", 0},
		{"minute", 0},
	    {"second", 0}
	};
	string order[4] = { "day", "hour", "minute", "second" };
	char separator;

	cout << "Time1 (hours minutes seconds) ? ";
	cin >> time1[0] >> separator >> time1[1] >> separator >> time1[2];
	//scanf(" %f%*c%f%*c%f", &time1[0], &time1[1], &time1[2])
	cout << "Time2 (hours minutes seconds) ? ";
	cin >> time2[0] >> separator >> time2[1] >> separator >>  time2[2];

	totalSeconds = (time1[0] * 3600 + time1[1] * 60 + time1[2]) + (time2[0] * 3600 + time2[1] * 60 + time2[2]);

	resultTime["day"] = totalSeconds / 86400;
	resultTime["second"] = totalSeconds % 86400;
	cout << totalSeconds << endl;

	resultTime["hour"] = resultTime["second"] / 3600;
	resultTime["second"] = resultTime["second"] % 3600;

	resultTime["minute"] = resultTime["second"] / 60;
	resultTime["second"] = resultTime["second"] % 60;

	cout << "Time1 + Time2 = ";
	for (int it = 0; it < 4; it++) {
		cout << resultTime[order[it]] << " " << order[it];

		if (resultTime[order[it]] != 1) {
			cout << "s";
		}

		cout << ", ";
	}

	cout << endl;
}

float distance(pair<float, float> coord1, pair<float, float> coord2) {
	return sqrt(pow(coord2.first - coord1.first, 2) + pow(coord2.second - coord1.second, 2));
}

void ex_6() {
	//Area of a triangle knowing the coordinates of its vertices
	pair<float, float> coordinates[3];
	float perimiter = 0, sideLengths[3], s, area;
	
	for (int i = 0; i < 3; i++) {
		cout << "Vertex " << (i + 1) << ": ";
		cin >> coordinates[i].first >> coordinates[i].second;
	}
	for (int i = 0; i < 3; i++) {
		int next = (i + 1) % 3;
		sideLengths[i] = distance(coordinates[i], coordinates[next]);
		perimiter += sideLengths[i];
	}
	s = perimiter / 2.0f;

	area = sqrt(s * (s - sideLengths[0]) * (s - sideLengths[1]) * (s - sideLengths[2]));
	cout << "The area of the triangle is " << area << endl;
}




int main() {
	ex_2_5();

	return 0;
}