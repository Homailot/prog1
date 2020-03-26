#include "gameIO.h"
#include "game.h"
#include "common.h"
#include "board.h"
#include <sstream>


typedef void (*MenuOption) ();
// for the nerds, request an end of file to end the game.

void playSingle() {
	startSingleGame();
}

void playMulti() {
	startMultiGame();
}

void rules() {
	
}

void exit() {
	printMessage("Thanks for playing!");
	waitForKey();
}

void menu() {
	std::stringstream ss;
	int input;

	MenuOption menuOptions[4] = {
		playSingle,
		playMulti,
		rules,
		exit
	};

	ss << stringWithColor("Welcome to 201908250's Oware!!", GREEN) << " (that's a mouthfull)";
	printMessage(ss.str());

	ss.str(std::string());
	ss << "1. " << stringWithColor("Play Single-Player", GREEN, BLACK);
	printMessage(ss.str());
	ss.str(std::string());
	ss << "2. " << stringWithColor("Play Multi-Player", GREEN, BLACK);
	printMessage(ss.str());
	ss.str(std::string());
	ss << "3. " << stringWithColor("Show Rules", GREEN, BLACK);
	printMessage(ss.str());
	ss.str(std::string());
	ss << "4. " << stringWithColor("Exit", GREEN, BLACK);
	printMessage(ss.str());

	printMessage("What do you want to do? ", "");
	while (!checkInput(input) || input < 1 || input > 4) {
		printMessage("That option does not exist.", RED, BLACK);
		printMessage("What do you want to do? ", "");
	}

	clearScreen();
	menuOptions[input - 1]();
}