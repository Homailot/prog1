#include "gameIO.h"
#include "game.h"
#include "common.h"
#include "board.h"
#include <sstream>


typedef void (*MenuOption) ();

void playSingle() {
	startSingleGame();
}

void playMulti() {
	startMultiGame();
}

void rules() {
	printMessage("############################################################################################################################################");
	printMessage("Oware is a turn based game.");
	printMessage("There are forty-eight seeds distributed in groups of four through two rows of six holes.");
	printMessage("There exist two larger holes on the sides of the board that are used to store the seeds that players capture during the game.");
	printMessage("#----------- GOAL -----------# ", GREEN, BLACK);
	printMessage("Each player make moves in turns to try to capture the maximum amout of seeds.");
	printMessage("The player that has more seeds when the game is over wins.");
	printMessage("If both players have the same amount of seeds, it's a draw.");
	printMessage("#----------- HOW TO PLAY -----------# ", GREEN, BLACK);
	printMessage(" 1. COLLECTING", BLACK, GREEN);
	printMessage("In the collection phase the player chooses one of his holes (the ones that belong to the row closest to him).");
	printMessage("After that, the player collects those seeds, leaving that hole empty.");
	printMessage("Furthermore, the player may only choose a hole that has one or more seeds, and has to make a move that allows the opponent to continue to play.");
	printMessage(" 2. SOWING", BLACK, GREEN);
	printMessage("In this phase, the player distributes the seeds collected along the board in a counterclockwise rotation, dropping one seed in each hole until all the seeds are used");
	printMessage("Because the hole that was chosen has to be left empty, if it happens that the player has enough seeds to do a full rotation around the board, ");
	printMessage("the player never drops a seed in the hole from which the seeds where collected.");
	printMessage(" 3. CAPTURING", BLACK, GREEN);
	printMessage("After the last seed collected was dropped in one of the opponent's holes, if the hole has exactly two or three seeds, the player will capture them.");
	printMessage("To capture is to take all the seeds from that hole, and adding them to the player's storage.");
	printMessage("If the hole immediately to the right of the last hole captured also contains only two or three seeds, the player captures them too.");
	printMessage("This is repeated until the player can't capture any more seeds.");
	printMessage("The player can not capture seeds from one of their own holes.");
	printMessage("The player can not capture all the seeds from the opponent's row.");
	printMessage("If the player makes a move that would capture all the seeds, they will sow normally, but won't capture any seeds");
	printMessage("#----------- HOW TO END THE GAME -----------# ", GREEN, BLACK);
	printMessage("When one player captures more than 24 seeds, or both players have 24 seeds, the game ends.");
	printMessage("If the player can not make any legal moves (can't allow the other player to continue), the game ends and each player collect the seeds on their row.");
	printMessage("Sometimes the game enters a cycle, in that case the players may agree to end the game and each player capture the seeds on their side.");
	printMessage("To declare a cycle or ask to end the game, write the letter 's' in the input field and the deal will start.");
	printMessage("For the nerds, you can also input an end of file character into the input field to do the same thing.");
	printMessage("");
	printMessage("From http://www.joansala.com/auale/rules/en/");
	waitForKey();
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

	while (true) {
		clearScreen();
		ss.str(std::string());
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
		if (input == 4) break;
	}
}