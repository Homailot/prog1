#include "game.h"
#include "common.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <map>


const std::vector<std::pair<int, int>> oneSeed{
	std::make_pair(7, 3)
};
const std::vector<std::pair<int, int>> twoSeed{
	std::make_pair(4, 3), std::make_pair(10, 3)
};
const std::vector<std::pair<int, int>> threeSeed{
	std::make_pair(4, 4), std::make_pair(10, 4), std::make_pair(7, 2)
};
const std::vector<std::pair<int, int>> fourSeed{
	std::make_pair(4, 4), std::make_pair(10, 4), std::make_pair(4, 2), std::make_pair(10, 2)
};
const std::vector<std::pair<int, int>> fiveSeed{
	std::make_pair(4, 1), std::make_pair(10, 1), std::make_pair(4, 5), std::make_pair(10, 5),
	std::make_pair(7, 3)
};
const std::vector<std::pair<int, int>> sixSeed{
	std::make_pair(4, 5), std::make_pair(10, 5), std::make_pair(4, 3), std::make_pair(10, 3),
	std::make_pair(4, 1), std::make_pair(10, 1)
};
const std::vector<std::pair<int, int>> sevenSeed{
	std::make_pair(3, 5), std::make_pair(11, 5), std::make_pair(3, 3), std::make_pair(11, 3),
	std::make_pair(3, 1), std::make_pair(11, 1), std::make_pair(7, 3)
};
const std::vector<std::pair<int, int>> eightSeed{
	std::make_pair(3, 5), std::make_pair(11, 5), std::make_pair(3, 3), std::make_pair(11, 3),
	std::make_pair(3, 1), std::make_pair(11, 1), std::make_pair(7, 1), std::make_pair(7, 5)
};
const std::vector<std::pair<int, int>> nineSeed{
	std::make_pair(3, 5), std::make_pair(11, 5), std::make_pair(3, 3), std::make_pair(11, 3),
	std::make_pair(3, 1), std::make_pair(11, 1), std::make_pair(7, 1), std::make_pair(7, 5),
	std::make_pair(7, 3)
};

const std::vector<std::pair<int, int>> graphicsArray[9] = { oneSeed, twoSeed, threeSeed, fourSeed, fiveSeed, sixSeed, sevenSeed, eightSeed, nineSeed };

std::vector<std::string> getStorageVector(int numOfSeeds) {
	std::vector<std::string> storage{
		"+-------------+",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"+-------------+"
	};

	storage[6][7] = (char)(numOfSeeds / 10) + '0';
	storage[7][7] = (char)(numOfSeeds % 10) + '0';

	return storage;
}

std::vector<std::string> getHouseVector(int numOfSeeds) {
	int x, y;
	std::vector<std::pair<int, int>>::iterator it;
	std::vector<std::string> box{
		"+-------------+",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"|             |",
		"+-------------+"
	};

	if (numOfSeeds == 0) return box;

	std::vector<std::pair<int, int>> seedPlacement;
	if (numOfSeeds >= 10) {
		seedPlacement = eightSeed;

		box[3][6] = (char)(numOfSeeds / 10) + '0';
		box[3][8] = (char)(numOfSeeds % 10) + '0';
	}
	else {
		seedPlacement = graphicsArray[numOfSeeds - 1];
	}

	for (it = seedPlacement.begin(); it != seedPlacement.end(); it++) {
		x = (*it).first;
		y = (*it).second;

		box[y][x] = 'O';
	}

	return box;
}

// Don't look this is a mess
void drawBoard(int player, Board gameBoard) {
	std::stringstream ss;
	std::vector<std::string>::iterator it;
	std::vector<std::string> output(16, std::string(127, ' '));
	int playerCopy = player;

	for (int i = 0; i < 2; i++, playerCopy = trueMod(playerCopy + 1, 2)) {
		// Put the names in the output vector
		ss.str(std::string());
		if (i == 0) {
			ss << std::setw(13) << std::right << gameBoard.playerNames[playerCopy];
		}
		else {
			ss << std::setw(13) << std::left << gameBoard.playerNames[playerCopy];
		}

		output[(1 - i) * 15].replace((1 - i) * (112) + 1, 13, ss.str());

		// Puts the storage holes in the ouput vector
		std::vector<std::string> storage = getStorageVector(gameBoard.storage[playerCopy]);

		for (it = storage.begin(); it != storage.end(); it++) {
			output[it - storage.begin() + 1].replace((1-i)*(112), (*it).length(), *it);
		}


		// Puts the holes in the output vector
		for (int hole = 0; hole < 6; hole++) {
			std::vector<std::string> house = getHouseVector(gameBoard.holes[playerCopy][hole]);

			if (i == 0) {
				for (it = house.begin(); it != house.end(); it++) {
					output[8 + (it - house.begin())].replace(16 + 16 * hole, 15, (*it));
				}
				
				// 23 = 16 + 7
				output[15][23 + (hole * 16)] = hole + 'A';
			}
			else {
				for (it = house.begin(); it != house.end(); it++) {
					output[1 + (it - house.begin())].replace(96 - 16 * hole, 15, (*it));
				}

				// 103 = 96 + 7
				output[0][103 - (hole * 16)] = hole + 'a';
			}
		}
	}

	for (it = output.begin(); it != output.end(); it++) {
		std::cout << (*it) << std::endl;
	}
}

// Player2	             a               b              ...
//+-------------+ +-------------+ +-------------+    
//|				| |             | |             | 
//|				| |             | |             |
//|				| |      O      | |      O      |       ...
//|				| |             | |             |
//|				| |             | |             | 
//|		 0  	| +-------------+ +-------------+
//|	     9		| +-------------+    
//|				| |             | 
//|				| |             |
//|				| |   O     O   |
//|				| |             |
//|				| |             |  
//+-------------+ +-------------+
//                       A               B                 Player1
//+-------------+    
//|             |  
//|      O      |
//|             |
//|   O     O   |
//|             |  
//+-------------+
//+-------------+    
//|             |  
//|   O     O   |
//|             |
//|   O     O   |
//|             |  
//+-------------+
//+-------------+    
//|   O     O   |  
//|             |
//|      O      |
//|             |
//|   O     O   |  
//+-------------+
//+-------------+    
//|   O     O   |  
//|             |
//|   O     O   |
//|             |
//|   O     O   |  
//+-------------+
//+-------------+    
//|  O       O  |  
//|             |
//|  O   O   O  |
//|             |
//|  O       O  |  
//+-------------+
//+-------------+    
//|  O   O   O  |  
//|             |
//|  O       O  |
//|             |
//|  O   O   O  |  
//+-------------+
//+-------------+    
//|  O   O   O  |  
//|             |
//|  O   O   O  |
//|             |
//|  O   O   O  |  
//+-------------+
//+-------------+    
//|  O   O   O  | 
//|             |
//|  O  1 2  O  |
//|             |
//|  O   O   O  |  
//+-------------+
