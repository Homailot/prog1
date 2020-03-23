// TP04.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

using namespace std;
#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <string>
#include <limits>
#include <iomanip>
#include <iostream>
#include <vector>
#include <algorithm>

const int NE = 5;

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

// Exercise 1

void readArray(int a[], size_t nElem) {
	for (size_t i = 0; i < nElem; i++) {
		cout << i << ": ";
		while (!checkInput(a[i]));
	}
}

int findValueInArray(const int a[], size_t nElem, int value, size_t pos1 = 0, size_t pos2 = -1) {
	if (pos2 == -1) pos2 = nElem - 1;
	for (size_t i = pos1; i <= pos2 && i < nElem; i++) {
		if (a[i] == value) {
			return i;
		}
	}

	return -1;
}

int findValueInArray(const int a[], size_t nElem, int value, size_t index[], size_t pos1 = 0, size_t pos2 = NULL) {
	if (pos2 == NULL) pos2 = nElem - 1;
	size_t indexElement = 0;

	for (size_t i = pos1; i <= pos2 && i < nElem; i++) {
		if (a[i] == value) {
			index[indexElement] = i;
			indexElement++;
		}
	}

	return indexElement;
}

void testArrays() {
	int a[12];
	size_t index[12];
	readArray(a, 12);
	size_t indexSize = findValueInArray(a, 12, 4, index);

	for (size_t i = 0; i < indexSize; i++) {
		cout << index[i] << endl;
	}
}

// Exercise 2

void readVector(vector<int>& v, size_t nElem) {
	int  input;

	for (size_t i = 0; i < nElem; i++) {
		cout << i << ": ";
		while (!checkInput(input));

		v.push_back(input);
	}
}

size_t findValueInVector(const vector<int>& v, int value, size_t pos1, size_t pos2) {
	vector<int>::const_iterator it;

	for (it = v.begin() + pos1; it != v.end() && it != v.begin() + pos2; it++) {
		if (*it == value) return it - v.begin();
	}

	return -1;
}

size_t findValueInVector(const vector<int>& v, int value, vector<size_t> &index, size_t pos1 = 0, size_t pos2 = NULL) {
	vector<int>::const_iterator it;
	index.clear();
	if (pos2 == NULL) pos2 = v.end() - v.begin();

	for (it = v.begin() + pos1; it != v.end() && it != v.begin() + pos2; it++) {
		if (*it == value) {
			index.push_back(it - v.begin());
		}
	}

	return index.size();
}

void testVectors() {
	vector<int> vec;
	vector<size_t> index;
	vector<size_t>::iterator it;
	readVector(vec, 10);
	findValueInVector(vec, 4, index, 0, 9);

	for (it = index.begin(); it != index.end(); it++) {
		cout << *it << endl;
	}
}

// Exercise 3

void bubbleSort(vector<int>& v, char order) {
	vector<int>::iterator it;
	bool sorted = false;

	while (!sorted) {
		sorted = true;

		for (it = v.begin(); (it + 1) != v.end(); it++) {
			if((order == 'a' && *(it + 1) < *it) || (order == 'd' && *(it + 1) > *it)) {
				swap(*(it + 1), *it);
				
				sorted = false;
			}
		}
	}
}

void bubbleSort(vector<int>& v, bool f(int x, int y)) {
	vector<int>::iterator it;
	bool sorted = false;

	while (!sorted) {
		sorted = true;

		for (it = v.begin(); (it + 1) != v.end(); it++) {
			if (f(*it, *(it+1))) {
				swap(*(it + 1), *it);

				sorted = false;
			}
		}
	}
}

bool ascending(int x, int y) {
	return x > y;
}

bool descending(int x, int y) {
	return x < y;
}

void testSort() {
	vector<int> vec;
	readVector(vec, 10);

	bubbleSort(vec, descending);
	vector<int>::iterator intIt;

	for (intIt = vec.begin(); intIt != vec.end(); intIt++) {
		cout << *intIt << endl;
	}
}

// Exercise 4

int binarySearch(const vector<int>& v, int value) {
	vector<int>::const_iterator begin, end, mid;
	begin = v.begin();
	end = v.end();

	while (begin < end) {
		mid = begin + (end - begin) / 2;
		
		if (*mid == value) {
			return mid - v.begin();
		}
		else if (*mid > value) {
			end = mid;
		}
		else {
			begin = mid + 1;
		}
	}

	return -1;
}

void testSearch() {
	vector<int> vec;
	readVector(vec, 10);
	sort(vec.begin(), vec.end());

	cout << binarySearch(vec, -1);
}

// Exercise 5

void printVector(vector<int>& v) {
	vector<int>::iterator it2;

	for (it2 = v.begin(); it2 != v.end(); it2++) {
		cout << *it2 << endl;
	}
}

void printVector(vector<vector<int>>& v) {
	vector<vector<int>>::iterator it2;
	vector<int>::iterator it;

	for (it2 = v.begin(); it2 != v.end(); it2++) {
		for (it = (*it2).begin(); it != (*it2).end(); it++) {
			cout << *it << " ";
		}

		cout << endl;
	}
}


void removeDuplicates(vector<int>& v) {
	vector<int>::iterator it2;
	size_t it = 0;

	for (it = 0; it < v.size(); it++) {
		for (it2 = v.begin() + it + 1; it2 != v.end(); it2++) {
			if (v[it] == *it2) {
				it2 = v.erase(it2);
				it2--;
			}
		}
	}
}

void testDuplicates() {
	vector<int> vec;
	vector<int>::iterator intIt;
	readVector(vec, 10);
	removeDuplicates(vec);

	printVector(vec);
}

// Exercise 7

bool isLocalMax(size_t row, size_t column, const int a[][NE]) {
	for (size_t r = row - 1; r <= row + 1; r++) {
		for (size_t c = column - 1; c <= column + 1; c++) {
			if (a[r][c] > a[row][column]) return false;
		}
	}

	return true;
}

bool isLocalMax(size_t row, size_t column, const vector<vector<int>> a) {
	for (size_t r = row - 1; r <= row + 1; r++) {
		for (size_t c = column - 1; c <= column + 1; c++) {
			if (a[r][c] > a[row][column]) return false;
		}
	}

	return true;
}

void initializeMax(bool a[][NE]) {
	for (int row = 0; row < NE; row++) {
		for (int column = 0; column < NE; column++) {
			a[row][column] = false;
		}
	}
}

void setImpossibles(size_t row, size_t column, bool a[][NE]) {
	for (size_t r = row - 1; r <= row + 1; r++) {
		for (size_t c = column - 1; c <= column + 1; c++) {
			a[r][c] = true;
		}
	}
}

void setImpossibles(size_t row, size_t column, vector<vector<bool>>& a) {
	for (size_t r = row - 1; r <= row + 1; r++) {
		for (size_t c = column - 1; c <= column + 1; c++) {
			a[r][c] = true;
		}
	}
}

void localMax(const int a[][NE]) {
	bool impossibleMax[NE][NE];
	initializeMax(impossibleMax);

	for (int row = 1; row < NE - 1; row++) {
		for (int column = 1; column < NE - 1; column++) {
			if (!impossibleMax[row][column] && isLocalMax(row, column, a)) {
				cout << "Local Max in Row: " << row << " and Column: " << column << " with the value of: " << a[row][column] << endl;
				setImpossibles(row, column, impossibleMax);
			}
		}
	}
}

void localMax(const vector<vector<int>> aOrig, bool considerBorders = false) {
	vector<vector<int>> a = aOrig;

	if (considerBorders) {
		vector<vector<int>>::iterator it;
		int newSize = a.size() + 2;
		constexpr int minValue = numeric_limits<int>::min();

		for (it = a.begin(); it != a.end(); it++) {
			(*it).push_back(minValue);
			(*it).insert((*it).begin(), minValue);
		}

		a.push_back(vector<int>(newSize, minValue));
		a.insert(a.begin(), vector<int>(newSize, minValue));
	}
	
	vector<vector<bool>> impossibleMax(a.size(), vector<bool>(a.size(), false));

	for (int row = 1; row < a.size() - 1; row++) {
		for (int column = 1; column < a.size() - 1; column++) {
			if (!impossibleMax[row][column] && isLocalMax(row, column, a)) {
				cout << "Local Max in Row: " << row << " and Column: " << column << " with the value of: " << a[row][column] << endl;
				setImpossibles(row, column, impossibleMax);
			}
		}
	}
}

void testLocalMax() {
	int matrix[NE][NE] = {
		{7, 3, 4, 1, 3},
		{2, 9, 6, 2, 1},
		{1, 3, 5, 1, 4},
		{6, 5, 2, 7, 5},
		{4, 2, 1, 3, 6}
	};

	vector<vector<int>> vecMatrix{
		{7, 3, 4, 1, 3},
		{2, 9, 6, 2, 1},
		{1, 3, 5, 1, 4},
		{6, 5, 2, 7, 5},
		{4, 2, 1, 3, 6}
	};

	localMax(matrix);
	localMax(vecMatrix, true);
}

// Exercise 11


void testQSort() {
	vector<int> toSort { 1, 2, 1, 03, 30, 2, 12, 30, 412, 123, 4,2, 2, 1,7, 9, 19, 29, 39, 1, 3, 2, 1, 0 };

	qsort(&(toSort[0]), toSort.size(), sizeof(int), [](const void* a, const void* b) {
		int arg1 = *static_cast<const int*>(a);
		int arg2 = *static_cast<const int*>(b);

		if (arg1 < arg2) return -1;
		if (arg1 > arg2) return 1;
		return 0;
	});

	printVector(toSort);
}

int main()
{
	testQSort();

	return 0;
}
