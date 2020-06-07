#include<iostream>
#include<string>
using namespace std; 
class Animal{ 
public:
	Animal(const string & name) : name(name) {}
	virtual string talk() = 0;
	const string name;//public attribute!!!HOW TO MAKE IT PRIVATE?
};

class Cat : public Animal{
public:
	Cat(const string& name) : Animal(name){}
	string talk() { return"Meow!"; }
};

class Dog : public Animal{
public:
	Dog(const string& name) : Animal(name){}
	string talk() { return"Arf! Arf!"; }
};

int main(){
	Animal* animals[] =//NOTE the initialization
	{
		new Cat("Mr. Jinks"),
		new Cat("Garfield"),
		new Dog("Milou")
	}; 
	for(int i = 0; i < 3; i++){
		cout << animals[i]->name<< ": "<< animals[i]->talk() << endl;
		delete animals[i];
	}

	try {

	}
	catch (...) {

	}
	return 0;
}