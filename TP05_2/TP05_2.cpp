#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <fstream>
#include <algorithm>

int trueMod(int n, int divisor) {
	int result = n % divisor;
	
	if (result < 0) {
		return result + divisor;
	}

	return result;
}


// Exercise 5.1
bool isUpper(char c) {
	return c <= 'Z' && c >= 'A';
}

bool isLower(char c) {
	return c <= 'z' && c >= 'a';
}

bool isAlpha(char c) {
	return isLower(c) || isUpper(c);
}

char encryptChar(char c, int key) {
	if (!isAlpha(c)) return c;

	bool lower = isLower(c);
	unsigned short int cCopy = lower ? c - 'a' : c - 'A';

	cCopy = trueMod(cCopy + key, 26);

	return static_cast<char>(lower ? cCopy + 'a' : cCopy + 'A');
}

std::string encryptString(std::string s, int key) {
	std::string sCopy = s;

	for (std::string::iterator it = sCopy.begin(); it != sCopy.end(); it++) {
		*it = encryptChar(*it, key);
	}

	return sCopy;
}

// Exercise 5.4
bool sequenceSearch_1(const std::string& s, int nc, char c) {
	int sum = 0;

	for (std::string::const_iterator it = s.begin(); it != s.end(); it++) {
		if (*it == c) {
			sum++;

			if (sum == nc) return true;
		}
		else {
			sum = 0;
		}
	}

	return false;
}

bool sequenceSearch_2(const std::string& s, int nc, char c) {
	std::string match(nc, c);
	size_t idx = s.find(match);

	return idx != std::string::npos;
}

// Exercise 5.5
std::string truncateString(std::string str) {
	size_t firstLetter = str.find_first_not_of(' ');
	str.replace(0, firstLetter, "");

	size_t lastLetter = str.find_last_not_of(' ');
	str.replace(lastLetter + 1, str.size() - lastLetter, "");

	return str;
}

std::string removeSpaces(std::string str) {
	size_t position;

	while ((position = str.find("  ")) != std::string::npos) {
		str.replace(position, 2, " ");
	}

	// or a faster more manual way
	/*int sum = 0;

	for (std::string::iterator it = str.begin(); it != str.end(); it++) {
		if (*it == ' ') {
			sum++;

			if (sum > 1) {
				str.replace(it, it + 1, "");
				it--;
			}
		}
		else sum = 0;
	}*/

	return str;
}

std::string toUppercase(std::string str) {
	for (std::string::iterator it = str.begin(); it != str.end(); it++) {
		*it = toupper(*it);
	}

	return str;
}

std::string removeParticles(std::string str) {
	std::vector<std::string> particles = { " DE ", " DO ", " DA ", " DOS ", " DAS ", " E " };
	size_t position;

	for (std::vector<std::string>::iterator it = particles.begin(); it != particles.end(); it++) {
		while ((position = str.find(*it)) != std::string::npos) {
			str.replace(position, it->size(), " ");
		}
	}

	return str;
}

std::string normalizeString(const std::string& name) {
	std::string nameCopy = truncateString(name);
	nameCopy = removeSpaces(nameCopy);
	nameCopy = toUppercase(nameCopy);
	nameCopy = removeParticles(nameCopy);

	return nameCopy;
}

// Exercicio 5.7
typedef struct {
	unsigned int year, month, day;
} Date;

void readDate(Date* d) {
	char sep;

	std::cout << "Date? YYYY/MM/DD: ";
	std::cin >> d->year >> sep >> d->month >> sep >> d->day;
}

void writeDate(const Date* d) {
	std::cout << d->year << "/" << d->month << "/" << d->day << std::endl;
}

int compareDates(const Date* d1, const Date* d2) {
	if (d1->year < d2->year || d1->year == d2->year && d1->month < d2->month || d1->year == d2->year && d1->month == d2->month && d1->day < d2->day) {
		return -1;
	}
	else if (d1->year == d2->year && d1->month == d2->month && d1->day == d2->day) {
		return 0;
	}

	return 1;
}

void sortDates(Date* d1, Date* d2) {
	if (compareDates(d1, d2) == 1) {
		std::swap(*d1, *d2);
	}
}

// Exercise 8
struct EuroMillionsBet {
	std::vector<unsigned> mainNumbers;
	std::vector<unsigned> luckyStars;
};

void readBet(EuroMillionsBet& emb) {
	for (int i = 0; i < 5; i++) {
		int number;

		do {
			std::cout << "Choose a number between 1 to 50" << std::endl;
			std::cin >> number;
		} while (number < 1 || number > 50);
		
		std::cout << "Success!" << std::endl;
		emb.mainNumbers.push_back(number);
	}
}

// Exercise 10

typedef struct {
	int x, y;
} Point;

typedef struct {
	std::vector<Point> points;
} Polygon;

void readPolygon(Polygon& p) {
	Point point;

	std::cout << "Please input the polygon's points (three minimum) either clockwise or counter-clockwise" << std::endl;
	std::cout << "Input a point: (format x y); CTRL+Z to stop. " << std::endl;
	std::cin >> point.x >> point.y;

	while (p.points.size() < 3 || !std::cin.eof()) {
		if (std::cin.eof()) {
			std::cin.clear();

			std::cout << "Less than 3 points were input" << std::endl;
		}
		else {
			p.points.push_back(point);
		}

		std::cout << "Input a point: (format x y); CTRL+Z to stop. " << std::endl;
		std::cin >> point.x >> point.y;
	}
}

void showPolygon(const Polygon& p) {
	for (auto it = p.points.begin(); it != p.points.end(); it++) {
		std::cout << it->x << " " << it->y << std::endl;
	}
}

double getPolygonArea(const Polygon& p) {
	int sum = 0;

	for (auto it = p.points.begin(); it + 1 != p.points.end(); it++) {
		sum += (it->x * (it + 1)->y - it->y * (it + 1)->x);
	}
	sum += (p.points.end() - 1)->x * p.points.begin()->y - (p.points.end() - 1)->y * p.points.begin()->x;

	double result = static_cast<double>(sum) / 2;

	return abs(result);
}

// Exercise 11.b

std::vector<std::string> readPersonsFile(std::string name) {
	std::vector<std::string> persons;
	std::string str;
	std::stringstream ss;
	ss << name << ".txt";
	std::fstream file(ss.str(), std::ios::in);

	if (!file.is_open()) {
		std::cout << "Not Found";
		exit(1);
	}

	while (std::getline(file, str)) {
		persons.push_back(str);
	}

	return persons;
}

void writePersons(std::string name, const std::vector<std::string> persons) {
	std::stringstream ss;
	ss << name << ".txt";
	std::fstream file(ss.str(), std::ios::out | std::ios::trunc);

	for (auto it = persons.begin(); it != persons.end(); it++) {
		file << *it << std::endl;
	}
}

void testPersons() {
	std::string name;
	std::stringstream ss;
	std::cout << "input the name of the file (without .txt): ";
	std::cin >> name;

	std::vector<std::string> persons = readPersonsFile(name);
	std::sort(persons.begin(), persons.end());
	ss << name << "_sorted";
	writePersons(ss.str(), persons);
}

// Exercise 12


int main()
{
	testPersons();
}