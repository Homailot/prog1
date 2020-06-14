#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <ios>
#include <algorithm>
#include<strstream>
#include <exception>
#include <fstream>

// Exercise 4

class Client {
public:
	Client() {
		this->address = ""; this->name = "";
	}
	Client(std::string name, std::string address) {
		this->name = name; this->address = address;
	};
	std::string getName() {
		return name;
	}
	std::string getAddress() { return address; }
private:
	std::string name, address;
};

class Product {
public:
	Product(std::string name, double price) {
		this->name = name; this->price = price;
	}
	Product() {
		this->name = ""; this->price = 0;
	}
	long double getPrice() { return price; };
	std::string getName() { return name; };
private:
	long double price;
	std::string name;
};

class Item {
public:
	Item(Product product, int quantity) {
		this->product = product;
		this->quantity = quantity;
	};
	long double getTotal() {
		return quantity * product.getPrice();
	};
	int getQuantity() {
		return quantity;
	}
	Product getProduct() {
		return product;
	}
private:
	long double total;
	int quantity;
	Product product;
};

class Invoice {
public:
	Invoice() {
		client = Client("", "");
	}
	Invoice(Client client, std::vector<Item> items) {
		this->client = client;
		this->items = items;
	}
	void printItems() {
		std::cout.imbue(std::locale("en_US.UTF-8"));
		std::cout << client.getName() << std::endl << client.getAddress() << std::endl << std::endl;

		int tableColumns = 4;
		int *tableSizes = new int[tableColumns] { 20, 7, 5, 8 };
		std::string *tableHeaders = new std::string[tableColumns] { "Description", "Price", "Qty", "Total" };

		for (int idx = 0; idx < tableColumns; idx++) {
			std::cout << std::setw(tableSizes[idx]) << std::left << tableHeaders[idx] << " ";
		}
		std::cout << std::endl;
		for (int idx = 0; idx < tableColumns; idx++) {
			std::cout << std::string(tableSizes[idx], '-') << " ";
		}
		std::cout << std::endl;
		for (auto it = items.begin(); it != items.end(); it++) {
			std::cout << std::left << std::setw(tableSizes[0]) << (*it).getProduct().getName() << " ";
			std::cout << std::setw(tableSizes[1]) << std::right << std::put_money(it->getProduct().getPrice()) << " ";
			std::cout << std::setw(tableSizes[2]) << std::right << it->getQuantity() << " ";
			std::cout << std::setw(tableSizes[3]) << std::right << std::put_money(it->getTotal());

			std::cout << std::endl;
		}

		delete[] tableSizes;
		delete[] tableHeaders;
	}
private:
	Client client;
	std::vector<Item> items;
};

void testInvoices() {
	Client client("DEI- FEUP", "Rua Dr. Roberto Frias, s/n\n4200-465 Porto");
	Product computer("Computer", 99990);
	Product printer("Printer", 14990);
	Item computers(computer, 10);
	Item printers(printer, 1);
	std::vector<Item> items = { computers, printers };
	Invoice invoice(client, items);

	invoice.printItems();
}

// Exercise 7

template <typename T>
T getMax(std::vector<T> values) {
	return *(std::max_element(values.begin(), values.end()));
}

// Exercise 8

template <typename T>
class Vector {
public:
	Vector();
	Vector(unsigned int size);
	Vector(unsigned int size, const T& initial);
	Vector(const Vector<T>& v);
	~Vector();
	size_t size() const;
	bool empty() const;
	T& front();
	T& back();
	T& at(size_t index);
	void push_back(const T& value);
	void pop_back();
	void clear();
private:
	T* buffer;
	size_t bufferSize;
	size_t last;
};

template <typename T>
Vector<T>::Vector() {
	bufferSize = 0;
	buffer = NULL;
	last = 0;
}

template <typename T>
Vector<T>::Vector(unsigned int size) {
	bufferSize = size;
	buffer = static_cast<T*>(malloc(size * sizeof(T)));
	last = 0;
}

template <typename T>
Vector<T>::Vector(unsigned int size, const T& initial) {
	bufferSize = size;
	buffer = static_cast<T*>(malloc(size * sizeof(T)));

	if (buffer) { // Making sure malloc worked
		for (size_t idx = 0; idx < size; idx++) {
			buffer[idx] = initial;
		}
	}
	else {
		throw std::bad_alloc();
	}
	last = bufferSize;
}

template <typename T>
Vector<T>::Vector(const Vector<T>& v) {
	bufferSize = v.bufferSize;
	buffer = static_cast<T*>(malloc(bufferSize * sizeof(T)));

	if (buffer) {
		for (size_t idx = 0; idx < bufferSize; idx++) {
			buffer[idx] = v.buffer[idx];
		}
	}
	else {
		throw std::bad_alloc();
	}
	last = bufferSize;
}

template <typename T>
Vector<T>::~Vector() {
	free(buffer);
}

template <typename T>
size_t Vector<T>::size() const {
	return bufferSize;
}

template <typename T>
bool Vector<T>::empty() const {
	return bufferSize == 0;
}

template <typename T>
T& Vector<T>::front() {
	return buffer[0];
}

template <typename T>
T& Vector<T>::back() {
	return buffer[bufferSize - 1];
}

template <typename T>
T& Vector<T>::at(size_t index) {
	if (index < 0 || index >= bufferSize) throw std::out_of_range("ERROR: Index is out of bounds.");
	return buffer[index];
}

template <typename T>
void Vector<T>::push_back(const T& value) {
	if (last >= bufferSize) {
		T* bufferCopy = static_cast<T*> (realloc(buffer, (bufferSize + 1) * sizeof(T)));

		if (bufferCopy) {
			buffer = bufferCopy;
			bufferSize++;
		}
		else {
			throw std::bad_alloc();
		}
	}

	buffer[last] = value;
	last++;
}

template <typename T>
void Vector<T>::pop_back() {
	T* bufferCopy = static_cast<T*>(realloc(buffer, (bufferSize - 1) * sizeof(T)));

	if (bufferCopy) {
		buffer = bufferCopy;
		bufferSize--;
	}
	else {
		throw std::bad_alloc();
	}

	last--;
}

template <typename T>
void Vector<T>::clear() {
	buffer = NULL;
	bufferSize = 0;
	last = 0;
}

void testVector() {
	Vector<int> test(4, 0);
	test.front() = 2;
	std::cout << test.front() << std::endl;
	std::cout << test.back() << " at " << test.size() << std::endl;
	test.push_back(3);
	std::cout << test.at(4) <<  " at " << test.size() << std::endl;
	test.push_back(2);
	std::cout << test.at(3) << std::endl;
	std::cout << test.at(5) << std::endl;
	test.pop_back();
	std::cout << test.size() << " : size, " << std::endl;
	std::cout << test.at(4) << std::endl;
	test.push_back(6);
	std::cout << test.at(5) << std::endl;
	test.clear();
	test.push_back(1);
	std::cout << test.at(0) << " with size " << test.size();
}

void test(int th, int tm, int ts) {
	int h = 2, m = 4, s = 3;
	int remaining = (s + ts) / 60;
	s = (s + ts) % 60;
	remaining = m + tm + remaining;
	m = remaining % 60; remaining /= 60;
	h = h + th + remaining;
	std::cout << h << ':' << m << ':' << s << std::endl;
}

int main()
{
	std::string a = "1234";
	std::string b = a;
	b.at(0) = 'a';

	test(1, 60, 60);

	std::cout << a << b;

	std::vector<std::vector<int>> board(10, std::vector<int>(15, -1));

	int line = 2, col = 3;
	bool horizontal = false;
	int* incrementer = horizontal? &col : &line;
	size_t size = 3;

	while (size > 0) {
		board[line][col] = 3;

		size--;
		*incrementer += 1;
	}

	for (auto it : board) {
		for (auto it2 : it) {
			std::cout << it2 << " ";
		}
		std::cout << std::endl;
	}

	std::cout << std::setfill('0') << std::setw(2) << 2 << ':' << 3;
}
